import datetime
import itertools


def anagram(str1, str2):
    start_time = datetime.datetime.now()

    flag = True
    parts = list(str2)
    for i in range(0, len(str1)):
        if str1[i] in parts:
            parts.remove(str1[i])
        else:
            flag = False
            break

    finish_time = datetime.datetime.now()
    delta = finish_time - start_time
    print('Функция без itertools')
    print('Является анаграммой: ', flag)
    print('Затраченное время: ', delta.total_seconds() * 1000)


def anagram_iter(str1, str2):
    start_time = datetime.datetime.now()

    sorted1 = list(itertools.islice(sorted(str1), len(str1)))
    sorted2 = list(itertools.islice(sorted(str2), len(str2)))

    flag = (sorted1 == sorted2)

    finish_time = datetime.datetime.now()
    delta = finish_time - start_time
    print('Функция с itertools')
    print('Является анаграммой: ', flag)
    print('Затраченное время: ', delta.total_seconds() * 1000)


word1 = input('Введите первое слово: ').upper()
word2 = input('Введите второе слово: ').upper()

anagram(word1, word2)
anagram_iter(word1, word2)
