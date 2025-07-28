# projeto-de-ED1

## Sistema de Gerenciamento - Açaiteria Bom Sabor (V 2.0)

Este projeto é um Sistema de Gerenciamento de Pedidos para uma Açaíteria desenvolvida em C. O sistema utiliza manipulação de arquivos de texto para persistência de dados e programação estruturada para implementação de operações básicas (Registrar, Listar, Editar, Excluir) e relatórios diversos.

*Observação: Esta versão foi aprimorada para utilizar listas encadeadas para um gerenciamento de dados mais eficiente em memória, implementa algoritmos de ordenação (Quicksort) e busca (Busca Binária), e foi modularizada em arquivos `.h` e `.c`.*

## Funcionalidades

### Sistema de Login

  * **Autenticação de Usuário:** Login baseado em usuário e senha pré-definida.
     *USUARIO: teste
     *SENHA: teste1234
  * **Validação de E-mail:** Solicita um e-mail após o login, garantindo que ele contenha o caractere `@` e que seja único (não tenha sido utilizado nos logins anteriores).

### Operações Básicas de Pedidos de Açaí

  * **Registrar:** Cadastro de novos pedidos, incluindo nome do cliente, tamanho do copo (300ml, 500ml, 700ml) e número de adicionais.
  * **Listar:** Exibe todos os pedidos registrados na base de dados.
  * **Editar:** Modifica o tamanho ou o número de adicionais de um pedido existente, buscando pelo nome do cliente.
  * **Excluir:** Remover um pedido específico da base de dados.

### Cálculo de Preço

O sistema calcula automaticamente o preço do pedido com base no tamanho escolhido e adicionando R$ 1,50 por cada adicional selecionado.

### Persistência de Dados

  * **Pedidos:** Todas as informações dos pedidos são salvas no arquivo `pedidos_acai.txt`.
  * **E-mails de Login:** Os e-mails utilizados nos logins são salvos em `emails_usados.txt` para controle de unicidade.

### Operações e Relatórios Específicos

  * **Calcular Faturamento Total:** Soma o valor de todos os pedidos registrados e informa o total arrecadado.
  * **Busca por Cliente:** Localiza e lista todos os pedidos feitos para um cliente específico (utilizando busca binária otimizada).
  * **Listagem por Tamanho:** Filtra e exibe pedidos de um tamanho específico (ex: 500ml).
  * **Listagem por Adicionais:** Lista todos os pedidos que possuem mais do que 'N' adicionais (onde 'N' é definido pelo usuário).
  * **Listagem por Valor:** Filtra pedidos que custam acima de um determinado valor em reais.

-----

## Como Compilar e Executar

Para compilar e rodar o projeto, você precisará de um compilador C (como o GCC).

**1. Compilar o programa:**

Abra o terminal na pasta do projeto e execute o comando abaixo. 

```bash
gcc main.c pedidos.c -o projeto_ed1_3un
```

**2. Executar o programa:**

Após a compilação, execute o arquivo gerado com o seguinte comando:

```bash
./projeto_ed1_3un
```
