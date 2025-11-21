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
    SEMI,
    END_OF_FILE,
    UNKNOWN,
    ID,
    INTEGER_CONST,
    FLOAT_CONST,

    //RESERVED KEYWORDS
    LET,
    INT,
    FLOAT
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
