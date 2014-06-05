#ifndef LEXICAL_ERROR_H
#define LEXICAL_ERROR_H

#include "AnalysisError.h"

#include <sstream>

class LexicalError : public AnalysisError
{
public:

    LexicalError(const char* msg, int position, int line, char s)
      : AnalysisError(msg, position, line), symbol(s) { }

      const char* getMessage() const {
      	std::stringstream msg;

      	msg << "Erro na Linha " << getLine() << ": ";

      	const char* error_msg = AnalysisError::getMessage(); 
        if (error_msg == SCANNER_ERROR[0]) {
            msg << symbol << " ";
        }

        msg << error_msg;

        return msg.str().c_str();
      }

private:
	char symbol;
};

#endif
