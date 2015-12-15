#include <iostream>

int main() {
    int depth = 0;
    int i = 1;
    int positionOfInstructionThatEnteredBasement = 0;
    bool stop = false;
    while (!stop) {
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
                stop = true;
                break;
        }

        if (depth == -1 && !positionOfInstructionThatEnteredBasement) {
            positionOfInstructionThatEnteredBasement = i;
        }

        ++i;
    }

    printf("Floor: %d\n", depth);
    if  (positionOfInstructionThatEnteredBasement) {
        printf("Entered basement at instruction %d\n", positionOfInstructionThatEnteredBasement);
    }

    return 0;
}

