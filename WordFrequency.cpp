/*
 Name - Vaishnavi Jaligama
 Student Id- 1936593
 Cruz id - vjaligam
 Course - CSE101
 Quarter - Winter 2024
 Professor - Mr. Patrick Tantalo
 Programming assignment - 8
 Due date - March 13th, 2024
 File name - WordFrequency.cpp
*/

#include "Dictionary.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>

std::string toLower(const std::string& str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return lowerStr;
}

void tokenizeAndUpdate(const std::string& line, Dictionary& dict) {
    std::string delimiters = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";
    size_t start = line.find_first_not_of(delimiters), end = 0;

    while ((end = line.find_first_of(delimiters, start)) != std::string::npos) {
        if (start != end) {
            std::string word = toLower(line.substr(start, end - start));
            if (!dict.contains(word)) {
                dict.setValue(word, 1);
            } else {
                dict.getValue(word) += 1;
            }
        }
        start = line.find_first_not_of(delimiters, end);
    }
    if (start != std::string::npos) {
        std::string word = toLower(line.substr(start));
        if (!dict.contains(word)) {
            dict.setValue(word, 1);
        } else {
            dict.getValue(word) += 1;
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input file> <output file>\n";
        return EXIT_FAILURE;
    }

    std::ifstream inFile(argv[1]);
    if (!inFile.is_open()) {
        std::cerr << "Unable to open file " << argv[1] << " for reading\n";
        return EXIT_FAILURE;
    }

    std::ofstream outFile(argv[2]);
    if (!outFile.is_open()) {
        std::cerr << "Unable to open file " << argv[2] << " for writing\n";
        return EXIT_FAILURE;
    }

    Dictionary wordFreq;
    std::string line;

    while (getline(inFile, line)) {
        tokenizeAndUpdate(line, wordFreq);
    }

    inFile.close();
    outFile << wordFreq.to_string();
    outFile.close();

    return EXIT_SUCCESS;
}
