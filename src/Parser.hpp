#pragma once

#include "Token.hpp"
#include "ast/Expr.hpp"
#include "ast/Stmt.hpp"
#include <vector>
#include <memory>
#include <stdexcept>

class Parser {
public:
    // --- Membros Públicos ---
    Parser(const std::vector<Token>& tokens);
    std::vector<std::unique_ptr<lox::Stmt>> parse();

    // MOVIDO PARA PUBLIC: A classe de erro precisa ser pública para ser capturada externamente.
    class ParseError : public std::runtime_error {
    public:
        ParseError() : std::runtime_error("") {}
    };

private:
    // --- Métodos para Regras da Gramática ---
    
    // Expressões
    std::unique_ptr<lox::Expr> expression();
    std::unique_ptr<lox::Expr> assignment();          // ADICIONADO
    std::unique_ptr<lox::Expr> equality();
    std::unique_ptr<lox::Expr> comparison();
    std::unique_ptr<lox::Expr> term();
    std::unique_ptr<lox::Expr> factor();
    std::unique_ptr<lox::Expr> unary();
    std::unique_ptr<lox::Expr> call();                // ADICIONADO
    std::unique_ptr<lox::Expr> primary();
    std::unique_ptr<lox::Expr> finishCall(std::unique_ptr<lox::Expr> callee); // ADICIONADO

    // Comandos
    std::unique_ptr<lox::Stmt> declaration();         // ADICIONADO
    std::unique_ptr<lox::Stmt> varDeclaration();      // ADICIONADO
    std::unique_ptr<lox::Stmt> statement();
    std::unique_ptr<lox::Stmt> forStatement();        // ADICIONADO
    std::unique_ptr<lox::Stmt> ifStatement();         // ADICIONADO
    std::unique_ptr<lox::Stmt> printStatement();
    std::unique_ptr<lox::Stmt> returnStatement();     // ADICIONADO
    std::unique_ptr<lox::Stmt> whileStatement();      // ADICIONADO
    std::unique_ptr<lox::Stmt> expressionStatement();
    std::vector<std::unique_ptr<lox::Stmt>> block();  // ADICIONADO
    
    // --- Métodos Auxiliares do Parser ---
    
    bool match(const std::vector<TokenType>& types);
    bool check(TokenType type) const;
    bool isAtEnd() const;
    const Token& advance();
    const Token& peek() const;
    const Token& previous() const;
    const Token& consume(TokenType type, const std::string& message);
    
    ParseError error(const Token& token, const std::string& message);
    void synchronize();

    // --- Estado do Parser ---
    const std::vector<Token>& m_tokens;
    int m_current = 0;
};