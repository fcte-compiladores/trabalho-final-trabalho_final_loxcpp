# Versão mínima do CMake necessária para usar os recursos deste script.
cmake_minimum_required(VERSION 3.15)

# Define o nome do projeto, a versão (opcional) e a linguagem principal.
project(LoxCpp VERSION 1.0 LANGUAGES CXX)

# --- Configurações do Compilador C++ ---

# Define o padrão do C++.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Ativa avisos úteis do compilador.
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()


# --- Encontrando os Arquivos Fonte ---

# Busca recursivamente dentro da pasta 'src/' por todos os arquivos
file(GLOB_RECURSE SOURCES "src/*.cpp")


# --- Definindo o Executável ---

# Cria o alvo principal do projeto: o executável.
add_executable(lox_cpp ${SOURCES})


# --- Configurando os Diretórios de Inclusão (Include) ---

# vir um #include "...", procure por esse arquivo a partir
# da pasta 'src/'".
target_include_directories(lox_cpp PUBLIC src)


# --- (Opcional) Adicionando Bibliotecas ---
# Se no futuro vocês precisarem de bibliotecas externas (ex: Google Test),
# vocês as adicionariam aqui com 'target_link_libraries()'. Por enquanto,
# não é necessário.

# Mensagem final para o usuário saber que a configuração terminou.
message(STATUS "Configuração do LoxCpp completa. Use 'make' para compilar.")
