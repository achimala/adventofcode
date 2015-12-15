#include <iostream>
#include <set>

bool isNice(const std::string& string) {
    static std::set<char> vowels { 'a', 'e', 'i', 'o', 'u' };
    static std::set<std::string> blacklist { "ab", "cd", "pq", "xy" };
    int numberOfVowels = 0;
    bool hasDoubleLetter = false;
    for (int i = 0; i < string.length(); ++i) {
        if (vowels.find(string[i]) != vowels.end()) {
            ++numberOfVowels;
        }

        if (i == string.length()) {
            break;
        }

        if (string[i] == string[i + 1]) {
            hasDoubleLetter = true;
        }

        if (blacklist.find(string.substr(i, 2)) != blacklist.end()) {
            return false;
        }
    }

    return numberOfVowels >= 3 && hasDoubleLetter;
}

int main() {
    std::string line;
    int count = 0;
    while (std::getline(std::cin, line)) {
        if (isNice(line)) {
            ++count;
        }
    }

    std::cout << count << std::endl;
    return 0;
}

