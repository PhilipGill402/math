#pragma once
#include <string>
#include <format>

enum TokenType{
    VAR,
    MUL,
    DIV,
    ADD,
    SUB,
    EQ,
    INTEGER_CONST,
    FLOAT_CONST,
    END_OF_FILE,
    UNKNOWN,
    ID
};

class Token{
public:
    //fields 
    TokenType type;
    std::string value;
    int line;
    int col;

    //constructor
    Token(TokenType type, std::string value, int line, int col);

    //functions
    std::string to_string();
};
