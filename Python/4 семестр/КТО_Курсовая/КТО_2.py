import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation


def explicit_heat(L, T, nx, nt, a_sq, u0_func, bc_left_func, bc_right_func):
    """
    Явная разностная схема для уравнения теплопроводности u_t = a²·u_xx
    Параметры:
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
    x : ndarray
        Координаты узлов (nx+1)
    t : ndarray
        Моменты времени (nt+1)
    u : ndarray
        Матрица решения (nx+1) x (nt+1)
    """
    # 1. Вычисляем шаги сетки
    h = L / nx          # пространственный шаг
    tau = T / nt        # временной шаг
    # Параметр схемы γ = a²·τ / h²
    gamma = a_sq * tau / (h * h)
    # Проверка устойчивости
    if gamma > 0.5:
        print(f"ВНИМАНИЕ: γ = {gamma:.3f} > 0.5")
        print("Условие устойчивости нарушено! Решение может быть неверным.")
        print(f"Рекомендуется: nt >= {int(a_sq * T / (0.5 * h * h)) + 1}")
    else:
        print(f"γ = {gamma:.3f} ≤ 0.5 — условие устойчивости выполнено.")
    # 2. Создаём сетки
    x = np.linspace(0, L, nx + 1)      # узлы по x: 0, h, 2h, ..., L
    t = np.linspace(0, T, nt + 1)      # узлы по t: 0, τ, 2τ, ..., T
    # 3. Инициализация матрицы решения
    # u[i, j] — температура в узле (x_i, t_j)
    u = np.zeros((nx + 1, nt + 1))
    # 4. Начальное условие (j = 0)
    for i in range(nx + 1):
        u[i, 0] = u0_func(x[i])
    # 5. Основной цикл по времени
    for j in range(nt):
        # Граничные условия (фиксируем на каждом шаге)
        u[0, j + 1] = bc_left_func(t[j + 1])      # левый конец (i=0)
        u[nx, j + 1] = bc_right_func(t[j + 1])     # правый конец (i=nx)
        # Внутренние узлы (i = 1, 2, ..., nx-1)
        for i in range(1, nx):
            u[i, j + 1] = (u[i, j] + 
                           gamma * (u[i + 1, j] - 2 * u[i, j] + u[i - 1, j]))
    return x, t, u


# 6. Задание параметров задачи
L = 1.0                     # длина стержня (м)
T = 0.1                     # время расчёта (с)
nx = 50                     # количество интервалов по x
nt = 2000                   # количество интервалов по времени
a_sq = 1.0                  # коэффициент температуропроводности (м²/с)


# Начальное условие: u(x,0) = sin(π·x)
def u0(x):
    return np.sin(np.pi * x)


# Граничные условия Дирихле: u(0,t) = 0, u(L,t) = 0
def bc_left(t):
    return 0.0


def bc_right(t):
    return 0.0


# 7. Выполнение расчёта
x, t, u = explicit_heat(L, T, nx, nt, a_sq, u0, bc_left, bc_right)

# 8. Визуализация результатов
# Выбираем несколько моментов времени для отображения
time_indices = [0, nt // 4, nt // 2, 3 * nt // 4, nt]
time_labels = [f"t = {t[idx]:.3f} с" for idx in time_indices]

plt.figure(figsize=(10, 6))
for idx in time_indices:
    plt.plot(x, u[:, idx], label=f"t = {t[idx]:.3f} с", linewidth=2)

plt.title("Распределение температуры вдоль стержня в разные моменты времени", fontsize=14)
plt.xlabel("Координата x(м)", fontsize=12)
plt.ylabel("Температура u(°C)", fontsize=12)
plt.grid(True, linestyle='--', alpha=0.7)
plt.legend()
plt.show()

# 9. Создание анимации
fig, ax = plt.subplots(figsize=(8, 5))
line, = ax.plot(x, u[:, 0], 'b-', linewidth=2)
ax.set_xlim(0, L)
ax.set_ylim(-0.1, 1.1)
ax.set_xlabel("x(м)")
ax.set_ylabel("Температура(°C)")
ax.set_title("Эволюция температуры во времени")
ax.grid(True, linestyle='--', alpha=0.7)


def animate(j):
    line.set_ydata(u[:, j])
    ax.set_title(f"t = {t[j]:.4f} с")
    return line,


ani = FuncAnimation(fig, animate, frames=nt+1, interval=20, repeat=True)
plt.show()

# 10. Вывод информации о расчёте
print("\nИтоги расчёта:")
print(f"nx = {nx}, h = {L/nx:.4f} м")
print(f"nt = {nt}, τ = {T/nt:.6f} с")
print(f"γ = {a_sq * (T/nt) / ((L/nx)**2):.4f}")
print(f"Размер матрицы u: {u.shape}")
