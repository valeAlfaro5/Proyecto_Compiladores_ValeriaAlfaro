#include "Lexer.h"

class Parser {

    public:
        Parser(Lexer &lexer_) : lexer(lexer_) {
            token = lexer.nextToken();
        }
        void program();
        
    private:
        Lexer lexer;
        Token token;
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
};