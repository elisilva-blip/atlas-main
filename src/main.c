// Ponto de entrada do sistema Atlas — inicializa os dados e gerencia o menu principal

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pessoa.h"
#include "cadastrar.h"
#include "listar.h"
#include "edicao.h"
#include "salvar.h"
#include "excluir.h"

// Limpa o terminal de forma compatível com Windows e sistemas Unix
void limpar_tela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Aguarda o usuário pressionar Enter e limpa a tela em seguida
void aguardar_enter() {
    printf("\nPressione Enter para continuar...");
    getchar();
    limpar_tela();
}

// Carrega os registros do arquivo binário para o array em memória.
// Se o arquivo não existir ou houver erro de leitura, inicializa o total como 0.
void carregar_pessoas(Pessoa pessoas[], int *total) {
    FILE *arquivo = fopen(DB_PATH, "rb");

    // Se o arquivo não existir, inicializa sem registros
    if (arquivo == NULL) {
        *total = 0;
        return;
    }

    // Lê o total de registros armazenados no início do arquivo
    if (fread(total, sizeof(int), 1, arquivo) != 1) {
        *total = 0;
    } else {
        // Garante que o total não ultrapasse o limite máximo do array
        if (*total > MAX_PESSOAS) {
            *total = MAX_PESSOAS;
        }

        // Lê os registros do arquivo para o array em memória
        if (fread(pessoas, sizeof(Pessoa), *total, arquivo) != (size_t)*total) {
            *total = 0;
        }
    }

    fclose(arquivo);
}

int main() {
    Pessoa pessoas[MAX_PESSOAS];
    int total = 0;
    int opcao;

    // Carrega os dados persistidos do arquivo binário ao iniciar o sistema
    carregar_pessoas(pessoas, &total);

    // Determina o maior ID existente para garantir que o próximo seja único
    int proximo_id = 0;
    for (int i = 0; i < total; i++)
        if (pessoas[i].id > proximo_id)
            proximo_id = pessoas[i].id;

    // Loop principal do sistema — exibe o menu e processa a opção escolhida
    do {
        printf("\n=====================================\n");
        printf("         SISTEMA ATLAS - v1.0        \n");
        printf("=====================================\n");
        printf("1. Cadastrar pessoa\n");
        printf("2. Listar pessoas\n");
        printf("3. Buscar por ID\n");
        printf("4. Buscar por nome\n");
        printf("5. Editar pessoa\n");
        printf("6. Excluir pessoa (backup preservado)\n");
        printf("7. Excluir permanentemente\n");
        printf("8. Restaurar backup\n");
        printf("0. Sair\n");
        printf("=====================================\n");
        printf("Escolha: ");

        // Lê a opção e trata entrada inválida para evitar loop infinito
        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n');
            opcao = -1;
        } else {
            getchar();
        }

        switch (opcao) {
            // Cadastra uma nova pessoa com ID sequencial e salva no arquivo
            case 1:
                if (total >= MAX_PESSOAS) {
                    printf("Limite atingido.\n");
                } else {
                    pessoas[total] = cadastrar_pessoa(++proximo_id);
                    total++;
                    salvar_pessoas_em_binario(pessoas, total);
                }
                break;

            // Exibe todos os registros cadastrados
            case 2:
                listar_todos(pessoas, total);
                break;

            // Busca e exibe um registro pelo ID informado
            case 3: {
                int id;
                printf("ID: ");
                scanf("%d", &id);
                getchar();

                Pessoa *p = buscar_por_id(pessoas, total, id);
                if (p) {
                    printf("\nID: %d\n", p->id);
                    printf("Nome: %s\n", p->nome);
                    printf("CPF: %s\n", p->cpf);
                    printf("Idade: %d\n", p->idade);
                    printf("Email: %s\n", p->email);
                    printf("Telefone: %s\n", p->telefone);
                } else {
                    printf("Nao encontrado.\n");
                }
                break;
            }

            // Busca e exibe todos os registros cujo nome contenha a substring informada
            case 4: {
                char nome[MAX_NOME];
                printf("Nome: ");
                fgets(nome, MAX_NOME, stdin);
                nome[strcspn(nome, "\n")] = '\0';

                int encontrados = 0;
                for (int i = 0; i < total; i++) {
                    if (buscar_por_nome(&pessoas[i], 1, nome)) {
                        printf("\nID: %d\n", pessoas[i].id);
                        printf("Nome: %s\n", pessoas[i].nome);
                        printf("CPF: %s\n", pessoas[i].cpf);
                        printf("Idade: %d\n", pessoas[i].idade);
                        printf("Email: %s\n", pessoas[i].email);
                        printf("Telefone: %s\n", pessoas[i].telefone);
                        printf("------------------\n");
                        encontrados++;
                    }
                }
                if (encontrados == 0) printf("Nao encontrado.\n");
                break;
            }

            // Abre o fluxo de edição de um registro existente
            case 5:
                editar_pessoa(pessoas, total);
                break;

            // Exclui um registro com backup automático (exclusão reversível)
            case 6:
                excluir_pessoa(pessoas, &total);
                break;

            // Exclui um registro permanentemente de todos os arquivos
            case 7:
                excluir_permanente(pessoas, &total);
                break;

            // Restaura o último estado salvo no arquivo de backup
            case 8:
                restaurar_backup(pessoas, &total);
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida.\n");
        }

        // Aguarda confirmação do usuário antes de exibir o menu novamente
        if (opcao != 0) {
            aguardar_enter();
        }

    } while (opcao != 0);

    return 0;
}
