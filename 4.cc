#include "md5.cc"
#include <iostream>

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("USAGE: %s <secret key>\n", argv[0]);
        return 0;
    }

    std::string secretKey(argv[1]);
    for (int i = 0;; ++i) {
        auto string = md5(secretKey + std::to_string(i));
        bool works = true;
        for (int j = 0; j < 5; ++j) {
            if (string[j] != '0') {
                works = false;
                break;
            }
        }

        if (works) {
            std::cout << i << std::endl;
            return 0;
        }
    }

    return 1;
}

