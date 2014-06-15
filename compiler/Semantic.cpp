#include "Semantic.h"
#include "Constants.h"
#include "SemanticActions.h"

#include <iostream>

Semantic::Semantic(std::fstream& output) :
    code(output)
{
}

Semantic::~Semantic()
{
}

void Semantic::executeAction(int action, const Token *token) throw (SemanticError)
{
    code << actions[action-1](token);
}
