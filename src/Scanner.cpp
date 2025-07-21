#include "Scanner.hpp"
#include <iostream>
#include <map>
#include <cctype>

// O mapa de palavras-chave não precisa de alterações.
static const std::map<std::string, TokenType> keywords = {
    {"and",    TokenType::AND}, {"class",  TokenType::CLASS},
    {"else",   TokenType::ELSE}, {"false",  TokenType::FALSE},
    {"for",    TokenType::FOR}, {"fun",    TokenType::FUN},
    {"if",     TokenType::IF}, {"nil",    TokenType::NIL},
    {"or",     TokenType::OR}, {"print",  TokenType::PRINT},
    {"return", TokenType::RETURN}, {"super",  TokenType::SUPER},
    {"this",   TokenType::THIS}, {"true",   TokenType::TRUE},
    {"var",    TokenType::VAR}, {"while",  TokenType::WHILE}
};

Scanner::Scanner(const std::string& source)
    : m_source(source) {}

std::vector<Token> Scanner::scanTokens() {
    while (!isAtEnd()) {
        m_start = m_current;
        scanToken();
    }
    // Cria o token de fim de arquivo com um literal 'nil' do tipo lox::Value.
    m_tokens.emplace_back(TokenType::END_OF_FILE, "", lox::Value{std::monostate{}}, m_line);
    return m_tokens;
}

// MUDANÇA CRÍTICA: A definição do método agora corresponde ao .hpp
void Scanner::addToken(TokenType type, const lox::Value& literal) {
    std::string text = m_source.substr(m_start, m_current - m_start);
    m_tokens.emplace_back(type, text, literal, m_line);
}

// Esta sobrecarga para tokens sem literal agora funciona perfeitamente.
void Scanner::addToken(TokenType type) {
    addToken(type, lox::Value{std::monostate{}});
}

void Scanner::string() {
    while (peek() != '"' && !isAtEnd()) {
        if (peek() == '\n') m_line++;
        advance();
    }

    if (isAtEnd()) {
        std::cerr << "Erro na linha " << m_line << ": String não terminada." << std::endl;
        return;
    }

    advance(); // O '"' final.

    std::string value = m_source.substr(m_start + 1, m_current - m_start - 2);
    addToken(TokenType::STRING, value); // O std::string é convertido para lox::Value
}

void Scanner::number() {
    while (isdigit(peek())) advance();

    if (peek() == '.' && isdigit(peekNext())) {
        advance();
        while (isdigit(peek())) advance();
    }
    
    double value = std::stod(m_source.substr(m_start, m_current - m_start));
    addToken(TokenType::NUMBER, value); // O double é convertido para lox::Value
}

void Scanner::identifier() {
    while (isalnum(peek()) || peek() == '_') advance();

    std::string text = m_source.substr(m_start, m_current - m_start);
    auto it = keywords.find(text);
    TokenType type = (it == keywords.end()) ? TokenType::IDENTIFIER : it->second;
    addToken(type);
}

// O restante do arquivo (funções de apoio e scanToken) não precisa de alterações.
bool Scanner::isAtEnd() const { return m_current >= m_source.length(); }
char Scanner::advance() { return m_source[m_current++]; }
bool Scanner::match(char expected) {
    if (isAtEnd() || m_source[m_current] != expected) return false;
    m_current++;
    return true;
}
char Scanner::peek() const { return isAtEnd() ? '\0' : m_source[m_current]; }
char Scanner::peekNext() const {
    if (m_current + 1 >= m_source.length()) return '\0';
    return m_source[m_current + 1];
}

void Scanner::scanToken() {
    char c = advance();
    switch (c) {
        case '(': addToken(TokenType::LEFT_PAREN); break;
        case ')': addToken(TokenType::RIGHT_PAREN); break;
        case '{': addToken(TokenType::LEFT_BRACE); break;
        case '}': addToken(TokenType::RIGHT_BRACE); break;
        case ',': addToken(TokenType::COMMA); break;
        case '.': addToken(TokenType::DOT); break;
        case '-': addToken(TokenType::MINUS); break;
        case '+': addToken(TokenType::PLUS); break;
        case ';': addToken(TokenType::SEMICOLON); break;
        case '*': addToken(TokenType::STAR); break;
        case '!': addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG); break;
        case '=': addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL); break;
        case '<': addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS); break;
        case '>': addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER); break;
        case '/':
            if (match('/')) { while (peek() != '\n' && !isAtEnd()) advance(); }
            else { addToken(TokenType::SLASH); }
            break;
        case ' ': case '\r': case '\t': break;
        case '\n': m_line++; break;
        case '"': string(); break;
        default:
            if (isdigit(c)) { number(); }
            else if (isalpha(c) || c == '_') { identifier(); }
            else { std::cerr << "Erro na linha " << m_line << ": Caractere inesperado '" << c << "'." << std::endl; }
            break;
    }
}