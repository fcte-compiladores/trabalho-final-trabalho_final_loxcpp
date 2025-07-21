#pragma once

#include <any> 

namespace lox {

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

    // Visitor não é mais um template.
    class Visitor {
    public:
        virtual ~Visitor() = default;

        // Métodos para visitar expressões retornam std::any.
        virtual std::any visitAssignExpr(const Assign& expr) = 0;
        virtual std::any visitBinaryExpr(const Binary& expr) = 0;
        virtual std::any visitCallExpr(const Call& expr) = 0;
        virtual std::any visitGroupingExpr(const Grouping& expr) = 0;
        virtual std::any visitLiteralExpr(const Literal& expr) = 0;
        virtual std::any visitUnaryExpr(const Unary& expr) = 0;
        virtual std::any visitVariableExpr(const Variable& expr) = 0;

        // Métodos para visitar statements retornam std::any.
        virtual std::any visitBlockStmt(const BlockStmt& stmt) = 0;
        virtual std::any visitExpressionStmt(const ExpressionStmt& stmt) = 0;
        virtual std::any visitIfStmt(const IfStmt& stmt) = 0;
        virtual std::any visitPrintStmt(const PrintStmt& stmt) = 0;
        virtual std::any visitVarStmt(const VarStmt& stmt) = 0;
        virtual std::any visitWhileStmt(const WhileStmt& stmt) = 0;
    };

} // Fim do namespace lox