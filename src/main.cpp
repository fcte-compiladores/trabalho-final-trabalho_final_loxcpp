#include "Scanner.hpp"
#include "ast/ASTPrinter.hpp"
#include "Parser.hpp"         // Fornece lox::Parser
#include "Interpreter.hpp"    // Fornece lox::Interpreter

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

// Usa o namespace lox para evitar ter que escrever lox:: a todo momento.
using namespace lox;

// Instâncias globais para o interpretador e controle de erro.
static Interpreter interpreter;
static bool hadError = false;

void run(const std::string& source) {
    hadError = false;

    Scanner scanner(source);
    std::vector<Token> tokens = scanner.scanTokens();

    // MUDANÇA CRÍTICA: Usa lox::Parser para criar o objeto.
    Parser parser(tokens);
    auto statements = parser.parse();

    // Se o parser encontrou um erro, paramos aqui.
    if (hadError) return;

    // Descomente para ver a AST
    // std::cout << "--- AST ---\n";
    // ASTPrinter printer;
    // for(const auto& stmt : statements) {
    //     if(stmt) std::cout << printer.print(*stmt) << std::endl;
    // }
    // std::cout << "\n--- Output ---\n";

    interpreter.interpret(statements);
}

void runFile(const std::string& path) {
    std::ifstream file(path);
    if (!file) {
        std::cerr << "Could not open file: " << path << std::endl;
        exit(74);
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    run(buffer.str());
    if (hadError) exit(65);
}

void runPrompt() {
    std::string line;
    std::cout << "Lox C++ Interpreter\n";
    for (;;) {
        std::cout << "> ";
        if (!std::getline(std::cin, line)) {
            std::cout << "\n";
            break;
        }
        run(line);
    }
}

int main(int argc, char* argv[]) {
    if (argc > 2) {
        std::cout << "Usage: cpplox [script]" << std::endl;
        return 64;
    } else if (argc == 2) {
        runFile(argv[1]);
    } else {
        runPrompt();
    }
    return 0;
}