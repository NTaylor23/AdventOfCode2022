#include "advent.h"
#include <fstream>
#include <iostream>

bool has_overlap(const auto& a, const auto& b, bool partial = false) {
    if (partial) return std::max(a.first, b.first) <= std::min(a.second, b.second);
    return (a.first >= b.first && a.second <= b.second)
           || (a.second >= b.second && a.first <= b.first);
}

std::pair<int, int> split_pair(const std::string& s, char delim) {
    size_t idx = s.find(delim);
    return {stoi(s.substr(0, idx)),stoi(s.substr(idx + 1, s.length()))};
}

auto day04() -> int {

    std::string line;
    std::fstream inFile("input/day04.txt");
    assert(inFile.is_open());

    int part1 = 0, part2 = 0;

    while (getline(inFile, line)) {
        size_t idx = line.find(',');
        auto left = split_pair(line.substr(0, idx), '-');
        auto right = split_pair(line.substr(idx + 1, line.length()), '-');

        part1 += has_overlap(left, right);
        part2 += has_overlap(left, right, true);
    }

    inFile.close();
    std::cout << "Day 4:\n" << part1 << " pairs fully contain the other pair.\n"
              << part2 << " pairs partially contain the other pair.\n\n";
    return 0;
}