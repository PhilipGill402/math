#include "lexer.h"

Lexer::Lexer(std::string given_program){
    program = given_program;
    int pos = 0;
    int line = 1;
    int col = 1;
    char current_char = program.empty() ? '\0' : program[0];
    std::cout << current_char << "\n";
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


    }

    if (current_char == '\0'){
        return Token(TokenType::END_OF_FILE, "EOF", line, col);
    } else {
        return Token(TokenType::UNKNOWN, "Unknown", line, col);
    }
}

Token Lexer::id(){
    std::string val;
    int currline = line;
    int currcol = col;

    while (isalnum(current_char)){
        val += current_char;
        advance();
    }

    //TODO: check reserved keywords
    
    return Token(TokenType::ID, val, currline, currcol);
}
