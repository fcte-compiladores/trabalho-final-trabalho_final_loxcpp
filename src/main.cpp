#include "Scanner.hpp"
#include "ast/ASTPrinter.hpp"
#include "Parser.hpp"
#include "Interpreter.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace lox;

static Interpreter interpreter;
static bool hadError = false;

void run(const std::string& source, bool printAst) {
    hadError = false;

    Scanner scanner(source);
    std::vector<Token> tokens = scanner.scanTokens();

    Parser parser(tokens);
    auto statements = parser.parse();

    if (hadError) return;

    if (printAst) {
        std::cout << "--- AST ---\n";
        ASTPrinter printer;
        for (const auto& stmt : statements) {
            if (stmt) {
                std::cout << printer.print(*stmt) << std::endl;
            }
        }
        std::cout << "\n--- Output ---\n";
    }

    interpreter.interpret(statements);
}

void runFile(const std::string& path, bool printAst) {
    std::ifstream file(path);
    if (!file) {
        std::cerr << "Could not open file: " << path << std::endl;
        exit(74);
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    run(buffer.str(), printAst);
    if (hadError) exit(65);
}

void runPrompt(bool printAst) {
    std::string line;
    std::cout << "Lox C++ Interpreter\n";
    for (;;) {
        std::cout << "> ";
        if (!std::getline(std::cin, line)) {
            std::cout << "\n";
            break;
        }
        run(line, printAst);
    }
}

int main(int argc, char* argv[]) {
    bool printAst = false;
    std::string filePath;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--print-ast") {
            printAst = true;
        } else {
            if (!filePath.empty()) {
                std::cout << "Usage: cpplox [--print-ast] [script]" << std::endl;
                return 64;
            }
            filePath = arg;
        }
    }

    if (!filePath.empty()) {
        runFile(filePath, printAst);
    } else {
        runPrompt(printAst);
    }

    return 0;
}