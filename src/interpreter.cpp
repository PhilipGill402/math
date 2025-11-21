#include"interpreter.h"

Interpreter::Interpreter(AST* root) : tree(root) {};

AST* Interpreter::visit(AST* node){
    if (auto program = dynamic_cast<Program*>(node)){
        return visit_program(program);
    } else if (auto integer = dynamic_cast<Integer*>(node)){
        return new Integer(visit_integer(integer)); 
    } else if (auto num = dynamic_cast<Float*>(node)){
        return new Float(visit_float(num));
    } else if (auto binary_op = dynamic_cast<Binary_Op*>(node)){
        return visit_binary_op(binary_op);
    } else if (auto var = dynamic_cast<Var*>(node)){
        return visit_var(var);
    } else if (auto assign = dynamic_cast<Assign*>(node)){
        return visit_assign(assign);
    } else if (auto empty = dynamic_cast<Empty*>(node)){
        return visit_empty(empty); 
    } else {
        throw std::runtime_error("Unsupported node in in 'visit'");
    }
}



AST* Interpreter::visit_program(Program* node){
    for (AST* statement : node->statements){
        visit(statement);
    }

    return new Empty();
}


int Interpreter::visit_integer(Integer* node){
    return node->num;
}

double Interpreter::visit_float(Float* node){
    return node->num;
}

Value* Interpreter::visit_binary_op(Binary_Op* node){
    if (!node->left || !node->right){
        throw std::runtime_error("Either the left or right node is null in 'visit_binary_op'");
    }

    if (dynamic_cast<Num*>(visit(node->left)) && dynamic_cast<Num*>(visit(node->right))){
        return visit_num_binary_op(node);
    } else {
        throw std::runtime_error("Unsupported types in either the left or right node in 'visit_binary_op'");
    }
}

Value* Interpreter::visit_num_binary_op(Binary_Op* node){
    Num* left = dynamic_cast<Num*>(node->left);
    Num* right = dynamic_cast<Num*>(node->right);

    if (!left || !right){
        throw std::runtime_error("Either the left value or right value in the binary op is not a number in 'visit_num_binary_op'");
    }
    
    double result = 0.0;

    if (node->op->op == "+"){
        result = left->num + right->num; 
    } else if (node->op->op == "-"){
        result = left->num - right->num;
    } else if (node->op->op == "/"){
        result = left->num / right->num;
    } else if (node->op->op == "*"){
        result = left->num * right->num;
    } else{
        throw std::runtime_error("Operator " + node->op->op + "not recognized in 'visit_num_binary_op'");
    }

    if (left->is_float || right->is_float){
        return new Float(result);
    } else {
        return new Integer(static_cast<int>(result));
    }
}


AST* Interpreter::visit_var(Var* node){
    std::string var_name = node->token.value;
    Value* val = variables.at(var_name);

    return val;
}

AST* Interpreter::visit_assign(Assign* node){
    Var* var = dynamic_cast<Var*>(node->left);
    Value* val = dynamic_cast<Value*>(node->right);

    if (!var){
        throw std::runtime_error("Left side of assignment statement is not a variable in 'visit_assign'");
    } else if (!val){
        throw std::runtime_error("Right side of assignment statement is not a value in 'visit_assign'");
    }

    std::string var_name = var->token.value;
    variables.insert({var_name, val});
    
    return new Empty();
}


AST* Interpreter::visit_empty(Empty* node){
    return new Empty();
}


