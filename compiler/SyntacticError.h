#ifndef SYNTACTIC_ERROR_H
#define SYNTACTIC_ERROR_H

#include "AnalysisError.h"
#include "Token.h"

#include <sstream>

class SyntacticError : public AnalysisError
{
public:

    SyntacticError(const char* msg, Token *t)
      : AnalysisError(msg, t->getPosition(), t->getLine()),
      	token(t) { }

    const char* getMessage() const {
    	std::stringstream msg;

    	msg << "Erro na Linha " << getLine() << ":";
    	if (token->getId() <= DOLLAR) {
    		//if EPSILON or DOLLAR
    		msg << " encontrado fim de programa ";
    	} else if (token->getId() <= t_const_string) {
    		//if id, const_int, const_float or const_string
    		msg << " encontrado " << token->getClassName() << 
    			   " (" << token->getLexeme() << ") ";
    	} else {
            //reserved words or especial symbols
    		msg << " encontrado " << token->getLexeme() << " ";
    	}

    	msg << AnalysisError::getMessage();

    	return msg.str().c_str();
    }

private:
	Token *token;
};

#endif
