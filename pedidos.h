#ifndef PEDIDOS_H
#define PEDIDOS_H

typedef struct {
    char nomeCliente[80];
    char tamanho[80];
    int numAdicionais;
    float preco;
} Acai;

typedef struct Node {
    Acai data;
    struct Node *next;
} Node;

extern Node *listaDePedidos;

void carregarPedidosDoArquivo();
void salvarPedidosNoArquivo();
void liberarLista();
void limparBuffer();

void registrarPedido();
void listarTodosPedidos();
void editarPedido();
void excluirPedido();


void calcularFaturamentoTotal();
void listarPedidosPorTamanho();
void listarPedidosComMaisDeNAdicionais();
void listarPedidosAcimaDeValor();
void buscarPedidoPorCliente();

#endif 