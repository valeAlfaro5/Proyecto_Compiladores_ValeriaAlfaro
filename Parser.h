#include "Lexer.h"

class Parser {
    friend class Lexer;

    public:
        Parser();

        void program();
        void statement();
        void varDecl();
        void assignment();
        void ifStmt();
        void whileStmt();
        void printStmt();
        void block();
        void expression();
        void logicalOr();
        void logicalAnd();
        void equality();
        void comparison();
        void term();
        void factor();
        void unary();
        void primary();

    private:
        Lexer lexer;
        Token token;
}