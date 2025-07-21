#pragma once

#include "Value.hpp"
#include "Visitor.hpp"
#include <memory>  // Para std::shared_ptr, std::unique_ptr
#include <vector>  // Para std::vector

// Forward declarations para evitar includes circulares
namespace lox {
    class Environment;
    struct Expr;
    struct Stmt;
    struct Assign;
    struct Binary;
    struct Call;
    struct Grouping;
    struct Literal;
    struct Unary;
    struct Variable;
    struct BlockStmt;
    struct ExpressionStmt;
    struct IfStmt;
    struct PrintStmt;
    struct VarStmt;
    struct WhileStmt;
}

namespace lox {

class Interpreter : public Visitor<Value> {
public:
    Interpreter();
    void interpret(const std::vector<std::unique_ptr<Stmt>>& statements);

    // --- Implementações do Visitor para Expressões ---
    Value visitAssignExpr(const Assign& expr) override;
    Value visitBinaryExpr(const Binary& expr) override;
    Value visitCallExpr(const Call& expr) override;
    Value visitGroupingExpr(const Grouping& expr) override;
    Value visitLiteralExpr(const Literal& expr) override;
    Value visitUnaryExpr(const Unary& expr) override;
    Value visitVariableExpr(const Variable& expr) override;

    // --- Implementações do Visitor para Statements ---
    Value visitBlockStmt(const BlockStmt& stmt) override;
    Value visitExpressionStmt(const ExpressionStmt& stmt) override;
    Value visitIfStmt(const IfStmt& stmt) override;
    Value visitPrintStmt(const PrintStmt& stmt) override;
    Value visitVarStmt(const VarStmt& stmt) override;
    Value visitWhileStmt(const WhileStmt& stmt) override;

private:
    friend class LoxFunction; // Permite que LoxFunction acesse o ambiente do interpretador
    
    // Ponteiros inteligentes para gerenciar os ambientes de escopo
    std::shared_ptr<Environment> m_globals;
    std::shared_ptr<Environment> m_environment;

    // Funções auxiliares para avaliar e executar os nós da árvore
    Value evaluate(const Expr& expr);
    void execute(const Stmt& stmt);
    void executeBlock(const std::vector<std::unique_ptr<Stmt>>& statements, std::shared_ptr<Environment> environment);

    // Funções de apoio à lógica da linguagem
    bool isTruthy(const Value& value);
    bool valuesEqual(const Value& a, const Value& b);
};

} // Fim do namespace lox