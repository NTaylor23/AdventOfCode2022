#include "advent.h"
#include "parser.h"
#include <iostream>
#include <deque>
#include <vector>

// For part 2, we have to maintain order when modifying the stacks
void move_ordered(int quantity, int source, int dest, std::vector<std::deque<char>>& stacks) {
    for (int i = 0; i < quantity; i++) {
        auto pos = stacks[source].end() - quantity + i;
        stacks[dest].push_back(*pos);
        stacks[source].erase(pos);
    }
}

// For part 1, we just pop/push as usual
void move(int quantity, int source, int dest, std::vector<std::deque<char>>& stacks) {
    for (int i = 0; i < quantity; i++) {
        stacks[dest].push_back(stacks[source].back());
        stacks[source].pop_back();
    }
}

void parse_instruction(const std::string& line, parser& p, std::vector<std::deque<char>>& stacks, bool part2 = false) {
    VecStr nums = p.split_to_new(line, ' ');
    int quantity = stoi(nums[1]), source = stoi(nums[3]) - 1, dest = stoi(nums[5]) - 1;
    if (part2) {
        move_ordered(quantity, source, dest, stacks);
    } else {
        move(quantity, source, dest, stacks);
    }
}

// Slow and convoluted - come back to this one
auto day05() -> int {
    parser p("input/day05.txt", "str");
    const VecStr in = p.getStrs();
    std::string part1, part2;
    VecStr stack_definition;

    auto itr = in.begin();
    while (!itr->empty()) { // stack definition ends with an empty line
        stack_definition.emplace_back(*itr++);
    }

    std::vector<std::deque<char>> stacks(stack_definition.size());
    stacks.reserve(stack_definition.size());

    for (const std::string& line : stack_definition) {
        for (int i = 0; i < line.length(); i += 4) { // Tokens are separated by four chars each
            if (line[i] != ' ') {
                int idx = i >> 2;
                stacks[idx].push_front(line[i + 1]); // Just the letter, skip the brackets.
            }
        }
    }

    std::vector<std::deque<char>> part2Copy = stacks;
    while (++itr != in.end()) {
        parse_instruction(*itr, p, stacks);
        parse_instruction(*itr, p, part2Copy, true);
    }

    for (int i = 0; i < stacks.size(); i++) {
        part1 += stacks[i].back();
        part2 += part2Copy[i].back();
    }

    //VCTFTJQCG, GCFGLDNJZ
    std::cout << "Day 5:\nAt the end of our reshuffling, we get the letters " << part1 << " at the top of each stack.\n"
              << "After upgrading to a new CrateMover 9001, we get " << part2 << " at the top of each stack.\n\n";

    return 0;
}