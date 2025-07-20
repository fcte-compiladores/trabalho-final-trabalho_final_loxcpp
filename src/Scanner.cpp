#include "Scanner.hpp" // Inclui a declaração

// Implementação do construtor
Scanner::Scanner(const std::string& source)
    : m_source(source) {
    // Inicializações adicionais, se necessário
}

// Implementação "vazia" do método principal
std::vector<Token> Scanner::scanTokens() {
    // TODO: Implementar a lógica real do scanner aqui

    // Por enquanto, apenas retorna um vetor vazio e um token de fim de arquivo.
    m_tokens.emplace_back(TokenType::END_OF_FILE, "", std::monostate{}, m_line);
    return m_tokens;
}
