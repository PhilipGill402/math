#include "token.h"

Token::Token(TokenType given_type, std::string given_value, int given_line, int given_col){
    type = given_type;
    value = given_value;
    line = given_line;
    col = given_col;
}

std::string token_type_to_string(TokenType type){
    switch (type){
        case VAR:           return "VAR";
        case MUL:           return "MUL";
        case DIV:           return "DIV";
        case ADD:           return "ADD";
        case SUB:           return "SUB";
        case ASSIGN:        return "ASSIGN";
        case FUNCTION:      return "FUNCTION";
        case L_PAREN:       return "L_PAREN";     
        case R_PAREN:       return "R_PAREN";
        case LT:            return "LESS_THAN";
        case GT:            return "GREATER_THAN";
        case LTE:           return "LESS_THAN_EQUAL";
        case GTE:           return "GREATER_THAN_EQUAL";
        case EQUAL:         return "EQUAL";
        case NOT_EQUAL:     return "NOT_EQUAL";
        case SEMI:          return "SEMI";
        case END_OF_FILE:   return "EOF";
        case ID:            return "ID";
        case INTEGER_CONST: return "INTEGER_CONST";
        case FLOAT_CONST:   return "FLOAT_CONST";
        
        //RESERVED KEYWORDS
        case LET:           return "LET";
        case INT:           return "INT";
        case FLOAT:         return "FLOAT";

        default:            return "UNKNOWN";
    }
}

TokenType string_to_token_type(std::string type){
    if (type == "VAR"){
        return TokenType::VAR;
    } else if (type == "MUL"){
        return TokenType::MUL;
    } else if (type == "DIV"){
        return TokenType::DIV;
    } else if (type == "ADD"){
        return TokenType::ADD;
    } else if (type == "SUB"){
        return TokenType::SUB;
    } else if (type == "ASSIGN"){
        return TokenType::ASSIGN;
    } else if (type == "FUNCTION"){
        return TokenType::FUNCTION;
    } else if (type == "L_PAREN"){
        return TokenType::L_PAREN;
    } else if (type == "R_PAREN"){
        return TokenType::R_PAREN;
    } else if (type == "LT"){
        return TokenType::LT;
    } else if (type == "GT"){
        return TokenType::GT;
    } else if (type == "LTE"){
        return TokenType::LTE;
    } else if (type == "GTE"){
        return TokenType::GTE;
    } else if (type == "EQUAL"){
        return TokenType::EQUAL;
    } else if (type == "NOT_EQUAL"){
        return TokenType::NOT_EQUAL;
    } else if (type == "SEMI"){
        return TokenType::SEMI;
    } else if (type == "END_OF_FILE"){
        return TokenType::END_OF_FILE;
    } else if (type == "LET"){
        return TokenType::LET;
    } else if (type == "INTEGER_CONST"){
        return TokenType::INTEGER_CONST;
    } else if (type == "FLOAT_CONST"){
        return TokenType::FLOAT_CONST;
    } else if (type == "INT"){
        return TokenType::INT;
    } else if (type == "FLOAT"){
        return TokenType::FLOAT;
    } else {
        return TokenType::UNKNOWN;
    }
}

std::string Token::to_string(){
    return std::format("Token(Token Type: {}, Value: {}, Line: {}, Column: {})", token_type_to_string(type), value, line, col);
}
