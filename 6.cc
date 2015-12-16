#include <iostream>
#include <map>

static bool hasPrefix(std::string string, std::string prefix) {
    return std::mismatch(prefix.begin(), prefix.end(), string.begin()).first == prefix.end();
}

int main() {
    bool grid[1000][1000];
    for (int i = 0; i < 1000; ++i) {
        for (int j = 0; j < 1000; ++j) {
            grid[i][j] = false;
        }
    }

    std::string line;
    while (std::getline(std::cin, line)) {
        enum class Command {
            On,
            Off,
            Toggle,
        } command;

        static std::map<std::string, Command> prefixes {
            { "turn on", Command::On },
            { "turn off", Command::Off },
            { "toggle", Command::Toggle },
        };

        int x1;
        int y1;
        int x2;
        int y2;
        for (auto pair : prefixes) {
            if (hasPrefix(line, pair.first)) {
                command = pair.second;
                sscanf(line.c_str() + pair.first.length() + 1, "%d,%d through %d,%d", &x1, &y1, &x2, &y2);
                break;
            }
        }

        for (int i = std::min(x1, x2); i <= std::max(x1, x2); ++i) {
            for (int j = std::min(y1, y2); j <= std::max(y1, y2); ++j) {
                switch (command) {
                    case Command::On:
                        grid[i][j] = true;
                        break;
                    case Command::Off:
                        grid[i][j] = false;
                        break;
                    case Command::Toggle:
                        grid[i][j] = !grid[i][j];
                        break;
                }
            }
        }
    }

    int count = 0;
    for (int i = 0; i < 1000; ++i) {
        for (int j = 0; j < 1000; ++j) {
            if (grid[i][j]) {
                ++count;
            }
        }
    }

    std::cout << count << std::endl;
    return 0;
}

