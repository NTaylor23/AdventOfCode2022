#include "advent.h"
#include <iostream>
#include <unordered_map>
#include <fstream> //will need when we delete parser
#include <vector>
#include <deque>
#include "parser.h"

auto day07() -> int {
    int part1 = 0, part2 = 0;
    std::string line;
    parser p("input/day07.txt", "str"); // do a better split
    std::fstream inFile("input/day07.txt");
    assert (inFile.is_open());

    std::deque<std::string> pathRoute{""};

    std::unordered_map<std::string, int> sizes;
    std::unordered_map<std::string, std::vector<std::string>> subdirs;

    std::string currentDir;

    while (getline(inFile, line)) {

        if (line.starts_with("$ cd")) {

            if (!line.ends_with("..")) {

                currentDir = pathRoute.back() + line.substr(5);
                pathRoute.emplace_back(currentDir);

                if (sizes.find(currentDir) == sizes.end()) {
                    sizes.insert({currentDir, 0});
                }

                if (subdirs.find(currentDir) == subdirs.end()) {
                    subdirs.insert({currentDir, std::vector<std::string>{}});
                }

            } else {
                pathRoute.pop_back();
                currentDir = pathRoute.back();
            }

        } else if (isdigit(line[0])) {
            sizes[currentDir] += std::stoi(p.split_to_new(line, ' ')[0]);

        } else if (line.starts_with("dir")) {
            subdirs[currentDir].emplace_back(currentDir + line.substr(4));
        }
    }

    for (auto const& [directory, subdirectories] : subdirs) {
        //std::cout << directory << '\n';
        for (const std::string& dir : subdirectories) {
            //std::cout << "--" << dir << '\n';
            sizes[directory] += sizes[dir];
        }
    }

    for (auto const& [k, v] : subdirs) {
        if (sizes[k] <= 100000) part1 += sizes[k];
    }
    std::cout << part1;

    return 0;
}
