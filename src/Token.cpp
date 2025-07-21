#include "Token.hpp"
#include <string>

// A implementação do construtor agora aceita lox::Value
Token::Token(TokenType type, std::string lexeme, lox::Value literal, int line)
    : type(type), lexeme(std::move(lexeme)), literal(std::move(literal)), line(line) {}

std::string Token::toString() const {
    // A implementação pode ser mais detalhada se você quiser, mas esta funciona.
    return "Type: " + std::to_string(static_cast<int>(type)) + " Lexeme: '" + lexeme + "'";
}