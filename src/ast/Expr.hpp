// src/ast/Expr.hpp
#pragma once

#include "Visitor.hpp"
#include "../Token.hpp"
#include <vector>
#include <memory> // Para std::unique_ptr

// Classe base para todas as expressões
class Expr {
public:
    virtual ~Expr() = default;
    // O método 'accept' é o que conecta a AST ao Visitor.
    virtual void accept(ExprVisitor<void>& visitor) const = 0;
};

// --- Classes Concretas de Expressão ---

struct Binary : public Expr {
    // Usamos unique_ptr para gerenciar a memória dos nós filhos automaticamente.
    std::unique_ptr<Expr> left;
    Token op;
    std::unique_ptr<Expr> right;

    Binary(std::unique_ptr<Expr> left, Token op, std::unique_ptr<Expr> right)
        : left(std::move(left)), op(std::move(op)), right(std::move(right)) {}

    void accept(ExprVisitor<void>& visitor) const override {
        visitor.visitBinaryExpr(*this);
    }
};

// Literal expression class should be outside of Binary struct
struct Literal : public Expr {
    LiteralValue value;

    explicit Literal(LiteralValue value) : value(std::move(value)) {}

    void accept(ExprVisitor<void>& visitor) const override {
        visitor.visitLiteralExpr(*this);
    }
};
//
// ... todas com seus campos e o método 'accept' correspondente.