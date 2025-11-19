#include "lexer.h"

int main(){
    std::string program = "let x = 10 + 9\0";
    Lexer lexer = Lexer(program);

    Token token = lexer.get_next_token();
    while (token.value != "EOF"){
        std::cout << token.to_string() << "\n";
        token = lexer.get_next_token();
    }
}
