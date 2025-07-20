// src/ast/Stmt.hpp
#pragma once

#include "Visitor.hpp"
#include "Expr.hpp" // Stmt pode conter Expr
#include <vector>
#include <memory>

// Classe base para todos os Statements
class Stmt {
public:
    virtual ~Stmt() = default;
    virtual void accept(StmtVisitor& visitor) const = 0;
};

// --- Classes Concretas de Statement ---

struct ExpressionStmt : public Stmt {
    std::unique_ptr<Expr> expression;

    explicit ExpressionStmt(std::unique_ptr<Expr> expression)
        : expression(std::move(expression)) {}

    void accept(StmtVisitor& visitor) const override {
        visitor.visitExpressionStmt(*this);
    }
};

struct PrintStmt : public Stmt {
    std::unique_ptr<Expr> expression;

    explicit PrintStmt(std::unique_ptr<Expr> expression)
        : expression(std::move(expression)) {}

    void accept(StmtVisitor& visitor) const override {
        visitor.visitPrintStmt(*this);
    }
};

struct BlockStmt : public Stmt {
    std::vector<std::unique_ptr<Stmt>> statements;

    explicit BlockStmt(std::vector<std::unique_ptr<Stmt>> statements)
        : statements(std::move(statements)) {}

    void accept(StmtVisitor& visitor) const override {
        visitor.visitBlockStmt(*this);
    }
};

// ... defina aqui todas as outras classes que herdam de Stmt (Var, If, While, Fun, etc.)