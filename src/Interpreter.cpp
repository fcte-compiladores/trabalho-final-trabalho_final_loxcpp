#include "Interpreter.hpp"
#include "Environment.hpp"
#include "RuntimeError.hpp"
#include "Expr.hpp"
#include "Stmt.hpp"
#include <iostream>
#include <vector>
#include <memory>

namespace lox {

// Helper function to convert Value to string for printing
std::string valueToString(const Value& value) {
    return std::visit([](const auto& v) -> std::string {
        using T = std::decay_t<decltype(v)>;
        if constexpr (std::is_same_v<T, std::monostate>) {
            return "nil";
        } else if constexpr (std::is_same_v<T, bool>) {
            return v ? "true" : "false";
        } else if constexpr (std::is_same_v<T, double>) {
            return std::to_string(v);
        } else if constexpr (std::is_same_v<T, std::string>) {
            return v;
        } else if constexpr (std::is_same_v<T, std::shared_ptr<LoxCallable>>) {
            return "<function>";
        } else {
            return "<unknown>";
        }
    }, value);
}

Interpreter::Interpreter() {
    m_globals = std::make_shared<Environment>();
    m_environment = m_globals;
    // Aqui seria um bom lugar para definir funções nativas (ex: clock())
}

void Interpreter::interpret(const std::vector<std::unique_ptr<Stmt>>& statements) {
    try {
        for (const auto& statement : statements) {
            execute(*statement);
        }
    } catch (const RuntimeError& error) {
        // Reporta o erro para o usuário, incluindo a linha
        std::cerr << "[line " << error.token.line << "] RuntimeError: " << error.what() << std::endl;
    }
}

// --- Funções Auxiliares ---

Value Interpreter::evaluate(const Expr& expr) {
    return expr.accept(*this);
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
        // Garante que o ambiente anterior seja restaurado mesmo que uma exceção ocorra
        this->m_environment = previous;
        throw;
    }
    this->m_environment = previous;
}

bool Interpreter::isTruthy(const Value& value) {
    if (std::holds_alternative<std::monostate>(value)) return false;
    if (std::holds_alternative<bool>(value)) return std::get<bool>(value);
    return true; // Números, strings e outros objetos são considerados 'verdadeiros'
}

bool Interpreter::valuesEqual(const Value& a, const Value& b) {
    // Compare variants by type and value
    if (a.index() != b.index()) return false;
    return std::visit([](const auto& av, const auto& bv) -> bool {
        using T = std::decay_t<decltype(av)>;
        if constexpr (std::is_same_v<T, std::monostate>) {
            return true; // nil == nil
        } else if constexpr (std::is_same_v<T, bool>) {
            if constexpr (std::is_same_v<decltype(bv), bool>) {
                return av == bv;
            } else {
                return false;
            }
        } else if constexpr (std::is_same_v<T, double>) {
            if constexpr (std::is_same_v<decltype(bv), double>) {
                return av == bv;
            } else {
                return false;
            }
    } else if constexpr (std::is_same_v<T, std::string>) {
        if constexpr (std::is_same_v<decltype(bv), std::string>) {
            return av == bv;
        } else {
            return false;
        }
    } else {
        return false;
    }
}, a, b);
}

// --- Implementações do Visitor para Statements ---

Value Interpreter::visitExpressionStmt(const ExpressionStmt& stmt) {
    evaluate(*stmt.expression);
    return Value(); // Retorna um valor 'nil' padrão
}

Value Interpreter::visitPrintStmt(const PrintStmt& stmt) {
    Value value = evaluate(*stmt.expression);
    std::cout << value.toString() << std::endl;
    return Value();
}

Value Interpreter::visitVarStmt(const VarStmt& stmt) {
    Value value; // Inicializa com 'nil'
    if (stmt.initializer != nullptr) {
        value = evaluate(*stmt.initializer);
    }
    m_environment->define(stmt.name.lexeme, value);
    return Value();
}

Value Interpreter::visitBlockStmt(const BlockStmt& stmt) {
    executeBlock(stmt.statements, std::make_shared<Environment>(m_environment));
    return Value();
}

Value Interpreter::visitIfStmt(const IfStmt& stmt) {
    if (isTruthy(evaluate(*stmt.condition))) {
        execute(*stmt.thenBranch);
    } else if (stmt.elseBranch != nullptr) {
        execute(*stmt.elseBranch);
    }
    return Value();
}

Value Interpreter::visitWhileStmt(const WhileStmt& stmt) {
    while (isTruthy(evaluate(*stmt.condition))) {
        execute(*stmt.body);
    }
    return Value();
}

// --- Implementações do Visitor para Expressões ---

Value Interpreter::visitAssignExpr(const Assign& expr) {
    Value value = evaluate(*expr.value);
    m_environment->assign(expr.name, value);
    return value;
}

Value Interpreter::visitVariableExpr(const Variable& expr) {
    return m_environment->get(expr.name);
}

Value Interpreter::visitLiteralExpr(const Literal& expr) {
    return expr.value;
}

Value Interpreter::visitGroupingExpr(const Grouping& expr) {
    return evaluate(*expr.expression);
}

Value Interpreter::visitUnaryExpr(const Unary& expr) {
    Value right = evaluate(*expr.right);
    switch (expr.op.type) {
        case TokenType::MINUS:
            if (!right.isNumber()) throw RuntimeError(expr.op, "Operand must be a number.");
            return Value(-right.asNumber());
        case TokenType::BANG:
            return Value(!isTruthy(right));
        default:
            throw RuntimeError(expr.op, "Invalid unary operator."); // Inalcançável
    }
}

Value Interpreter::visitBinaryExpr(const Binary& expr) {
    Value left = evaluate(*expr.left);
    Value right = evaluate(*expr.right);
    switch (expr.op.type) {
        // Comparação
        case TokenType::GREATER:
            if (!left.isNumber() || !right.isNumber()) throw RuntimeError(expr.op, "Operands must be numbers.");
            return Value(left.asNumber() > right.asNumber());
        case TokenType::GREATER_EQUAL:
            if (!left.isNumber() || !right.isNumber()) throw RuntimeError(expr.op, "Operands must be numbers.");
            return Value(left.asNumber() >= right.asNumber());
        case TokenType::LESS:
            if (!left.isNumber() || !right.isNumber()) throw RuntimeError(expr.op, "Operands must be numbers.");
            return Value(left.asNumber() < right.asNumber());
        case TokenType::LESS_EQUAL:
            if (!left.isNumber() || !right.isNumber()) throw RuntimeError(expr.op, "Operands must be numbers.");
            return Value(left.asNumber() <= right.asNumber());
        // Igualdade
        case TokenType::BANG_EQUAL: return Value(!valuesEqual(left, right));
        case TokenType::EQUAL_EQUAL: return Value(valuesEqual(left, right));
        // Aritmética
        case TokenType::MINUS:
            if (!left.isNumber() || !right.isNumber()) throw RuntimeError(expr.op, "Operands must be numbers.");
            return Value(left.asNumber() - right.asNumber());
        case TokenType::SLASH:
            if (!left.isNumber() || !right.isNumber()) throw RuntimeError(expr.op, "Operands must be numbers.");
            if (right.asNumber() == 0) throw RuntimeError(expr.op, "Division by zero.");
            return Value(left.asNumber() / right.asNumber());
        case TokenType::STAR:
            if (!left.isNumber() || !right.isNumber()) throw RuntimeError(expr.op, "Operands must be numbers.");
            return Value(left.asNumber() * right.asNumber());
        case TokenType::PLUS:
            if (left.isNumber() && right.isNumber()) {
                return Value(left.asNumber() + right.asNumber());
            }
            if (left.isString() && right.isString()) {
                return Value(left.asString() + right.asString());
            }
            throw RuntimeError(expr.op, "Operands must be two numbers or two strings.");
        default:
            throw RuntimeError(expr.op, "Invalid binary operator."); // Inalcançável
    }
}

Value Interpreter::visitCallExpr(const Call& expr) {
    // A implementação de chamadas de função é um passo mais avançado.
    throw RuntimeError(expr.paren, "Can only call functions and classes.");
}

} // Fim do namespace lox
