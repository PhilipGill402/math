#include "lexer.h"
#include "parser.h"
#include "interpreter.h"

int main(){
    std::string program = "let x = 10 + 9;\0";
    Lexer lexer = Lexer(program);
    Parser parser = Parser(lexer);
    Program* program_node = parser.parse();
    Interpreter interpreter = Interpreter(program_node);

    interpreter.visit(interpreter.tree);

    std::cout << interpreter.variables.at("=") << "\n";
}
