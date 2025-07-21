// src/callable.hpp
#pragma once

#include <vector>
#include <string>
#include "Value.hpp"

// Forward declaration para evitar include circular
namespace lox {
    class Interpreter;
}

class LoxCallable {
public:
    virtual ~LoxCallable() = default;

    /**
     * @brief Executa a lógica do objeto chamável.
     * @param interpreter A instância do interpretador que está executando a chamada.
     * @param arguments A lista de argumentos passados para a função.
     * @return O valor de retorno da função.
     */
    // CORREÇÃO: Adicionado 'lox::' antes de Value
    virtual lox::Value call(lox::Interpreter& interpreter, const std::vector<lox::Value>& arguments) = 0;

    /**
     * @brief Retorna o número de argumentos que a função espera.
     * @return O número de parâmetros (aridade) da função.
     */
    virtual int arity() const = 0;

    /**
     * @brief Retorna uma representação em string do chamável (ex: <fn nome_da_funcao>).
     * @return Uma string.
     */
    virtual std::string toString() const = 0;
};