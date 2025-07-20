#include "Parser.hpp"
#include <iostream>

Parser::Parser(const std::vector<Token>& tokens) : m_tokens(tokens) {}

std::vector<std::unique_ptr<lox::Stmt>> Parser::parse() {
    std::vector<std::unique_ptr<lox::Stmt>> statements;
    while (!isAtEnd()) {
        statements.push_back(statement()); // Futuramente, será declaration()
    }
    return statements;
}

// ---- Implementação das regras de precedência ----

std::unique_ptr<lox::Expr> Parser::expression() { return equality(); }

template<typename F1, typename F2>
std::unique_ptr<lox::Expr> binary_helper(F1&& next_rule, F2&& match_tokens) {
    auto expr = next_rule();
    while (match_tokens()) {
        const Token& op = previous();
        auto right = next_rule();
        expr = std::make_unique<lox::Binary>(std::move(expr), op, std::move(right));
    }
    return expr;
}

std::unique_ptr<lox::Expr> Parser::equality() {
    return binary_helper( [this] { return comparison(); }, [this] { return match({TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL}); });
}
std::unique_ptr<lox::Expr> Parser::comparison() {
    return binary_helper( [this] { return term(); }, [this] { return match({TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL}); });
}
std::unique_ptr<lox::Expr> Parser::term() {
    return binary_helper( [this] { return factor(); }, [this] { return match({TokenType::MINUS, TokenType::PLUS}); });
}
std::unique_ptr<lox::Expr> Parser::factor() {
    return binary_helper( [this] { return unary(); }, [this] { return match({TokenType::SLASH, TokenType::STAR}); });
}

std::unique_ptr<lox::Expr> Parser::unary() {
    if (match({TokenType::BANG, TokenType::MINUS})) {
        const Token& op = previous();
        auto right = unary();
        return std::make_unique<lox::Unary>(op, std::move(right));
    }
    return primary();
}

std::unique_ptr<lox::Expr> Parser::primary() {
    if (match({TokenType::FALSE})) return std::make_unique<lox::Literal>(false);
    if (match({TokenType::TRUE})) return std::make_unique<lox::Literal>(true);
    if (match({TokenType::NIL})) return std::make_unique<lox::Literal>(std::monostate{});
    if (match({TokenType::NUMBER, TokenType::STRING})) {
        return std::make_unique<lox::Literal>(previous().literal);
    }
    if (match({TokenType::LEFT_PAREN})) {
        auto expr = expression();
        consume(TokenType::RIGHT_PAREN, "Esperado ')' após a expressão.");
        return std::make_unique<lox::Grouping>(std::move(expr));
    }
    throw error(peek(), "Expressão esperada.");
}

// ---- Implementação das regras de Statements ----
std::unique_ptr<lox::Stmt> Parser::statement() {
    if (match({TokenType::PRINT})) return printStatement();
    return expressionStatement();
}

std::unique_ptr<lox::Stmt> Parser::printStatement() {
    auto value = expression();
    consume(TokenType::SEMICOLON, "Esperado ';' após o valor.");
    return std::make_unique<lox::PrintStmt>(std::move(value));
}

std::unique_ptr<lox::Stmt> Parser::expressionStatement() {
    auto expr = expression();
    consume(TokenType::SEMICOLON, "Esperado ';' após a expressão.");
    return std::make_unique<lox::ExpressionStmt>(std::move(expr));
}

