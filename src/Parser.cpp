#include "Parser.hpp"
#include <iostream>
#include <vector>

// Abre o namespace lox
namespace lox {

    // A função binary_helper agora é um método da classe Parser.
    template<typename F>
    std::unique_ptr<Expr> Parser::binary_helper(F&& next_rule, const std::vector<TokenType>& types) {
        auto expr = (this->*next_rule)();
        while (match(types)) { // Agora pode chamar 'match' diretamente.
            const Token op = previous();
            auto right = (this->*next_rule)();
            expr = std::make_unique<Binary>(std::move(expr), op, std::move(right));
        }
        return expr;
    }

    Parser::Parser(const std::vector<Token>& tokens) : m_tokens(tokens) {}

    std::vector<std::unique_ptr<Stmt>> Parser::parse() {
        std::vector<std::unique_ptr<Stmt>> statements;
        while (!isAtEnd()) {
            statements.push_back(declaration());
        }
        return statements;
    }

    // --- Regras de Statement ---
    std::unique_ptr<Stmt> Parser::declaration() {
        try {
            if (match({TokenType::VAR})) return varDeclaration();
            return statement();
        } catch (ParseError& error) {
            synchronize();
            return nullptr;
        }
    }

    std::unique_ptr<Stmt> Parser::varDeclaration() {
        Token name = consume(TokenType::IDENTIFIER, "Expect variable name.");
        std::unique_ptr<Expr> initializer = nullptr;
        if (match({TokenType::EQUAL})) {
            initializer = expression();
        }
        consume(TokenType::SEMICOLON, "Expect ';' after variable declaration.");
        return std::make_unique<VarStmt>(std::move(name), std::move(initializer));
    }

    std::unique_ptr<Stmt> Parser::statement() {
        if (match({TokenType::IF})) return ifStatement();
        if (match({TokenType::PRINT})) return printStatement();
        if (match({TokenType::WHILE})) return whileStatement();
        if (match({TokenType::LEFT_BRACE})) {
            return std::make_unique<BlockStmt>(block());
        }
        return expressionStatement();
    }

    std::unique_ptr<Stmt> Parser::ifStatement() {
        consume(TokenType::LEFT_PAREN, "Expect '(' after 'if'.");
        auto condition = expression();
        consume(TokenType::RIGHT_PAREN, "Expect ')' after if condition.");
        
        auto thenBranch = statement();
        std::unique_ptr<Stmt> elseBranch = nullptr;
        if (match({TokenType::ELSE})) {
            elseBranch = statement();
        }
        
        return std::make_unique<IfStmt>(std::move(condition), std::move(thenBranch), std::move(elseBranch));
    }
    
    std::unique_ptr<Stmt> Parser::whileStatement() {
        consume(TokenType::LEFT_PAREN, "Expect '(' after 'while'.");
        auto condition = expression();
        consume(TokenType::RIGHT_PAREN, "Expect ')' after condition.");
        auto body = statement();
        
        return std::make_unique<WhileStmt>(std::move(condition), std::move(body));
    }

    std::unique_ptr<Stmt> Parser::printStatement() {
        auto value = expression();
        consume(TokenType::SEMICOLON, "Expect ';' after value.");
        return std::make_unique<PrintStmt>(std::move(value));
    }

    std::unique_ptr<Stmt> Parser::expressionStatement() {
        auto expr = expression();
        consume(TokenType::SEMICOLON, "Expect ';' after expression.");
        return std::make_unique<ExpressionStmt>(std::move(expr));
    }

    std::vector<std::unique_ptr<Stmt>> Parser::block() {
        std::vector<std::unique_ptr<Stmt>> statements;
        while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
            statements.push_back(declaration());
        }
        consume(TokenType::RIGHT_BRACE, "Expect '}' after block.");
        return statements;
    }

    // --- Regras de Expressão ---
    std::unique_ptr<Expr> Parser::expression() {
        return assignment();
    }

    std::unique_ptr<Expr> Parser::assignment() {
        auto expr = equality();
        if (match({TokenType::EQUAL})) {
            Token equals = previous();
            auto value = assignment();
            if (auto* var = dynamic_cast<Variable*>(expr.get())) {
                return std::make_unique<Assign>(var->name, std::move(value));
            }
            error(equals, "Invalid assignment target.");
        }
        return expr;
    }

    std::unique_ptr<Expr> Parser::equality() {
        return binary_helper(&Parser::comparison, {TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL});
    }

    std::unique_ptr<Expr> Parser::comparison() {
        return binary_helper(&Parser::term, {TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL});
    }

    std::unique_ptr<Expr> Parser::term() {
        return binary_helper(&Parser::factor, {TokenType::MINUS, TokenType::PLUS});
    }

    std::unique_ptr<Expr> Parser::factor() {
        return binary_helper(&Parser::unary, {TokenType::SLASH, TokenType::STAR});
    }

    std::unique_ptr<Expr> Parser::unary() {
        if (match({TokenType::BANG, TokenType::MINUS})) {
            Token op = previous();
            auto right = unary();
            return std::make_unique<Unary>(std::move(op), std::move(right));
        }
        return primary();
    }

    std::unique_ptr<Expr> Parser::primary() {
        if (match({TokenType::FALSE})) return std::make_unique<Literal>(Value{false});
        if (match({TokenType::TRUE})) return std::make_unique<Literal>(Value{true});
        if (match({TokenType::NIL})) return std::make_unique<Literal>(Value{std::monostate{}});
        
        if (match({TokenType::NUMBER, TokenType::STRING})) {
            // LiteralValue (de Token) é um std::variant compatível com lox::Value
            // mas o construtor de Literal espera um lox::Value.
            // A conversão direta é possível se os tipos no variant forem os mesmos.
            return std::make_unique<Literal>(previous().literal);
        }

        if (match({TokenType::IDENTIFIER})) {
            return std::make_unique<Variable>(previous());
        }

        if (match({TokenType::LEFT_PAREN})) {
            auto expr = expression();
            consume(TokenType::RIGHT_PAREN, "Expect ')' after expression.");
            return std::make_unique<Grouping>(std::move(expr));
        }

        throw error(peek(), "Expect expression.");
    }
    
    // O resto dos métodos auxiliares aqui...
    // (check, isAtEnd, advance, peek, previous, consume, error, synchronize)
    bool Parser::match(const std::vector<TokenType>& types) {
        for (TokenType type : types) {
            if (check(type)) {
                advance();
                return true;
            }
        }
        return false;
    }
    
    const Token& Parser::consume(TokenType type, const std::string& message) {
        if (check(type)) return advance();
        throw error(peek(), message);
    }
    
    bool Parser::check(TokenType type) const {
        if (isAtEnd()) return false;
        return peek().type == type;
    }
    
    const Token& Parser::advance() {
        if (!isAtEnd()) m_current++;
        return previous();
    }
    
    bool Parser::isAtEnd() const {
        return peek().type == TokenType::END_OF_FILE;
    }
    
    const Token& Parser::peek() const {
        return m_tokens.at(m_current);
    }
    
    const Token& Parser::previous() const {
        return m_tokens.at(m_current - 1);
    }
    
    Parser::ParseError Parser::error(const Token& token, const std::string& message) {
        // Lox::error(token, message); // Futuramente
        std::cerr << "[line " << token.line << "] Error";
        if (token.type == TokenType::END_OF_FILE) {
            std::cerr << " at end";
        } else {
            std::cerr << " at '" << token.lexeme << "'";
        }
        std::cerr << ": " << message << std::endl;
        return ParseError();
    }
    
    void Parser::synchronize() {
        advance();
        while (!isAtEnd()) {
            if (previous().type == TokenType::SEMICOLON) return;
            switch (peek().type) {
                case TokenType::CLASS:
                case TokenType::FUN:
                case TokenType::VAR:
                case TokenType::FOR:
                case TokenType::IF:
                case TokenType::WHILE:
                case TokenType::PRINT:
                case TokenType::RETURN:
                    return;
                default:
                    // Do nothing
                    break;
            }
            advance();
        }
    }


} // Fecha o namespace lox