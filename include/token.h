#pragma once
#include <string>
#include <format>

enum TokenType{
    VAR,
    MUL,
    DIV,
    ADD,
    SUB,
    ASSIGN,
    FUNCTION,
    L_PAREN,
    R_PAREN,
    LT,
    GT,
    LTE,
    GTE,
    EQUAL,
    NOT_EQUAL,
    END_OF_FILE,
    UNKNOWN,
    ID,

    //RESERVED KEYWORDS
    LET,
    INTEGER_CONST,
    FLOAT_CONST
};

std::string token_type_to_string(TokenType type);
TokenType string_to_token_type(std::string type);

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
