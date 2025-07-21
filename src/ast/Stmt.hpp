#pragma once

#include "ast/Visitor.hpp"
#include "ast/Expr.hpp"
#include <vector>
#include <memory>
#include <any> // Incluído para std::any
#include "../Token.hpp"

namespace lox {

// Classe base para todos os Statements (comandos).
struct Stmt {
public:
    virtual ~Stmt() = default;
    // Assinatura corrigida para usar std::any e Visitor não-template.
    virtual std::any accept(Visitor& visitor) const = 0;
};

// --- Classes Concretas de Statement ---

struct ExpressionStmt : public Stmt {
    const std::unique_ptr<Expr> expression;

    explicit ExpressionStmt(std::unique_ptr<Expr> expression)
        : expression(std::move(expression)) {}

    // Assinatura corrigida
    std::any accept(Visitor& visitor) const override {
        return visitor.visitExpressionStmt(*this);
    }
};

struct PrintStmt : public Stmt {
    const std::unique_ptr<Expr> expression;

    explicit PrintStmt(std::unique_ptr<Expr> expression)
        : expression(std::move(expression)) {}

    // Assinatura corrigida
    std::any accept(Visitor& visitor) const override {
        return visitor.visitPrintStmt(*this);
    }
};

struct BlockStmt : public Stmt {
    const std::vector<std::unique_ptr<Stmt>> statements;

    explicit BlockStmt(std::vector<std::unique_ptr<Stmt>> statements)
        : statements(std::move(statements)) {}

    // Assinatura corrigida
    std::any accept(Visitor& visitor) const override {
        return visitor.visitBlockStmt(*this);
    }
};

struct VarStmt : public Stmt {
    const Token name;
    const std::unique_ptr<Expr> initializer;

    VarStmt(Token name, std::unique_ptr<Expr> initializer)
        : name(std::move(name)), initializer(std::move(initializer)) {}

    // Assinatura corrigida
    std::any accept(Visitor& visitor) const override {
        return visitor.visitVarStmt(*this);
    }
};

struct IfStmt : public Stmt {
    const std::unique_ptr<Expr> condition;
    const std::unique_ptr<Stmt> thenBranch;
    const std::unique_ptr<Stmt> elseBranch;

    IfStmt(std::unique_ptr<Expr> condition, std::unique_ptr<Stmt> thenBranch, std::unique_ptr<Stmt> elseBranch)
        : condition(std::move(condition)), thenBranch(std::move(thenBranch)), elseBranch(std::move(elseBranch)) {}

    std::any accept(Visitor& visitor) const override {
        return visitor.visitIfStmt(*this);
    }
};

struct WhileStmt : public Stmt {
    const std::unique_ptr<Expr> condition;
    const std::unique_ptr<Stmt> body;

    WhileStmt(std::unique_ptr<Expr> condition, std::unique_ptr<Stmt> body)
        : condition(std::move(condition)), body(std::move(body)) {}

    std::any accept(Visitor& visitor) const override {
        return visitor.visitWhileStmt(*this);
    }
};

} // Fim do namespace lox