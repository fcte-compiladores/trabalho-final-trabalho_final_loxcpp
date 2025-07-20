// src/Value.hpp
#pragma once

#include <string>
#include <variant>
#include <memory> // Para std::shared_ptr

// Forward declaration
class LoxCallable;

// O tipo 'Value' pode ser qualquer um destes.
// Usamos std::monostate para representar 'nil' de forma segura.
// Usamos std::shared_ptr<LoxCallable> para representar funções e classes.
using Value = std::variant<
    std::monostate, // nil
    bool,
    double,
    std::string,
    std::shared_ptr<LoxCallable>
>;

// Funções utilitárias para operar sobre o 'Value'
std::string toString(const Value& value);
bool isTruthy(const Value& value);