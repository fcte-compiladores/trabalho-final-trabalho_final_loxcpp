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