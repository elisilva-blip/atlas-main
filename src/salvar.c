// Módulo responsável por salvar, fazer backup e restaurar os dados do sistema

#include "salvar.h"
#include <stdio.h>

// Copia o conteúdo de um arquivo binário para outro em blocos de 4096 bytes.
// Encerra silenciosamente se qualquer um dos arquivos não puder ser aberto.
static void copiar_arquivo(const char* src, const char* dst) {
    FILE *origem = fopen(src, "rb");
    if (origem == NULL) return;

    FILE *destino = fopen(dst, "wb");
    if (destino == NULL) {
        fclose(origem);
        return;
    }

    // Lê e escreve em blocos até que todo o conteúdo seja copiado
    char buffer[4096];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), origem)) > 0) {
        fwrite(buffer, 1, bytes, destino);
    }

    fclose(origem);
    fclose(destino);
}

// Serializa o array de pessoas em um arquivo binário no caminho informado.
// Grava primeiro o total de registros e em seguida os dados de cada pessoa.
void salvar_em_arquivo(const char* path, Pessoa pessoas[], int total) {
    FILE *f = fopen(path, "wb");
    if (f == NULL) {
        printf("Erro ao abrir arquivo '%s'.\n", path);
        return;
    }

    // Grava o total de registros seguido dos dados de cada pessoa
    fwrite(&total, sizeof(int), 1, f);
    if (total > 0) {
        fwrite(pessoas, sizeof(Pessoa), total, f);
    }
    fclose(f);
}

// Copia o arquivo principal para o backup, preservando o estado anterior
void fazer_backup(void) {
    copiar_arquivo(DB_PATH, BACKUP_PATH);
}

// Salva os dados no arquivo principal, criando um backup do estado anterior antes de sobrescrever
void salvar_pessoas_em_binario(Pessoa pessoas[], int total) {
    copiar_arquivo(DB_PATH, BACKUP_PATH);
    salvar_em_arquivo(DB_PATH, pessoas, total);
    printf("Dados salvos.\n");
}

// Salva os dados no arquivo principal sem gerar backup
void salvar_sem_backup(Pessoa pessoas[], int total) {
    salvar_em_arquivo(DB_PATH, pessoas, total);
    printf("Dados salvos.\n");
}

// Restaura o array em memória a partir do arquivo de backup, com confirmação do usuário.
// Sobrescreve o arquivo principal com o conteúdo do backup e recarrega os dados em memória.
void restaurar_backup(Pessoa pessoas[], int *total) {
    // Verifica se o arquivo de backup existe antes de prosseguir
    FILE *teste = fopen(BACKUP_PATH, "rb");
    if (teste == NULL) {
        printf("Nenhum backup encontrado ('%s' nao existe).\n", BACKUP_PATH);
        return;
    }
    fclose(teste);

    // Solicita confirmação do usuário antes de substituir os dados atuais
    char confirm;
    printf("Tem certeza que deseja restaurar o backup?\n");
    printf("Os dados atuais serao substituidos pelo conteudo de '%s'. (s/n): ", BACKUP_PATH);
    scanf(" %c", &confirm);
    while (getchar() != '\n');

    // Se o usuário não confirmar, cancela a operação
    if (confirm != 's' && confirm != 'S') {
        printf("Cancelado.\n");
        return;
    }

    // Sobrescreve o arquivo principal com o conteúdo do backup
    copiar_arquivo(BACKUP_PATH, DB_PATH);

    // Reabre o arquivo principal para recarregar os dados em memória
    FILE *f = fopen(DB_PATH, "rb");
    if (f == NULL) {
        printf("Erro ao reabrir arquivo apos restauracao.\n");
        return;
    }

    // Lê o total de registros e em seguida os dados de cada pessoa
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
