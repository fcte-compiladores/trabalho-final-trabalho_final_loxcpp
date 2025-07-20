#pragma once

#include "ast/Visitor.hpp"
#include "ast/Expr.hpp"
#include <vector>
#include <memory>
#include "../Token.hpp" // Necessário para VarStmt, etc.

namespace lox { // <-- ADICIONADO: Início do namespace

// Classe base para todos os Statements
struct Stmt {
public:
    virtual ~Stmt() = default;
    // CORRIGIDO: Usa nosso Visitor<void> unificado. Statements não retornam valor.
    virtual void accept(Visitor<void>& visitor) const = 0;
};

// --- Classes Concretas de Statement ---

struct ExpressionStmt : public Stmt {
    const std::unique_ptr<Expr> expression;

    explicit ExpressionStmt(std::unique_ptr<Expr> expression)
        : expression(std::move(expression)) {}

    void accept(Visitor<void>& visitor) const override {
        visitor.visitExpressionStmt(*this);
    }
};

struct PrintStmt : public Stmt {
    const std::unique_ptr<Expr> expression;

    explicit PrintStmt(std::unique_ptr<Expr> expression)
        : expression(std::move(expression)) {}

    void accept(Visitor<void>& visitor) const override {
        visitor.visitPrintStmt(*this);
    }
};

struct BlockStmt : public Stmt {
    const std::vector<std::unique_ptr<Stmt>> statements;

    explicit BlockStmt(std::vector<std::unique_ptr<Stmt>> statements)
        : statements(std::move(statements)) {}

    void accept(Visitor<void>& visitor) const override {
        visitor.visitBlockStmt(*this);
    }
};

// Adicione as outras classes aqui dentro do namespace, por exemplo:
struct VarStmt : public Stmt {
    const Token name;
    const std::unique_ptr<Expr> initializer;

    VarStmt(Token name, std::unique_ptr<Expr> initializer)
        : name(std::move(name)), initializer(std::move(initializer)) {}

    void accept(Visitor<void>& visitor) const override {
        visitor.visitVarStmt(*this);
    }
};


} // <-- ADICIONADO: Fim do namespace