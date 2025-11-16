#include "Lexer.h"

enum class State {
    Q0,
    END_OF_FILE_Q1,
    NUMBER_Q1,
    IDENTIFIER_Q1,
    IDENTIFIER_Q2,
    IDENTIFIER_Q3,
    SPACES_Q1
};

Token Lexer::nextToken() {
    text.clear();
    State state = State::Q0;

    while (true) {
        switch (state) {
            case State::Q0:
                if (currentChar == EOF){
                    state = State::END_OF_FILE_Q1;
                }else if (currentChar >='0' && currentChar <= '9'){
                    text += static_cast<char>(currentChar);
                    currentChar = in.get();
                    state = State::NUMBER_Q1;
                }else if ( (currentChar >='a' && currentChar <='z') ||
                        (currentChar >='A' && currentChar <='Z') ){
                            text += static_cast<char>(currentChar);
                            currentChar = in.get();
                            state = State::IDENTIFIER_Q1;
                }else if ( currentChar == ' ' || currentChar == '\n' || currentChar =='\t'){
                    text += static_cast<char>(currentChar);
                    currentChar = in.get();
                    state = State::SPACES_Q1;
                }else{
                    throw std::runtime_error(std::string("Invalid character '") + static_cast<char>(currentChar) + std::string("'"));
                }
                break;

            case State::NUMBER_Q1:
                if (currentChar >='0' && currentChar <= '9'){
                    text += static_cast<char>(currentChar);
                    currentChar = in.get();
                    state = State::NUMBER_Q1;
                }else{
                    return Token::NUMBER;
                }

                break;
            
            case State::IDENTIFIER_Q1:
                if (currentChar >='0' && currentChar <= '9'){
                    text += static_cast<char>(currentChar);
                    currentChar = in.get();
                    state = State::IDENTIFIER_Q2;
                }else if ( (currentChar >='a' && currentChar <='z') ||
                    (currentChar >='A' && currentChar <='Z') ){
                        text += static_cast<char>(currentChar);
                        currentChar = in.get();
                        state = State::IDENTIFIER_Q3;
                }else {
                    if( text == "int") {
                        return Token::INT_KEYWORD;
                    } else if (text == "if") {
                        return Token::IF_KEYWORD;
                    } else if (text == "else") {
                        return Token::ELSE_KEYWORD;
                    } else if (text == "while") {
                        return Token::WHILE_KEYWORD;
                    } else if (text == "print") {
                        return Token::PRINT_KEYWORD;
                    }else{
                        return Token::IDENTIFIER;
                    }
                }
                break;

            case State::IDENTIFIER_Q2:
                if (currentChar >='0' && currentChar <= '9'){
                    text += static_cast<char>(currentChar);
                    currentChar = in.get();
                    state = State::IDENTIFIER_Q2;
                }else if ( (currentChar >='a' && currentChar <='z') ||
                    (currentChar >='A' && currentChar <='Z') ){
                        text += static_cast<char>(currentChar);
                        currentChar = in.get();
                        state = State::IDENTIFIER_Q3;
                }else {
                    if( text == "int") {
                        return Token::INT_KEYWORD;
                    } else if (text == "if") {
                        return Token::IF_KEYWORD;
                    } else if (text == "else") {
                        return Token::ELSE_KEYWORD;
                    } else if (text == "while") {
                        return Token::WHILE_KEYWORD;
                    } else if (text == "print") {
                        return Token::PRINT_KEYWORD;
                    }else{
                        return Token::IDENTIFIER;
                    }
                }
                break;
            
            case State::IDENTIFIER_Q3:
                if (currentChar >='0' && currentChar <= '9'){
                    text += static_cast<char>(currentChar);
                    currentChar = in.get();
                    state = State::IDENTIFIER_Q2;
                }else if ( (currentChar >='a' && currentChar <='z') ||
                    (currentChar >='A' && currentChar <='Z') ){
                        text += static_cast<char>(currentChar);
                        currentChar = in.get();
                        state = State::IDENTIFIER_Q3;
                }else {
                    if( text == "int") {
                        return Token::INT_KEYWORD;
                    } else if (text == "if") {
                        return Token::IF_KEYWORD;
                    } else if (text == "else") {
                        return Token::ELSE_KEYWORD;
                    } else if (text == "while") {
                        return Token::WHILE_KEYWORD;
                    } else if (text == "print") {
                        return Token::PRINT_KEYWORD;
                    }else{
                        return Token::IDENTIFIER;
                    }
                }
                break;
            
            case State::SPACES_Q1:
                if ( currentChar == ' ' || currentChar == '\n' || currentChar =='\t'){
                    currentChar = in.get();
                    state = State::SPACES_Q1;
                }else {
                     state = State::Q0;
                }
                break;
            
            case State::END_OF_FILE_Q1:
                return Token::END_OF_FILE;
                
        }
    };
}

const char* Lexer::tokenToString(Token token)
{
    switch (token)
    {
    case Token::END_OF_FILE:
        return "END_OF_FILE";
    case Token::NUMBER:
        return "NUMBER";
    case Token::IDENTIFIER:
        return "IDENTIFIER";
    default:
        return "UNKNOWN_TOKEN";
    }
}   