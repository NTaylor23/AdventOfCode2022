#include "parser.h"
#include <iostream>
#include <utility>
#include <vector>

parser::parser(std::string filepath, std::string type) :
    path(std::move(filepath)),
    type(std::move(type)) { parse(); }

void parser::parse() {
    std::string buf;
    std::fstream inFile(path);

    if (inFile.is_open()) {
        while (getline(inFile, buf)) {
            if (type == "str") {
                strList.push_back(buf);
            } else if (type == "int") {
                std::cout << buf << " ";
                intList.push_back(stoi(buf));
            }
        }
    } else {
        std::cout << "Could not open file. Check filepath or CMakeLists.txt\n";
    }
    inFile.close();
}

void tokenize(std::string s, const std::string& delim, std::vector<std::string>& v) {
    int idx = s.find(delim);
    if (idx < 0) {
        v.emplace_back(s);
        return;
    }
    v.emplace_back(s.substr(0, idx));
    tokenize(s.substr(idx + delim.size()), delim, v);
}

std::vector<std::string> parser::split(std::string s, const std::string &delim) {
    std::vector<std::string> res;
    tokenize(s, delim, res);
    return res;
}

bool parser::is_number(const std::string &s) {
    return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

