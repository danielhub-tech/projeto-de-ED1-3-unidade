#include <stdio.h>
#include <string.h>
#include "pedidos.h"

// !AVISO!
// USUARIO: teste
// SENHA: teste1234

int realizarLoginComEmail() {
    char usuario[80], senha[80], email[80];

    printf("\n--- TELA DE LOGIN ---\n");
    printf("Usuario: ");
    scanf("%s", usuario);
    limparBuffer();

    printf("Senha: ");
    scanf("%s", senha);
    limparBuffer();

    if (strcmp(usuario, "teste") != 0 || strcmp(senha, "teste1234") != 0) {
        printf("\nUsuario ou senha incorretos.");
        return 0;
    }

    while (1) {
        printf("E-mail: ");
        scanf("%s", email);
        limparBuffer();

        if (strchr(email, '@') == NULL) {
            printf("O e-mail informado deve conter '@', tente novamente.\n");
            continue;
        }

        FILE *arquivoEmails = fopen("emails_usados.txt", "r");
        int emailJaExiste = 0;
        if (arquivoEmails != NULL) {
            char emailSalvo[80];
            while (fscanf(arquivoEmails, "%s", emailSalvo) != EOF) {
                if (strcmp(email, emailSalvo) == 0) {
                    emailJaExiste = 1;
                    break;
                }
            }
            fclose(arquivoEmails);
        }

        if (emailJaExiste) {
            printf("Este e-mail ja foi utilizado, tente novamente.\n");
            continue;
        }

        arquivoEmails = fopen("emails_usados.txt", "a");
        if (arquivoEmails != NULL) {
            fprintf(arquivoEmails, "%s\n", email);
            fclose(arquivoEmails);
        }
        break;
    }
    
    return 1;
}

void exibirMenuPrincipal() {
    printf("\n--- BEM VINDO(A) ACAITERIA BOM SABOR ---\n");
    printf("1. Registrar Pedido\n");
    printf("2. Listar Todos os Pedidos\n");
    printf("3. Editar um Pedido\n");
    printf("4. Excluir um Pedido\n");
    printf("5. Buscar Pedido por Cliente\n");
    printf("--------------------------------------------\n");
    printf("6. Calcular Faturamento Total\n");
    printf("7. Listar Pedidos por Tamanho\n");
    printf("8. Listar Pedidos com Mais de 'N' Adicionais\n");
    printf("9. Listar Pedidos Acima de um Valor\n");
    printf("--------------------------------------------\n");
    printf("0. Salvar e Sair\n");
}

int main() {
    carregarPedidosDoArquivo();

    while (realizarLoginComEmail() != 1) {
        printf("\nTente novamente.\n");
    }

    int opcaoPrincipal;
    do {
        exibirMenuPrincipal();
        printf("Opcao: ");
        scanf("%d", &opcaoPrincipal);
        limparBuffer();

        switch (opcaoPrincipal) {
            case 1: registrarPedido(); break;
            case 2: listarTodosPedidos(); break;
            case 3: editarPedido(); break;
            case 4: excluirPedido(); break;
            case 5: buscarPedidoPorCliente(); break;
            case 6: calcularFaturamentoTotal(); break;
            case 7: listarPedidosPorTamanho(); break;
            case 8: listarPedidosComMaisDeNAdicionais(); break;
            case 9: listarPedidosAcimaDeValor(); break;
            case 0: break;
            default: printf("\nOpcao invalida.\n"); break;
        }
    } while (opcaoPrincipal != 0);

    printf("\nSalvando todos os pedidos...");
    salvarPedidosNoArquivo();
    liberarLista();
    printf("\nSistema encerrado.\n");

    return 0;
}