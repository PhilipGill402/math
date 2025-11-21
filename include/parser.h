#pragma once
#include "lexer.h"
#include "token.h"
#include "ast.h"
#include <unordered_map>
#include <string>
#include <stdexcept>

class Parser{
public:
    //fields
    Lexer &lexer;
    Token current_token;
    std::unordered_map<std::string, Token> global_variables;
    
    //constructor
    Parser(Lexer &given_lexer);

    //functions
    void eat(TokenType expected_type);
    Program* program();
    std::vector<AST*> statement_list();
    AST* statement();
    Empty* empty();
    AST* term();
    AST* factor();
    AST* expr();
    Var* variable();
    Assign* assignment_statement();
    Program* parse();
};
