#include "Lexer.h"

enum class State {
    Q0,
    END_OF_FILE_Q1,
    NUMBER_Q1,
    IDENTIFIER_Q1,
    IDENTIFIER_Q2,
    IDENTIFIER_Q3,
    SPACES_Q1,
    EQUAL_Q1,
    GREATER_Q1,
    NOT_Q1,
    LESS_Q1,
    LOGIC_AND_Q1,
    LOGIC_OR_Q1,
    COMMENT_Q1,
    MINUS_Q1, 
    BRACKETS_Q1
};

Token Lexer::nextToken() {
    text.clear();
    State state = State::Q0;

    while (true) {
        switch (state) {
            case State::Q0:

                //que no termine el archivo
                if (currentChar == EOF){
                    state = State::END_OF_FILE_Q1;
                    
                //si es numero o empieza con negativo
                }else if ((currentChar >='0' && currentChar <= '9')){
                    text += static_cast<char>(currentChar);
                    currentChar = in.get();
                    state = State::NUMBER_Q1;
                
                //si empieza con letra a o guion bajo
                }else if ( (currentChar >='a' && currentChar <='z') ||
                        (currentChar >='A' && currentChar <='Z') || (currentChar == '_') ){
                            text += static_cast<char>(currentChar);
                            currentChar = in.get();
                            state = State::IDENTIFIER_Q1;

                //espacios, tabulaciones, saltos de linea y retornos de carro
                }else if ( currentChar == ' ' || currentChar == '\n' || currentChar =='\t' || currentChar == '\r'){
                    currentChar = in.get();
                    state = State::SPACES_Q1;
                
                    //suma
                }else if( currentChar == '+'){
                    text += static_cast<char>(currentChar);
                    currentChar = in.get();
                    return Token::PLUS;

                    //minus o negative
                }else if (currentChar == '-'){
                    text += static_cast<char>(currentChar);
                    currentChar = in.get();
                    state = State::MINUS_Q1;

                    //multiply
                }else if (currentChar == '*'){
                    text += static_cast<char>(currentChar);
                    currentChar = in.get();
                    return Token::MULTIPLY;

                    //divide o comment
                }else if (currentChar == '/'){
                    text += static_cast<char>(currentChar);
                    currentChar = in.get();
                    state = State::COMMENT_Q1;

                    //module
                }else if(currentChar == '%'){
                    text += static_cast<char>(currentChar);
                    currentChar = in.get();
                    return Token::MODULE;

                    //assign o equal to
                }else if( currentChar == '='){
                    text += static_cast<char>(currentChar);
                    currentChar = in.get();
                    state = State::EQUAL_Q1;

                    //not logic o not equal
                }else if(currentChar == '!' ){
                    text += static_cast<char>(currentChar);
                    currentChar = in.get();
                    state = State::NOT_Q1;

                    //less than o less or equal to
                } else if(currentChar =='<'){
                    text += static_cast<char>(currentChar);
                    currentChar = in.get();
                    state = State::LESS_Q1;

                    //greater than o greater or equal to
                }else if(currentChar == '>' ){
                    text += static_cast<char>(currentChar);
                    currentChar = in.get();
                    state = State::GREATER_Q1;

                    //semicolon
                }else if(currentChar == ';'){
                    text += static_cast<char>(currentChar);
                    currentChar = in.get();
                    return Token::SEMICOLON;

                    //left paren
                }else if(currentChar == '('){
                    text += static_cast<char>(currentChar);
                    currentChar = in.get();
                    return Token::LEFT_PAREN;

                    //right paren
                }else if (currentChar == ')'){
                    text += static_cast<char>(currentChar);
                    currentChar = in.get();
                    return Token::RIGHT_PAREN;

                    //left bracket
                }else if(currentChar == '{'){
                    text += static_cast<char>(currentChar);
                    currentChar = in.get();
                    return Token::LEFT_BRACE;

                    //right bracket
                }else if (currentChar == '}'){
                    text += static_cast<char>(currentChar);
                    currentChar = in.get();
                    return Token::RIGHT_BRACE;

                    //comma
                }else if (currentChar == ','){
                    text+= static_cast<char>(currentChar);
                    currentChar = in.get();
                    return Token::COMMA;

                    //inicio and
                }else if(currentChar == '&'){
                    text += static_cast<char>(currentChar);
                    currentChar = in.get();
                    state = State::LOGIC_AND_Q1;

                    //inicio or
                }else if(currentChar == '|'){
                    text += static_cast<char>(currentChar);
                    currentChar = in.get();
                    state = State::LOGIC_OR_Q1;
                }else if (currentChar == '['){
		     text += static_cast<char>(currentChar);
		     state = State::BRACKETS_Q1;
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
                    //overflow
                    try {
                        std::stoll(text); 
                    } catch (const std::out_of_range&) {
                        throw std::runtime_error("Integer literal out of int64 range: " + text);
                    }

                    return Token::NUMBER;
                }

                break;
            
            case State::IDENTIFIER_Q1:
                if (currentChar >='0' && currentChar <= '9'){
                    text += static_cast<char>(currentChar);
                    currentChar = in.get();
                    state = State::IDENTIFIER_Q2;
                }else if ( (currentChar >='a' && currentChar <='z') ||
                    (currentChar >='A' && currentChar <='Z') || (currentChar == '_') ){
                        text += static_cast<char>(currentChar);
                        currentChar = in.get();
                        state = State::IDENTIFIER_Q3;
                }else {
                   return Token::IDENTIFIER;
                }
                break;

            case State::IDENTIFIER_Q2:
                if (currentChar >='0' && currentChar <= '9'){
                    text += static_cast<char>(currentChar);
                    currentChar = in.get();
                    state = State::IDENTIFIER_Q2;
                }else if ( (currentChar >='a' && currentChar <='z') ||
                    (currentChar >='A' && currentChar <='Z') || (currentChar == '_')){
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
                    (currentChar >='A' && currentChar <='Z') || (currentChar == '_') ){
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
                if ( currentChar == ' ' || currentChar == '\n' || currentChar =='\t' || currentChar == '\r'){
                    currentChar = in.get();
                    state = State::SPACES_Q1;
                }else {
                     state = State::Q0;
                }
                break;
            
            case State::MINUS_Q1:
                //si le sigue un numero, moverlo
                if((currentChar>='0' && currentChar<='9')){
                    text += static_cast<char>(currentChar);
                    currentChar = in.get();
                    state = State::NUMBER_Q1;

                    //else solo es el signo
                }else{
                    return Token::MINUS;
                }
                break;

            case State::EQUAL_Q1:
                if(currentChar == '='){
                    text +=static_cast<char>(currentChar);
                    currentChar = in.get();
                    return Token::EQUAL_TO;
                }else{
                   return Token::ASSIGN;
                }
                break;
            
            case State::NOT_Q1:
                if(currentChar == '='){
                    text +=static_cast<char>(currentChar);
                    currentChar = in.get();
                    return Token::NOT_EQUAL_TO;
                }else{
                   return Token::NOT_LOGIC;
                }
                break;
            
            case State::GREATER_Q1:
                if(currentChar == '='){
                        text +=static_cast<char>(currentChar);
                        currentChar = in.get();
                        return Token::GREATER_EQUAL;
                }else{
                    return Token::GREATER_THAN;
                }
                break;
            
            case State::LESS_Q1:
                if(currentChar == '='){
                    text +=static_cast<char>(currentChar);
                    currentChar = in.get();
                    return Token::LESS_EQUAL;
                }else{
                   return Token::LESS_THAN;
                }
                break;
            
            
            case State::COMMENT_Q1:
                if(currentChar == '/'){
                    text += static_cast<char>(currentChar);
                    currentChar = in.get();
                    
                    //no se consume nada porque se ignora
                    while (currentChar != '\n' && currentChar != EOF) {
                        currentChar = in.get();
                    }

                    if (currentChar == '\n') {
                        currentChar = in.get();
                    }

                    //return Token::COMMENT;
                }else if (currentChar == '*'){
			//no se consume nada porque se ignora
                    while (currentChar != '/' && currentChar != EOF) {
                        currentChar = in.get();
                    }

                    if (currentChar == '\n') {
                        currentChar = in.get();
                    }

		}

		else{
                    return Token::DIVIDE;
                }
                break;

            case State::LOGIC_AND_Q1:
                if(currentChar == '&'){
                    text += static_cast<char>(currentChar);
                    currentChar = in.get();
                    return Token::LOGIC_AND;
                }else{
                    throw std::runtime_error(std::string("Invalid character '") + static_cast<char>('&') + std::string("'"));
                }
                break;
            
            case State::LOGIC_OR_Q1:
                if(currentChar== '|'){
                    text += static_cast<char>(currentChar);
                    currentChar = in.get();
                    return Token::LOGIC_OR;
                }else{
                    throw std::runtime_error(std::string("Invalid character '") + static_cast<char>('|') + std::string("'"));
                }
		break;
 	    
	     case State::BRACKETS_Q1:
		if(currentChar == '['){
		    currentChar= in.get();
			
                    while(currentChar != ']' || currentChar != EOF){

			text += static_cast<char>(currentChar);
			currentChar = in.get();
		
			}
		    
  	    	    if (currentChar == ']') {
	                text += static_cast<char>(currentChar);

                        currentChar = in.get();
                    }

                    return Token::BRACKET_IDENT;
                }else{
                    throw std::runtime_error(std::string("Invalid character '") + static_cast<char>('[') + std::string("'"));
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
    case Token::ASSIGN:
        return "ASSIGN";
    case Token::COMMA:
        return "COMMA";
    case Token::COMMENT:
        return "COMMENT";
    case Token::DIVIDE:
        return "DIVISION";
    case Token::ELSE_KEYWORD:
        return "ELSE";
    case Token::EQUAL_TO:
        return "EQUAL TO";
    case Token::GREATER_EQUAL:
        return "GREATHER THAN OR EQUAL TO";
    case Token::GREATER_THAN:
        return "GREATER THAN";
    case Token::IF_KEYWORD:
        return "IF";
    case Token::INT_KEYWORD:
        return "INT";
    case Token::LEFT_BRACE:
        return "LEFT BRACKET";
    case Token::LEFT_PAREN:
        return "LEFT PARENTHESIS";
    case Token::LESS_EQUAL:
        return "LESS THAN OR EQUAL TO";
    case Token::LESS_THAN:
        return "LESS THAN";
    case Token::LOGIC_AND:
        return "LOGIC AND";
    case Token::LOGIC_OR:
        return "LOGIC OR";
    case Token::MINUS:
        return "MINUS";
    case Token::MODULE:
        return "MODULE";
    case Token::MULTIPLY:
        return "MULTIPLY";
    case Token::NOT_EQUAL_TO:
        return "NOT EQUAL TO";
    case Token::NOT_LOGIC:
        return "NOT LOGIC";
    case Token::PLUS:
        return "PLUS";
    case Token::PRINT_KEYWORD:
        return "PRINT";
    case Token::RIGHT_BRACE:
        return "RIGHT BRACKET";
    case Token::RIGHT_PAREN:
        return "RIGHT PARENTHESIS";
    case Token::SEMICOLON:
        return "SEMICOLON";
    case Token::WHILE_KEYWORD:
        return "WHILE";
    default:
        return "UNKNOWN_TOKEN";
    }
}   