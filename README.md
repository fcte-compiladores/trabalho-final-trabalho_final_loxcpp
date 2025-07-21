# LoxCpp: Um Interpretador para a Linguagem Lox em C++

Este é o repositório para o projeto final da disciplina de Compiladores, uma implementação do interpretador para a linguagem de programação Lox em C++ moderno.

---

## Integrantes

<div align = "center">
<table>
  <tr>
     <td align="center"><a href="https://github.com/leticiatmartins"><img style="border-radius: 50%;" src="https://github.com/anajoyceamorim.png" width="190px;" alt=""/><br /><sub><b>Ana Joyce</b></sub></a><br />
    <td align="center"><a href="https://github.com/BiancaPatrocinio7"><img style="border-radius: 50%;" src="https://github.com/BiancaPatrocinio7.png" width="190px;" alt=""/><br /><sub><b>Bianca Patrocínio</b></sub></a><br /></td>
  </tr>
</table>

| Matrícula    | Aluno                       |
| ------------ | --------------------------- |
| 21/1031566   | Ana Joyce |
| 22/1008801   | Bianca Patrocínio   |

</div>

---

## Introdução

Este projeto consiste na implementação de um **interpretador para a linguagem Lox**, conforme descrito no livro "Crafting Interpreters" de Robert Nystrom. Nosso interpretador foi desenvolvido utilizando **C++ moderno**, focando na clareza do código, desempenho e aderência aos princípios da disciplina de Compiladores.

A linguagem Lox é uma linguagem de programação de propósito geral, com tipagem dinâmica e sintaxe inspirada em C, Java e Ruby. Sua simplicidade a torna ideal para fins didáticos, permitindo explorar os principais conceitos de construção de compiladores e interpretadores. Implementamos as etapas de **análise léxica**, **análise sintática** e **interpretação direta** da Abstract Syntax Tree (AST).

### Sintaxe e Semântica de Lox

Lox suporta os seguintes elementos e estruturas:

* **Variáveis:** Declaração com `var`, atribuição e uso.
    ```lox
    var a = 10;
    print a; // Saída: 10
    ```
* **Expressões Aritméticas e Lógicas:** Operadores `+`, `-`, `*`, `/`, `!`, `==`, `!=`, `<`, `<=`, `>`, `>=`.
    ```lox
    print 1 + 2 * 3; // Saída: 7
    ```
* **Estruturas de Controle:**
    * **Condicionais (`if`/`else`):**
        ```lox
        if (true) {
            print "Verdadeiro!";
        } else {
            print "Falso!";
        }
        ```
    * **Laços (`while`):**
        ```lox
        var i = 0;
        while (i < 3) {
            print i;
            i = i + 1;
        }
        // Saída: 0, 1, 2
        ```
* **Funções e Classes (Conforme o livro `Crafting Interpreters`)**

---

## Instalação

Siga estas instruções para compilar e executar o projeto em um ambiente Linux ou macOS.

### Pré-requisitos

Antes de começar, garanta que você tenha as seguintes ferramentas instaladas:

* **Git:** Para clonar o repositório.
* **Um compilador C++17:** `g++` (GCC) ou `Clang`.
* **CMake:** Versão 3.15 ou superior.
* **Make:** A ferramenta de build padrão em sistemas baseados em Unix.

### Compilação e Execução do Projeto

1.  **Clone o Repositório**
    Abra seu terminal e clone o projeto.

    ```bash
    git clone [https://github.com/fcte-compiladores/trabalho-final-trabalho_final_loxcpp.git](https://github.com/fcte-compiladores/trabalho-final-trabalho_final_loxcpp.git)
    cd trabalho-final-trabalho_final_loxcpp
    ```

2.  **Crie o Diretório de Build e Compile**
    Nós seguimos a prática de "out-of-source build", que mantém os arquivos de compilação separados do código-fonte.

    ```bash
    mkdir build
    cd build
    cmake ..
    make
    ```

    Se a compilação for bem-sucedida, você terá um executável chamado `lox_cpp` dentro da pasta `build/`.

### Executando o Interpretador

Após a compilação, você pode executar o interpretador Lox de duas maneiras:

* **Modo Interativo (REPL):**
    ```bash
    ./build/lox_cpp
    ```

* **Executando um Arquivo Lox:**
    ```bash
    ./build/lox_cpp <caminho/para/seu/arquivo.lox>
    ```

---

## Executando os Testes Unitários

O projeto inclui uma suíte de testes unitários utilizando o framework **Google Test** para garantir a corretude do Scanner, do Parser e do Interpretador.

Para configurar e rodar os testes, siga os passos abaixo a partir da **raiz do projeto**:

1.  **Gerar os Arquivos de Teste**
    Nós fornecemos um script para criar automaticamente todos os arquivos de teste necessários. Primeiro, dê a ele permissão de execução e depois o rode:

    ```bash
    chmod +x setup_tests.sh
    ./setup_tests.sh
    ```
    Isso irá popular a pasta `tests/` com todos os casos de teste.

2.  **Compilar o Projeto e os Testes**
    O processo de compilação é o mesmo, mas agora o CMake irá configurar e compilar os testes também. Se já tiver uma pasta `build`, é recomendado limpá-la para garantir que os testes sejam incluídos corretamente.

    ```bash
    rm -rf build
    mkdir build
    cd build
    cmake ..
    make
    ```

3.  **Rodar os Testes**
    Com tudo compilado, execute os testes com o seguinte comando:

    ```bash
    make test
    ```
    A saída deve indicar que todos os 20 testes passaram (`100% tests passed`).

---

## Referências

* **Nystrom, Robert. "Crafting Interpreters".** Esta foi a principal referência para a construção do interpretador Lox. A estrutura geral, a gramática da linguagem e muitos dos algoritmos foram diretamente inspirados por esta obra.
    * [Link para o livro online](https://craftinginterpreters.com/)

---

## Estrutura do Código

O código-fonte do interpretador LoxCpp está organizado nos seguintes módulos e classes principais:

* **`src/`**: Contém todos os arquivos-fonte C++.
    * **`Scanner.hpp` / `Scanner.cpp`**: Implementa o **Analisador Léxico**.
    * **`Parser.hpp` / `Parser.cpp`**: Implementa o **Analisador Sintático** e constrói a AST.
    * **`ast/`**: Contém as definições das classes da AST (`Expr.hpp`, `Stmt.hpp`, etc.).
    * **`Interpreter.hpp` / `Interpreter.cpp`**: Contém a lógica do **Interpretador**, que executa o código a partir da AST.
    * **`Environment.hpp` / `Environment.cpp`**: Implementa o ambiente de execução para gerenciar escopos e variáveis.
    * **`main.cpp`**: Ponto de entrada do programa.

---

## Bugs/Limitações/Problemas Conhecidos

Apesar de funcional, o interpretador LoxCpp possui algumas limitações:

* **Ausência de Otimização:** O interpretador não realiza nenhuma otimização de código. A AST é interpretada diretamente.
* **Recursos da Linguagem:** Atualmente, LoxCpp não suporta funcionalidades mais avançadas como `for`, operadores lógicos `and`/`or`, funções e classes, que são descritos no livro mas não foram implementados.
* **Coleta de Lixo:** A gestão de memória é baseada em ponteiros inteligentes do C++, mas não há um coletor de lixo para gerenciar objetos Lox dinamicamente.
* **Testes Unitários:** O projeto possui uma boa cobertura de testes para as funcionalidades implementadas (Scanner, Parser de statements básicos, e o Interpretador). A suíte de testes pode ser expandida para cobrir mais casos de erro e funcionalidades futuras.