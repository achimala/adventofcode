#include <iostream>
#include <sstream>
#include <vector>

int areaNeeded(std::vector<int>& dimensions) {
    std::sort(dimensions.begin(), dimensions.end());
    int area = 0;
    for (size_t i = 0; i < dimensions.size(); ++i) {
        area += 2 * dimensions[i] * dimensions[(i + 1) % dimensions.size()];
    }

    return area + dimensions[0] * dimensions[1];
}

int main() {
    std::string line;
    int area = 0;
    while (std::getline(std::cin, line)) {
        std::stringstream stream(line);
        std::string number;
        std::vector<int> dimensions;
        while (std::getline(stream, number, 'x')) {
            dimensions.push_back(std::stoi(number));
        }

        area += areaNeeded(dimensions);
    }

    std::cout << area << std::endl;
    return 0;
}

