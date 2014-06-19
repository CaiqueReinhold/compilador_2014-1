#ifndef SEMANTIC_ERROR_H
#define SEMANTIC_ERROR_H

#include "AnalysisError.h"

#include <string>
#include <sstream>

class SemanticError : public AnalysisError
{
public:

    SemanticError(const char* msg, int position, int line)
      : AnalysisError(msg, position, line) { }

    const char* getMessage() const
    {
    	std::stringstream msg;
    	msg << "Erro na linha " << getLine() << ": ";
    	msg << AnalysisError::getMessage();

    	return msg.str().c_str();
    }
};

#endif
