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
        case EQ:            return "EQ";
        case INTEGER_CONST: return "INTEGER_CONST";
        case FLOAT_CONST:   return "FLOAT_CONST";
        case END_OF_FILE:   return "EOF";
        case ID:            return "ID";
        default:            return "UNKNOWN";
    }
}

std::string Token::to_string(){
    return std::format("Token(Token Type: {}, Value: {}, Line: {}, Column: {})", token_type_to_string(type), value, line, col);
}
