#include <iostream>

int main() {
    int depth = 0;
    while (true) {
        char c;
        scanf("%c", &c);
        switch (c) {
            case '(':
                ++depth;
                break;
            case ')':
                --depth;
                break;
            default:
                printf("%d\n", depth);
                return 0;
        }
    }

    return 1;
}

