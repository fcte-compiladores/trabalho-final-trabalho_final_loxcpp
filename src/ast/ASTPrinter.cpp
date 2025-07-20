#include "ast/ASTPrinter.hpp"
#include "ast/Expr.hpp"
#include "ast/Stmt.hpp"
#include "Value.hpp"

#include <sstream>
#include <string>
#include <variant>

// Métodos públicos para iniciar a impressão
std::string ASTPrinter::print(const lox::Expr& expr) {
//    return expr.accept(*this); // ta dando erro, ver o que é 
}

std::string ASTPrinter::print(const lox::Stmt& stmt) {
   // return stmt.accept(*this); // ta dando erro, ver o que é 
}

// --- Implementações dos Métodos para Expressões ---

std::string ASTPrinter::visitAssignExpr(const lox::Assign& expr) {
    return parenthesize("= " + expr.name.lexeme, *expr.value);
}

std::string ASTPrinter::visitBinaryExpr(const lox::Binary& expr) {
    return parenthesize(expr.op.lexeme, *expr.left, *expr.right);
}

std::string ASTPrinter::visitCallExpr(const lox::Call& expr) {
    // Para simplificar, vamos imprimir apenas o nome da função chamada.
    return parenthesize("call", *expr.callee);
}

std::string ASTPrinter::visitGroupingExpr(const lox::Grouping& expr) {
    return parenthesize("group", *expr.expression);
}

std::string ASTPrinter::visitLiteralExpr(const lox::Literal& expr) {
    if (std::holds_alternative<std::monostate>(expr.value)) return "nil";
    if (std::holds_alternative<std::string>(expr.value)) return "\"" + std::get<std::string>(expr.value) + "\"";
    if (std::holds_alternative<double>(expr.value)) return std::to_string(std::get<double>(expr.value));
    if (std::holds_alternative<bool>(expr.value)) return std::get<bool>(expr.value) ? "true" : "false";
    return "unknown literal";
}

std::string ASTPrinter::visitUnaryExpr(const lox::Unary& expr) {
    return parenthesize(expr.op.lexeme, *expr.right);
}

std::string ASTPrinter::visitVariableExpr(const lox::Variable& expr) {
    return expr.name.lexeme;
}

// --- Implementações dos Métodos para Statements ---

std::string ASTPrinter::visitBlockStmt(const lox::BlockStmt& stmt) {
    std::stringstream ss;
    ss << "(block";
    for (const auto& statement : stmt.statements) {
        ss << " " << print(*statement);
    }
    ss << ")";
    return ss.str();
}

std::string ASTPrinter::visitExpressionStmt(const lox::ExpressionStmt& stmt) {
    return parenthesize(";", *stmt.expression);
}

std::string ASTPrinter::visitPrintStmt(const lox::PrintStmt& stmt) {
    return parenthesize("print", *stmt.expression);
}

std::string ASTPrinter::visitVarStmt(const lox::VarStmt& stmt) {
    if (stmt.initializer == nullptr) {
        return parenthesize("var " + stmt.name.lexeme);
    }
    return parenthesize("var " + stmt.name.lexeme + " =", *stmt.initializer);
}