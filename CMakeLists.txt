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
# CUIDADO: Não inclua o main.cpp aqui para a biblioteca
file(GLOB_RECURSE LIB_SOURCES "src/*.cpp" "src/ast/*.cpp")
list(FILTER LIB_SOURCES EXCLUDE REGEX ".*/main\\.cpp$")


# --- Definindo a Biblioteca e o Executável ---

# 1. Cria uma biblioteca estática com todo o código do interpretador
add_library(lox_lib STATIC ${LIB_SOURCES})

# 2. Torna os includes de 'src' públicos para quem usar a lox_lib
target_include_directories(lox_lib PUBLIC src)

# 3. Cria o executável principal APENAS com o main.cpp
add_executable(lox_cpp src/main.cpp)

# 4. Linka o executável com a nossa biblioteca
target_link_libraries(lox_cpp PRIVATE lox_lib)


# --- Configuração do Google Test ---
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

FetchContent_MakeAvailable(googletest)

# Habilita o diretório de testes
enable_testing()
add_subdirectory(tests)

message(STATUS "Configuração do LoxCpp completa. Use 'make' para compilar e 'make test' para rodar os testes.")