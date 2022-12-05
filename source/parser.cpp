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

void parser::split(const std::string& input_string, char delim, std::vector<std::string>& out, bool strip) {

    size_t start { 0 };
    size_t end { 0 };

    constexpr size_t npos = std::string::npos;

    while ((start = input_string.find_first_not_of(delim, end)) != npos) {
        end = input_string.find(delim, start);
        out.push_back(input_string.substr(start, end - start));
    }
}

void parser::strip(std::string &input_string) {
    unsigned int left = 0, right = input_string.size() - 1;
    while (input_string[left] == ' ') {left++;}
    while (input_string[right] == ' ') {right--;}
    input_string = input_string.substr(left, right - left + 1);
}

VecStr parser::split_to_new(const std::string &input_string, char delim, bool strip) {
    VecStr out;
    size_t start { 0 };
    size_t end { 0 };

    constexpr size_t npos = std::string::npos;

    while ((start = input_string.find_first_not_of(delim, end)) != npos) {
        end = input_string.find(delim, start);
        out.push_back(input_string.substr(start, end - start));
    }

    return out;
}
