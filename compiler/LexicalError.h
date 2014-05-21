#ifndef LEXICAL_ERROR_H
#define LEXICAL_ERROR_H

#include "AnalysisError.h"

class LexicalError : public AnalysisError
{
public:

    LexicalError(const char* msg, int position, int line)
      : AnalysisError(msg, position, line) { }
};

#endif
