#!/bin/bash
# (Conteúdo do script de setup_tests.sh atualizado e corrigido)
# Este script cria e preenche os arquivos de teste para o projeto LoxCpp.
# Deve ser executado a partir da raiz do projeto.

# Garante que a pasta de testes exista
mkdir -p tests
cd tests

echo "Gerando ScannerTests.cpp..."
cat > ScannerTests.cpp << 'EOF'
#include <gtest/gtest.h>
#include "Scanner.hpp"
#include "Token.hpp"
#include <vector>

TEST(ScannerTests, TestVariableDeclaration) {
    std::string source = "var language = \"Lox\";";
    Scanner scanner(source);
    std::vector<Token> tokens = scanner.scanTokens();

    ASSERT_EQ(tokens.size(), 6);
    EXPECT_EQ(tokens[0].type, TokenType::VAR);
    EXPECT_EQ(tokens[1].type, TokenType::IDENTIFIER);
    EXPECT_EQ(tokens[2].type, TokenType::EQUAL);
    EXPECT_EQ(tokens[3].type, TokenType::STRING);
    EXPECT_EQ(std::get<std::string>(tokens[3].literal), "Lox");
    EXPECT_EQ(tokens[4].type, TokenType::SEMICOLON);
    EXPECT_EQ(tokens[5].type, TokenType::END_OF_FILE);
}

TEST(ScannerTests, TestArithmeticOperators) {
    std::string source = "1 + 2 * (3 - 4) / 5";
    Scanner scanner(source);
    std::vector<Token> tokens = scanner.scanTokens();

    std::vector<TokenType> expected_types = {
        TokenType::NUMBER, TokenType::PLUS, TokenType::NUMBER, TokenType::STAR,
        TokenType::LEFT_PAREN, TokenType::NUMBER, TokenType::MINUS, TokenType::NUMBER,
        TokenType::RIGHT_PAREN, TokenType::SLASH, TokenType::NUMBER, TokenType::END_OF_FILE
    };

    ASSERT_EQ(tokens.size(), expected_types.size());

    for (size_t i = 0; i < tokens.size(); ++i) {
        EXPECT_EQ(tokens[i].type, expected_types[i]);
    }
}

TEST(ScannerTests, TestAllSingleCharTokens) {
    std::string source = "(){},.-+;*/!<=>";
    Scanner scanner(source);
    std::vector<Token> tokens = scanner.scanTokens();

    std::vector<TokenType> expected_types = {
        TokenType::LEFT_PAREN, TokenType::RIGHT_PAREN, TokenType::LEFT_BRACE,
        TokenType::RIGHT_BRACE, TokenType::COMMA, TokenType::DOT, TokenType::MINUS,
        TokenType::PLUS, TokenType::SEMICOLON, TokenType::STAR, TokenType::SLASH,
        TokenType::BANG, TokenType::LESS, TokenType::GREATER, TokenType::EQUAL,
        TokenType::END_OF_FILE
    };

    ASSERT_EQ(tokens.size(), expected_types.size());
    // CORREÇÃO: O loop deve ir até o final (i < expected_types.size())
    for (size_t i = 0; i < expected_types.size(); ++i) {
        EXPECT_EQ(tokens[i].type, expected_types[i]);
    }
}

TEST(ScannerTests, TestTwoCharTokens) {
    std::string source = "!= == <= >=";
    Scanner scanner(source);
    std::vector<Token> tokens = scanner.scanTokens();

    std::vector<TokenType> expected_types = {
        TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL,
        TokenType::LESS_EQUAL, TokenType::GREATER_EQUAL,
        TokenType::END_OF_FILE
    };

    ASSERT_EQ(tokens.size(), expected_types.size());
    for (size_t i = 0; i < expected_types.size(); ++i) {
        EXPECT_EQ(tokens[i].type, expected_types[i]);
    }
}

TEST(ScannerTests, TestCommentsAndLineNumbers) {
    std::string source =
        "var a = 1;\n"
        "// this is a comment\n"
        "var b = 2;\n"
        "// another one";
    Scanner scanner(source);
    std::vector<Token> tokens = scanner.scanTokens();

    ASSERT_EQ(tokens.size(), 11);
    EXPECT_EQ(tokens[0].line, 1);
    EXPECT_EQ(tokens[4].line, 1);
    EXPECT_EQ(tokens[5].line, 3);
    EXPECT_EQ(tokens[9].line, 3);
    EXPECT_EQ(tokens[10].line, 4);
}

TEST(ScannerTests, TestKeywords) {
    std::string source = "and class else false for fun if nil or print return super this true var while";
    Scanner scanner(source);
    std::vector<Token> tokens = scanner.scanTokens();
    
    std::vector<TokenType> expected_types = {
        TokenType::AND, TokenType::CLASS, TokenType::ELSE, TokenType::FALSE, TokenType::FOR,
        TokenType::FUN, TokenType::IF, TokenType::NIL, TokenType::OR, TokenType::PRINT,
        TokenType::RETURN, TokenType::SUPER, TokenType::THIS, TokenType::TRUE,
        TokenType::VAR, TokenType::WHILE, TokenType::END_OF_FILE
    };

    ASSERT_EQ(tokens.size(), expected_types.size());
    for (size_t i = 0; i < expected_types.size(); ++i) {
        EXPECT_EQ(tokens[i].type, expected_types[i]);
    }
}
EOF

echo "Gerando ParserTests.cpp..."
cat > ParserTests.cpp << 'EOF'
#include <gtest/gtest.h>
#include "Scanner.hpp"
#include "Parser.hpp"
#include "ast/ASTPrinter.hpp"
#include <vector>
#include <string>

std::string parseAndPrint(const std::string& source) {
    lox::ASTPrinter printer;
    Scanner scanner(source);
    std::vector<Token> tokens = scanner.scanTokens();
    lox::Parser parser(tokens);
    auto statements = parser.parse();
    if (!statements.empty()) {
        std::string result;
        for (const auto& stmt : statements) {
            if (stmt) {
                result += printer.print(*stmt);
            }
        }
        if (!result.empty()) return result;
    }
    return "Error or empty statement";
}

TEST(ParserTests, TestPrintStatement) {
    std::string source = "print 1 + 2;";
    std::string expected_ast = "(print (+ 1 2))";
    EXPECT_EQ(parseAndPrint(source), expected_ast);
}

TEST(ParserTests, TestVariableDeclaration) {
    std::string source = "var name = \"Bianca\";";
    std::string expected_ast = "(var name = Bianca)";
    EXPECT_EQ(parseAndPrint(source), expected_ast);
}

TEST(ParserTests, TestIfStatement) {
    std::string source = "if (x > 10) print true;";
    std::string expected_ast = "(if (> x 10) (print true))";
    EXPECT_EQ(parseAndPrint(source), expected_ast);
}

TEST(ParserTests, TestWhileStatement) {
    std::string source = "while (x < 10) print x;";
    std::string expected_ast = "(while (< x 10) (print x))";
    EXPECT_EQ(parseAndPrint(source), expected_ast);
}

TEST(ParserTests, TestBlockStatement) {
    std::string source = "{ var a = 1; print a + 2; }";
    std::string expected_ast = "(block (var a = 1) (print (+ a 2)))";
    EXPECT_EQ(parseAndPrint(source), expected_ast);
}

TEST(ParserTests, TestInvalidAssignmentTarget) {
    std::string source = "1 + 2 = 3;";
    EXPECT_EQ(parseAndPrint(source), "Error or empty statement");
}
EOF

echo "Gerando InterpreterTests.cpp..."
cat > InterpreterTests.cpp << 'EOF'
#include <gtest/gtest.h>
#include "Scanner.hpp"
#include "Parser.hpp"
#include "Interpreter.hpp"
#include "Value.hpp"
#include <string>
#include <vector>
#include <sstream>

void runInterpreter(const std::string& source, std::stringstream& buffer) {
    std::streambuf* old_cout = std::cout.rdbuf(buffer.rdbuf());
    std::streambuf* old_cerr = std::cerr.rdbuf(buffer.rdbuf());

    lox::Interpreter interpreter;
    Scanner scanner(source);
    std::vector<Token> tokens = scanner.scanTokens();
    lox::Parser parser(tokens);
    auto statements = parser.parse();
    interpreter.interpret(statements);

    std::cout.rdbuf(old_cout);
    std::cerr.rdbuf(old_cerr);
}

TEST(InterpreterTests, TestPrintOutput) {
    std::stringstream buffer;
    runInterpreter("print 3 * (2 + 1);", buffer);
    EXPECT_EQ(buffer.str(), "9\n");
}

TEST(InterpreterTests, TestVariableScope) {
    std::stringstream buffer;
    std::string source =
        "var a = \"global a\";"
        "var b = \"global b\";"
        "{"
        "  var a = \"outer a\";"
        "  print a;"
        "  print b;"
        "  b = \"outer b\";"
        "  {"
        "    print a;"
        "    print b;"
        "  }"
        "}"
        "print a;"
        "print b;";

    runInterpreter(source, buffer);
    
    std::string expected_output =
        "outer a\n"
        "global b\n"
        "outer a\n"
        "outer b\n"
        "global a\n"
        "outer b\n";

    EXPECT_EQ(buffer.str(), expected_output);
}

TEST(InterpreterTests, TestTruthiness) {
    std::stringstream buffer;
    runInterpreter("if (nil) print \"no\"; else print \"yes\";", buffer);
    runInterpreter("if (false) print \"no\"; else print \"yes\";", buffer);
    runInterpreter("if (true) print \"yes\"; else print \"no\";", buffer);
    runInterpreter("if (0) print \"yes\"; else print \"no\";", buffer);
    runInterpreter("if (\"\") print \"yes\"; else print \"no\";", buffer);

    std::string expected_output = "yes\nyes\nyes\nyes\nyes\n";
    EXPECT_EQ(buffer.str(), expected_output);
}

TEST(InterpreterTests, TestIfElseStatement) {
    std::stringstream buffer;
    std::string source =
        "var n = 5;"
        "if (n > 10) {"
        "  print \"maior\";"
        "} else {"
        "  print \"menor\";"
        "}";
    runInterpreter(source, buffer);
    EXPECT_EQ(buffer.str(), "menor\n");
}

TEST(InterpreterTests, TestWhileLoop) {
    std::stringstream buffer;
    std::string source =
        "var i = 0;"
        "while (i < 3) {"
        "  print i;"
        "  i = i + 1;"
        "}";
    runInterpreter(source, buffer);
    std::string expected_output = "0\n1\n2\n";
    EXPECT_EQ(buffer.str(), expected_output);
}

TEST(InterpreterTests, TestRuntimeErrorDivisionByZero) {
    std::stringstream buffer;
    runInterpreter("print 10 / 0;", buffer);
    EXPECT_NE(buffer.str().find("Division by zero."), std::string::npos);
}

TEST(InterpreterTests, TestRuntimeErrorInvalidOperand) {
    std::stringstream buffer;
    runInterpreter("print 5 + \"cinco\";", buffer);
    EXPECT_NE(buffer.str().find("Operands must be two numbers or two strings."), std::string::npos);
}

TEST(InterpreterTests, TestRuntimeErrorUndefinedVariable) {
    std::stringstream buffer;
    runInterpreter("print variavel_inexistente;", buffer);
    EXPECT_NE(buffer.str().find("Undefined variable"), std::string::npos);
}
EOF

echo "Arquivos de teste gerados com sucesso na pasta 'tests/'!"