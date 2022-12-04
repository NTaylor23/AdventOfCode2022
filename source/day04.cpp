#include "advent.h"
#include "parser.h"
#include <iostream>

bool has_overlap(const auto& a, const auto& b, bool partial = false) {
    if (partial) return std::max(a.first, b.first) <= std::min(a.second, b.second);
    return (a.first >= b.first && a.second <= b.second)
           || (a.second >= b.second && a.first <= b.first);
}

auto split_pair(const std::string& s, char delim) {
    size_t idx = s.find(delim);
    return std::pair<int, int>(stoi(s.substr(0, idx)),
                               stoi(s.substr(idx + 1, s.length())));
}

auto day04() -> int {
    parser p("input/day04.txt", "str");
    const VecStr in = p.getStrs(), sep;
    int part1 = 0, part2 = 0;

    for (const std::string& line : in) {
        size_t idx = line.find(',');
        auto left = split_pair(line.substr(0, idx), '-');
        auto right = split_pair(line.substr(idx + 1, line.length()), '-');

        part1 += has_overlap(left, right);
        part2 += has_overlap(left, right, true);
    }

    std::cout << "Day 3:\n" << part1 << " pairs fully contain the other pair.\n"
              << part2 << " pairs partially contain the other pair.\n\n";
    return 0;
}