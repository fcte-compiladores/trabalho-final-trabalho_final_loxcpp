#include "Token.hpp"
#include <string>


Token::Token(TokenType type, std::string lexeme, lox::Value literal, int line)
    : type(type), lexeme(std::move(lexeme)), literal(std::move(literal)), line(line) {}

std::string Token::toString() const {
    return "Type: " + std::to_string(static_cast<int>(type)) + " Lexeme: '" + lexeme + "'";
}