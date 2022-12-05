#include "advent.h"
#include "parser.h"
#include <iostream>
#include <queue>
#include <vector>

void move(int quantity, int source, int dest, std::vector<std::deque<char>>& stacks) {
    for (int i = 0; i < quantity; i++) {
        stacks[dest].push_back(stacks[source].back());
        stacks[source].pop_back();
    }
}

void parse_instruction(const std::string& line, parser& p, std::vector<std::deque<char>>& stacks) {
    VecStr nums = p.split_to_new(line, ' ');
    int quantity = stoi(nums[1]), source = stoi(nums[3]) - 1, dest = stoi(nums[5]) - 1;
    move(quantity, source, dest, stacks);
}

auto day05() -> int {
    parser p("input/day05.txt", "str");
    std::string part1, part2;
    const VecStr in = p.getStrs();
    VecStr stack_definition;

    auto itr = in.begin();
    while (!itr->empty()) {
        stack_definition.push_back(*itr++);
    }
    itr++;

    VecStr range = p.split_to_new(stack_definition.back(), ' ');
    size_t amt = stoi(range.back());
    std::vector<std::deque<char>> stacks(amt);

    for (const std::string& line : stack_definition) {
        for (int i = 0; i < line.length(); i += 4) {
            std::string curr = line.substr(i, 4);
            if (!curr.starts_with(' ')) {
                int idx = i / 4;
                stacks[idx].push_front(curr[1]);
            }
        }
    }

    while (itr != in.end()) {
        parse_instruction(*itr++, p, stacks);
    }

    for (const std::deque<char>& dq : stacks) {
        std::cout << dq.back();
    }

    return 0;
}