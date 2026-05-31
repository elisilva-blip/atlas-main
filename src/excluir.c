// Módulo responsável pela exclusão de pessoas cadastradas no sistema

#include "excluir.h"
#include "salvar.h"
#include <stdio.h>
#include <string.h>

// Remove uma pessoa do array pelo ID, com confirmação do usuário e backup automático.
// A exclusão pode ser desfeita pela opção 8 do sistema.
void excluir_pessoa(Pessoa pessoas[], int *total) {
    int id;
    int idx = -1;

    // Solicita o ID da pessoa a ser excluída
    printf("\nID para excluir: ");
    scanf("%d", &id);
    while (getchar() != '\n');

    // Percorre o array procurando o registro com o ID informado
    for (int i = 0; i < *total; i++) {
        if (pessoas[i].id == id) {
            idx = i;
            break;
        }
    }

    // Se não encontrado, encerra a função sem realizar alterações
    if (idx == -1) {
        printf("Nao encontrado.\n");
        return;
    }

    // Exibe os dados do registro encontrado para confirmação do usuário
    printf("Nome: %s | CPF: %s\n", pessoas[idx].nome, pessoas[idx].cpf);

    // Solicita confirmação antes de prosseguir com a exclusão
    char confirm;
    printf("Tem certeza que quer excluir? (s/n): ");
    scanf(" %c", &confirm);
    while (getchar() != '\n');

    // Se o usuário não confirmar, cancela a operação
    if (confirm != 's' && confirm != 'S') {
        printf("Cancelado.\n");
        return;
    }

    // Preserva o estado atual no arquivo .bak antes de remover
    fazer_backup();

    // Desloca os elementos seguintes uma posição à esquerda, sobrescrevendo o excluído
    for (int i = idx; i < *total - 1; i++) {
        pessoas[i] = pessoas[i + 1];
    }
    (*total)--;

    // Salva as alterações sem gerar um novo backup
    salvar_sem_backup(pessoas, *total);

    printf("Excluido com sucesso. Use a opcao 8 para desfazer.\n");
}

// Remove uma pessoa do array pelo ID de forma permanente e irreversível,
// atualizando tanto o arquivo principal quanto o backup.
void excluir_permanente(Pessoa pessoas[], int *total) {
    int id;
    int idx = -1;

    // Solicita o ID da pessoa a ser excluída permanentemente
    printf("\nID para excluir PERMANENTEMENTE: ");
    scanf("%d", &id);
    while (getchar() != '\n');

    // Percorre o array procurando o registro com o ID informado
    for (int i = 0; i < *total; i++) {
        if (pessoas[i].id == id) {
            idx = i;
            break;
        }
    }

    // Se não encontrado, encerra a função sem realizar alterações
    if (idx == -1) {
        printf("Nao encontrado.\n");
        return;
    }

    // Exibe os dados do registro encontrado para confirmação do usuário
    printf("Nome: %s | CPF: %s\n", pessoas[idx].nome, pessoas[idx].cpf);

    // Alerta o usuário sobre a irreversibilidade da operação e solicita confirmação
    char confirm;
    printf("ATENCAO: Esta acao e IRREVERSIVEL!\n");
    printf("Confirma exclusao permanente? (s/n): ");
    scanf(" %c", &confirm);
    while (getchar() != '\n');

    // Se o usuário não confirmar, cancela a operação
    if (confirm != 's' && confirm != 'S') {
        printf("Cancelado.\n");
        return;
    }

    // Desloca os elementos seguintes uma posição à esquerda, sobrescrevendo o excluído
    for (int i = idx; i < *total - 1; i++) {
        pessoas[i] = pessoas[i + 1];
    }
    (*total)--;

    // Sobrescreve tanto o arquivo principal quanto o backup, tornando a exclusão permanente
    salvar_em_arquivo(DB_PATH,     pessoas, *total);
    salvar_em_arquivo(BACKUP_PATH, pessoas, *total);

    printf("Excluido permanentemente de ambos os arquivos.\n");
}
