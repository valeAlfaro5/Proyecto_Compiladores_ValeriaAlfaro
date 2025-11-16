#include <string>
#include <istream>

enum class Token{
    IDENTIFIER, 
    NUMBER,
    END_OF_FILE
};

class Lexer {
public:
    Lexer(std::istream &in_) : in(in_) {currentChar = in.get();}
    
    std::string getText() const {return text;}

    Token nextToken();

    static const char* tokenToString(Token t);
private:
    std::istream &in;
    char currentChar;
    std::string text;
};