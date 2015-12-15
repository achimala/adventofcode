#include <iostream>
#include <unordered_set>

int main() {
    struct Coordinate {
        int x;
        int y;
        bool operator==(const Coordinate& other) const {
            return x == other.x && y == other.y;
        }
    };

    struct CoordinateHasher {
        size_t operator()(Coordinate const& coordinate) const {
            return coordinate.x;
        }
    };

    Coordinate position { 0, 0 };
    std::unordered_set<Coordinate, CoordinateHasher> visited { position };
    std::string line;
    std::getline(std::cin, line);
    for (char c : line) {
        switch (c) {
            case '^':
                --position.y;
                break;
            case 'v':
                ++position.y;
                break;
            case '<':
                --position.x;
                break;
            case '>':
                ++position.x;
                break;
        }

        visited.emplace(position);
    }

    std::cout << visited.size() << std::endl;
    return 0;
}

