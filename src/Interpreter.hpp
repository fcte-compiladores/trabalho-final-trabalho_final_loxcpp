#pragma once

#include "Value.hpp"
#include "ast/Visitor.hpp"
#include <memory>
#include <vector>
#include <any>

// Forward declaration para a classe Environment no namespace GLOBAL.
// Esta é a correção principal para o erro "incomplete type".
class Environment;

namespace lox {

    // Forward declarations para todos os nós da AST DENTRO do namespace lox.
    // Expressões
    struct Assign;
    struct Binary;
    struct Call;
    struct Grouping;
    struct Literal;
    struct Unary;
    struct Variable;

    // Statements
    struct BlockStmt;
    struct ExpressionStmt;
    struct IfStmt;
    struct PrintStmt;
    struct VarStmt;
    struct WhileStmt;

    // A classe Interpreter herda de Visitor (que agora não é um template).
    class Interpreter : public Visitor {
    public:
        Interpreter();
        void interpret(const std::vector<std::unique_ptr<Stmt>>& statements);

        // --- Implementações do Visitor para Expressões ---
        // Todos os métodos de visita agora retornam std::any.
        std::any visitAssignExpr(const Assign& expr) override;
        std::any visitBinaryExpr(const Binary& expr) override;
        std::any visitCallExpr(const Call& expr) override;
        std::any visitGroupingExpr(const Grouping& expr) override;
        std::any visitLiteralExpr(const Literal& expr) override;
        std::any visitUnaryExpr(const Unary& expr) override;
        std::any visitVariableExpr(const Variable& expr) override;

        // --- Implementações do Visitor para Statements ---
        std::any visitBlockStmt(const BlockStmt& stmt) override;
        std::any visitExpressionStmt(const ExpressionStmt& stmt) override;
        std::any visitIfStmt(const IfStmt& stmt) override;
        std::any visitPrintStmt(const PrintStmt& stmt) override;
        std::any visitVarStmt(const VarStmt& stmt) override;
        std::any visitWhileStmt(const WhileStmt& stmt) override;

    private:
        friend class LoxFunction;

        // Ponteiros para os ambientes de escopo.
        // std::shared_ptr<Environment> agora se refere corretamente à classe no namespace global.
        std::shared_ptr<Environment> m_globals;
        std::shared_ptr<Environment> m_environment;

        // Funções auxiliares para avaliar e executar os nós da árvore.
        Value evaluate(const Expr& expr);
        void execute(const Stmt& stmt);
        void executeBlock(const std::vector<std::unique_ptr<Stmt>>& statements, std::shared_ptr<Environment> environment);

        // Funções de apoio à lógica da linguagem.
        bool isTruthy(const Value& value);
        bool valuesEqual(const Value& a, const Value& b);
    };

} // Fim do namespace lox