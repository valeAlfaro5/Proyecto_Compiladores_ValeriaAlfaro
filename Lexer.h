#include <string>
#include <istream>

enum class Token{
    IDENTIFIER, 
    NUMBER,
    FLOAT,
    POINT,
    END_OF_FILE,
    COMMENT,
    PLUS,//+
    MINUS,//-
    MULTIPLY,//*
    DIVIDE,// /
    ASSIGN,// =
    SEMICOLON,//;
    COMMA,//,
    LEFT_PAREN,//(
    RIGHT_PAREN,//)
    LEFT_BRACE,//{
    RIGHT_BRACE,//}
    LEFT_SQBK, //[
    RIGHT_SQBK,//]
    INT_KEYWORD,//'int'
    BOOL_KEYWORD,//'bool'
    FLOAT_KEYWORD,//'float
    RETURN_KEYWORD,
    IF_KEYWORD,//'if'
    ELSE_KEYWORD,//'else'
    WHILE_KEYWORD,//'while'
    PRINT_KEYWORD,//'print'
    BREAK_KEYWORD,//'break'
    CONTINUE_KEYWORD, //'continue'
    INPUT_KEYWORD,//'input'
    TWO_POINTS,//:
    QUESTION_MARK,//?
    MODULE,//%
    EQUAL_TO,//==
    NOT_EQUAL_TO,//!=
    LESS_THAN,//<
    GREATER_THAN,//>
    LESS_EQUAL,//<=
    GREATER_EQUAL,//>=
    LOGIC_AND,//&&
    LOGIC_OR, //||
    NOT_LOGIC,//! 
};

class Lexer {
public:
    Lexer(std::istream &in_) : in(in_) {currentChar = in.get();}
    
    std::string getText() const {return text;}

    Token nextToken();

    static const char* tokenToString(Token t);

    int getLineNumber() const { return lineNumber; }
private:
    std::istream &in;
    char currentChar;
    std::string text;
    int lineNumber = 0;
};