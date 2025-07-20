
# LoxCpp: Um Interpretador para a Linguagem Lox em C++

Este é o repositório para o projeto final da disciplina de Compiladores, uma implementação do interpretador para a linguagem de programação Lox em C++ moderno.

---

## Integrantes

<table>
  <tr>
     <td align="center"><a href="https://github.com/leticiatmartins"><img style="border-radius: 50%;" src="https://github.com/anajoyceamorim.png" width="190px;" alt=""/><br /><sub><b>Ana Joyce</b></sub></a><br />
    <td align="center"><a href="https://github.com/BiancaPatrocinio7"><img style="border-radius: 50%;" src="https://github.com/BiancaPatrocinio7.png" width="190;" alt=""/><br /><sub><b>Bianca Patrocínio</b></sub></a><br /></td>
  </tr>
</table>

| Matrícula    | Aluno                       |
| ------------ | --------------------------- |
| 20/2016702   | Ana Joyce |
| 22/1008801   | Bianca Patrocínio Castro    |

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
    a = "Hello";
    print a; // Saída: Hello
    ```
* **Expressões Aritméticas e Lógicas:** Operadores `+`, `-`, `*`, `/`, `!`, `==`, `!=`, `<`, `<=`, `>`, `>=`.
    ```lox
    print 1 + 2 * 3; // Saída: 7
    print (5 > 3) and (2 < 4); // Saída: true
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
    * **Laços (`for`):**
        ```lox
        for (var i = 0; i < 3; i = i + 1) {
            print i;
        }
        // Saída: 0, 1, 2
        ```
* **Funções:** Declaração com `fun`, parâmetros, retorno e chamadas.
    ```lox
    fun fib(n) {
        if (n <= 1) return n;
        return fib(n - 2) + fib(n - 1);
    }
    print fib(8); // Saída: 21
    ```
* **Classes e Objetos:** Criação de classes, instâncias e acesso a propriedades e métodos.
    ```lox
    class Pessoa {
        init(nome, idade) {
            this.nome = nome;
            this.idade = idade;
        }

        saudar() {
            print "Olá, meu nome é " + this.nome + " e tenho " + this.idade + " anos.";
        }
    }

    var joao = Pessoa("João", 30);
    joao.saudar(); // Saída: Olá, meu nome é João e tenho 30 anos.
    ```

---

## Instalação

Siga estas instruções para compilar e executar o projeto em um ambiente Linux ou macOS.

### Pré-requisitos

Antes de começar, garanta que você tenha as seguintes ferramentas instaladas:

* **Git:** Para clonar o repositório.
* **Um compilador C++:** `g++` (GCC) ou `Clang`.
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

### Compilação e Execução do Projeto

1.  **Clone o Repositório**
    Abra seu terminal e clone o projeto do GitHub/GitLab.

    ```bash
    git clone <URL_DO_SEU_REPOSITORIO>
    cd <NOME_DA_PASTA_DO_PROJETO>
    ```

2.  **Crie o Diretório de Build**
    Nós seguimos a prática de "out-of-source build", que mantém os arquivos de compilação separados do código-fonte.

    ```bash
    mkdir build
    cd build
    ```

3.  **Gere os Arquivos de Build com CMake**
    A partir da pasta `build`, execute o CMake para ele encontrar seu `CMakeLists.txt` e gerar os Makefiles.

    ```bash
    cmake ..
    ```

4.  **Compile o Projeto com Make**
    Agora, com tudo configurado, compile o código.

    ```bash
    make
    ```

    Se a compilação for bem-sucedida, você terá um executável chamado `lox_cpp` dentro da pasta `build/`.

### Executando o Interpretador

Após a compilação, você pode executar o interpretador Lox de duas maneiras:

  * **Modo Interativo (REPL):**

    ```bash
    ./lox_cpp
    ```

    Isso iniciará um prompt onde você pode digitar código Lox linha por linha. Digite `exit` ou `quit` para sair.

  * **Executando um Arquivo Lox:**

    ```bash
    ./lox_cpp <caminho/para/seu/arquivo.lox>
    ```

    Por exemplo, para executar um dos exemplos:

    ```bash
    ./lox_cpp ../examples/hello_world.lox
    ```

-----

## Exemplos

A pasta `examples/` contém diversos arquivos `.lox` para demonstrar a sintaxe e as capacidades do nosso interpretador, com diferentes níveis de complexidade:

  * `hello_world.lox`: Um exemplo simples para verificar a execução básica.
  * `fibonacci.lox`: Implementação da sequência de Fibonacci usando funções recursivas.
  * `closures.lox`: Demonstra o suporte a closures em Lox.
  * `classes_objects.lox`: Exemplo de definição e uso de classes e objetos.
  * `quicksort.lox`: Implementação do algoritmo de ordenação QuickSort (ou outro algoritmo mais elaborado que você tenha implementado).
  * `binary_search_tree.lox`: Exemplo de uma estrutura de dados, como uma árvore binária de busca simples.

Para executar um exemplo, utilize o comando: `./lox_cpp examples/nome_do_arquivo.lox`.

-----

## Referências

Nosso projeto foi amplamente baseado nas seguintes referências:

  * **Nystrom, Robert. "Crafting Interpreters".** Esta foi a principal referência para a construção do interpretador Lox. O livro oferece uma abordagem detalhada e didática, cobrindo desde a análise léxica até a implementação de classes e closures. A estrutura geral do interpretador, a gramática da linguagem e muitos dos algoritmos de parsing foram diretamente inspirados por esta obra.
      * [Link para o livro online](https://craftinginterpreters.com/)

-----

## Estrutura do Código

O código-fonte do interpretador LoxCpp está organizado nos seguintes módulos e classes principais:

  * **`src/`**: Contém todos os arquivos-fonte C++.
      * **`Scanner.hpp` / `Scanner.cpp`**: Implementa o **Analisador Léxico**. Esta etapa é responsável por ler o código-fonte Lox e convertê-lo em uma sequência de **tokens**. Cada token representa uma unidade léxica (palavras-chave, identificadores, operadores, literais, etc.).
      * **`Parser.hpp` / `Parser.cpp`**: Implementa o **Analisador Sintático**. Baseado na gramática de Lox, o parser consome os tokens gerados pelo scanner e constrói a **Abstract Syntax Tree (AST)**. Ele garante que a sequência de tokens está em conformidade com as regras sintáticas da linguagem.
      * **`Expr.hpp` / `Stmt.hpp`**: Definições das classes que representam os nós da AST (expressões e declarações). Estas classes são geradas automaticamente por uma ferramenta (ou criadas manualmente) para representar a estrutura hierárquica do código Lox.
      * **`Interpreter.hpp` / `Interpreter.cpp`**: Contém a lógica do **Interpretador**. Esta classe "visita" a AST gerada pelo parser e executa as ações correspondentes a cada nó. É aqui que a **Análise Semântica** implícita ocorre, como verificação de tipos em tempo de execução e resolução de variáveis.
      * **`Lox.hpp` / `Lox.cpp`**: Gerencia o ciclo de vida do interpretador, tratamento de erros e a interface com o usuário (REPL ou leitura de arquivo).
      * **`Environment.hpp` / `Environment.cpp`**: Implementa o ambiente de execução, responsável por armazenar e gerenciar as variáveis e funções no escopo atual.
      * **`LoxCallable.hpp` / `LoxFunction.hpp` / `LoxClass.hpp` / `LoxInstance.hpp`**: Classes que representam funções Lox, classes e instâncias de objetos, e a interface para chamadas.
      * **`main.cpp`**: O ponto de entrada do programa, responsável por lidar com a execução do REPL ou de arquivos.

-----

## Bugs/Limitações/Problemas Conhecidos

Apesar de funcional, o interpretador LoxCpp possui algumas limitações e pontos a serem melhorados no futuro:

  * **Ausência de Otimização:** O interpretador não realiza nenhuma otimização de código. A AST é interpretada diretamente, o que pode impactar o desempenho em programas Lox muito grandes ou complexos.
  * **Mensagens de Erro Aprimoradas:** Embora o tratamento de erros básicos esteja presente (erros léxicos, sintáticos e de tempo de execução), as mensagens poderiam ser mais detalhadas e amigáveis para auxiliar na depuração.
  * **Recursos da Linguagem:** Atualmente, LoxCpp não suporta:
      * Herança múltipla.
      * Tratamento de exceções (`try-catch`).
      * Módulos ou importação de arquivos.
  * **Coletor de Lixo Básico:** A gestão de memória para objetos Lox é rudimentar (geralmente baseada em `shared_ptr` ou `unique_ptr` para objetos em C++), mas um coletor de lixo mais sofisticado poderia ser implementado para gerenciar objetos Lox dinamicamente.
  * **Testes Unitários:** A cobertura de testes unitários poderia ser expandida para garantir a robustez de todas as partes do interpretador.

-----

## Código

O código-fonte completo do projeto, juntamente com todas as suas dependências (gerenciadas pelo `CMakeLists.txt`), está disponível no repositório principal.

-----
