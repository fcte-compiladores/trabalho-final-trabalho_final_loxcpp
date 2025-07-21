#pragma once

#include "Visitor.hpp"
#include <string>
#include <any>

namespace lox {

    // Forward-declarations
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

    class ASTPrinter : public Visitor {
    public:
        std::string print(const Expr& expr);
        std::string print(const Stmt& stmt);

        // Métodos de visita
        std::any visitAssignExpr(const Assign& expr) override;
        std::any visitBinaryExpr(const Binary& expr) override;
        std::any visitCallExpr(const Call& expr) override;
        std::any visitGroupingExpr(const Grouping& expr) override;
        std::any visitLiteralExpr(const Literal& expr) override;
        std::any visitUnaryExpr(const Unary& expr) override;
        std::any visitVariableExpr(const Variable& expr) override;
        std::any visitBlockStmt(const BlockStmt& stmt) override;
        std::any visitExpressionStmt(const ExpressionStmt& stmt) override;
        std::any visitIfStmt(const IfStmt& stmt) override;
        std::any visitPrintStmt(const PrintStmt& stmt) override;
        std::any visitVarStmt(const VarStmt& stmt) override;
        std::any visitWhileStmt(const WhileStmt& stmt) override;
    };

} 