#pragma once
#include "token.h"
#include <string>
#include <vector>

//AST base class, everything inherits cfrom here
class AST{
public:
    //virtual destructor, allows for polymorphism 
    virtual ~AST() = default;
};

//AST node for operators
class Op : public AST{
public:
    std::string op;

    Op(std::string given_op);
};

//AST Base class, all constants inherit from here
class Value : public AST{
public:
    //polymorphic to_string() helper function for debugging
    virtual std::string to_string() const = 0;

    //virtual destructor, allows for polymorphism
    virtual ~Value() = default;
};

//AST base class, all numbers inherit from here
class Num : public Value{
public:
    //fields
    double num;
    bool is_float = false;

    //constructors
    Num(double val);
    Num(double val, bool given_is_real);
    
    //virtual destructor, allows for polymorphism
    virtual ~Num() = default;
};

//AST node for integer constants
class Integer : public Num{
public:
    Integer(int val);
    std::string to_string() const override;
};

//AST node for float constants
class Float : public Num{
public:
    Float(double val);
    std::string to_string() const override;
};

//AST node for the whole program
class Program : public AST{
public:
    std::string program_name;
    std::vector<AST*> statements = {};

    Program(std::string give_name, std::vector<AST*>& given_statements);
};

//AST node for binary operations
class Binary_Op : public AST{
public:
    AST* left;
    Op* op;
    AST* right;

    Binary_Op(AST* given_left, Op* given_op, AST* given_right);
};

//AST node for variables
class Var : public AST{
public:
    Token token;
    std::string type;

    Var(Token given_token);
};

//AST node for types
class Type : public AST{
public:
    TokenType type;

    Type(TokenType given_type);
};

//AST node for assignment of variables
class Assign : public AST{
public: 
    AST* left;
    Token token;
    AST* right;

    Assign(AST* given_left, Token given_token, AST* given_right);
};

//AST node for variable declaration
class VarDecl : public AST{
public:
    Var* var;
    Type* type;
    AST* val = nullptr; 

    VarDecl(Var* given_var, Type* given_type);
    VarDecl(Var* given_var, Type* given_type, AST* val);
};

//re-evaluate: is it needed??
class Function : public AST{
public: 
    Token token;
    Type* type;

    Function(Token given_token, Type* given_type);
};

class Param : public AST{
public:
    std::string name;
    Type* type;

    Param(std::string given_name, Type* given_type);
};

//AST node for assignment of functions
class FunctionDecl : public AST{
public:
    std::string name;
    std::vector<Param*> parameters;
    Type* return_type;
    //need to add parsing to make this usuable
    std::string value;

    FunctionDecl(std::string given_name, std::vector<Param*> &given_parameters, Type* given_return_type, std::string given_value);
};

class Empty : public AST{};
