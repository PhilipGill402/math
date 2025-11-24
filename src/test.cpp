#include "lexer.h"
#include "parser.h"
#include "interpreter.h"

int main(){
    std::string program = 
        "fn f(x: int)->int: x^2+2x+1;"
        "\0"
        ;
    Lexer lexer = Lexer(program);
    Parser parser = Parser(lexer);
    Program* program_node = parser.parse();
    Interpreter interpreter = Interpreter(program_node);
    interpreter.visit(interpreter.tree);

    std::cout << interpreter.functions[0]->value << "\n";
}
