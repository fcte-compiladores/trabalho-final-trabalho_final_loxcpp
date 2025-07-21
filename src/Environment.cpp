#include "Environment.hpp"
#include <stdexcept> // Para std::runtime_error

Environment::Environment() : m_enclosing(nullptr) {}

Environment::Environment(std::shared_ptr<Environment> enclosing)
    : m_enclosing(std::move(enclosing)) {}

void Environment::define(const std::string& name, const Value& value) {
    // 'define' sempre declara no escopo atual.
    // Usamos 'insert' que não sobrescreve se a chave já existir,
    // mas a semântica de Lox (e dos nossos validadores) deve prevenir isso.
    m_values[name] = value;
}

const Value& Environment::get(const Token& name) {
    // Procura no escopo atual primeiro.
    if (m_values.count(name.lexeme)) {
        return m_values.at(name.lexeme);
    }

    // Se não encontrar, tenta procurar no escopo pai.
    if (m_enclosing != nullptr) {
        return m_enclosing->get(name);
    }

    // Se chegou ao topo da cadeia e não encontrou, lança um erro.
    throw std::runtime_error("Undefined variable '" + name.lexeme + "'.");
}

void Environment::assign(const Token& name, const Value& value) {
    // Procura no escopo atual primeiro.
    if (m_values.count(name.lexeme)) {
        m_values[name.lexeme] = value;
        return;
    }

    // Se não encontrar, tenta atribuir no escopo pai.
    if (m_enclosing != nullptr) {
        m_enclosing->assign(name, value);
        return;
    }
    
    // Se não existe em nenhum escopo, é um erro.
    throw std::runtime_error("Undefined variable '" + name.lexeme + "'.");
}
