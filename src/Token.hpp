// src/Token.hpp

#pragma once // Evita que o header seja incluído múltiplas vezes

#include <string>
#include <variant>

// Usamos 'enum class' para criar um enumerador com escopo e fortemente tipado.
// É mais seguro que o 'enum' tradicional do C.
enum class TokenType {
    // Tokens de um caractere
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
    COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

    // Tokens de um ou dois caracteres
    BANG, BANG_EQUAL,
    EQUAL, EQUAL_EQUAL,
    GREATER, GREATER_EQUAL,
    LESS, LESS_EQUAL,

    // Literais
    IDENTIFIER, STRING, NUMBER,

    // Palavras-chave
    AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
    PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

    END_OF_FILE
};

// Usamos std::variant para guardar o valor de um literal.
// Pode ser uma string, um número, ou nada (monostate).
using LiteralValue = std::variant<std::monostate, std::string, double>;

struct Token {
    const TokenType type;
    const std::string lexeme;
    const LiteralValue literal;
    const int line;

    // Construtor para facilitar a criação de tokens
    Token(TokenType type, std::string lexeme, LiteralValue literal, int line)
        : type(type), lexeme(std::move(lexeme)), literal(std::move(literal)), line(line) {}

    std::string toString() const; // Implementação pode ficar em Token.cpp
};