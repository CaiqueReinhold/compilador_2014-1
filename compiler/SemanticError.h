#ifndef SEMANTIC_ERROR_H
#define SEMANTIC_ERROR_H

#include "AnalysisError.h"

#include <string>

class SemanticError : public AnalysisError
{
public:

    SemanticError(const char* msg, int position, int line)
      : AnalysisError(msg, position, line) { }
};

#endif
