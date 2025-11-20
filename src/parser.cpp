#include "parser.h"

//constructor
Parser::Parser(Lexer &given_lexer): lexer(given_lexer), current_token(lexer.get_next_token()) {}

//functions
void Parser::eat(TokenType type){
    if (current_token.type == type){
        current_token = lexer.get_next_token();
    } else {
        throw std::runtime_error("Unexpected token: Expected: " + token_type_to_string(type) + " Received: " + token_type_to_string(token.type) + "\n");  
    }
}

AST* Parser::term(){

}

AST* Parser::factor(){

}

AST* Parser::expr(){

}

Var* Parser::variable(){

}

Assign* Parser::assignment_statement(){
    eat(TokenType::LET);

    AST* left = variable();
    
    Assign*

    AST* right = term();  
}
