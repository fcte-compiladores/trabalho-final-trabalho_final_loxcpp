#pragma once

#include "ast/Visitor.hpp"
#include "ast/Expr.hpp"
#include "Value.hpp"
#include <vector>
#include <memory>
#include "../Token.hpp"

namespace lox {

// Classe base para todos os Statements
struct Stmt {
public:
    virtual ~Stmt() = default;
    // CORRIGIDO: Assinatura alterada para bater com o Interpreter (Visitor<Value>).
    virtual Value accept(Visitor<Value>& visitor) const = 0;
};

// --- Classes Concretas de Statement ---

struct ExpressionStmt : public Stmt {
    const std::unique_ptr<Expr> expression;

    explicit ExpressionStmt(std::unique_ptr<Expr> expression)
        : expression(std::move(expression)) {}

    // CORRIGIDO: Retorna 'Value' e aceita 'Visitor<Value>'.
    Value accept(Visitor<Value>& visitor) const override {
        return visitor.visitExpressionStmt(*this); // ADICIONADO: return
    }
};

struct PrintStmt : public Stmt {
    const std::unique_ptr<Expr> expression;

    explicit PrintStmt(std::unique_ptr<Expr> expression)
        : expression(std::move(expression)) {}

    // CORRIGIDO: Retorna 'Value' e aceita 'Visitor<Value>'.
    Value accept(Visitor<Value>& visitor) const override {
        return visitor.visitPrintStmt(*this); // ADICIONADO: return
    }
};

struct BlockStmt : public Stmt {
    const std::vector<std::unique_ptr<Stmt>> statements;

    explicit BlockStmt(std::vector<std::unique_ptr<Stmt>> statements)
        : statements(std::move(statements)) {}

    // CORRIGIDO: Retorna 'Value' e aceita 'Visitor<Value>'.
    Value accept(Visitor<Value>& visitor) const override {
        return visitor.visitBlockStmt(*this); // ADICIONADO: return
    }
};

struct VarStmt : public Stmt {
    const Token name;
    const std::unique_ptr<Expr> initializer;

    VarStmt(Token name, std::unique_ptr<Expr> initializer)
        : name(std::move(name)), initializer(std::move(initializer)) {}

    // CORRIGIDO: Retorna 'Value' e aceita 'Visitor<Value>'.
    Value accept(Visitor<Value>& visitor) const override {
        return visitor.visitVarStmt(*this); // ADICIONADO: return
    }
};


} // Fim do namespace lox