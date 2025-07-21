#include "Environment.hpp"
#include <stdexcept> // Para std::runtime_error

// Abre o namespace lox
namespace lox {

    Environment::Environment() : m_enclosing(nullptr) {}

    Environment::Environment(std::shared_ptr<Environment> enclosing)
        : m_enclosing(std::move(enclosing)) {}

    void Environment::define(const std::string& name, const Value& value) {
        m_values[name] = value;
    }

    const Value& Environment::get(const Token& name) {
        // Procura no escopo atual primeiro.
        auto it = m_values.find(name.lexeme);
        if (it != m_values.end()) {
            return it->second;
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
        auto it = m_values.find(name.lexeme);
        if (it != m_values.end()) {
            it->second = value;
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

} // Fecha o namespace lox