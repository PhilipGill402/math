#include "lexer.h"

int main(){
    std::string program = "let x = 10 + 9\0";
    Lexer lexer = Lexer(program);

    std::cout << lexer.current_char << "\n";

    Token token = lexer.get_next_token();
    while (token.value != "EOF"){
        std::cout << token.to_string() << "\n";
        token = lexer.get_next_token();
    }
}
