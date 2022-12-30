#include "advent.h"
#include "parser.h"
#include <fstream>
#include <iostream>
#include <vector>

// ~~~~~~~ COMPARISON FUNCTIONS ~~~~~~~
bool compareInt(const int a, const int b) { return a <= b; }

bool compareList(const std::vector<int>& a, const std::vector<int>& b) {
    for (int i = 0; i < a.size(); i++) {
        if (!compareInt(a[i], b[i])) return false;
    }
    return true;
}

bool compareLength(const std::string& a, const std::string& b) { return a.size() <= b.size(); }
// ~~~~~~~ /COMPARISON FUNCTIONS ~~~~~~~


// ~~~~~~~ UTIL FUNCTIONS ~~~~~~~
std::vector<int> convToList(const std::string& s) {
    std::vector<int> nums;
    std::vector<std::string> asInts = parser::split(s.substr(1, s.length() - 2),  ",");
    for (const auto& n : asInts) {
        // can be removed if all input values succeed
        try {
            nums.emplace_back(std::stoi(n));
        } catch (std::exception& ex) {
            std::cerr << ex.what();
        }
    }
    return nums;
}

void removeExtBrackets(std::string& s) {
    s = s.substr(1, s.size() - 2);
}

bool window(std::string& s, auto& res) {
    int i = 0, j = s.length() - 1;
    for (; i < j; i++) {
        if (s[i] == '[') break;
    }
    for (; j > i; j--) {
        if (s[j] == ']') break;
    }
    if (j == i) return false;
    res.emplace_back(convToList(s.substr(i, j + 1)));
    return true;
}

std::vector<std::vector<int>> disassemble(std::string& s) {
    //[1, [2, [3, [4, [5, 6, 7] ] ] ], 8, 9]
    //[[1], [2], [3], [4], [5, 6, 7], [8], [9]]
    std::vector<std::vector<int>> res;
    removeExtBrackets(s);

    while (window(s, res)) {}
    return res;
}
// ~~~~~~~ /UTIL FUNCTIONS ~~~~~~~


auto day13() -> int {
    std::string line;
    std::fstream inFile("input/day13.txt");
    assert (inFile.is_open());

    std::string a = "[1,1,3,1,1]";
    std::string b = "[1,1,5,1,1]";
    std::string c = "[[4,4],4,4]";

    auto res = disassemble(c);
    if (compareLength(a, b)) {
        auto l_a = convToList(a), l_b = convToList(b);
        if (compareList(l_a, l_b)) std::cout << "valid list\n";
    }
    return 0;
}