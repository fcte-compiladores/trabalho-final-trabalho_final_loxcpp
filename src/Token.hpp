#pragma once

#include "Value.hpp" // Para usar lox::Value
#include <string>

// A definição do TokenType não muda.
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

// O tipo LiteralValue foi removido.

struct Token {
    const TokenType type;
    const std::string lexeme;
    const lox::Value literal; // <-- MUDANÇA CRÍTICA: Usa lox::Value
    const int line;

    // Construtor atualizado para aceitar lox::Value
    Token(TokenType type, std::string lexeme, lox::Value literal, int line);

    std::string toString() const;
};