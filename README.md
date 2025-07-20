[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/Hppw7Zh2)
# Trabalho Final

## Escopo e organização

O trabalho é de tema livre dentro do escopo da disciplina de compiladores e
consiste no desenvolvimento de alguma aplicação na área da disciplina (um
interpretador para uma linguagem simples, compilador, analisadores de código,
etc.)

O trabalho pode ser feito em grupos de até 4 pessoas.

## Estrutura

Os trabalhos devem ser entregues na atividade própria no [github-classrrom](...).
Cada repositório deve ter uma estrutura parecida com a delineada abaixo:

* **README:** o arquivo README.md na base do repositório deve descrever os
  detalhes da implementação do código. O README deve ter algumas seções 
  obrigatórias:
  - **Título**: nome do projeto
  - **Integrantes**: lista com os nomes, matrículas e turma de cada integrante.
  - **Introdução**: deve detalhar o que o projeto implementou, quais foram as
    estratégias e algoritmos relevantes. Se o projeto implementa uma linguagem
    não-comum ou um subconjunto de uma linguagem comum, deve conter alguns
    exemplos de comandos nesta linguagem, descrendo a sua sintaxe e semântica,
    quando necessário.
  - **Instalação**: deve detalhar os passos para instalar as dependências e
    rodar o código do projeto. Pode ser algo simples como *"Rode
    `uv run lox hello.lox` para executar o interpretador."*, se a linguagem de
    implementação permitir este tipo de facilidade.

    Você pode usar gerenciadores de pacotes específicos de linguagens populares
    como uv, npm, cargo, etc, containers Docker/Podman, ou `.nix`.
  - **Exemplos**: o projeto deve conter uma pasta "exemplos" com alguns arquivos
    na linguagem de programação implementada. Deve conter exemplos com graus
    variáveis de complexidade. Algo como: hello world, fibonacci, função
    recursiva, alguma estrutura de dados e para finalizar um algoritmo um pouco
    mais elaborado como ordenamento de listas, busca binária, etc.
    
    Note que isto é apenas um guia da ordem de dificuldade dos problemas.
    Algumas linguagens sequer permitem a implementação de alguns dos exemplos
    acima.
  - **Referências**: descreva as referências que você utilizou para a
    implementação da linguagem. Faça uma breve descrição do papel de cada
    referência ou como ela foi usada no projeto. Caso você tenha usado algum 
    código existente como referência, descreva as suas contribuições originais
    para o projeto.
  - **Estrutura do código**: faça uma descrição da estrutura geral do código
    discutindo os módulos, classes, estruturas de dados ou funções principais. 
    Explicite onde as etapas tradicionais de compilação (análise léxica, 
    sintática, semântica, etc) são realizadas, quando relevante.
  - **Bugs/Limitações/problemas conhecidos**: discuta as limitações do seu
    projeto e problemas conhecidos e coisas que poderiam ser feitas para
    melhorá-lo no futuro. Note: considere apenas melhorias incrementais e não
    melhorias grandes como: "reimplementar tudo em Rust".
* **Código:** O codigo fonte deve estar presente no repositório principal junto com
  a declaração das suas dependências. Cada linguagem possui um mecanismo
  específico para isso, mas seria algo como o arquivo pyproject.toml em Python
  ou package.json no caso de Javascript.

## Critérios

Cada trabalho começa com 100% e pode receber penalizações ou bônus de acordo com
os critérios abaixo:

- Ausência do README: -50%
- Instruções de instalação não funcionam: até -20%
- Referências não atribuídas ou falta de referâncias: -10%
- Código confuso ou mal organizado: até -15%
- Falta de clareza em apresentar as técnicas e etapas de compilação: -15%
- Bugs e limitações sérias na implementação: até -25%
- Escopo reduzido, ou implementação insuficiente: até 25%
- Uso de código não atribuído/plágio: até -100%
- Repositório bem estruturado e organizado: até 10%
- Linguagem com conceitos originais/interessantes: até +15%
- Testes unitários: até +15%, dependendo da cobertura

Após aplicar todos os bônus, a nota é truncada no intervalo 0-100%. 

---

# LoxCpp: Um Interpretador para a Linguagem Lox em C++

Este é o repositório para o projeto final da disciplina de Compiladores, uma implementação da linguagem de programação Lox em C++ moderno.

## Como Compilar e Executar

Siga estas instruções para compilar e executar o projeto em um ambiente Linux ou macOS.

### Pré-requisitos

Antes de começar, garanta que você tenha as seguintes ferramentas instaladas:

* **Git:** Para clonar o repositório.
* **Um compilador C++:** `g++` (GCC) ou `Clang`.
* **CMake:** Versão 3.15 ou superior.
* **Make:** A ferramenta de build padrão em sistemas baseados em Unix.

### Passo a Passo

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
