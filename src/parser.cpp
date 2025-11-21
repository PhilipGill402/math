#include "parser.h"

//constructor
Parser::Parser(Lexer &given_lexer): lexer(given_lexer), current_token(lexer.get_next_token()) {}

//functions
void Parser::eat(TokenType type){
    if (current_token.type == type){
        current_token = lexer.get_next_token();
    } else {
        throw std::runtime_error("Unexpected token: Expected: " + token_type_to_string(type) + " Received: " + token_type_to_string(current_token.type) + "\n");  
    }
}

Program* Parser::program(){
    //TODO: hardcoded name, change this once I add support for input files
    std::string program_name = "main.math";
    std::vector<AST*> children = statement_list();

    return new Program(program_name, children);
}

AST* Parser::statement(){
    if (current_token.type == TokenType::LET){
        return variable_declaration();
    } if (current_token.type == TokenType::ID){
        return assignment_statement();
    } else {
        return empty();
    }
}

std::vector<AST*> Parser::statement_list(){
    AST* node = statement();
    std::vector<AST*> children = {node};

    while (current_token.type == TokenType::SEMI){
        eat(SEMI);
        children.push_back(statement()); 
    }

    return children;
}

Empty* Parser::empty(){
    return new Empty();
}

AST* Parser::term(){
    AST* node = factor();

    while (current_token.type == TokenType::MUL || current_token.type == DIV){
        Op* op = new Op(current_token.value); 
        if (current_token.type == TokenType::MUL){
            eat(TokenType::MUL); 
        } else {
            eat(TokenType::DIV);
        }

        AST* right = factor();
        node = new Binary_Op(node, op, right);
    }
    
    return node;
}

AST* Parser::factor(){
    if (current_token.type == TokenType::INTEGER_CONST){
        int value = stoi(current_token.value);
        eat(INTEGER_CONST);
        return new Integer(value);
    } else if (current_token.type == TokenType::FLOAT_CONST){
        double value = stod(current_token.value);
        eat(FLOAT_CONST);
        return new Float(value);
    } else if (current_token.type == TokenType::L_PAREN){
        eat(L_PAREN);
        AST* node = expr();
        eat(R_PAREN);
        return node;
    } else if (current_token.type == TokenType::ID){
        return variable();
    } else {
        throw std::runtime_error("Unexpected token in factor(): " + current_token.value);
    }
}

AST* Parser::expr(){
    AST* node = term();

    while (current_token.type == TokenType::ADD || current_token.type == TokenType::SUB){
        Op* op = new Op(current_token.value);
        if (current_token.type == TokenType::ADD){
            eat(TokenType::ADD);
        } else {
            eat(TokenType::SUB);
        }

        AST* right = term();
        node = new Binary_Op(node, op, right);
    }

    return node;
}

Var* Parser::variable(){
    Token token = current_token;
    eat(ID);
    Var* var = new Var(token);

    return var;
}

VarDecl* Parser::variable_declaration(){
    eat(TokenType::LET);
    Type* type = type_declaration();
    Var* var = variable();
    
    if (current_token.type == TokenType::ASSIGN){
        Assign* assignment = assignment_statement();

        return new VarDecl(var, type, assignment);
    }

    return new VarDecl(var, type);
}

Type* Parser::type_declaration(){
    TokenType type;
    if (current_token.type == TokenType::INT){
        type = TokenType::INT;
        eat(TokenType::INT);
    } else if (current_token.type == TokenType::FLOAT){
        type = TokenType::FLOAT;
        eat(TokenType::FLOAT);
    } else {
        throw std::runtime_error("Expected type at " + std::to_string(current_token.line) + ":" + std::to_string(current_token.col) + ". Not " + current_token.to_string());
    }

    return new Type(type);
}

Assign* Parser::assignment_statement(){
    Var* left = variable();
    Token token = left->token;
    eat(ASSIGN);
    AST* right = expr();

    return new Assign(left, token, right);
}

Program* Parser::parse(){
    return program();
}
