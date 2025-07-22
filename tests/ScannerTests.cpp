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
    std::string source = "(){},.-+;*/! < = >";
    Scanner scanner(source);
    std::vector<Token> tokens = scanner.scanTokens();

    std::vector<TokenType> expected_types = {
        TokenType::LEFT_PAREN, TokenType::RIGHT_PAREN, TokenType::LEFT_BRACE,
        TokenType::RIGHT_BRACE, TokenType::COMMA, TokenType::DOT, TokenType::MINUS,
        TokenType::PLUS, TokenType::SEMICOLON, TokenType::STAR, TokenType::SLASH,
        TokenType::BANG, TokenType::LESS, TokenType::EQUAL, TokenType::GREATER,
        TokenType::END_OF_FILE
    };

    ASSERT_EQ(tokens.size(), expected_types.size());
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