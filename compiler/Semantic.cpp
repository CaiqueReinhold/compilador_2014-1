#include "Semantic.h"
#include "Constants.h"

#include <iostream>

void Semantic::executeAction(int action, const Token *token) throw (SemanticError )
{
    std::cout << "A��o: " << action << ", Token: "  << token->getId() 
              << ", Lexema: " << token->getLexeme() << std::endl;
}
