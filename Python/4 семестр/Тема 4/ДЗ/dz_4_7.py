import itertools
from fractions import Fraction


def split_digits(digits):
    n = len(digits)
    splits = []

    for i in range(1 << (n-1)):
        numbers = []
        current = digits[0]

        for j in range(n-1):
            if i & (1 << j):
                numbers.append(current)
                current = digits[j+1]
            else:
                current += digits[j+1]

        numbers.append(current)
        splits.append(numbers)

    return splits


def generate_all_expressions(digits):
    operators = ['+', '-', '*', '/']
    all_expressions = []

    splits = split_digits(digits)

    for numbers in splits:
        if len(numbers) == 1:
            all_expressions.append(numbers[0])
        else:
            for ops in itertools.product(operators, repeat=len(numbers)-1):
                expr = numbers[0]
                for num, op in zip(numbers[1:], ops):
                    expr += op + num
                all_expressions.append(expr)

    return all_expressions


def evaluate_expression(expr):
    try:
        parts = []
        current_num = ''

        for char in expr:
            if char in '+-*/':
                if current_num:
                    parts.append(f'Fraction({current_num})')
                    current_num = ''
                parts.append(char)
            else:
                current_num += char

        if current_num:
            parts.append(f'Fraction({current_num})')

        fraction_expr = ''.join(parts)
        return eval(fraction_expr)
    except ZeroDivisionError:
        return None
    except Exception:
        return None


def create_expressions_dict(digits):
    all_exprs = generate_all_expressions(digits)
    expressions_dict = {}

    for expr in all_exprs:
        value = evaluate_expression(expr)
        if value is not None:
            expressions_dict[expr] = value

    return expressions_dict


def find_matches(expressions_dict, target_str):
    if '/' in target_str:
        num, den = target_str.split('/')
        target = Fraction(int(num), int(den))
    else:
        target = Fraction(int(target_str))

    return [expr for expr, value in expressions_dict.items()
            if value == target]


def main():
    digits = input('Введите цифры: ')

    expressions_dict = create_expressions_dict(digits)

    print('Словарь выражений:')
    for expr, value in expressions_dict.items():
        print(f"'{expr}': {value}", end=', ')
    print('\n')

    while True:
        target = input(
            'Введите искомое число или дробь (например, 1/111) или "выход": ')
        if target.lower() == 'выход':
            break

        matches = find_matches(expressions_dict, target)

        if matches:
            print(f'Результаты для {target}:')
            for expr in matches:
                value = expressions_dict[expr]
                print(f'{target} = {expr}')
        else:
            print(f'Выражений, равных {target}, не найдено')
        print()


if __name__ == "__main__":
    main()
