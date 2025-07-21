#pragma once

#include "../Value.hpp"

namespace lox {

    // Forward declarations de todos os tipos de nós para evitar include circular.
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
    // Adicione outros aqui conforme for criando...

    // A classe Visitor, corretamente definida DENTRO do namespace lox
    template <typename R>
    class Visitor {
    public:
        virtual ~Visitor() = default;

        // Métodos para visitar expressões
        virtual R visitAssignExpr(const Assign& expr) = 0;
        virtual R visitBinaryExpr(const Binary& expr) = 0;
        virtual R visitCallExpr(const Call& expr) = 0;
        virtual R visitGroupingExpr(const Grouping& expr) = 0;
        virtual R visitLiteralExpr(const Literal& expr) = 0;
        virtual R visitUnaryExpr(const Unary& expr) = 0;
        virtual R visitVariableExpr(const Variable& expr) = 0;

        // Métodos para visitar statements
        virtual R visitBlockStmt(const BlockStmt& stmt) = 0;
        virtual R visitExpressionStmt(const ExpressionStmt& stmt) = 0;
        virtual R visitIfStmt(const IfStmt& stmt) = 0;
        virtual R visitPrintStmt(const PrintStmt& stmt) = 0;
        virtual R visitVarStmt(const VarStmt& stmt) = 0;
        virtual R visitWhileStmt(const WhileStmt& stmt) = 0;
    };

} // Fim do namespace lox