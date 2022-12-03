#include "advent.h"
#include "parser.h"
#include <iostream>
#include <unordered_set>

auto priority = [](const char& c) { return c < 'a' ? c % 'A' + 27 : c % 'a' + 1; };

std::vector<char> duplicateInLine(const std::string& vs, size_t midpoint) {
    std::vector<char> res;
    std::unordered_set<char> letters;

    for (int i = 0; i < midpoint; i++) { letters.insert(vs[i]); }
    for (int i = midpoint; i < vs.size(); i++) {
        if (letters.find(vs[i]) != letters.end()) {
            res.push_back(vs[i]);
        }
    }

    return res;
}

char triplicate(const VecStr& vs) {
    std::vector<char> firstTwoStrs = duplicateInLine(vs[0] + vs[1], vs[0].size());
    std::string temp(firstTwoStrs.begin(), firstTwoStrs.end());
    return duplicateInLine(temp + vs[2], firstTwoStrs.size())[0];
}

auto day03() -> int {
    parser p("input/day03.txt", "str");
    VecStr in = p.getStrs(), group;

    int part1 = 0, part2 = 0;
    std::unordered_set<char> letters;

    for (const std::string& bag : in) {
        group.push_back(bag);
        if (group.size() == 3) {
            part2 += priority(triplicate(group));
            group.clear();
        }
        part1 += priority(duplicateInLine(bag, bag.size() / 2)[0]);
    }

    std::cout << "Day 3:\nCombining the priorities of the items in the bags gives us a sum total of " << part1 << ".\n"
    << "When we combine the bags into groups of three, we get " << part2 << ".\n\n";

    return 0;
}