#include "ast.h"

//constructors
Op::Op(std::string given_op) : op(given_op) {};
Num::Num(double val): num(val) {};
Num::Num(double val, bool given_is_float): num(val), is_float(given_is_float) {};
Integer::Integer(int val) : Num(val) {};
Float::Float(double val) : Num(val, true) {};
Program::Program(std::string given_name, std::vector<AST*> &given_statements) : program_name(given_name), statements(given_statements) {};
Binary_Op::Binary_Op(AST* given_left, Op* given_op, AST* given_right) : left(given_left), op(given_op), right(given_right) {};
Var::Var(Token given_token) : token(given_token) {};
Assign::Assign(AST* given_left, Token given_token, AST* given_right) : left(given_left), token(given_token), right(given_right) {};

//helper functions
std::string Integer::to_string() const {
    return std::to_string(static_cast<int>(num));
}

std::string Float::to_string() const {
    return std::to_string(num);
}
