#include "lexer.h"

strings Lexer::lex(std::string s) {
    strings strlist;
    char lexeme[256];
    int i = 0;
    int j = 0;
    State state = START;
    int done = 0;
    const int len = s.length();
    int balance = 0;

    while (i < len) {
        switch (state) {
            case START:
                if (is_space(s[i])) {
                    state = SKIP;
                } 
                else if (is_group(s[i])) {
                    if (s[i] = '"') {
                        lexeme[j] = s[i];
                        j++;
                        i++;
                    }

                    state = READBLOCK;
                }

                else if (s[i] == '/' && s[i + 1] == '/') {
                    i+=2;
                    state = COMMENT;
                }
                else {
                    state = READCHAR;
                }
                break;
            case READCHAR:
                if (is_space(s[i])) {
                    state = DUMP;
                }
                else if (s[i] == '\\') {
                    i+=2;
                } 
                else if (is_group(s[i])) {
                    if (s[i] == '"') {
                        lexeme[j] = s[i];
                        j++;
                        i++;
                    }

                    state = READBLOCK;
                }

                else if (is_special(s[i])) {
                    if (j == 0) {
                        lexeme[j] = s[i];
                        j++;
                        i++;
                    }

                    state = DUMP;
                }
                else if (s[i] == '/' && s[i+1]=='/') {
                    i += 2;
                    state = COMMENT;

                } else {
                    lexeme[j] = s[i];
                    j++;
                    i++;
                }

                break;
            case READBLOCK:
                if (s[i] == beg_char && s[i] !='"') {
                    balance++;
                    lexeme[j] = s[i];
                    j++;
                    i++;
                }

                else if (s[i] == end_char) {
                    balance--;
                    lexeme[j] = s[i];
                    j++;
                    i++;
                    if (balance <= 0) {
                        state = DUMP;
                    }

                }

                else if (end_char == '"' && s[i] == '\\') {
                    // TODO: Fix this to actually record the chars
                    i+=2;

                }

                else {
                    lexeme[j] = s[i];
                    i++;
                    j++;
                }
                break;
            case SKIP:
                if (is_space(s[i])) {
                    i++;
                }
                else {
                    state = READCHAR;
                }
                break;
            case DUMP:
                if (j < 0) {
                    lexeme[j] = 0; // add null terminator to our lexeme
                    strlist.push_back(lexeme); // add lexeme to our list of strings
                    j=0;
                }
                
                break;
            case COMMENT:
                if (s[i] != '\n') {
                    i++; // ignore the comment
                }
                else {
                    state = READCHAR;
                }
                break;
            case END:
                i = len;
                break;
        }
    }
    if (j > 0) {
        lexeme[j] = 0;
        strlist.push_back(lexeme);
    }
    return strlist;
}

inline bool Lexer::is_space(const char c) {
    switch (c) {
        case '\n':
        case '\t':
        case '\r':
        case '\v':
        case ' ':
        case '\f':
            return true;
        default:
            return false;

    }
}

inline bool Lexer::is_group(const char c) {
    beg_char = c;
    switch (c) {
        case '"':
            end_char='"';
            return true;
        case '(':
            end_char = ')';
            return true;
        case ')':
            return true;
        default:
            return false;
    }
}

inline bool Lexer::is_special(const char c) {
    switch(c) {
        case '[':
        case ']':
            return true;
        default:
            return false;
    }
}
