#include "ASTPrinter.hpp"
#include "Expr.hpp"
#include "Stmt.hpp"
#include "../Value.hpp"

#include <sstream>
#include <string>
#include <vector>
#include <any>

// Abre o namespace lox para todo o arquivo
namespace lox {

    // --- Implementação dos Métodos Públicos ---

    std::string ASTPrinter::print(const Expr& expr) {
        return std::any_cast<std::string>(expr.accept(*this));
    }

    std::string ASTPrinter::print(const Stmt& stmt) {
        return std::any_cast<std::string>(stmt.accept(*this));
    }

    // --- Implementações dos Métodos de Visita ---

    std::any ASTPrinter::visitAssignExpr(const Assign& expr) {
        return "(assign " + expr.name.lexeme + " = " + print(*expr.value) + ")";
    }

    std::any ASTPrinter::visitBinaryExpr(const Binary& expr) {
        return "(" + expr.op.lexeme + " " + print(*expr.left) + " " + print(*expr.right) + ")";
    }

    std::any ASTPrinter::visitCallExpr(const Call& expr) {
        return "(call " + print(*expr.callee) + ")";
    }

    std::any ASTPrinter::visitGroupingExpr(const Grouping& expr) {
        return "(group " + print(*expr.expression) + ")";
    }

    std::any ASTPrinter::visitLiteralExpr(const Literal& expr) {
        return valueToString(expr.value);
    }

    std::any ASTPrinter::visitUnaryExpr(const Unary& expr) {
        return "(" + expr.op.lexeme + " " + print(*expr.right) + ")";
    }

    std::any ASTPrinter::visitVariableExpr(const Variable& expr) {
        return expr.name.lexeme;
    }

    std::any ASTPrinter::visitBlockStmt(const BlockStmt& stmt) {
        std::stringstream ss;
        ss << "(block";
        for (const auto& statement : stmt.statements) {
            ss << " " << print(*statement);
        }
        ss << ")";
        return ss.str();
    }

    std::any ASTPrinter::visitExpressionStmt(const ExpressionStmt& stmt) {
        return "(; " + print(*stmt.expression) + ")";
    }

    std::any ASTPrinter::visitIfStmt(const IfStmt& stmt) {
        std::string ifStr = "(if " + print(*stmt.condition) + " " + print(*stmt.thenBranch);
        if (stmt.elseBranch != nullptr) {
            ifStr += " else " + print(*stmt.elseBranch);
        }
        ifStr += ")";
        return ifStr;
    }

    std::any ASTPrinter::visitPrintStmt(const PrintStmt& stmt) {
        return "(print " + print(*stmt.expression) + ")";
    }

    std::any ASTPrinter::visitVarStmt(const VarStmt& stmt) {
        if (stmt.initializer == nullptr) {
            return "(var " + stmt.name.lexeme + ")";
        }
        return "(var " + stmt.name.lexeme + " = " + print(*stmt.initializer) + ")";
    }

    std::any ASTPrinter::visitWhileStmt(const WhileStmt& stmt) {
        return "(while " + print(*stmt.condition) + " " + print(*stmt.body) + ")";
    }

} // Fecha o namespace lox