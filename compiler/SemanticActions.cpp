#include "SemanticActions.h"
#include "Token.h"
#include "SemanticError.h"

#include <stack>
#include <sstream>
#include <map>
#include <vector>

std::string (*actions[35])(const Token*) = 
{
    action_01,
    action_02,
    action_03,
    action_04,
    action_05,
    action_06,
    action_07,
    action_08,
    NULL,
    NULL,
    action_11,
    action_12,
    action_13,
    action_14,
    action_15,
    action_16,
    action_17,
    action_18,
    action_19,
    action_20,
    action_21,
    action_22,
    action_23,
    action_24,
    action_25,
    action_26,
    action_27,
    action_28,
    action_29,
    action_30,
    action_31,
    action_32,
    action_33,
    action_34,
    action_35
};

enum type
{
    INT = 1,
    FLOAT = 2,
    STRING = 3,
    BOOL = 4
};

std::stack<type> type_stack;

//used in actions 20 and 21
TokenId relationalOperator;

//used for id manipulation actions (24 through 30)
type idListType;
std::map<std::string, type> idTable;
std::vector<Token> tmpIds;

//used for if and do while actions (31 through 35)
unsigned labelCounter = 1;
std::stack<unsigned> labelStack;

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
        type_stack.push(FLOAT);
    else
        type_stack.push(INT);
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
    std::stringstream code;
    code << "ldc.i8 ";
    code << token->getLexeme();
    code << "\n";
    return code.str();
}

std::string action_06(const Token* token)
{
    type_stack.push(FLOAT);
    std::stringstream code;
    code << "ldc.r8 ";
    std::string tmpStr = token->getLexeme();
    tmpStr[tmpStr.find_first_of(',')] = '.';
    code << tmpStr;
    code << "\n";
    return code.str(); 
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

std::string action_08(const Token*)
{
    tmpIds.clear();
    return "";
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

    return "ldc.i4.1\n"
           "xor\n";
}

std::string action_14(const Token*)
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
    tmpIds.clear();
    idTable.clear();
    while (!type_stack.empty())
        type_stack.pop();
    while (!labelStack.empty())
        labelStack.pop();
    labelCounter = 1;

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
                   "ldc.i4.1\n"
                   "xor\n";
        case t_TOKEN_35:// <
            return "clt\n";
        case t_TOKEN_36:// <=
            return "cgt\n"
                   "ldc.i4.1\n"
                   "xor\n";
        case t_TOKEN_37:// >
            return "cgt\n";
        case t_TOKEN_38:// >=
            return "clt\n"
                   "ldc.i4.1\n"
                   "xor\n";
        default: throw 1;
    }
}

std::string action_22(const Token* token)
{
    type_stack.push(STRING);
    std::stringstream code;
    code << "ldstr ";
    code << token->getLexeme();
    code << "\n";
    return code.str();
}

std::string action_23(const Token* token)
{
    if (type_stack.top() != INT &&
        type_stack.top() != FLOAT)
        throw SemanticError("Tipo incompatível com operador '+'",
                            token->getPosition(), token->getLine());

    return "";
}

std::string action_24(const Token* token)
{
    switch (token->getId())
    {
        case t_integer: idListType = INT; break;
        case t_float: idListType = FLOAT; break;
        case t_boolean: idListType = BOOL; break;
        case t_string: idListType = STRING; break;
        default: throw SemanticError("1", token->getPosition(), token->getLine());
    }
    return "";
}

std::string action_25(const Token* token)
{
    tmpIds.push_back((*token));
    return "";
}

std::string parseType(type t)
{
    switch (t)
    {
        case INT: return "int64";
        case FLOAT: return "float64";
        case BOOL: return "bool";
        case STRING: return "string";
        default: throw 1;
    }
}

std::string action_26(const Token*)
{
    std::stringstream code;
    code << ".locals (";

    for (unsigned i = 0; i < tmpIds.size(); i++)
    {
        Token t = tmpIds[i];
        if (idTable.find(t.getLexeme()) == idTable.end())
        {
            code << parseType(idListType);
            code << " ";
            idTable[t.getLexeme()] = idListType;
            code << t.getLexeme();
            if (i+1 != tmpIds.size())
                code << ", ";
            else
                code << ")\n";
        }
        else
            throw SemanticError("2", t.getPosition(), t.getLine());
    }

    return code.str();
}

std::string action_27(const Token*)
{
    std::stringstream code;

    for (unsigned i = 0; i < tmpIds.size(); i++)
    {
        Token t = tmpIds[i];
        std::map<std::string, type>::iterator it;
        it = idTable.find(t.getLexeme());

        if (it != idTable.end())
        {
            code << "call string [mscorlib]System.Console::ReadLine()\n";
            
            if (it->second == INT)
                code << "call int64 [mscorlib]System.Int64::Parse(string)\n";
            else if (it->second == FLOAT)
                code << "call float64 [mscorlib]System.Float64::Parse(string)\n";
            else if (it->second == BOOL)
                code << "call bool [mscorlib]System.Boolean::Parse(string)\n";
            
            code << "stloc ";
            code << t.getLexeme();
            code << "\n";
        }
        else
            throw SemanticError("3", t.getPosition(), t.getLine());
    }

    tmpIds.clear();

    return code.str();
}

std::string action_28(const Token* token)
{
    std::stringstream code;
    std::map<std::string, type>::iterator it;
    it = idTable.find(token->getLexeme());

    if (it != idTable.end())
    {
        code << "ldloc ";
        code << token->getLexeme();
        code << "\n";
        type_stack.push(it->second);
    }
    else 
        throw SemanticError("4", token->getPosition(), token->getLine());

    return code.str();
}

std::string action_29(const Token*)
{
    std::stringstream code;
    std::map<std::string, type>::iterator it;
    it = idTable.find(tmpIds[0].getLexeme());

    if (it != idTable.end())
    {
        type t = type_stack.top();
        type_stack.pop();

        if (t == it->second)
        {
            code << "stloc ";
            code << tmpIds[0].getLexeme();
            code << "\n";
        }
        else
            throw SemanticError("5", tmpIds[0].getPosition(), tmpIds[0].getLine());
    }
    else
        throw SemanticError("6", tmpIds[0].getPosition(), tmpIds[0].getLine());

    tmpIds.clear();

    return code.str();
}

std::string action_30(const Token* token)
{
    std::stringstream code;

    type t = type_stack.top();
    type_stack.pop();

    if (t != idListType)
        throw SemanticError("7", token->getPosition(), token->getLine());

    for (unsigned i = 0; i < tmpIds.size(); i++)
    {
        Token t = tmpIds[i];

        if (i+1 == tmpIds.size())
        {
            code << "stloc ";
            code << t.getLexeme();
            code << "\n";
        }
        else
        {
            code << "dup\n";
            code << "stloc ";
            code << t.getLexeme();
            code << "\n";
        }
    }

    return code.str();
}

std::string action_31(const Token* token)
{
    type t = type_stack.top();
    type_stack.pop();

    if (t != BOOL)
        throw SemanticError("8", token->getPosition(), token->getLine());

    std::stringstream code;
    code << "brfalse l";
    code << labelCounter;
    code << "\n";

    labelStack.push(labelCounter++);

    return code.str();
}

std::string action_32(const Token*)
{
    unsigned label = labelStack.top();
    labelStack.pop();

    std::stringstream code;
    code << "l" << label << ": ";

    return code.str();
}

std::string action_33(const Token*)
{
    std::stringstream code;
    unsigned label = labelStack.top();
    labelStack.pop();

    code << "br l" << labelCounter << "\n";
    
    labelStack.push(labelCounter++);
    
    code << "l" << label << ": ";

    return code.str();
}

std::string action_34(const Token*)
{
    std::stringstream code;

    code << "l" << labelCounter << ": ";

    labelStack.push(labelCounter++);

    return code.str();
}

std::string action_35(const Token* token)
{
    std::stringstream code;
    type t = type_stack.top();
    type_stack.pop();

    if (t != BOOL)
        throw SemanticError("9", token->getPosition(), token->getLine());

    unsigned label = labelStack.top();
    labelStack.pop();

    code << "brtrue l" << label << "\n";

    return code.str();
}
