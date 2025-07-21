#include "Environment.hpp"
#include "ast/Stmt.hpp"
#include "ast/Expr.hpp"
#include "RuntimeError.hpp"

#include "Interpreter.hpp"

#include <iostream>
#include <vector>
#include <memory>
#include <any>

namespace lox {

void checkNumberOperand(const Token& op, const Value& operand) {
    if (!std::holds_alternative<double>(operand)) {
        throw RuntimeError(op, "Operand must be a number.");
    }
}

void checkNumberOperands(const Token& op, const Value& left, const Value& right) {
    if (!std::holds_alternative<double>(left) || !std::holds_alternative<double>(right)) {
        throw RuntimeError(op, "Operands must be numbers.");
    }
}

Interpreter::Interpreter() {
    m_globals = std::make_shared<Environment>();
    m_environment = m_globals;
}

void Interpreter::interpret(const std::vector<std::unique_ptr<Stmt>>& statements) {
    try {
        for (const auto& statement : statements) {
            if (statement) {
                execute(*statement);
            }
        }
    } catch (const RuntimeError& error) {
        std::cerr << "RuntimeError: " << error.what() << "\n[line " << error.token.line << "]" << std::endl;
    }
}

Value Interpreter::evaluate(const Expr& expr) {
    return std::any_cast<Value>(expr.accept(*this));
}

void Interpreter::execute(const Stmt& stmt) {
    stmt.accept(*this);
}

void Interpreter::executeBlock(const std::vector<std::unique_ptr<Stmt>>& statements, std::shared_ptr<Environment> environment) {
    std::shared_ptr<Environment> previous = this->m_environment;
    try {
        this->m_environment = environment;
        for (const auto& statement : statements) {
            execute(*statement);
        }
    } catch (...) {
        this->m_environment = previous;
        throw;
    }
    this->m_environment = previous;
}

bool Interpreter::isTruthy(const Value& value) {
    if (std::holds_alternative<std::monostate>(value)) return false;
    if (std::holds_alternative<bool>(value)) return std::get<bool>(value);
    return true;
}

bool Interpreter::valuesEqual(const Value& a, const Value& b) {
    return a == b;
}

std::any Interpreter::visitExpressionStmt(const ExpressionStmt& stmt) {
    evaluate(*stmt.expression);
    return Value{std::monostate{}};
}

std::any Interpreter::visitPrintStmt(const PrintStmt& stmt) {
    Value value = evaluate(*stmt.expression);
    std::cout << valueToString(value) << std::endl;
    return Value{std::monostate{}};
}

std::any Interpreter::visitVarStmt(const VarStmt& stmt) {
    Value value = std::monostate{};
    if (stmt.initializer != nullptr) {
        value = evaluate(*stmt.initializer);
    }
    m_environment->define(stmt.name.lexeme, value);
    return Value{std::monostate{}};
}

std::any Interpreter::visitBlockStmt(const BlockStmt& stmt) {
    executeBlock(stmt.statements, std::make_shared<Environment>(m_environment));
    return Value{std::monostate{}};
}

std::any Interpreter::visitIfStmt(const IfStmt& stmt) {
    if (isTruthy(evaluate(*stmt.condition))) {
        execute(*stmt.thenBranch);
    } else if (stmt.elseBranch != nullptr) {
        execute(*stmt.elseBranch);
    }
    return Value{std::monostate{}};
}

std::any Interpreter::visitWhileStmt(const WhileStmt& stmt) {
    while (isTruthy(evaluate(*stmt.condition))) {
        execute(*stmt.body);
    }
    return Value{std::monostate{}};
}

std::any Interpreter::visitAssignExpr(const Assign& expr) {
    Value value = evaluate(*expr.value);
    m_environment->assign(expr.name, value);
    return value;
}

std::any Interpreter::visitVariableExpr(const Variable& expr) {
    return m_environment->get(expr.name);
}

std::any Interpreter::visitLiteralExpr(const Literal& expr) {
    return expr.value;
}

std::any Interpreter::visitGroupingExpr(const Grouping& expr) {
    return evaluate(*expr.expression);
}

std::any Interpreter::visitUnaryExpr(const Unary& expr) {
    Value right = evaluate(*expr.right);
    switch (expr.op.type) {
        case TokenType::MINUS:
            checkNumberOperand(expr.op, right);
            return Value{-std::get<double>(right)};
        case TokenType::BANG:
            return Value{!isTruthy(right)};
        default:
            throw RuntimeError(expr.op, "Invalid unary operator.");
    }
}

std::any Interpreter::visitBinaryExpr(const Binary& expr) {
    Value left = evaluate(*expr.left);
    Value right = evaluate(*expr.right);

    switch (expr.op.type) {
        case TokenType::GREATER:
            checkNumberOperands(expr.op, left, right);
            return Value{std::get<double>(left) > std::get<double>(right)};
        case TokenType::GREATER_EQUAL:
            checkNumberOperands(expr.op, left, right);
            return Value{std::get<double>(left) >= std::get<double>(right)};
        case TokenType::LESS:
            checkNumberOperands(expr.op, left, right);
            return Value{std::get<double>(left) < std::get<double>(right)};
        case TokenType::LESS_EQUAL:
            checkNumberOperands(expr.op, left, right);
            return Value{std::get<double>(left) <= std::get<double>(right)};
        case TokenType::BANG_EQUAL:
            return Value{!valuesEqual(left, right)};
        case TokenType::EQUAL_EQUAL:
            return Value{valuesEqual(left, right)};
        case TokenType::MINUS:
            checkNumberOperands(expr.op, left, right);
            return Value{std::get<double>(left) - std::get<double>(right)};
        case TokenType::SLASH:
            checkNumberOperands(expr.op, left, right);
            if (std::get<double>(right) == 0.0) {
                throw RuntimeError(expr.op, "Division by zero.");
            }
            return Value{std::get<double>(left) / std::get<double>(right)};
        case TokenType::STAR:
            checkNumberOperands(expr.op, left, right);
            return Value{std::get<double>(left) * std::get<double>(right)};
        case TokenType::PLUS:
            if (std::holds_alternative<double>(left) && std::holds_alternative<double>(right)) {
                return Value{std::get<double>(left) + std::get<double>(right)};
            }
            if (std::holds_alternative<std::string>(left) && std::holds_alternative<std::string>(right)) {
                return Value{std::get<std::string>(left) + std::get<std::string>(right)};
            }
            throw RuntimeError(expr.op, "Operands must be two numbers or two strings.");
        default:
            throw RuntimeError(expr.op, "Invalid binary operator.");
    }
}

std::any Interpreter::visitCallExpr(const Call& expr) {
    throw RuntimeError(expr.paren, "Can only call functions and classes.");
}

}