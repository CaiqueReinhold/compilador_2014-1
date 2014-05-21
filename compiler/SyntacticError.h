#ifndef SYNTACTIC_ERROR_H
#define SYNTACTIC_ERROR_H

#include "AnalysisError.h"

#include <string>

class SyntacticError : public AnalysisError
{
public:

    SyntacticError(const char* msg, int position, int line)
      : AnalysisError(msg, position, line) { }
};

#endif
