#include "Scanner.hpp"
#include "Parser.hpp"
#include "ast/ASTPrinter.hpp"
#include <iostream>
#include <string>
#include <vector>

void run(const std::string& source) {
    try {
        Scanner scanner(source);
        std::vector<Token> tokens = scanner.scanTokens();
        
        std::cout << "--- TOKENS ---" << std::endl;
        for (const auto& token : tokens) {
            std::cout << token.toString() << std::endl;
        }

        Parser parser(tokens);
        auto statements = parser.parse();

        // Se o parser falhou, ele pode retornar um vetor com nullptr
        if (statements.empty() || statements[0] == nullptr) {
            std::cout << "\nParse falhou ou não produziu statements." << std::endl;
            return;
        }

        std::cout << "\n--- ARVORE SINTATICA (AST) ---" << std::endl;
        ASTPrinter printer;
        for (const auto& stmt : statements) {
            std::cout << printer.print(*stmt) << std::endl;
        }

    } catch (const Parser::ParseError& error) {
        std::cerr << "Erro de Parse capturado." << std::endl;
    }
}

int main() {
    // Coloque o código que você quer testar aqui
    std::string test_code = "var language = \"Lox\"; print language;";

    std::cout << "Executando codigo de teste:\n" << test_code << std::endl;
    std::cout << "--------------------------\n" << std::endl;
    run(test_code);

    return 0;
}