#pragma once

#include "Value.hpp"
#include "Token.hpp"
#include <memory>
#include <string>
#include <unordered_map>

namespace lox {

    class Environment : public std::enable_shared_from_this<Environment> {
    public:
        // Construtor para o escopo global (sem pai)
        Environment();
        // Construtor para escopos aninhados (com um pai)
        explicit Environment(std::shared_ptr<Environment> enclosing);

        // Define uma nova variável no escopo ATUAL.
        void define(const std::string& name, const Value& value);

        // Busca o valor de uma variável, procurando nos escopos pais se necessário.
        const Value& get(const Token& name);

        // Atribui um novo valor a uma variável EXISTENTE, procurando nos escopos pais.
        void assign(const Token& name, const Value& value);

    private:
        // Ponteiro para o escopo pai (ex: o escopo de um bloco dentro de uma função)
        std::shared_ptr<Environment> m_enclosing;
        
        // Tabela hash que mapeia nomes de variáveis para seus valores.
        std::unordered_map<std::string, Value> m_values;
    };

} 