#ifndef LEXICAL_H
#define LEXICAL_H

#include "Token.h"
#include "LexicalError.h"

#include <string>

class Lexical
{
public:
    Lexical(const char *input = "") : line(1), lastPosition(0) { setInput(input); }

    void setInput(const char *input);
    void setPosition(unsigned pos) { position = pos; }
    Token *nextToken() throw (LexicalError);

private:
    unsigned position;
    std::string input;
    int line;
    int lastPosition;

    int nextState(unsigned char c, int state) const;
    TokenId tokenForState(int state) const;
    TokenId lookupToken(TokenId base, const std::string &key);

    bool hasInput() const { return position < input.size(); }
    char nextChar();
};

#endif