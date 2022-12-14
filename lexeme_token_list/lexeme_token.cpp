#include <iostream>
#include <string>
using namespace std;

class lexeme_token
{
public:
    string lexeme;
    string token;

    lexeme_token()
    {
    }
    lexeme_token(string lexeme, string token)
    {
        this->lexeme = lexeme;
        this->token = token;
    }

    void setLexeme(string lexeme)
    {
        this->lexeme = lexeme;
    }
    void setToken(string token)
    {
        this->token = token;
    }
};