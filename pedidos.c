#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "pedidos.h"

Node *listaDePedidos = NULL;

static float calcularPreco(char* tamanho, int numAdicionais) {
    float precoBase = 0;
    if(strstr(tamanho, "300")) precoBase = 10.0;
    else if(strstr(tamanho, "500")) precoBase = 14.0;
    else if(strstr(tamanho, "700")) precoBase = 18.0;
    else precoBase = 12.0;
    return precoBase + (numAdicionais * 1.50);
}

static void imprimirDetalhesPedido(Acai p) {
    printf("----------------------------------------\n");
    printf("Cliente: %s\n", p.nomeCliente);
    printf("Tamanho: %s\n", p.tamanho);
    printf("Adicionais: %d\n", p.numAdicionais);
    printf("Preco: R$ %.2f\n", p.preco);
}

static void adicionarPedidoNaLista(Acai pedido) {
    Node *novoNode = (Node*) malloc(sizeof(Node));
    if (!novoNode) {
        printf("Erro de alocacao de memoria!\n");
        return;
    }
    novoNode->data = pedido;
    novoNode->next = listaDePedidos;
    listaDePedidos = novoNode;
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void carregarPedidosDoArquivo() {
    FILE *arquivo = fopen("pedidos_acai.txt", "r");
    if (arquivo == NULL) return;
    liberarLista();
    Acai p;
    while (fscanf(arquivo, "%[^;];%[^;];%d;%f\n", p.nomeCliente, p.tamanho, &p.numAdicionais, &p.preco) == 4) {
        adicionarPedidoNaLista(p);
    }
    fclose(arquivo);
}

void salvarPedidosNoArquivo() {
    FILE *arquivo = fopen("pedidos_acai.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo para salvar!\n");
        return;
    }
    Node *atual = listaDePedidos;
    while (atual != NULL) {
        fprintf(arquivo, "%s;%s;%d;%.2f\n", atual->data.nomeCliente, atual->data.tamanho, atual->data.numAdicionais, atual->data.preco);
        atual = atual->next;
    }
    fclose(arquivo);
}

void liberarLista() {
    Node *atual = listaDePedidos;
    Node *proximo;
    while (atual != NULL) {
        proximo = atual->next;
        free(atual);
        atual = proximo;
    }
    listaDePedidos = NULL;
}

void registrarPedido() {
    Acai novoPedido;
    printf("\n--- Registrar Novo Pedido ---\n");
    printf("Nome do Cliente: ");
    fgets(novoPedido.nomeCliente, 80, stdin);
    novoPedido.nomeCliente[strcspn(novoPedido.nomeCliente, "\n")] = 0;
    printf("Tamanho do copo (ex: 300ml, 500ml, 700ml): ");
    fgets(novoPedido.tamanho, 80, stdin);
    novoPedido.tamanho[strcspn(novoPedido.tamanho, "\n")] = 0;
    printf("Quantidade de adicionais: ");
    scanf("%d", &novoPedido.numAdicionais);
    limparBuffer();
    novoPedido.preco = calcularPreco(novoPedido.tamanho, novoPedido.numAdicionais);
    printf("Preco do pedido: R$ %.2f\n", novoPedido.preco);
    adicionarPedidoNaLista(novoPedido);
    printf("Pedido registrado com sucesso!\n");
}

void listarTodosPedidos() {
    if (listaDePedidos == NULL) {
        printf("\nNenhum pedido registrado.\n");
        return;
    }
    printf("\n--- Lista de Todos os Pedidos ---\n");
    Node *atual = listaDePedidos;
    while(atual != NULL) {
        imprimirDetalhesPedido(atual->data);
        atual = atual->next;
    }
    printf("----------------------------------------\n");
}

void editarPedido() {
    char nomeBusca[80];
    printf("\n--- Editar Pedido ---\n");
    if (listaDePedidos == NULL) {
        printf("Nenhum pedido para editar.\n");
        return;
    }
    printf("Nome do cliente para editar: ");
    fgets(nomeBusca, 80, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;

    Node *atual = listaDePedidos;
    int encontrado = 0;
    while(atual != NULL) {
        if (strcasecmp(atual->data.nomeCliente, nomeBusca) == 0) {
            encontrado = 1;
            printf("Editando pedido de '%s'.\n", atual->data.nomeCliente);
            printf("Novo Tamanho: ");
            fgets(atual->data.tamanho, 80, stdin);
            atual->data.tamanho[strcspn(atual->data.tamanho, "\n")] = 0;
            printf("Nova Quantidade de Adicionais: ");
            scanf("%d", &atual->data.numAdicionais);
            limparBuffer();
            atual->data.preco = calcularPreco(atual->data.tamanho, atual->data.numAdicionais);
            printf("Pedido atualizado com sucesso!\n");
        }
        atual = atual->next;
    }

    if (!encontrado) {
        printf("\nPedido nao encontrado.\n");
    }
}

void excluirPedido() {
    char nomeBusca[80];
    printf("\n--- Excluir Pedido ---\n");
     if (listaDePedidos == NULL) {
        printf("Nenhum pedido para excluir.\n");
        return;
    }
    printf("Nome do cliente para excluir: ");
    fgets(nomeBusca, 80, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;

    Node *atual = listaDePedidos;
    Node *anterior = NULL;
    int encontrado = 0;

    while (atual != NULL) {
        if (strcasecmp(atual->data.nomeCliente, nomeBusca) == 0) {
            encontrado = 1;
            Node* proximo = atual->next;
            if (anterior == NULL) {
                listaDePedidos = proximo;
            } else {
                anterior->next = proximo;
            }
            free(atual);
            atual = proximo;
        } else {
            anterior = atual;
            atual = atual->next;
        }
    }

    if (encontrado) {
        printf("Pedido(s) excluido(s) com sucesso!\n");
    } else {
        printf("\nPedido nao encontrado.\n");
    }
}

void calcularFaturamentoTotal() {
    if (listaDePedidos == NULL) {
        printf("\nNenhum pedido registrado.\n");
        return;
    }
    float faturamento = 0.0;
    int totalPedidos = 0;
    Node* atual = listaDePedidos;
    while (atual != NULL) {
        faturamento += atual->data.preco;
        totalPedidos++;
        atual = atual->next;
    }
    printf("\n--- Faturamento Total ---\n");
    printf("Total de pedidos: %d\n", totalPedidos);
    printf("Faturamento total: R$ %.2f\n", faturamento);
}

void listarPedidosPorTamanho() {
    if (listaDePedidos == NULL) {
        printf("\nNenhum pedido registrado.\n"); return;
    }
    char tamanhoBusca[80];
    printf("\n--- Listar Pedidos por Tamanho ---\n");
    printf("Digite o tamanho para buscar (ex: 500ml): ");
    fgets(tamanhoBusca, 80, stdin);
    tamanhoBusca[strcspn(tamanhoBusca, "\n")] = 0;

    int encontrados = 0;
    Node* atual = listaDePedidos;
    printf("\nPedidos de tamanho '%s':\n", tamanhoBusca);
    while (atual != NULL) {
        if (strcasecmp(atual->data.tamanho, tamanhoBusca) == 0) {
            imprimirDetalhesPedido(atual->data);
            encontrados++;
        }
        atual = atual->next;
    }
    if (encontrados == 0) {
        printf("Nenhum pedido encontrado para este tamanho.\n");
    }
}

void listarPedidosComMaisDeNAdicionais() {
    if (listaDePedidos == NULL) {
        printf("\nNenhum pedido registrado.\n"); return;
    }
    int n;
    printf("\n--- Listar Pedidos por No. de Adicionais ---\n");
    printf("Mostrar pedidos com mais de quantos adicionais? ");
    scanf("%d", &n);
    limparBuffer();

    int encontrados = 0;
    Node* atual = listaDePedidos;
    printf("\nPedidos com mais de %d adicional(is):\n", n);
    while (atual != NULL) {
        if (atual->data.numAdicionais > n) {
            imprimirDetalhesPedido(atual->data);
            encontrados++;
        }
        atual = atual->next;
    }
    if (encontrados == 0) {
        printf("Nenhum pedido encontrado com mais de %d adicional(is).\n", n);
    }
}

void listarPedidosAcimaDeValor() {
    if (listaDePedidos == NULL) {
        printf("\nNenhum pedido registrado.\n"); return;
    }
    float valorBusca;
    printf("\n--- Listar Pedidos Acima de um Valor ---\n");
    printf("Mostrar pedidos com valor acima de: R$ ");
    scanf("%f", &valorBusca);
    limparBuffer();
    
    int encontrados = 0;
    Node* atual = listaDePedidos;
    printf("\nPedidos com valor acima de R$ %.2f:\n", valorBusca);
    while (atual != NULL) {
        if (atual->data.preco > valorBusca) {
            imprimirDetalhesPedido(atual->data);
            encontrados++;
        }
        atual = atual->next;
    }
    if (encontrados == 0) {
        printf("Nenhum pedido encontrado acima deste valor.\n");
    }
}

static int partition(Acai arr[], int low, int high) {
    Acai pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (strcmp(arr[j].nomeCliente, pivot.nomeCliente) < 0) {
            i++;
            Acai temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    Acai temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

static void quickSort(Acai arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

static int binarySearch(Acai arr[], int l, int r, char* nome) {
    while (l <= r) {
        int m = l + (r - l) / 2;
        int res = strcmp(arr[m].nomeCliente, nome);
        if (res == 0) return m;
        if (res < 0) l = m + 1;
        else r = m - 1;
    }
    return -1;
}

void buscarPedidoPorCliente() {
    if (listaDePedidos == NULL) {
        printf("\nNenhum pedido registrado para buscar.\n"); return;
    }

    int count = 0;
    Node *temp = listaDePedidos;
    while(temp != NULL) {
        count++;
        temp = temp->next;
    }

    Acai *arrayDePedidos = (Acai*) malloc(count * sizeof(Acai));
    if(!arrayDePedidos) {
        printf("Erro de alocacao de memoria!\n"); return;
    }

    temp = listaDePedidos;
    for(int i = 0; i < count; i++) {
        arrayDePedidos[i] = temp->data;
        temp = temp->next;
    }

    quickSort(arrayDePedidos, 0, count - 1);
    
    char nomeBusca[80];
    printf("\n--- Buscar Pedido por Cliente (Otimizado) ---\n");
    printf("Digite o nome do cliente: ");
    fgets(nomeBusca, 80, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;

    int resultado = binarySearch(arrayDePedidos, 0, count - 1, nomeBusca);

    if(resultado != -1) {
        printf("\nPedido encontrado!\n");
        imprimirDetalhesPedido(arrayDePedidos[resultado]);
    } else {
        printf("\nPedido para o cliente '%s' nao encontrado.\n", nomeBusca);
    }

    free(arrayDePedidos);
}