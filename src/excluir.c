#include "excluir.h"
#include "salvar.h"
#include <stdio.h>
#include <string.h>

void excluir_pessoa(Pessoa pessoas[], int *total) {
    int id;
    int idx = -1;

    printf("\nID para excluir: ");
    scanf("%d", &id);
    while (getchar() != '\n');

    for (int i = 0; i < *total; i++) {
        if (pessoas[i].id == id) {
            idx = i;
            break;
        }
    }

    if (idx == -1) {
        printf("Nao encontrado.\n");
        return;
    }

    printf("Nome: %s | CPF: %s\n", pessoas[idx].nome, pessoas[idx].cpf);

    char confirm;
    printf("Tem certeza que quer excluir? (s/n): ");
    scanf(" %c", &confirm);
    while (getchar() != '\n');

    if (confirm != 's' && confirm != 'S') {
        printf("Cancelado.\n");
        return;
    }

    fazer_backup(); /* preserva estado atual no .bak ANTES de remover */

    for (int i = idx; i < *total - 1; i++) {
        pessoas[i] = pessoas[i + 1];
    }
    (*total)--;

    salvar_sem_backup(pessoas, *total);

    printf("Excluido com sucesso. Use a opcao 8 para desfazer.\n");
}

void excluir_permanente(Pessoa pessoas[], int *total) {
    int id;
    int idx = -1;

    printf("\nID para excluir PERMANENTEMENTE: ");
    scanf("%d", &id);
    while (getchar() != '\n');

    for (int i = 0; i < *total; i++) {
        if (pessoas[i].id == id) {
            idx = i;
            break;
        }
    }

    if (idx == -1) {
        printf("Nao encontrado.\n");
        return;
    }

    printf("Nome: %s | CPF: %s\n", pessoas[idx].nome, pessoas[idx].cpf);

    char confirm;
    printf("ATENCAO: Esta acao e IRREVERSIVEL!\n");
    printf("Confirma exclusao permanente? (s/n): ");
    scanf(" %c", &confirm);
    while (getchar() != '\n');

    if (confirm != 's' && confirm != 'S') {
        printf("Cancelado.\n");
        return;
    }

    for (int i = idx; i < *total - 1; i++) {
        pessoas[i] = pessoas[i + 1];
    }
    (*total)--;

    salvar_em_arquivo(DB_PATH,     pessoas, *total);
    salvar_em_arquivo(BACKUP_PATH, pessoas, *total);

    printf("Excluido permanentemente de ambos os arquivos.\n");
}
