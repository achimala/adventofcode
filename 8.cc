#include <cassert>
#include <iostream>

int difference(std::string string) {
    int subtract = 2;
    for (int i = 1; i < string.length() - 1; ++i) {
        if (string[i] == '\\') {
            assert(i != string.length() - 2);
            if (string[i + 1] == '\\' || string[i + 1] == '"') {
                ++i;
                ++subtract;
                continue;
            }

            assert(string[i + 1] == 'x');
            i += 3;
            subtract += 3;
        }
    }

    return subtract;
}

int extra(std::string string) {
    int length = 2;
    for (char c : string) {
        ++length;
        if (c == '"' || c == '\\') {
            ++length;
        }
    }

    return length - string.length();
}

int main() {
    int answer1 = 0;
    int answer2 = 0;
    std::string line;
    while (std::getline(std::cin, line)) {
        answer1 += difference(line);
        answer2 += extra(line);
    }

    std::cout << answer1 << std::endl;
    std::cout << answer2 << std::endl;
    return 0;
}

