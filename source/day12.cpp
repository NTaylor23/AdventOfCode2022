#include "advent.h"
#include <deque>
#include <fstream>
#include <iostream>
#include <vector>

std::vector<std::vector<char>> grid;
constexpr char MAX_ELV {'M'};

struct Coordinate {
    int x, y;
    Coordinate() : x(-1), y(-1) {};
    Coordinate(int _x, int _y) : x(_x), y(_y) {};
};

const std::pair<int, int> DELTAS[4] {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

struct Point {
    int cost;
    Coordinate loc;
    Point(int c, Coordinate d) : cost(c), loc(d) {};
};

bool compare(int y, int x, int _y, int _x, bool forwards = true) {
    int val = int(grid[_y][_x]) - int(grid[y][x]);
    return forwards ? val > 1 : val < - 1;
}

bool find_in_queue(const auto& q, const Point& target) {
    for (const Point& obj : q) {
         if (obj.cost == target.cost
         && obj.loc.x == target.loc.x
         && obj.loc.y == target.loc.y) return true;
    }
    return false;
}

int search(auto& ent, auto& elevation_lookup, const int MAX_Y, const int MAX_X, bool part1) {

    auto in_range = [&MAX_Y, &MAX_X](int y, int x) {
        return (0 <= x && x < MAX_X) && (0 <= y && y < MAX_Y);
    };

    std::vector<std::vector<bool>> visited(MAX_Y, std::vector<bool>(MAX_X, false));
    std::deque<Point> queue;
    queue.push_back(Point(0, ent));

    while (!queue.empty()) { // BFS
        auto u = queue.front();
        queue.pop_front();
        int cost = u.cost, y = u.loc.y, x = u.loc.x;
        visited[y][x] = true;

        if (grid[y][x] == 'a' && !part1) return cost;
        if (part1 && elevation_lookup[y][x] == MAX_ELV) return cost;

        for (const auto& delta : DELTAS) { //BFS
            int xx = x + delta.first, yy = y + delta.second;

            // Sort validity checks in order of increasing complexity
            // New Point object should only be created to check if it exists in queue (this can be improved also...)
            if (!in_range(yy, xx)) continue;
            if (compare(y, x, yy, xx, part1)) continue;
            if (visited[yy][xx]) continue;

            const Point n = Point(cost + 1, Coordinate(xx, yy));
            if (find_in_queue(queue, n)) continue;
            queue.push_back(n);
        }
    }

    return 0;
}

void delegate(const Coordinate& ent, const Coordinate& ext, const int MAX_Y, const int MAX_X) {
    std::vector<std::vector<char>> elevation_lookup(MAX_Y, std::vector<char>(MAX_X, '.'));
    elevation_lookup[ext.y][ext.x] = MAX_ELV;

    grid[ent.y][ent.x] = 'a';
    grid[ext.y][ext.x] = 'z';
    int part1 = search(ent, elevation_lookup, MAX_Y, MAX_X, true);
    int part2 = search(ext, elevation_lookup, MAX_Y, MAX_X, false);
    std::cout << "Day 12:\nWe will get the best signal from the top of the mountain in " << part1 << " steps.\n"
              << "The fewest amount of steps to the top of the mountain from any [a] location is " << part2 << ".\n\n";
}

auto day12() -> int {
    std::string line;
    std::fstream inFile("input/day12.txt");
    assert (inFile.is_open());

    int r = 0;
    Coordinate ent, ext;
    while (getline(inFile, line)) {
        std::vector<char> row;
        for (int c = 0; c < line.length(); c++) {
            char letter = line.at(c);
            row.emplace_back(letter);
            if (letter == 'S') {
                ent = Coordinate(c, r);
            }
            if (letter == 'E') {
                ext = Coordinate(c, r);
            }
        }
        grid.emplace_back(row);
        r++;
    }

    delegate(ent, ext, r, grid[0].size());
    return 0;
}