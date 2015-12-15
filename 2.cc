#include <iostream>
#include <sstream>
#include <vector>

int areaNeeded(const std::vector<int>& dimensions) {
    int area = 0;
    for (size_t i = 0; i < dimensions.size(); ++i) {
        area += 2 * dimensions[i] * dimensions[(i + 1) % dimensions.size()];
    }

    return area + dimensions[0] * dimensions[1];
}

int ribbonLengthNeeded(const std::vector<int>& dimensions) {
    int length = 1;
    for (int i : dimensions) {
        length *= i;
    }

    return length + 2 * (dimensions[0] + dimensions[1]);
}

int main() {
    std::string line;
    int area = 0;
    int ribbonLength = 0;
    while (std::getline(std::cin, line)) {
        std::stringstream stream(line);
        std::string number;
        std::vector<int> dimensions;
        while (std::getline(stream, number, 'x')) {
            dimensions.push_back(std::stoi(number));
        }

        std::sort(dimensions.begin(), dimensions.end());
        area += areaNeeded(dimensions);
        ribbonLength += ribbonLengthNeeded(dimensions);
    }

    printf("Wrapping paper: %d\nRibbon: %d\n", area, ribbonLength);
    return 0;
}

