// Scanner.hpp
#pragma once

#include <string>
#include <vector>
#include "Token.hpp"

class Scanner {
public:
    Scanner(const std::string& source);
    std::vector<Token> scanTokens();

private:
    // Mantemos a referência para o código fonte
    const std::string& m_source; 
    
    // ADICIONE ESTAS DUAS LINHAS PARA CORRIGIR O ERRO
    std::vector<Token> m_tokens; // Onde os tokens serão armazenados
    int m_line = 1;              // Para rastrear a linha atual
};