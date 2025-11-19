#pragma once
#include "token.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

class Lexer{
    public:
        //fields 
        const std::vector<std::string> RESERVED_KEYWORDS = {"LET", "INT_CONST", "FLOAT_CONST"};
        std::string program;
        int pos;
        int line;
        int col;
        char current_char;
        
        //constructor
        Lexer(std::string program);
        
        //functions
        void advance();
        char peek();
        Token get_next_token();
        Token id();
};
