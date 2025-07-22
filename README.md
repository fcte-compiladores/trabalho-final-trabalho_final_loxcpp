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

## Instalação e Execução

Siga estas instruções para compilar e executar o projeto em um ambiente Linux ou macOS.

### Pré-requisitos

* **Git:** Para clonar o repositório.
* **Um compilador C++17:** `g++` (GCC) ou `Clang`.
* **CMake:** Versão 3.15 ou superior.
* **Make:** A ferramenta de build padrão em sistemas baseados em Unix.

#### Como instalar os pré-requisitos:

**Linux (Debian/Ubuntu):**

Abra seu terminal e execute os seguintes comandos:

```bash
sudo apt update
sudo apt install git build-essential cmake
````

  * `git`: Para gerenciar o código-fonte.
  * `build-essential`: Pacote que inclui o `g++` (compilador GCC para C++) e `make`.
  * `cmake`: Ferramenta para gerenciar o processo de build.

**Linux (Fedora):**

Abra seu terminal e execute os seguintes comandos:

```bash
sudo dnf install git gcc-c++ make cmake
```

  * `git`: Para gerenciar o código-fonte.
  * `gcc-c++`: Pacote que inclui o `g++` (compilador GCC para C++).
  * `make`: Ferramenta de build.
  * `cmake`: Ferramenta para gerenciar o processo de build.

**macOS (com Homebrew):**

Se você não tiver o Homebrew, instale-o primeiro seguindo as instruções em [brew.sh](https://brew.sh/).

Após instalar o Homebrew, abra seu terminal e execute:

```bash
brew install git cmake
brew install gcc # Para o g++ (GCC) ou use clang que já vem com Xcode Command Line Tools
```

  * `git`: Para gerenciar o código-fonte.
  * `cmake`: Ferramenta para gerenciar o processo de build.
  * `gcc`: Instala a versão do GCC. Alternativamente, as **Xcode Command Line Tools** (que incluem `clang` e `make`) geralmente são suficientes para a compilação. Você pode instalá-las com `xcode-select --install`.

### Compilação

1.  **Clone o Repositório:**
    ```bash
    git clone https://github.com/fcte-compiladores/trabalho-final-trabalho_final_loxcpp.git
    cd trabalho-final-trabalho_final_loxcpp
    ```

2.  **Crie o Diretório de Build e Compile:**
    ```bash
    mkdir -p build
    cd build
    cmake ..
    make
    ```
    Após a compilação, o executável `lox_cpp` estará disponível em `build/`.

### Executando o Interpretador

Você pode executar o interpretador de duas maneiras, a partir da pasta raiz do projeto:

* **Modo Interativo (REPL):**
    ```bash
    ./build/lox_cpp
    ```

* **Executando um Arquivo Lox:**
    ```bash
    ./build/lox_cpp caminho/para/seu/arquivo.lox
    ```

---

## Debugging e Visualização da AST

Para fins de depuração e para visualizar a **Árvore de Sintaxe Abstrata (AST)** que o Parser gera, você pode usar o flag `--print-ast`. Isso funciona tanto para arquivos quanto para o modo interativo.

* **Visualizar a AST de um arquivo:**
    ```bash
    ./build/lox_cpp --print-ast caminho/para/seu/arquivo.lox
    ```

* **Visualizar a AST no modo interativo:**
    ```bash
    ./build/lox_cpp --print-ast
    ```
    No modo interativo, a árvore de cada linha digitada será impressa antes da sua execução. 

---

## Exemplos

O projeto inclui uma pasta `exemplos/` com arquivos `.lox` que demonstram as funcionalidades da linguagem implementada. Você pode executá-los com o interpretador:

```bash
./build/lox_cpp exemplos/01_hello_world.lox
```

Os exemplos progridem em complexidade:

*   **`01_hello_world.lox`**: O programa mais simples, que imprime "Hello, world!".
*   **`02_variables.lox`**: Demonstra a declaração, atribuição e uso de variáveis com expressões aritméticas.
*   **`03_control_flow.lox`**: Mostra o uso de estruturas de controle como `if/else` e o laço `while`.
*   **`04_fibonacci.lox`**: Um algoritmo um pouco mais elaborado que calcula os primeiros números da sequência de Fibonacci de forma iterativa.
*   **`05_scope.lox`**: Ilustra como o escopo de variáveis funciona, incluindo o sombreamento de variáveis (shadowing) em blocos internos.

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
    Se já tiver compilado o projeto, é recomendado limpar a pasta `build` para garantir que os testes sejam incluídos corretamente.

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

* **`src/`**: Contém todos os arquivos-fonte C++.
    * **`Scanner.hpp` / `Scanner.cpp`**: Implementa o **Analisador Léxico**.
    * **`Parser.hpp` / `Parser.cpp`**: Implementa o **Analisador Sintático** e constrói a AST.
    * **`ast/`**: Contém as definições das classes da AST (`Expr.hpp`, `Stmt.hpp`, etc.).
    * **`Interpreter.hpp` / `Interpreter.cpp`**: Contém a lógica do **Interpretador**.
    * **`Environment.hpp` / `Environment.cpp`**: Implementa o ambiente de execução para gerenciar escopos e variáveis.
    * **`main.cpp`**: Ponto de entrada do programa.

---

## Bugs/Limitações/Problemas Conhecidos

* **Recursos da Linguagem:** Atualmente, LoxCpp não suporta funcionalidades mais avançadas como `for`, operadores lógicos `and`/`or`, funções e classes, que são descritos no livro mas não foram implementados.
* **Coleta de Lixo:** A gestão de memória é baseada em ponteiros inteligentes do C++, mas não há um coletor de lixo para gerenciar objetos Lox dinamicamente.
* **Testes Unitários:** O projeto possui uma boa cobertura de testes para as funcionalidades implementadas. A suíte de testes pode ser expandida para cobrir mais casos de erro e funcionalidades futuras.
