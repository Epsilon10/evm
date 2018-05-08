#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <vector>

typedef uint8_t byte;
typedef std::vector<std::string> strings;

enum State: byte {
    START,
    READCHAR,
    READBLOCK,
    SKIP,
    DUMP,
    COMMENT,
    END
};

class Lexer {
    private:
        inline bool is_space(const char c);
        inline bool is_special(const char c);
        inline bool is_group(const char c);
        char end_char, beg_char;
    public:
        strings lex(std::string s);
};

#endif
