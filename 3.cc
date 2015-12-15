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

    struct Santa {
        Santa()
            : position { 0, 0 }
            , visited { position }
        {
        }

        Coordinate position;
        std::unordered_set<Coordinate, CoordinateHasher> visited;

        void process(char command) {
            switch (command) {
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
    };

    Santa santa;

    std::string line;
    std::getline(std::cin, line);
    for (char c : line) {
        santa.process(c);
    }

    std::cout << santa.visited.size() << std::endl;
    return 0;
}

