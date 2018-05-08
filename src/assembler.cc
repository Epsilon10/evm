#include <iostream>
#include <fstream>
#include "lexer.h"

typedef uint32_t u32;

std::vector<u32> compileToInstructions(strings s);
inline bool isInteger(const std::string s);
inline bool isPrimitive(const std::string s);
inline u32 mapToNumber(const std::string s);

int main(const int argc, const char *argv[]) {
    // check for input errors
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " filename" << std::endl;
        exit(1);
    }

    // read input file
    std::ifstream infile;
    infile.open(argv[1]);
    if (!infile.is_open()) {
        std::cout << "Error could not open file" << std::endl;
    } 
    std::string line;
    std::string contents;
    while(getline(infile, line)) {
        contents += line + "\n";
    }

    infile.close();

    // parse file
    Lexer lexer;
    const strings lexemes = lexer.lex(contents);

    // compile to binary
    const std::vector<u32> instructions = compileToInstructions(lexemes);

    // write to binary file
    std::ofstream ofile;
    ofile.open("out.bin", std::ios::binary);
    for (const auto& instruction: instructions) {
        ofile.write(reinterpret_cast<char *>(instruction), sizeof(u32));
    }

    ofile.close();
    return 0;


}

std::vector<u32> compileToInstructions(strings s) {
    std::vector<u32> instructions;
    for (const auto& str: s) {
        if (isInteger(str)) {
            instructions.push_back(std::stoi(str));
        }
        else {
            u32 instruction = mapToNumber(str);
            if (instruction != -1) {
                instructions.push_back(instruction);
            }

            else {
                std::cout << "invalid" << std::endl;
            }

        }
        
    }

    return instructions;

}


inline bool isInteger(const std::string s) {
    for (const auto& chr : s) {
        if (!std::isdigit(chr)) {
            return false;
        }
        
    }
    return true;
}

inline u32 mapToNumber(const std::string s) {
    if (s == "+"){
        return 0x40000001;
    } 
    else if (s == "-") {
        return 0x40000002;
    }

    else if (s == "*") {
        return 0x40000002;
    }

    else if (s == "/") {
        return 0x40000004;
    }

    return -1;

}