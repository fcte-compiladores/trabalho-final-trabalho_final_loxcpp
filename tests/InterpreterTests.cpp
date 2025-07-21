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