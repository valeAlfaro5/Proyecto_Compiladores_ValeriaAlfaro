#include <fstream>
#include <iostream>
// #include "Lexer.h"
#include "Parser.h"

int main(int argc, char* argv[]) { 
  if (argc != 2) {
    std::cerr << "Missing argument\n";
    return 1;
  }

  std::ifstream in(argv[1]);

  if (!in) {
    std::cerr << "Could not open file\n";
    return 1;
  }

   std::cout << "\n--- Parsing ---\n";
  try {
      // std::cout << "\n--- Lexing ---\n";
    // Token token = lexer.nextToken();
    // while(token != Token::END_OF_FILE) {
    //   std::cout << "Token: " << Lexer::tokenToString(token) << ", Text: " << lexer.getText() << "\n";
    //   token = lexer.nextToken();
    // }
      Lexer lexer(in);
      Parser parser(lexer);
      parser.program();
      std::cout << "Parsing completed successfully.\n";
      
  } catch (const std::runtime_error& e) {
      std::cerr << e.what() << std::endl;
      return 1;
  }

  in.close();

  return 0;
}
