#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "Token.h"
#include "SemanticError.h"

#include <string>
#include <fstream>

class Semantic
{
public:
	Semantic(std::fstream&);
	~Semantic();
    void executeAction(int action, const Token *token) throw (SemanticError );

private:
	std::fstream& code;
};

#endif
