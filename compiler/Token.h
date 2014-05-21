#ifndef TOKEN_H
#define TOKEN_H

#include "Constants.h"

#include <string>

class Token
{
public:
    Token(TokenId id, const std::string &lexeme, int position, int line)
      : id(id), lexeme(lexeme), position(position), line(line) { }

    TokenId getId() const { return id; }
    const std::string &getLexeme() const { return lexeme; }
    int getPosition() const { return position; }
    int getLine() const { return line; }

    const char* getClassName() {
    	switch (id) {
    		case t_id: return "identificador";
    		case t_const_integer: return "constante inteira";
    		case t_const_float: return "constante real";
    		case t_const_string: return "constante literal";
    		default:
    			if (id >= 6 && id <= 21)
    				return "palavra reservada";
    			else 
    				return "caracter special";
    	}
    }

private:
    TokenId id;
    std::string lexeme;
    int position;
    int line;
};

#endif