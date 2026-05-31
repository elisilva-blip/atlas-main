#include "salvar.h"
#include <stdio.h>

static void copiar_arquivo(const char* src, const char* dst) {
    FILE *origem = fopen(src, "rb");
    if (origem == NULL) return;

    FILE *destino = fopen(dst, "wb");
    if (destino == NULL) {
        fclose(origem);
        return;
    }

    char buffer[4096];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), origem)) > 0) {
        fwrite(buffer, 1, bytes, destino);
    }

    fclose(origem);
    fclose(destino);
}

void salvar_em_arquivo(const char* path, Pessoa pessoas[], int total) {
    FILE *f = fopen(path, "wb");
    if (f == NULL) {
        printf("Erro ao abrir arquivo '%s'.\n", path);
        return;
    }
    fwrite(&total, sizeof(int), 1, f);
    if (total > 0) {
        fwrite(pessoas, sizeof(Pessoa), total, f);
    }
    fclose(f);
}

void fazer_backup(void) {
    copiar_arquivo(DB_PATH, BACKUP_PATH);
}

void salvar_pessoas_em_binario(Pessoa pessoas[], int total) {
    copiar_arquivo(DB_PATH, BACKUP_PATH);
    salvar_em_arquivo(DB_PATH, pessoas, total);
    printf("Dados salvos.\n");
}

void salvar_sem_backup(Pessoa pessoas[], int total) {
    salvar_em_arquivo(DB_PATH, pessoas, total);
    printf("Dados salvos.\n");
}

void restaurar_backup(Pessoa pessoas[], int *total) {
    FILE *teste = fopen(BACKUP_PATH, "rb");
    if (teste == NULL) {
        printf("Nenhum backup encontrado ('%s' nao existe).\n", BACKUP_PATH);
        return;
    }
    fclose(teste);

    char confirm;
    printf("Tem certeza que deseja restaurar o backup?\n");
    printf("Os dados atuais serao substituidos pelo conteudo de '%s'. (s/n): ", BACKUP_PATH);
    scanf(" %c", &confirm);
    while (getchar() != '\n');

    if (confirm != 's' && confirm != 'S') {
        printf("Cancelado.\n");
        return;
    }

    copiar_arquivo(BACKUP_PATH, DB_PATH);

    FILE *f = fopen(DB_PATH, "rb");
    if (f == NULL) {
        printf("Erro ao reabrir arquivo apos restauracao.\n");
        return;
    }

    if (fread(total, sizeof(int), 1, f) != 1) {
        *total = 0;
    } else {
        if (*total > MAX_PESSOAS) *total = MAX_PESSOAS;
        if (fread(pessoas, sizeof(Pessoa), *total, f) != (size_t)*total) {
            *total = 0;
        }
    }
    fclose(f);

    printf("Backup restaurado com sucesso! %d registro(s) carregado(s).\n", *total);
}
