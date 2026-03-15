import os


def get_priority(operation):
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


def evaluate_expression(expression, steps_list):
    tokens = []
    i = 0
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
        elif expression[i] in "+-*/":
            tokens.append(expression[i])
            i += 1
        else:
            i += 1

    for target_priority in (2, 1):
        i = 0
        while i < len(tokens):
            if get_priority(tokens[i]) == target_priority:
                a = float(tokens[i - 1])
                b = float(tokens[i + 1])
                operation = tokens[i]
                result = apply_operation(a, b, operation)
                steps_list.append(f"{a} {operation} {b} = {result}")
                tokens[i - 1] = str(result)
                del tokens[i:i + 2]
                i -= 1
            else:
                i += 1
    return tokens[0]


def solve(filename):
    with open(filename, "r") as file:
        expression = file.read().replace("\n", "").replace(" ", "")
    steps = []
    try:
        while "(" in expression:
            right = expression.find(")")
            left = expression.rfind("(", 0, right)

            sub_expr = expression[left+1:right]
            res = evaluate_expression(sub_expr, steps)

            expression = expression[:left] + res + expression[right+1:]

        final_result = evaluate_expression(expression, steps)
        steps.append(f"Итог: {final_result}")
        return steps
    except ZeroDivisionError:
        print("Ошибка: Деление на ноль!")
        return


script_dir = os.path.dirname(os.path.abspath(__file__))
file_path = os.path.join(script_dir, 'text.txt')
steps = solve(file_path)
if steps:
    for step in steps:
        print(step)
