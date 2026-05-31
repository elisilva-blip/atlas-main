// Cabeçalho principal do sistema — define constantes globais e a estrutura Pessoa

#ifndef PESSOA_H
#define PESSOA_H

// Tamanhos máximos dos campos de texto
#define MAX_NOME     50
#define MAX_EMAIL    50
#define MAX_TELEFONE 12
#define MAX_CPF      12

// Limite máximo de pessoas armazenadas no sistema
#define MAX_PESSOAS  100

// Caminhos dos arquivos de dados e backup
#define DB_PATH      "pessoas.bin"
#define BACKUP_PATH  "pessoas.bak"

#include <time.h>

// Estrutura que representa uma pessoa cadastrada no sistema
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
