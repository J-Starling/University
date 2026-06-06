import sys
import math
from PySide6.QtWidgets import (
    QApplication, QMainWindow, QWidget, QVBoxLayout, QHBoxLayout,
    QSlider, QLabel, QPushButton, QDoubleSpinBox, QSpinBox, QGroupBox
)
from PySide6.QtCore import Qt, QTimer
from PySide6.QtGui import QPainter, QPainterPath, QPen, QColor, QBrush
from PySide6.QtCharts import QChart, QChartView, QLineSeries


class SpringPendulumWidget(QWidget):
    """Виджет для отрисовки пружинного маятника с интерполяцией пружины"""

    def __init__(self, parent=None):
        super().__init__(parent)
        self.setMinimumSize(500, 400)
        self.setStyleSheet("background-color: white;")
        self.pivot_x = 250      # X точки подвеса
        self.pivot_y = 50       # Y точки подвеса
        self.mass_y = 400       # Y груза (начальное положение)
        self.rest_length = 350  # Длина пружины в покое (пикселей)
        self.spring_width = 50  # Ширина пружины (амплитуда витков)
        self.num_coils = 12     # Количество витков
        self.mass = 1.0         # кг
        self.stiffness = 10.0   # Н/м
        self.x = 0.0            # смещение от положения равновесия (м)
        self.v = 0.0            # скорость (м/с)
        self.px_per_meter = 50.0

    def set_physical_state(self, x, v):
        """Установка физического состояния"""
        self.x = x
        self.v = v

    def get_mass_y_pixels(self):
        """Возвращает Y координату груза в пикселях"""
        # Положение равновесия: pivot_y + rest_length
        equilibrium_y = self.pivot_y + self.rest_length
        # Смещение в пикселях
        displacement_px = self.x * self.px_per_meter
        return equilibrium_y + displacement_px

    def paintEvent(self, event):
        """Отрисовка сцены"""
        painter = QPainter(self)
        painter.setRenderHint(QPainter.Antialiasing)

        # 1. Рисуем опору (неподвижный прямоугольник)
        painter.setBrush(QBrush(QColor(100, 100, 100)))
        painter.drawRect(self.pivot_x - 50, self.pivot_y - 10, 100, 15)

        # 2. Рисуем пружину с интерполяцией
        self.draw_spring_interpolated(painter)

        # 3. Рисуем груз
        mass_y = self.get_mass_y_pixels()
        painter.setBrush(QBrush(QColor(70, 130, 200)))
        painter.setPen(QPen(Qt.black, 2))
        painter.drawRect(self.pivot_x - 20, mass_y - 15, 40, 30)

        # 4. Подпись текущего смещения
        painter.setPen(QPen(Qt.white))
        painter.drawText(10, 20, f"Смещение: {self.x:.2f} м")

    def draw_spring_interpolated(self, painter):
        """
        Рисует пружину через интерполяцию.
        Генерируются опорные точки, затем строится гладкий QPainterPath.
        """
        mass_y = self.get_mass_y_pixels()

        # Длина пружины в пикселях
        spring_length_px = mass_y - self.pivot_y
        if spring_length_px <= 0:
            return

        # Генерация опорных точек (каркас пружины)
        num_points = self.num_coils * 8  # 8 точек на виток для гладкости
        points = []

        for i in range(num_points + 1):
            t = i / num_points  # 0..1
            # Y: линейная интерполяция
            y = self.pivot_y + t * spring_length_px
            # X: синусоида для имитации витков
            angle = 2 * math.pi * self.num_coils * t
            # Амплитуда может слегка уменьшаться к краям (опционально)
            amplitude = self.spring_width * (1 - 0.2 * abs(2*t - 1))
            x = self.pivot_x + amplitude * math.sin(angle)
            points.append((x, y))

        # Построение гладкого пути через кубическую сплайн-интерполяцию
        path = QPainterPath()
        if len(points) < 2:
            return

        # Начинаем с первой точки
        path.moveTo(points[0][0], points[0][1])

        # Для каждой тройки точек строим кубическую кривую (Catmull-Rom)
        # Это даёт гладкую кривую, проходящую через все опорные точки
        for i in range(len(points) - 1):
            p0 = points[i]
            p1 = points[i + 1]

            if i == 0:
                path.lineTo(p1[0], p1[1])
            else:
                p_prev = points[i - 1]
                p_curr = p0
                p_next = p1
                p_next2 = points[i + 1] if i + 1 < len(points) else p1

                # Касательные
                tension = 0.5
                cp1_x = p_curr[0] + (p_next[0] - p_prev[0]) * tension / 3
                cp1_y = p_curr[1] + (p_next[1] - p_prev[1]) * tension / 3
                cp2_x = p_next[0] - (p_next2[0] - p_curr[0]) * tension / 3
                cp2_y = p_next[1] - (p_next2[1] - p_curr[1]) * tension / 3

                path.cubicTo(cp1_x, cp1_y, cp2_x, cp2_y, p_next[0], p_next[1])

        # Рисуем пружину
        pen = QPen(QColor(50, 50, 150), 3)
        painter.setPen(pen)
        painter.setBrush(Qt.NoBrush)
        painter.drawPath(path)


class MainWindow(QMainWindow):
    """Главное окно приложения"""

    def __init__(self):
        super().__init__()
        self.setWindowTitle("Моделирование пружинного маятника")
        self.setGeometry(100, 100, 1000, 600)

        # Физическое состояние
        self.x = 0.10          # начальное смещение 10 см
        self.v = 0.0
        self.time = 0.0

        # Параметры
        self.mass = 1.0        # кг
        self.stiffness = 10.0  # Н/м

        # Таймер анимации
        self.timer = QTimer()
        self.timer.timeout.connect(self.update_simulation)
        self.dt = 0.02  # шаг по времени
        self.is_running = True
        self.timer.start(int(self.dt * 1000))

        # Создание интерфейса
        self.setup_ui()

    def setup_ui(self):
        """Создание всех элементов GUI"""
        central_widget = QWidget()
        self.setCentralWidget(central_widget)

        main_layout = QHBoxLayout(central_widget)

        # Левая часть: виджет отрисовки
        self.spring_widget = SpringPendulumWidget()
        main_layout.addWidget(self.spring_widget, 2)

        # Правая часть: панель управления
        control_panel = QWidget()
        control_layout = QVBoxLayout(control_panel)
        control_layout.setAlignment(Qt.AlignTop)

        # Группа параметров системы
        params_group = QGroupBox("Параметры системы")
        params_layout = QVBoxLayout()

        # Ползунок массы
        mass_layout = QHBoxLayout()
        mass_layout.addWidget(QLabel("Масса (кг):"))
        self.mass_spin = QDoubleSpinBox()
        self.mass_spin.setRange(0.1, 5.0)
        self.mass_spin.setSingleStep(0.1)
        self.mass_spin.setValue(self.mass)
        self.mass_spin.valueChanged.connect(self.on_mass_changed)
        mass_layout.addWidget(self.mass_spin)

        self.mass_slider = QSlider(Qt.Horizontal)
        self.mass_slider.setRange(1, 50)
        self.mass_slider.setValue(int(self.mass * 10))
        self.mass_slider.valueChanged.connect(self.on_mass_slider)
        mass_layout.addWidget(self.mass_slider)
        params_layout.addLayout(mass_layout)

        # Ползунок жесткости
        stiffness_layout = QHBoxLayout()
        stiffness_layout.addWidget(QLabel("Жёсткость (Н/м):"))
        self.stiffness_spin = QDoubleSpinBox()
        self.stiffness_spin.setRange(1.0, 50.0)
        self.stiffness_spin.setSingleStep(1.0)
        self.stiffness_spin.setValue(self.stiffness)
        self.stiffness_spin.valueChanged.connect(self.on_stiffness_changed)
        stiffness_layout.addWidget(self.stiffness_spin)

        self.stiffness_slider = QSlider(Qt.Horizontal)
        self.stiffness_slider.setRange(10, 500)
        self.stiffness_slider.setValue(int(self.stiffness * 10))
        self.stiffness_slider.valueChanged.connect(self.on_stiffness_slider)
        stiffness_layout.addWidget(self.stiffness_slider)
        params_layout.addLayout(stiffness_layout)

        # Ползунок количества витков
        coils_layout = QHBoxLayout()
        coils_layout.addWidget(QLabel("Витков:"))
        self.coils_spin = QSpinBox()
        self.coils_spin.setRange(3, 30)
        self.coils_spin.setValue(self.spring_widget.num_coils)
        self.coils_spin.valueChanged.connect(self.on_coils_changed)
        coils_layout.addWidget(self.coils_spin)

        self.coils_slider = QSlider(Qt.Horizontal)
        self.coils_slider.setRange(3, 30)
        self.coils_slider.setValue(self.spring_widget.num_coils)
        self.coils_slider.valueChanged.connect(self.on_coils_slider)
        coils_layout.addWidget(self.coils_slider)
        params_layout.addLayout(coils_layout)

        params_group.setLayout(params_layout)
        control_layout.addWidget(params_group)

        # Группа управления моделированием
        control_group = QGroupBox("Управление")
        control_btn_layout = QHBoxLayout()

        self.start_btn = QPushButton("Старт")
        self.start_btn.clicked.connect(self.on_start)
        control_btn_layout.addWidget(self.start_btn)

        self.pause_btn = QPushButton("Пауза")
        self.pause_btn.clicked.connect(self.on_pause)
        control_btn_layout.addWidget(self.pause_btn)

        self.reset_btn = QPushButton("Сброс")
        self.reset_btn.clicked.connect(self.on_reset)
        control_btn_layout.addWidget(self.reset_btn)

        control_group.setLayout(control_btn_layout)
        control_layout.addWidget(control_group)

        # Группа графиков
        chart_group = QGroupBox("График координаты x(t)")
        chart_layout = QVBoxLayout()

        self.chart = QChart()
        self.chart.setTitle("Зависимость смещения от времени")
        self.chart.setAnimationOptions(QChart.SeriesAnimations)

        self.series = QLineSeries()
        self.series.setName("x(t)")
        self.chart.addSeries(self.series)

        self.chart.createDefaultAxes()
        self.chart.axes()[0].setTitleText("Время (с)")
        self.chart.axes()[1].setTitleText("Смещение (м)")
        self.chart.axes()[1].setRange(-0.75, 0.75)

        self.chart_view = QChartView(self.chart)
        self.chart_view.setRenderHint(QPainter.Antialiasing)
        chart_layout.addWidget(self.chart_view)

        chart_group.setLayout(chart_layout)
        control_layout.addWidget(chart_group)

        # Информационная строка
        self.info_label = QLabel("Состояние: Работа")
        control_layout.addWidget(self.info_label)

        main_layout.addWidget(control_panel, 1)

        # Запускаем сбор данных для графика
        self.time_data = []
        self.x_data = []

    def on_mass_slider(self, value):
        self.mass = value / 10.0
        self.mass_spin.blockSignals(True)
        self.mass_spin.setValue(self.mass)
        self.mass_spin.blockSignals(False)

    def on_mass_changed(self, value):
        self.mass = value
        self.mass_slider.blockSignals(True)
        self.mass_slider.setValue(int(value * 10))
        self.mass_slider.blockSignals(False)

    def on_stiffness_slider(self, value):
        self.stiffness = value / 10.0
        self.stiffness_spin.blockSignals(True)
        self.stiffness_spin.setValue(self.stiffness)
        self.stiffness_spin.blockSignals(False)

    def on_stiffness_changed(self, value):
        self.stiffness = value
        self.stiffness_slider.blockSignals(True)
        self.stiffness_slider.setValue(int(value * 10))
        self.stiffness_slider.blockSignals(False)

    def on_coils_slider(self, value):
        self.spring_widget.num_coils = value
        self.coils_spin.blockSignals(True)
        self.coils_spin.setValue(value)
        self.coils_spin.blockSignals(False)

    def on_coils_changed(self, value):
        self.spring_widget.num_coils = value
        self.coils_slider.blockSignals(True)
        self.coils_slider.setValue(value)
        self.coils_slider.blockSignals(False)

    def on_start(self):
        self.is_running = True
        self.info_label.setText("Состояние: Работа")

    def on_pause(self):
        self.is_running = False
        self.info_label.setText("Состояние: Пауза")

    def on_reset(self):
        self.is_running = False
        self.x = 0.10
        self.v = 0.0
        self.time = 0.0
        self.series.clear()
        self.time_data.clear()
        self.x_data.clear()
        self.series.append(0.0, self.x)
        self.chart.axes()[0].setMax(5)
        self.info_label.setText("Состояние: Сброс")

    def update_simulation(self):
        """Обновление физики и анимации"""
        if not self.is_running:
            return

        # Численное интегрирование (метод Эйлера)
        # a = - (k/m) * x
        acceleration = - (self.stiffness / self.mass) * self.x
        self.v += acceleration * self.dt
        self.x += self.v * self.dt
        self.time += self.dt

        # Обновляем график
        if len(self.time_data) < 20:
            self.series.append(self.time, self.x)
            if self.time > self.chart.axes()[0].max():
                self.chart.axes()[0].setMax(self.time + 1)

        # Обновляем виджет отрисовки
        self.spring_widget.set_physical_state(self.x, self.v)
        self.spring_widget.update()


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec())
