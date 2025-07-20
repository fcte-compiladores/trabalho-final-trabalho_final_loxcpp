// src/ast/Visitor.hpp
#pragma once

// Forward declarations para evitar inclusões circulares.
// Dizemos ao compilador que essas classes existem, sem precisar incluir seus headers.
struct Binary;
struct Grouping;
struct Literal;
struct Unary;
struct Variable;
struct Assign;
struct Call;
// ... (adicione um para cada classe de Expr)

struct ExpressionStmt;
struct PrintStmt;
struct VarStmt;
struct BlockStmt;
// ... (adicione um para cada classe de Stmt)


// A interface do Visitor.
// Usa 'std::any' como tipo de retorno genérico para permitir que diferentes
// visitantes retornem tipos diferentes (ex: o interpretador retorna 'Value',
// um pretty-printer retornaria 'std::string').
#include <any>

template<typename R>
class ExprVisitor {
public:
    virtual ~ExprVisitor() = default;
    virtual R visitBinaryExpr(const Binary& expr) = 0;
    virtual R visitLiteralExpr(const Literal& expr) = 0;
    virtual R visitUnaryExpr(const Unary& expr) = 0;
    virtual R visitVariableExpr(const Variable& expr) = 0;
    virtual R visitAssignExpr(const Assign& expr) = 0;
    virtual R visitCallExpr(const Call& expr) = 0;
    // ... adicione um método 'visit' para cada tipo de expressão ...
};

class StmtVisitor {
public:
    virtual ~StmtVisitor() = default;
    virtual void visitExpressionStmt(const ExpressionStmt& stmt) = 0;
    virtual void visitPrintStmt(const PrintStmt& stmt) = 0;
    virtual void visitVarStmt(const VarStmt& stmt) = 0;
    virtual void visitBlockStmt(const BlockStmt& stmt) = 0;
    // ... adicione um método 'visit' para cada tipo de statement ...
};