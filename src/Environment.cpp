#include "Environment.hpp"
#include "RuntimeError.hpp"
#include <string>

namespace lox {

    Environment::Environment() : m_enclosing(nullptr) {}

    Environment::Environment(std::shared_ptr<Environment> enclosing)
        : m_enclosing(std::move(enclosing)) {}

    void Environment::define(const std::string& name, const Value& value) {
        m_values[name] = value;
    }

    const Value& Environment::get(const Token& name) {
        auto it = m_values.find(name.lexeme);
        if (it != m_values.end()) {
            return it->second;
        }

        if (m_enclosing != nullptr) {
            return m_enclosing->get(name);
        }

        throw RuntimeError(name, "Undefined variable '" + name.lexeme + "'.");
    }

    void Environment::assign(const Token& name, const Value& value) {
        auto it = m_values.find(name.lexeme);
        if (it != m_values.end()) {
            it->second = value;
            return;
        }

        if (m_enclosing != nullptr) {
            m_enclosing->assign(name, value);
            return;
        }
        
        throw RuntimeError(name, "Undefined variable '" + name.lexeme + "'.");
    }

} 