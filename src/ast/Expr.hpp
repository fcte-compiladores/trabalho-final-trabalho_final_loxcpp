#pragma once

#include "../Token.hpp"
#include "../Value.hpp"
#include "Visitor.hpp"
#include <memory>
#include <vector>

namespace lox {
    // Classe base abstrata para todas as expressões.
    struct Expr {
        virtual ~Expr() = default;
        virtual Value accept(Visitor<Value>& visitor) const = 0;
    };

    // --- Classes Concretas de Expressão ---

    struct Assign : public Expr {
        const Token name;
        const std::unique_ptr<Expr> value;

        Assign(Token name, std::unique_ptr<Expr> value)
            : name(std::move(name)), value(std::move(value)) {}

        Value accept(Visitor<Value>& visitor) const override {
            return visitor.visitAssignExpr(*this);
        }
    };

    struct Binary : public Expr {
        const std::unique_ptr<Expr> left;
        const Token op;
        const std::unique_ptr<Expr> right;

        Binary(std::unique_ptr<Expr> left, Token op, std::unique_ptr<Expr> right)
            : left(std::move(left)), op(std::move(op)), right(std::move(right)) {}

        Value accept(Visitor<Value>& visitor) const override {
            return visitor.visitBinaryExpr(*this);
        }
    };

    struct Call : public Expr {
        const std::unique_ptr<Expr> callee;
        const Token paren; // O '(', útil para reportar erros.
        const std::vector<std::unique_ptr<Expr>> arguments;

        Call(std::unique_ptr<Expr> callee, Token paren, std::vector<std::unique_ptr<Expr>> arguments)
            : callee(std::move(callee)), paren(std::move(paren)), arguments(std::move(arguments)) {}

        Value accept(Visitor<Value>& visitor) const override {
            return visitor.visitCallExpr(*this);
        }
    };

    struct Grouping : public Expr {
        const std::unique_ptr<Expr> expression;

        explicit Grouping(std::unique_ptr<Expr> expression)
            : expression(std::move(expression)) {}

        Value accept(Visitor<Value>& visitor) const override {
            return visitor.visitGroupingExpr(*this);
        }
    };

    struct Literal : public Expr {
        const Value value;

        explicit Literal(Value value) : value(std::move(value)) {}

        Value accept(Visitor<Value>& visitor) const override {
            return visitor.visitLiteralExpr(*this);
        }
    };

    struct Unary : public Expr {
        const Token op;
        const std::unique_ptr<Expr> right;

        Unary(Token op, std::unique_ptr<Expr> right)
            : op(std::move(op)), right(std::move(right)) {}

        Value accept(Visitor<Value>& visitor) const override {
            return visitor.visitUnaryExpr(*this);
        }
    };

    struct Variable : public Expr {
        const Token name;

        explicit Variable(Token name) : name(std::move(name)) {}

        Value accept(Visitor<Value>& visitor) const override {
            return visitor.visitVariableExpr(*this);
        }
    };
}