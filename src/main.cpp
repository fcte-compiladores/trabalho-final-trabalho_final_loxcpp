#include "Scanner.hpp"
#include "Token.hpp"
#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
    if (argc > 1) {
        std::cout << "Uso: lox_cpp [script]" << std::endl;
        return 1;
    }

    std::cout << "LoxCpp - Iniciado" << std::endl;

    // Testando o esqueleto do Scanner
    Scanner scanner("var a = 1;");
    std::vector<Token> tokens = scanner.scanTokens();

    std::cout << "Scanner produziu " << tokens.size() << " token(s)." << std::endl;

    return 0;
}