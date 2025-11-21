#include "lexer.h"

Lexer::Lexer(std::string given_program){
    program = given_program;
    pos = 0;
    line = 1;
    col = 1;
    current_char = program.empty() ? '\0' : program[0];
}
        
void Lexer::advance(){
    pos++;
    if (pos < program.length()){
        if (current_char == '\n'){
            line++;
            col = 0;
            current_char = program[pos];
        } else {
            current_char = program[pos];
            col++;
        }
    } else {
        current_char = '\0';
    }
}

char Lexer::peek(){
    if (pos+1 >= program.length()){
        return '\0';
    }

    return program[pos+1];
};

Token Lexer::get_next_token(){
    while (current_char != '\0'){
        //whitespace 
        if (isspace(current_char)){
            advance();
            continue;
        }
        
        //comments
        if (current_char == '#'){
            while (current_char != '\n'){
                advance();
            }
            advance();
            continue;
        }

        //numbers
        if (isdigit(current_char)){
            int currline = line;
            int currcol = col;
            std::string val; 

            while (isdigit(current_char)){
                val += current_char;
                advance();
            }

            if (current_char == '.'){
                val += current_char;
                
                while (isdigit(current_char)){
                    val += current_char;
                    advance();
                }

                return Token(TokenType::FLOAT_CONST, val, currline, currcol);
            } else {
                return Token(TokenType::INTEGER_CONST, val, currline, currcol);
            }
        }

        //keywords / var names
        if (isalpha(current_char)){
            return id();
        }   
        
        int currline = line;
        int currcol = col;

        switch (current_char){
            case '=':
                advance();
                if (current_char == '='){
                    advance();
                    return Token(TokenType::EQUAL, "==", currline, currcol);
                } else {
                    return Token(TokenType::ASSIGN, "=", currline, currcol);
                }
            case '+':
                advance();
                return Token(TokenType::ADD, "+", currline, currcol);
            case '-':
                advance();
                return Token(TokenType::SUB, "-", currline, currcol);
            case '*':
                advance();
                return Token(TokenType::MUL, "*", currline, currcol);
            case '/':
                advance();
                return Token(TokenType::DIV, "/", currline, currcol);
            case '<':
                advance();
                if (current_char == '='){
                    advance();
                    return Token(TokenType::LTE, "<=", currline, currcol);
                } else {
                    return Token(TokenType::LT, "<", currline, currcol);
                }
            case '>':
                advance();
                if (current_char == '='){
                    advance();
                    return Token(TokenType::GTE, ">=", currline, currcol);
                } else {
                    return Token(TokenType::LT, ">", currline, currcol);
                }
            case '(':
                advance();
                return Token(TokenType::L_PAREN, "(", currline, currcol);
            case ')':
                advance();
                return Token(TokenType::R_PAREN, ")", currline, currcol);
            case ';':
                advance();
                return Token(TokenType::SEMI, ";", currline, currcol);
            default:
                advance();
                return Token(TokenType::UNKNOWN, "Unknown", currline, currcol);
        }
    }

    //we reached the end of the file 
    return Token(TokenType::END_OF_FILE, "EOF", line, col);
}

std::string toUpper(std::string str){
    std::string new_str;
    for (int i = 0; i < str.length(); i++){
        new_str += toupper(str[i]);
    }

    return new_str;
}

Token Lexer::id(){
    std::string val;
    int currline = line;
    int currcol = col;

    while (isalnum(current_char)){
        val += current_char;
        advance();
    }
    
    //if the value is in the keywords
    std::string upper_val = toUpper(val);

    if (find(RESERVED_KEYWORDS.begin(), RESERVED_KEYWORDS.end(), upper_val) != RESERVED_KEYWORDS.end()){
        TokenType type = string_to_token_type(upper_val);
        return Token(type, upper_val, currline, currcol);
    } 
    
    return Token(TokenType::ID, val, currline, currcol);
}
