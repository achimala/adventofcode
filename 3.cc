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
    Santa newSanta;
    Santa roboSanta;

    std::string line;
    std::getline(std::cin, line);
    int i = 0;
    for (char c : line) {
        santa.process(c);
        if (i++ % 2) {
            newSanta.process(c);
        } else {
            roboSanta.process(c);
        }
    }

    std::cout << santa.visited.size() << std::endl;
    auto set = newSanta.visited;
    set.insert(roboSanta.visited.begin(), roboSanta.visited.end());
    std::cout << set.size() << std::endl;
    return 0;
}

