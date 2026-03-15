import math
import os


def get_priority(operation):
    if operation == "^":
        return 3
    if operation in "*/":
        return 2
    if operation in "+-":
        return 1
    return 0


def apply_operation(a, b, operation):
    if operation == "+":
        return a + b
    if operation == "-":
        return a - b
    if operation == "*":
        return a * b
    if operation == "/":
        if b == 0:
            raise ZeroDivisionError("Деление на ноль!")
        return a / b
    if operation == "^":
        return a**b


def apply_function(func_name, value):
    funcs = {
        "sin": math.sin,
        "cos": math.cos,
        "tan": math.tan,
        "ln": math.log,
        "exp": math.exp,
        "sqrt": math.sqrt,
    }
    if func_name not in funcs:
        raise NameError(f"Неизвестная функция '{func_name}'")
    return funcs[func_name](value)


def tokenize_and_eval(expression):
    tokens = []
    i = 0
    # Разделение на токены (числа, слова-функции, операторы)
    while i < len(expression):
        if expression[i].isdigit():
            num = expression[i]
            i += 1
            while i < len(expression) and (
                expression[i].isdigit() or expression[i] == "."
            ):
                num += expression[i]
                i += 1
            tokens.append(num)
        elif expression[i].isalpha():
            word = expression[i]
            i += 1
            while i < len(expression) and expression[i].isalpha():
                word += expression[i]
                i += 1
            tokens.append(word)
        elif expression[i] in "+-*/^":
            tokens.append(expression[i])
            i += 1
        else:
            i += 1

    # Обработка функций (ищем слово и применяем к следующему числу)
    j = 0
    while j < len(tokens):
        if isinstance(tokens[j], str) and tokens[j].isalpha():
            val = float(tokens[j + 1])
            res = apply_function(tokens[j], val)
            tokens[j] = str(res)
            del tokens[j + 1]
        j += 1

    # Расчет по приоритетам
    for target_priority in (3, 2, 1):
        idx = 0
        while idx < len(tokens):
            if get_priority(tokens[idx]) == target_priority:
                a = float(tokens[idx - 1])
                b = float(tokens[idx + 1])
                op = tokens[idx]
                res = apply_operation(a, b, op)
                tokens[idx - 1] = str(res)
                del tokens[idx:idx+2]
                idx -= 1
            else:
                idx += 1
    return tokens[0]


def clean_and_merge_lines(filepath):
    try:
        with open(filepath, "r") as file:
            lines = [line.strip() for line in file if line.strip()]

        if not lines:
            print("Файл пустой.")
            return ""

        full_expression = lines[0]
        operators = ("+", "-", "*", "/", "^")

        for i in range(1, len(lines)):
            current_line = lines[i]
            if (
                full_expression[-1] in operators and
                current_line[0] in operators
            ):
                full_expression += current_line[1:]
            else:
                full_expression += current_line

        return full_expression

    except FileNotFoundError:
        print(f"Файл по адресу {filepath} не найден.")
        return ""


def solve(filepath):
    expression = clean_and_merge_lines(filepath)
    if not expression:
        return "Файл пуст или не найден."

    try:
        while "(" in expression:
            right = expression.find(")")
            left = expression.rfind("(", 0, right)
            if right == -1 or left == -1:
                break

            sub_expr = expression[left+1:right]
            res = tokenize_and_eval(sub_expr)
            expression = expression[:left] + str(res) + expression[right+1:]

        final_result = tokenize_and_eval(expression)
        return final_result

    except ZeroDivisionError:
        return "Ошибка: Деление на ноль."
    except NameError as e:
        return f"Ошибка: {e}"
    except Exception as e:
        return f"Ошибка при расчете: {e}"


script_dir = os.path.dirname(os.path.abspath(__file__))
file_path = os.path.join(script_dir, 'text.txt')
result = solve(file_path)
print(f"Результат: {result}")
