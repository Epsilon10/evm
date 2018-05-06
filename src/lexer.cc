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

                else if (end_char == '"') 
                break;
            case SKIP:
                break;
            case DUMP:
                break;
            case COMMENT:
                break;
            case END:
                break;
        }
    }
    return strlist;
}

