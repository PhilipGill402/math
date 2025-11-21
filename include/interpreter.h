#pragma once
#include "ast.h"
#include <string>
#include <unordered_map>

#include <iostream>

class Interpreter{
public:
    //fields
    AST* tree;
    std::unordered_map<std::string, Value*> variables = {}; 

    //constructor
    Interpreter(AST* root);
    
    //functions
    AST* visit(AST* node);
    AST* visit_program(Program* node);
    int visit_integer(Integer* node);
    double visit_float(Float* node);
    Value* visit_binary_op(Binary_Op* node);
    Value* visit_num_binary_op(Binary_Op* node);
    AST* visit_var(Var* node);
    AST* visit_assign(Assign* node);
    AST* visit_empty(Empty* node);
};
