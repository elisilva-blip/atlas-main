#ifndef PESSOA_H
#define PESSOA_H

#define MAX_NOME     50
#define MAX_EMAIL    50
#define MAX_TELEFONE 12
#define MAX_CPF      12
#define MAX_PESSOAS  100
#define DB_PATH      "pessoas.bin"
#define BACKUP_PATH  "pessoas.bak"

#include <time.h>

typedef struct {
    int id;
    char nome[MAX_NOME];
    char cpf[MAX_CPF];
    int idade;
    char email[MAX_EMAIL];
    char telefone[MAX_TELEFONE];
    time_t data_cadastro;
} Pessoa;

#endif
