/*Все адреса электронной почты в исходной строке заменить на "[contacts not allowed]"*/

#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

string replace_emails(string);

int main() {
    string s1, s2;

    ifstream input("input.txt", ios::in);
    if (!input) {
        cerr << "Error, couldn't read from the file";
        exit(1);
    }
    getline(input, s1);

    if (s1.empty()) {
        cout << "The string is empty" << endl;
        exit(2);
    }

    s2 = replace_emails(s1);

    ofstream output("output.txt", ios::out);
    if (!output) {
        cerr << "Error, couldn't open the file";
        exit(3);
    } else cout << "The result has been written in the output.exe" << endl;
    output << s2;

    return 0;
}

string replace_emails(string s) {
    string result;
    unsigned int i = 0, n = s.length();

    while (i < n) {
        unsigned int email_start = i;
        while (email_start < n && !isalnum(s[email_start])) {
            email_start++;
        }

        if (email_start >= n) {
            result += s.substr(i);
            break;
        }

        result += s.substr(i, email_start - i);

        unsigned int email_end = email_start;
        while (email_end < n) {
            char c = s[email_end];
            if (c == ' ') {
                break;
            }
            email_end++;
        }

        string potential_email = s.substr(email_start, email_end - email_start);

        size_t at_pos = potential_email.find('@');
        if (at_pos == string::npos) {
            result += potential_email;
            i = email_end;
            continue;
        }

        string local = potential_email.substr(0, at_pos);
        string domain = potential_email.substr(at_pos + 1);

        bool f = true;

        // 1. Только один @
        if (count(potential_email.begin(), potential_email.end(), '@') != 1) {
            f = false;
        }

        // 2. Длина имени пользователя <=64 / ненулевая
        if (local.length() > 64 || local.empty()) {
            f = false;
        }

        // 3. Доменная часть не пустая и содержит точку
        if (domain.empty() || domain.find('.') == string::npos) {
            f = false;
        }

        // 4. Проверка доменной части на нижнее подчёркивание и двойные точки
        if (domain.find('_') != string::npos || domain.find("..") != string::npos) {
            f = false;
        }

        // 5. Проверка имени пользователя на специальные символы
        if (f) {
            // В кавычках можно расставлять специальные символы, но до конца имени пользователя их нужно закрыть
            bool in_quotes = false;
            bool escape_next = false;

            for (unsigned int j = 0; j < local.length(); j++) {
                char c = local[j];

                if (escape_next) {
                    escape_next = false;
                    if (!in_quotes) {
                        f = false;
                        break;
                    }
                    continue;
                }

                if (c == '\\') {
                    escape_next = true;
                    if (!in_quotes) {
                        f = false;
                        break;
                    }
                    continue;
                }

                if (c == '"') {
                    in_quotes = !in_quotes;
                    continue;
                }

                if (!in_quotes) {
                    if (c == '(' || c == ')' || c == ',' || c == ':' || c == ';' ||
                        c == '<' || c == '>' || c == '[' || c == ']' || c == ' ') {
                        f = false;
                        break;
                    }
                }
            }

            if (in_quotes || escape_next) {
                f = false;
            }
        }

        // 6. Проверка структуры кавычек: в начале или после точки
        if (f && local.find('"') != string::npos) {
            size_t quote_pos = local.find('"');
            if (quote_pos != 0) {
                if (quote_pos >= local.length() || local[quote_pos - 1] != '.') {
                    f = false;
                }
            }
        }

        if (f) {
            result += "[contacts not allowed]";
        } else {
            result += potential_email;
        }

        i = email_end;
    }

    return result;
}
