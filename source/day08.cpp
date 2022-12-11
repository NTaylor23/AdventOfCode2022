#include "advent.h"
#include <iostream>
#include <fstream>
#include <vector>

static int maxView = 0;

// Meh... brute force... refactor with complex numbers for grid traversal & maybe DFS/BFS?
bool calculateVisibility(int i, int j, auto const& map) {
    int start = map[i][j];
    bool up{true}, down{true}, left{true}, right{true};
    int upView = 0, downView = 0, leftView = 0, rightView = 0;

    for (int idx = i - 1; idx >= 0; idx--) {
        ++upView;
        if (map[idx][j] >= start) { up = false; break; }

    }
    for (int idx = i + 1; idx < map.size(); idx++) {
        ++downView;
        if (map[idx][j] >= start) { down = false; break; }
    }
    for (int idx = j - 1; idx >= 0; idx--) {
        ++leftView;
        if (map[i][idx] >= start) { left = false; break; }
    }
    for (int idx = j + 1; idx < map[0].size(); idx++) {
        ++rightView;
        if (map[i][idx] >= start) { right = false; break; }
    }

    maxView = std::max(maxView, upView * downView * leftView * rightView);
    return up || down || left || right;
}


auto day08() -> int {
    std::string line;
    std::fstream inFile("input/day08.txt");
    assert (inFile.is_open());

    int part1{0}, part2;
    std::vector<std::vector<int>> treeMap;

    while (getline(inFile, line)) {
        std::vector<int> row;
        for (const char c : line) {
            row.emplace_back(c - '0');
        }
        treeMap.emplace_back(row);
    }

    inFile.close();
    size_t maxRow = treeMap.size(), maxCol = treeMap[0].size();
    part1 += ((maxCol - 1) * 2) + ((maxRow - 1) * 2);

    for (int i = 1; i < treeMap.size() - 1; i++) {
        for (int j = 1; j < treeMap[0].size() - 1; j++) {
            part1 += calculateVisibility(i, j, treeMap);
        }
    }

    part2 = maxView;
    std::cout << "Day 8:\nWe can see " << part1 << " trees from the outside grid.\n"
    << "The highest scenic score possible for any tree is " << part2 << ".\n\n";
    return 0;
}
