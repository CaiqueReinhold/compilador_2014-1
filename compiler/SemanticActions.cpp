#include "SemanticActions.h"
#include "Token.h"
#include "SemanticError.h"

#include <stack>
#include <sstream>

enum type
{
    INT = 1,
    FLOAT = 2,
    STRING = 3,
    BOOL = 4
};

std::stack<type> type_stack;

void verifyAritmeticTypes(const Token* token)
{
    type t1 = type_stack.top();
    type_stack.pop();
    type t2 = type_stack.top();
    type_stack.pop();

    if ((t1 != INT && t1 != FLOAT) ||
        (t2 != INT && t2 != FLOAT))
        throw SemanticError("Operador inválido em operação aritmética",
                            token->getPosition(), token->getLine());

    if (t1 == FLOAT || t2 == FLOAT)
    {
        type_stack.push(FLOAT);
    }
    else
    {
        type_stack.push(INT);
    }
}

std::string action_01(const Token* token)
{
    verifyAritmeticTypes(token);

    return "add\n";
}

std::string action_02(const Token* token)
{
    verifyAritmeticTypes(token);

    return "sub\n";
}

std::string action_03(const Token* token)
{
    verifyAritmeticTypes(token);

    return "mul\n";
}

std::string action_04(const Token* token)
{
   verifyAritmeticTypes(token);

   return "div\n";
}

std::string action_05(const Token* token)
{
    type_stack.push(INT);
    std::stringstream ss;
    ss << "ldc.i8 ";
    ss << token->getLexeme();
    ss << "\n";
    return ss.str();
}

std::string action_06(const Token* token)
{
    type_stack.push(FLOAT);
    std::stringstream ss;
    ss << "ldc.r8 ";
    ss << token->getLexeme();
    ss << "\n";
    return ss.str(); 
}

std::string action_07(const Token* token)
{
    type t1 = type_stack.top();

    if (t1 != INT && t1 != FLOAT)
        throw SemanticError("Tipo incompatível com operador '-'",
                            token->getPosition(), token->getLine());

    return "ldc.i4.m1\n"
           "mul\n";
}

std::string action_11(const Token*)
{
    type_stack.push(BOOL);
    return "ldc.i4.1\n";
}

std::string action_12(const Token*)
{
    type_stack.push(BOOL);
    return "ldc.i4.0\n";
}

std::string action_13(const Token* token)
{
	if (type_stack.top() != BOOL)
        throw SemanticError("Tipo não booleano usado com operador '!'",
                            token->getPosition(), token->getLine());

    return "not\n";
}

std::string action_14(const Token* token)
{
    type t = type_stack.top();
    type_stack.pop();

    if (t == INT)
        return "call void [mscorlib]System.Console::Write(int64)\n";
    else if (t == FLOAT)
        return "call void [mscorlib]System.Console::Write(float64)\n";
    else if (t == BOOL)
        return "call void [mscorlib]System.Console::Write(bool)\n";
    else
        return "call void [mscorlib]System.Console::Write(string)\n";
}

std::string action_15(const Token*)
{
    return ".assembly Hello {}\n"
           ".assembly extern mscorlib {}\n"
           ".class public Hello {\n"
           ".method public static void main() {\n"
           ".entrypoint\n";
}

std::string action_16(const Token*)
{
    return "ret\n}\n}\n";
}

std::string action_17(const Token*)
{
    return "ldstr \"\\n\"\ncall void [mscorlib]System.Console::Write(string)\n";
}

std::string action_18(const Token* token)
{
    type t1 = type_stack.top();
    type_stack.pop();
    type t2 = type_stack.top();
    type_stack.pop();

    if (t1 != BOOL || t2 != BOOL)
        throw SemanticError("Comparação 'ou' com tipos não booleanos",
                            token->getPosition(), token->getLine());;

    type_stack.push(BOOL);

    return "or\n";
}

std::string action_19(const Token* token)
{
    char t1 = type_stack.top();
    type_stack.pop();
    char t2 = type_stack.top();
    type_stack.pop();

    if (t1 != BOOL || t2 != BOOL)
        throw SemanticError("Comparação 'e' com tipos não booleanos",
                            token->getPosition(), token->getLine());

    type_stack.push(BOOL);

    return "and\n";
}

//used in actions 20 and 21
TokenId relationalOperator;

std::string action_20(const Token* token)
{
    relationalOperator = token->getId();
    return "";
}

std::string action_21(const Token* token)
{
    type t1 = type_stack.top();
    type_stack.pop();
    type t2 = type_stack.top();
    type_stack.pop();

    if (t1 != t2)
        throw SemanticError("Operadores de tipos diferentes em comparação relacional", 
                            token->getPosition(), token->getLine());
    else
        type_stack.push(BOOL);

    switch (relationalOperator)
    {
        case t_TOKEN_33:// ==
            return "ceq\n";
        case t_TOKEN_34:// !=
            return "ceq\n"
                   "not\n";
        case t_TOKEN_35:// <
            return "clt\n";
        case t_TOKEN_36:// <=
            return "cgt\n"
                   "not\n";
        case t_TOKEN_37:// >
            return "cgt\n";
        case t_TOKEN_38:// >=
            return "clt\n"
                   "not\n";
    }
}

std::string action_22(const Token* token)
{
    type_stack.push(STRING);
    std::stringstream ss;
    ss << "ldstr ";
    ss << token->getLexeme();
    ss << "\n";
    return ss.str();
}

std::string action_23(const Token* token)
{
    if (type_stack.top() != INT &&
        type_stack.top() != FLOAT)
        throw SemanticError("Tipo incompatível com operador '+'",
                            token->getPosition(), token->getLine());

    return "";
}