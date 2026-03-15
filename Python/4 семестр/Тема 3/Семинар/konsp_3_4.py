def quad_sol(a=1, b=2, c=1):
    try:
        if not all(isinstance(x, (int, float)) for x in [a, b, c]):
            raise TypeError("Все коэффициенты должны быть числами")
        if a == 0:
            raise ZeroDivisionError("Коэффициент a не может быть равен 0")
        d = b**2 - 4*a*c
        return {(b + d**0.5) / (2 * a), (b - d**0.5) / (2 * a)}
    except TypeError as e:
        print(f"Ошибка типа данных: {e}")
        return None
    except ZeroDivisionError as e:
        print(f"Ошибка деления на ноль: {e}")
        return None


a = input()
b = input()
c = input()
print(quad_sol(a, b, c))
