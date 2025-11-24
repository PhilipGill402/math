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
Type::Type(TokenType given_type) : type(given_type) {};
VarDecl::VarDecl(Var* given_var, Type* given_type) : var(given_var), type(given_type) {};
VarDecl::VarDecl(Var* given_var, Type* given_type, AST* give_val) : var(given_var), type(given_type), val(give_val) {};
Assign::Assign(AST* given_left, Token given_token, AST* given_right) : left(given_left), token(given_token), right(given_right) {};
FunctionDecl::FunctionDecl(std::string given_name, std::vector<Param*> &given_parameters, Type* given_return_type, std::string given_value) : name(given_name), parameters(given_parameters), return_type(given_return_type), value(given_value) {};
Function::Function(Token given_token, Type* given_type) : token(given_token), type(given_type) {};
Param::Param(std::string given_name, Type* given_type) : name(given_name), type(given_type) {};

//helper functions
std::string Integer::to_string() const {
    return std::to_string(static_cast<int>(num));
}

std::string Float::to_string() const {
    return std::to_string(num);
}
