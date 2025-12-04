#include "Parser.h"
#include <iostream>

void Parser::program() {
    while(token != Token::END_OF_FILE) {
        statement();
        std::cout<<lexer.getLineNumber()<< "\n";
    }  
}


void Parser::statement(){

    if(token == Token::INT_KEYWORD || token == Token::BOOL_KEYWORD || token == Token::FLOAT_KEYWORD  ){
        varDecl();
    }else if (token == Token::IDENTIFIER){
        assignment();
    }else if (token == Token::IF_KEYWORD){
        ifStmt();
    }else if (token == Token::WHILE_KEYWORD){
        whileStmt();
    }else if(token == Token::PRINT_KEYWORD){
        printStmt();
    }else if (token == Token::LEFT_BRACE){
        block();
    }else{
         throw std::runtime_error(std::string("Line ") + std::to_string(lexer.getLineNumber()) + std::string(": Expected a Statement."));
    }

}

void Parser::varDecl(){
    if(token == Token::INT_KEYWORD || token == Token::BOOL_KEYWORD || token == Token::FLOAT_KEYWORD){
        token = lexer.nextToken();

        if (token == Token::IDENTIFIER){
            token = lexer.nextToken();

            if(token == Token::LEFT_SQBK){
                token = lexer.nextToken();
                //se debe validar que sea numero en semantico
                if(token == Token::NUMBER){
                    token = lexer.nextToken();

                    if(token == Token::RIGHT_SQBK){
                        token = lexer.nextToken();
                    }else{
                         throw std::runtime_error(std::string("Line ") + std::to_string(lexer.getLineNumber()) + std::string(": Expected a Right Sqaure Bracket."));
                    }
                }else{
                     throw std::runtime_error(std::string("Line ") + std::to_string(lexer.getLineNumber()) + std::string(": Expected a Number."));
                }
            }

            if(token == Token::ASSIGN){
                token = lexer.nextToken();
                expression();
            }//if aparte porque es opcional pero antes del semicolon porque no seria una declaracion
            
            if (token == Token::SEMICOLON){
                token = lexer.nextToken();
            }else{
                 throw std::runtime_error(std::string("Line ") + std::to_string(lexer.getLineNumber()) + std::string(": Expected a Semicolon."));
            }
        }else{
            throw std::runtime_error(std::string("Line ") + std::to_string(lexer.getLineNumber()) + std::string(": Expected an Identifier."));
        }
    }else{
        throw std::runtime_error(std::string("Line ") + std::to_string(lexer.getLineNumber()) + std::string(": Expected an Int Keyword."));
    }
}

void Parser::assignment(){
    if(token == Token::IDENTIFIER){
        token = lexer.nextToken();

        if(token == Token::ASSIGN){
            token = lexer.nextToken();
            expression();

            if(token == Token::SEMICOLON){
                token = lexer.nextToken();
            }else{
               throw std::runtime_error(std::string("Line ") + std::to_string(lexer.getLineNumber()) + std::string(": Expected a Semicolon."));
            }
        }else{
            throw std::runtime_error(std::string("Line ") + std::to_string(lexer.getLineNumber()) + std::string(": Expected an Equal Sign."));
        }
    }else{
        throw std::runtime_error(std::string("Line ") + std::to_string(lexer.getLineNumber()) + std::string(": Expected an Identifier."));
    }
}

void Parser::ifStmt(){
    if(token == Token::IF_KEYWORD){
        token = lexer.nextToken();

        if(token== Token::LEFT_PAREN){
            token = lexer.nextToken();
            expression();

            if(token == Token::RIGHT_PAREN){
                token = lexer.nextToken();
                statement();

                if(token == Token::ELSE_KEYWORD){
                    token = lexer.nextToken();
                    statement();
                }//no tira error porque es opcional

            }else{
                throw std::runtime_error(std::string("Line ") + std::to_string(lexer.getLineNumber()) + std::string(": Expected a Right Parenthesis."));
            }
        }else{
            throw std::runtime_error(std::string("Line ") + std::to_string(lexer.getLineNumber()) + std::string(": Expected a Left Parenthesis."));
        }
    }else{
       throw std::runtime_error(std::string("Line ") + std::to_string(lexer.getLineNumber()) + std::string(": Expected an If Keyword."));
    }

}

void Parser::whileStmt(){
    if(token == Token::WHILE_KEYWORD){
        token = lexer.nextToken();
        if(token == Token::LEFT_PAREN){
            token = lexer.nextToken();
            expression();

            if(token == Token::RIGHT_PAREN){
                token = lexer.nextToken();
                statement();

            }else{
                 throw std::runtime_error(std::string("Line ") + std::to_string(lexer.getLineNumber()) + std::string(": Expected a Right Parenthesis."));
            }
        }else{
            throw std::runtime_error(std::string("Line ") + std::to_string(lexer.getLineNumber()) + std::string(": Expected a Left Parenthesis."));
        }
    }else{
         throw std::runtime_error(std::string("Line ") + std::to_string(lexer.getLineNumber()) + std::string(": Expected a While Keyword."));
    }
}

void Parser::printStmt(){
    if(token == Token::PRINT_KEYWORD){
        token = lexer.nextToken();
        if(token == Token::LEFT_PAREN){
            token = lexer.nextToken();
            expression();

            if(token == Token::RIGHT_PAREN){
                token = lexer.nextToken();

                if(token == Token::SEMICOLON){
                    token = lexer.nextToken();
                }else{
                     throw std::runtime_error(std::string("Line ") + std::to_string(lexer.getLineNumber()) + std::string(": Expected a Semicolon."));
                }
            }else{
                throw std::runtime_error(std::string("Line ") + std::to_string(lexer.getLineNumber()) + std::string(": Expected a Right Parenthesis."));
            }
        }else{
             throw std::runtime_error(std::string("Line ") + std::to_string(lexer.getLineNumber()) + std::string(": Expected a Left Parenthesis."));
        }
    }else{
        throw std::runtime_error(std::string("Line ") + std::to_string(lexer.getLineNumber()) + std::string(": Expected a Print Keyword."));
    }

}

void Parser::block(){
    if(token == Token::LEFT_BRACE){
        token = lexer.nextToken();

        while(token != Token::RIGHT_BRACE && token != Token::END_OF_FILE){
            statement();
        }

        if (token == Token::RIGHT_BRACE) {
            token = lexer.nextToken();
        } else { // token == Token::END_OF_FILE
            throw std::runtime_error(std::string("Line ") + std::to_string(lexer.getLineNumber()) + std::string(": Expected a Right Bracket."));
        }
    }else{
        throw std::runtime_error(std::string("Line ") + std::to_string(lexer.getLineNumber()) + std::string(": Expected a Left Bracket."));
    }
}

void Parser::ternary(){
    
}

void Parser::expression(){
    logicalOr();
}

void Parser::logicalOr(){
    logicalAnd();

    //while es equvalente a 0 o mas
    while(token == Token::LOGIC_OR){
        token = lexer.nextToken();
        logicalAnd();
    }
}

void Parser::logicalAnd(){
    equality();

    while(token == Token::LOGIC_AND){
        token = lexer.nextToken();
        equality();
    }

}

void Parser::equality(){
    comparison();

    while(token == Token::EQUAL_TO || token == Token::NOT_EQUAL_TO){
        token = lexer.nextToken();
        comparison();
    }

}

void Parser::comparison(){
    term();

    while (token == Token::GREATER_EQUAL || token == Token::GREATER_THAN 
        || token == Token::LESS_EQUAL || token == Token::LESS_THAN)
    {
        token = lexer.nextToken();
        term();
    }
    

}

void Parser::term(){
    factor();

    while (token == Token::PLUS || token == Token::MINUS){
        token = lexer.nextToken();
        factor();
    }

}

void Parser::factor(){
    unary();

    while(token == Token::MULTIPLY || token == Token::DIVIDE || token == Token::MODULE){
        token = lexer.nextToken();
        unary();
    }

}

void Parser::unary(){
    if(token== Token::NOT_LOGIC || token == Token::MINUS){
        token = lexer.nextToken();
        unary();
    }else{
        primary();
    }
}

void Parser::primary(){
    if(token == Token::NUMBER){
        token = lexer.nextToken();
    }else if (token == Token::IDENTIFIER){
        token = lexer.nextToken();
    }else if (token == Token::LEFT_PAREN){
        token = lexer.nextToken();
        expression();
        if(token == Token::RIGHT_PAREN){
            token= lexer.nextToken();
        }else{
            throw std::runtime_error(std::string("Line ") + std::to_string(lexer.getLineNumber()) + std::string(": Expected a Right Parenthesis."));
        }
    }else{
        throw std::runtime_error(std::string("Line ") + std::to_string(lexer.getLineNumber()) + std::string(": Expected a Left Parenthesis, Number or Identifier."));

}
}
