/*
 Name - Vaishnavi Jaligama
 Student Id- 1936593
 Cruz id - vjaligam
 Course - CSE101
 Quarter - Winter 2024
 Professor - Mr. Patrick Tantalo
 Programming assignment - 8
 Due date - March 13th, 2024
 File name - Order.cpp
*/

#include "Dictionary.h"
#include <fstream>
#include <iostream>
#include <string>

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

    Dictionary dict;
    std::string line;
    int lineNum = 0;

    while (getline(inFile, line)) {
        lineNum++; 
        dict.setValue(line, lineNum); 
    }

    inFile.close();

    outFile << dict.to_string();

    outFile << dict.pre_string(); 

    outFile.close();

    return EXIT_SUCCESS;
}
