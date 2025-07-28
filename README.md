# Sistema de Gerenciamento - Açaiteria Bom Sabor (Versão Avançada)

Este projeto é um Sistema de Gerenciamento de Pedidos para uma Açaíteria, desenvolvido em C, que evoluiu de uma simples manipulação de arquivos para uma arquitetura mais robusta e eficiente.

A versão atual utiliza uma **lista encadeada** para gerenciar os dados em memória, proporcionando operações de cadastro, edição e exclusão muito mais rápidas. O sistema também implementa algoritmos avançados como **Quicksort** e **Busca Binária** para oferecer uma funcionalidade de pesquisa otimizada. O código é totalmente **modularizado** em arquivos `.h` e `.c` para melhor organização e manutenção, e a persistência dos dados é garantida através da leitura e gravação em arquivos de texto no início e no fim da execução.

## Melhorias e Conceitos Aplicados

Esta versão do projeto implementa conceitos fundamentais de Estrutura de Dados 1:

1.  **Estrutura de Dados Avançada (Lista Encadeada):** As operações não são mais feitas diretamente no arquivo. Os dados são carregados para uma lista encadeada na memória, permitindo que o cadastro, a edição e a remoção de pedidos sejam instantâneos, sem a lentidão do acesso a disco a cada operação.

2.  **Algoritmos de Ordenação e Busca Eficientes:** O sistema demonstra o uso prático de algoritmos clássicos:

      * **Quicksort:** Utilizado para ordenar os pedidos por nome de cliente em tempo hábil.
      * **Busca Binária:** Implementada para realizar buscas de clientes de forma extremamente rápida em dados já ordenados, contrastando com a busca linear tradicional.

3.  **Modularização de Código:** O projeto foi separado em arquivos de interface (`.h`) e implementação (`.c`), uma prática essencial para o desenvolvimento de software organizado.

      * **`pedidos.h`**: Define a interface do módulo de pedidos (estruturas e protótipos de funções).
      * **`pedidos.c`**: Contém a implementação de toda a lógica de negócio dos pedidos.
      * **`main.c`**: Responsável pela interface com o usuário (menu, login) e o fluxo principal do programa.

## Funcionalidades

#### Sistema de Login

  * **Autenticação de Usuário:** Login baseado em usuário e senha pré-definida (`teste` / `teste1234`).
  * **Validação de E-mail:** Solicita um e-mail após o login, garantindo que ele contenha o caractere `@` e que seja único (verificado no arquivo `emails_usados.txt`).

#### Gerenciamento de Pedidos em Memória

  * **Registrar:** Cadastro de novos pedidos diretamente na lista encadeada.
  * **Listar:** Exibe todos os pedidos registrados percorrendo a lista.
  * **Editar:** Modifica o tamanho ou o número de adicionais de um pedido existente, buscando pelo nome do cliente.
  * **Excluir:** Remove um pedido específico da lista de forma eficiente.

#### Cálculo de Preço

  * O sistema calcula automaticamente o preço do pedido com base no tamanho escolhido e adicionando **R$ 1,50 por cada adicional** selecionado.

#### Persistência de Dados

  * **Carregamento Inicial:** Ao iniciar, o sistema carrega todos os pedidos do arquivo `pedidos_acai.txt` para a lista em memória.
  * **Salvamento Final:** Ao encerrar, todos os dados da lista são salvos de volta no arquivo `pedidos_acai.txt`, garantindo que nenhuma informação seja perdida.
  * **E-mails de Login:** Os e-mails utilizados continuam sendo salvos em `emails_usados.txt` para controle de unicidade.

#### Operações e Relatórios Específicos

  * **Calcular Faturamento Total:** Soma o valor de todos os pedidos da lista e informa o total arrecadado.
  * **Busca por Cliente (Otimizada):** Utiliza Quicksort e Busca Binária para localizar e exibir um pedido de um cliente específico de forma muito rápida.
  * **Listagem por Tamanho:** Filtra e exibe pedidos de um tamanho específico (ex: 500ml).
  * **Listagem por Adicionais:** Lista todos os pedidos que possuem mais do que 'N' adicionais.
  * **Listagem por Valor:** Filtra pedidos que custam acima de um determinado valor em reais.

## Como Compilar e Executar

Para utilizar o programa, siga os passos abaixo.

#### Pré-requisitos

  * Você precisa ter um compilador C instalado no seu sistema, como o **GCC**.

#### 1\. Compilação

Navegue pelo terminal até a pasta onde salvou os arquivos `main.c` e `pedidos.c`. Execute o seguinte comando para compilar o projeto:

```bash
gcc main.c pedidos.c -o projeto_ed1_3un
```

*Este comando irá compilar os dois arquivos-fonte e vinculá-los (linkar) em um único arquivo executável chamado `projeto_ed1_3un`.*

#### 2\. Execução

Após a compilação bem-sucedida, execute o programa com o comando:

```bash
./projeto_ed1_3un
```

*O sistema será iniciado, solicitando o login e, em seguida, exibindo o menu principal de funcionalidades.*
