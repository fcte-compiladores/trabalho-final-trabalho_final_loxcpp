#pragma once

#include "Token.hpp"
#include "ast/Expr.hpp"
#include "ast/Stmt.hpp"
#include <vector>
#include <memory>
#include <stdexcept>

// Abre o namespace lox
namespace lox {

    class Parser {
    public:
        Parser(const std::vector<Token>& tokens);
        std::vector<std::unique_ptr<Stmt>> parse();

        class ParseError : public std::runtime_error {
        public:
            ParseError() : std::runtime_error("") {}
        };

    private:
        // --- Métodos para Regras da Gramática ---
        std::unique_ptr<Expr> expression();
        std::unique_ptr<Expr> assignment();
        std::unique_ptr<Expr> equality();
        std::unique_ptr<Expr> comparison();
        std::unique_ptr<Expr> term();
        std::unique_ptr<Expr> factor();
        std::unique_ptr<Expr> unary();
        std::unique_ptr<Expr> call();
        std::unique_ptr<Expr> primary();
        
        std::unique_ptr<Stmt> declaration();
        std::unique_ptr<Stmt> varDeclaration();
        std::unique_ptr<Stmt> statement();
        std::unique_ptr<Stmt> ifStatement();
        std::unique_ptr<Stmt> printStatement();
        std::unique_ptr<Stmt> whileStatement();
        std::unique_ptr<Stmt> expressionStatement();
        std::vector<std::unique_ptr<Stmt>> block();
        
        // --- Métodos Auxiliares do Parser ---
        
        // A função binary_helper agora é um método privado.
        template<typename F>
        std::unique_ptr<Expr> binary_helper(F&& next_rule, const std::vector<TokenType>& types);
        
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

} // Fecha o namespace lox