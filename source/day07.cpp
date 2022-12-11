#include "advent.h"
#include "parser.h"
#include <iostream>
#include <unordered_map>
#include <deque>

auto day07() -> int {
    std::string line;
    std::fstream inFile("input/day07.txt");
    assert (inFile.is_open());

    constexpr size_t totalDiskSpace {70000000};
    constexpr size_t requiredSpace {30000000};
    int part1 = 0, part2;

    std::deque<std::string> pathRoute{""};
    std::unordered_map<std::string, int> sizes;

    while (getline(inFile, line)) {
        if (line.starts_with("$ cd")) {
            if (line.ends_with("..")) {
                pathRoute.pop_back();
            } else {
                std::string currentDir = line.substr(5);
                pathRoute.push_back(currentDir);
            }
        } else if (isdigit(line[0])) {
            std::string currDir;
            for (const auto& loc : pathRoute) {
                currDir += loc;
                if (sizes.find(currDir) == sizes.end()) {
                    sizes.insert({loc, 0});
                }
                sizes[currDir] += std::stoi(parser::split_to_new(line, ' ')[0]);
            }
        }
    }

    part2 = sizes["/"];
    auto freeSpace = totalDiskSpace - part2;
    auto goal = requiredSpace - freeSpace;

    for (auto const& [directory, size] : sizes) {
        if (size <= 100000) part1 += size;
        if (size > goal) part2 = std::min(size, part2);
    }

    inFile.close();
    std::cout << "Day 7:\nThe sum of the total sizes of our directories is " << part1 << ".\n"
    << "The total size of the smallest directory that'll free up the space we need is " << part2 << "\n\n";

    return 0;
}
