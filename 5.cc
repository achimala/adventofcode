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

bool isNice2(const std::string& string) {
    bool foundRepeatingPair = false;
    bool foundSandwich = false;
    for (int i = 0; i < string.length() - 2; ++i) {
        auto pair = string.substr(i, 2);
        if (string.find(pair, i + 2) != std::string::npos) {
            foundRepeatingPair = true;
        }

        auto triplet = string.substr(i, 3);
        if (triplet[0] == triplet[2]) {
            foundSandwich = true;
        }

        if (foundRepeatingPair && foundSandwich) {
            return true;
        }
    }

    return foundRepeatingPair && foundSandwich;
}

int main() {
    std::string line;
    int count = 0;
    int count2 = 0;
    while (std::getline(std::cin, line)) {
        if (isNice(line)) {
            ++count;
        }

        if (isNice2(line)) {
            ++count2;
        }
    }

    std::cout << count << std::endl;
    std::cout << count2 << std::endl;
    return 0;
}

