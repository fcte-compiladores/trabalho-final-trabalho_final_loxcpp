#pragma once

#include <stdexcept>
#include "Token.hpp"

namespace lox {

class RuntimeError : public std::runtime_error {
public:
    // Deixamos o token público para que o bloco catch possa acessá-lo facilmente
    const Token token;

    /**
     * @brief Construtor da exceção de erro em tempo de execução.
     * @param token O token que causou o erro.
     * @param message A mensagem descrevendo o erro.
     */
    RuntimeError(const Token& token, const std::string& message)
        // Chama o construtor da classe pai (std::runtime_error) com a mensagem
        : std::runtime_error(message), token(token) {}
};

} 
