def find_all_in_str(target, symbol):
    lst = list()
    for i in range(len(target)):
        if target[i] == symbol:
            lst.append(i)
    return lst


str = input()
char = input()
print(find_all_in_str(str, char))
