#include "Lexical.h"

#include <string>

void Lexical::setInput(const char *input)
{
    this->input = input;
    setPosition(0);
}

Token *Lexical::nextToken() throw (LexicalError)
{
    if ( !hasInput() )
        return NULL;

    int startLine = line;
    unsigned start = position;

    int state = 0;
    int oldState = 0;
    int endState = -1;
    int end = -1;

    while (hasInput())
    {
        oldState = state;
        state = nextState(nextChar(), state);

        if (state < 0)
            break;

        else
        {
            if (tokenForState(state) >= 0)
            {
                endState = state;
                end = position;
            }
        }
    }
    if (endState < 0 || (endState != state && tokenForState(oldState) == -2))
        throw LexicalError(SCANNER_ERROR[oldState], start, startLine);

    position = end;

    TokenId token = tokenForState(endState);

    if (token == 0)
        return nextToken();
    else
    {
        std::string lexeme = input.substr(start, end-start);
        token = lookupToken(token, lexeme);
        return new Token(token, lexeme, start, startLine);
    }
}

int Lexical::nextState(unsigned char c, int state) const
{
    int next = SCANNER_TABLE[state][c];
    return next;
}

TokenId Lexical::tokenForState(int state) const
{
    int token = -1;

    if (state >= 0 && state < STATES_COUNT)
        token = TOKEN_STATE[state];

    return static_cast<TokenId>(token);
}

TokenId Lexical::lookupToken(TokenId base, const std::string &key)
{
    int start = SPECIAL_CASES_INDEXES[base];
    int end   = SPECIAL_CASES_INDEXES[base+1]-1;

    while (start <= end)
    {
        int half = (start+end)/2;
        const std::string current = SPECIAL_CASES_KEYS[half];

        if (current == key)
            return static_cast<TokenId>(SPECIAL_CASES_VALUES[half]);
        else if (current < key)
            start = half+1;
        else  //(current > key)
            end = half-1;
    }

    return base;
}

char Lexical::nextChar()
{
    char c;
    if (hasInput())
    {
        c = input[position++];
        if (c == '\n' && position > lastPosition)
        {
            line++;
            lastPosition = position;
        }
    }
    else
    {
        c = (char) -1;
    }

    return c;
}