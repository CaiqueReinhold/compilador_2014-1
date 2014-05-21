#ifndef Syntactic_H
#define Syntactic_H

#include "Constants.h"
#include "Token.h"
#include "Lexical.h"
#include "Semantic.h"
#include "SyntacticError.h"

#include <stack>

class Syntactic
{
public:
    Syntactic() : previousToken(0), currentToken(0) { }

    ~Syntactic()
    {
        if (previousToken != 0 && previousToken != currentToken) delete previousToken;
        if (currentToken != 0)  delete currentToken;
    }

    void parse(Lexical *scanner, Semantic *semanticAnalyser) throw (AnalysisError);

private:
    std::stack<int> stack;
    Token *currentToken;
    Token *previousToken;
    Lexical *scanner;
    Semantic *semanticAnalyser;

    bool step() throw (AnalysisError);
    bool pushProduction(int topStack, int tokenInput);

    static bool isTerminal(int x) { return x < FIRST_NON_TERMINAL; }
    static bool isNonTerminal(int x) { return x >= FIRST_NON_TERMINAL && x < FIRST_SEMANTIC_ACTION; }
    static bool isSemanticAction(int x) { return x >= FIRST_SEMANTIC_ACTION; }
};

#endif
