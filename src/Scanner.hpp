#pragma once

#include <string>
#include <vector>
#include "Token.hpp"
#include "Value.hpp" 

class Scanner {
public:
    Scanner(const std::string& source);
    std::vector<Token> scanTokens();

private:
    bool isAtEnd() const;
    void scanToken();
    char advance();
 
    void addToken(TokenType type);
    void addToken(TokenType type, const lox::Value& literal);

    bool match(char expected);
    char peek() const;
    char peekNext() const;
    void string();
    void number();
    void identifier();

    const std::string& m_source;
    std::vector<Token> m_tokens;
    size_t m_start = 0;
    size_t m_current = 0;
    int m_line = 1;
};