import numpy as np
import matplotlib.pyplot as plt


def implicit_heat(L, T, nx, nt, a_sq, u0_func, bc_left_func, bc_right_func):
    """
    Неявная разностная схема для уравнения теплопроводности u_t = a²·u_xx
    Решение трёхдиагональной СЛАУ методом прогонки.
    Параметры:
    ----------
    L : float
        Длина стержня (м)
    T : float
        Время расчёта (с)
    nx : int
        Количество интервалов по x (сетка: nx+1 узел)
    nt : int
        Количество интервалов по времени (сетка: nt+1 узел)
    a_sq : float
        Коэффициент температуропроводности a² (м²/с)
    u0_func : function
        Начальное условие u0(x)
    bc_left_func : function
        Граничное условие на левом конце u(0,t)
    bc_right_func : function
        Граничное условие на правом конце u(L,t)
    Возвращает:
    -----------
    x : ndarray
        Координаты узлов (nx+1)
    t : ndarray
        Моменты времени (nt+1)
    u : ndarray
        Матрица решения (nx+1) x (nt+1)
    """
    # 1. Вычисляем шаги сетки и параметр γ
    h = L / nx          # пространственный шаг
    tau = T / nt        # временной шаг
    gamma = a_sq * tau / (h * h)   # параметр схемы (может быть любым!)
    print("Параметры расчёта:")
    print(f"h = {h:.4f} м, τ = {tau:.6f} с")
    print(f"γ = {gamma:.4f} (неявная схема устойчива при любом γ)")
    # 2. Создаём сетки
    x = np.linspace(0, L, nx + 1)      # узлы по x: 0, h, 2h, ..., L
    t = np.linspace(0, T, nt + 1)      # узлы по t: 0, τ, 2τ, ..., T
    # 3. Инициализация матрицы решения
    u = np.zeros((nx + 1, nt + 1))
    # 4. Начальное условие (j = 0)
    for i in range(nx + 1):
        u[i, 0] = u0_func(x[i])
    # 5. Основной цикл по времени
    for j in range(nt):
        # Граничные условия на новом слое
        u_left_new = bc_left_func(t[j + 1])
        u_right_new = bc_right_func(t[j + 1])
        m = nx - 1
        # 6. Построение трёхдиагональной системы
        # Диагональные и внедиагональные элементы
        a = np.zeros(m)     # нижняя диагональ (sub-diagonal)
        b = np.zeros(m)     # главная диагональ (main diagonal)
        c = np.zeros(m)     # верхняя диагональ (super-diagonal)
        d = np.zeros(m)     # правая часть
        # Заполнение для всех внутренних узлов i = 1..m (соответствуют x[1]..x[nx-1])
        for i in range(m):
            # Индекс в массиве u: i+1 (так как u[0] и u[nx] — границы)
            idx = i + 1
            b[i] = 1 + 2 * gamma      # главная диагональ
            d[i] = u[idx, j]          # правая часть (с предыдущего слоя)
            if i > 0:
                a[i] = -gamma         # нижняя диагональ (для i >= 1)
            if i < m - 1:
                c[i] = -gamma         # верхняя диагональ (для i <= m-2)
        # Учёт левого граничного условия (влияет на первое уравнение)
        d[0] = d[0] + gamma * u_left_new
        # Учёт правого граничного условия (влияет на последнее уравнение)
        d[m - 1] = d[m - 1] + gamma * u_right_new
        # 7. Метод прогонки (алгоритм Томаса)
        # Прямой ход
        for i in range(1, m):
            factor = a[i] / b[i - 1]
            b[i] = b[i] - factor * c[i - 1]
            d[i] = d[i] - factor * d[i - 1]
        # Обратный ход
        u_new_inner = np.zeros(m)
        u_new_inner[m - 1] = d[m - 1] / b[m - 1]
        for i in range(m - 2, -1, -1):
            u_new_inner[i] = (d[i] - c[i] * u_new_inner[i + 1]) / b[i]
        # 8. Сохранение результатов
        # Внутренние узлы
        for i in range(m):
            u[i + 1, j + 1] = u_new_inner[i]
        # Граничные узлы
        u[0, j + 1] = u_left_new
        u[nx, j + 1] = u_right_new
    return x, t, u


# 9. Задание параметров задачи
L = 1.0                     # длина стержня (м)
T = 0.1                     # время расчёта (с)
nx = 50                     # количество интервалов по x
nt = 500                    # количество интервалов по времени (можно брать меньше, чем в явной!)
a_sq = 1.0                  # коэффициент температуропроводности (м²/с)


# Начальное условие: u(x,0) = sin(π·x)
def u0(x):
    return np.sin(np.pi * x)


# Граничные условия Дирихле: u(0,t) = 0, u(L,t) = 0
def bc_left(t):
    return 0.0


def bc_right(t):
    return 0.0


# 10. Выполнение расчёта
x, t, u = implicit_heat(L, T, nx, nt, a_sq, u0, bc_left, bc_right)

# 11. Визуализация результатов
time_indices = [0, nt // 4, nt // 2, 3 * nt // 4, nt]

plt.figure(figsize=(10, 6))
for idx in time_indices:
    plt.plot(x, u[:, idx], label=f"t = {t[idx]:.3f} с", linewidth=2)

plt.title("Неявная схема: распределение температуры вдоль стержня", fontsize=14)
plt.xlabel("Координата x(м)", fontsize=12)
plt.ylabel("Температура u(°C)", fontsize=12)
plt.grid(True, linestyle='--', alpha=0.7)
plt.legend()
plt.show()


def analytical(x, t):
    return np.sin(np.pi * x) * np.exp(-np.pi**2 * t)


# Оценка погрешности в конечный момент времени
u_analyt_final = analytical(x, T)
error = np.max(np.abs(u[:, -1] - u_analyt_final))
print(f"\nМаксимальная погрешность в момент t = {T} с: {error:.6f}")
