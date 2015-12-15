#include "md5.cc"
#include <iostream>

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("USAGE: %s <secret key>\n", argv[0]);
        return 0;
    }

    std::string secretKey(argv[1]);
    bool found5 = false;
    for (int i = 0;; ++i) {
        auto string = md5(secretKey + std::to_string(i));
        bool worksFor5 = true;
        bool worksFor6 = false;
        for (int j = 0; j < 5; ++j) {
            if (string[j] != '0') {
                worksFor5 = false;
                break;
            }
        }

        if (worksFor5 && string[5] == '0') {
            worksFor6 = true;
        }

        if (worksFor5 && !found5) {
            std::cout << i << std::endl;
            found5 = true;
        }

        if (worksFor6) {
            std::cout << i << std::endl;
            return 0;
        }
    }

    return 1;
}

