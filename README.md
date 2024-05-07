# Expressões Lógicas e Satisfatibilidade

## Introdução

Neste trabalho prático, foi abordada a avaliação de expressões lógicas e a determinação de sua satisfatibilidade. A tarefa envolve a manipulação eficiente de variáveis, operadores lógicos e a resolução de expressões complexas. O programa desenvolvido foi estruturado cuidadosamente em diferentes partes funcionais para alcançar os objetivos propostos. A análise da expressão lógica, seguida pela construção e avaliação de uma árvore de expressão, constituem a primeira etapa. A segunda parte trata da determinação da satisfatibilidade, realizando uma busca exaustiva de casos satisfatíveis de forma eficiente. O trabalho oferece uma visão detalhada sobre o desenvolvimento do código para resolver problemas de lógica proposicional, destacando tanto a lógica do algoritmo quanto a implementação cuidadosa das estruturas de dados.

## Método

### Descrição da Implementação

O programa foi desenvolvido em C++ e utiliza a estrutura de dados de uma Árvore Binária de Expressão. Nessa árvore, os números ou operandos são representados pelas folhas, enquanto os operadores são representados pelos nós internos. As informações nos nós são armazenadas como strings. Para resolver o problema, o programa utiliza dois tipos de pilha: uma para armazenar os tipos de nós da árvore e outra para armazenar strings. A solução envolveu o mapeamento de
expressões por meio de caminhamentos na Árvore Binária, como ilustrado na imagem para o exemplo “( 0 & 1 ) | ( 2 & ~ 3 )”.

![image](https://github.com/leticiascofield/ExpressaoLogicaESatisfatibilidade/assets/125830543/102e660b-87bf-4db6-8c7e-ff8f40dc3563)


### Estruturas de Dados

- **TreeNode** (TreeNode.hpp, TreeNode.cpp): Representa um nó em uma árvore de expressão lógica.
- **NodeStack** (NodeStack.hpp, NodeStack.cpp): Representa uma pilha de nós da árvore de expressão.
- **NodeStackNode** (NodeStackNode.hpp, NodeStackNode.cpp): Representa um nó na pilha de nós da árvore de expressão.
- **StringStack** (StringStack.hpp, StringStack.cpp): Representa uma pilha de strings.
- **StringStackNode** (StringStackNode.hpp, StringStackNode.cpp): Representa um nó na pilha de strings.

### Funções e Métodos Implementados do main.cpp

As principais funções incluem:

- **replaceVariablesWithValues**: Substitui variáveis na expressão pelos valores correspondentes.
- **getOperatorPrecedence**: Retorna a precedência de um operador lógico.
- **evaluate**: Avalia operações lógicas entre operandos.
- **buildInfixExpressionTree**: Constrói uma árvore de expressão a partir de uma expressão lógica em notação infixada.
- **evaluateInfixExpressionTree**: Avalia uma árvore de expressão lógica.
- **completeEvaluate**: Avalia completamente uma expressão lógica.
- **satisfiability**: Determina a satisfatibilidade de uma expressão lógica.

## Instruções para Compilação e Execução

**Compilação:**
1. Extrair os conteúdos do ZIP do projeto em uma pasta.
2. Ter instalado o GCC.
3. Abrir um terminal no diretório raiz do projeto.
4. Executar o comando `make all`.

**Execução:**
- As entradas devem seguir o formato disponibilizado nos exemplos de entradas. Todos os números, operadores e parênteses estão separados por espaços. 
- Utilize `./bin/tp1.out <comando> <"expressão"> <valoração>`.
  
## Conclusão

O programa desenvolvido oferece uma solução funcional para a avaliação de expressões lógicas e determinação de satisfatibilidade. Destaca-se pela implementação eficiente e pelas estratégias de robustez adotadas. Em síntese, demonstra a aplicação prática dos conceitos de estruturas de dados na resolução de problemas de lógica proposicional.

## Bibliografias

- JENNY'S LECTURES. Data Structures and Algorithms.
- SCHMIDT, Douglas C. Case Study: Expression Tree Evaluator.
- CHAIMOWICZ, Luiz; PRATES, Raquel. Slides Estruturas de Dados.
- FEOFILOFF, Paulo. Árvores Binárias.
