#include "advent.h"
#include <iostream>
#include <fstream>
#include <deque>

int find_unique_index(const std::string& signal, int sz) {
    char head, tail;
    bool flag;
    std::deque<int*> active;
    int alpha[26]{0}, i{0};

    for (; i < sz; i++) {
        int idx = signal[i] - 'a';
        ++alpha[idx];
        active.emplace_back(&alpha[idx]);
    }
    tail = signal[0];

    for (int j = sz; j < signal.size(); j++) {
        flag = true;
        head = signal[j];
        --alpha[tail - 'a']; ++alpha[head - 'a'];
        tail = signal[j - sz + 1];
        active.pop_front();
        active.emplace_back(&alpha[head - 'a']);
        for (const int* val : active) {
            if (*val > 1) { flag = false; break; }
        }
        if (flag) return j + 1;
    }
    return -1;
}

auto day06() -> int {
    int part1, part2;
    std::fstream inFile("input/day06.txt");
    assert(inFile.is_open());
    std::string content( (std::istreambuf_iterator<char>(inFile) ),
                         (std::istreambuf_iterator<char>()    ) );

    part1 = find_unique_index(content, 4);
    part2 = find_unique_index(content, 14);
    std::cout << part1 << " " << part2;

    return 0;
}
