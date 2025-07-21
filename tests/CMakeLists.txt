# Define o nome do executável de teste
add_executable(run_tests
    ScannerTests.cpp
    ParserTests.cpp
    InterpreterTests.cpp
    # Adicione novos arquivos de teste aqui
)

# Faz o link do executável de teste com a biblioteca lox_lib
# para que os testes possam acessar o código do interpretador.
target_link_libraries(run_tests PRIVATE lox_lib)

# Faz o link com as bibliotecas do Google Test
target_link_libraries(run_tests PRIVATE gtest_main)

# Adiciona o executável à suíte de testes do CTest
include(GoogleTest)
gtest_discover_tests(run_tests)