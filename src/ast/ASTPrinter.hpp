#pragma once

#include "Visitor.hpp"
#include <string>

// Forward-declare as classes para evitar dependências circulares de includes
namespace lox {
    struct Expr;
    struct Stmt;
}

class ASTPrinter : public lox::Visitor<std::string> {
public:
    // ADICIONE OU VERIFIQUE ESTAS DUAS LINHAS:
    std::string print(const lox::Expr& expr);
    std::string print(const lox::Stmt& stmt);

    // Métodos para visitar expressões
    std::string visitAssignExpr(const lox::Assign& expr) override;
    std::string visitBinaryExpr(const lox::Binary& expr) override;
    std::string visitCallExpr(const lox::Call& expr) override;
    std::string visitGroupingExpr(const lox::Grouping& expr) override;
    std::string visitLiteralExpr(const lox::Literal& expr) override;
    std::string visitUnaryExpr(const lox::Unary& expr) override;
    std::string visitVariableExpr(const lox::Variable& expr) override;

    // Métodos para visitar statements
    std::string visitBlockStmt(const lox::BlockStmt& stmt) override;
    std::string visitExpressionStmt(const lox::ExpressionStmt& stmt) override;
    std::string visitPrintStmt(const lox::PrintStmt& stmt) override;
    std::string visitVarStmt(const lox::VarStmt& stmt) override;
    // Adicione os outros (If, While) quando for implementá-los
    std::string visitIfStmt(const lox::IfStmt& stmt) override { return ""; }
    std::string visitWhileStmt(const lox::WhileStmt& stmt) override { return ""; }

private:
    template<typename... Args>
    std::string parenthesize(const std::string& name, const Args&... parts);
};