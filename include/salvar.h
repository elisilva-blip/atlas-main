// Cabeçalho do módulo de persistência — declara as funções de salvamento e restauração de dados

#ifndef SALVAR_H
#define SALVAR_H

#include "pessoa.h"

// Copia o arquivo principal para o backup, preservando o estado anterior
void fazer_backup(void);

// Serializa o array de pessoas em um arquivo binário no caminho informado
void salvar_em_arquivo(const char* path, Pessoa pessoas[], int total);

// Faz backup do estado atual e salva os novos dados no arquivo principal
void salvar_pessoas_em_binario(Pessoa pessoas[], int total);

// Salva os dados no arquivo principal sem gerar backup
void salvar_sem_backup(Pessoa pessoas[], int total);

// Restaura o array em memória e o arquivo principal a partir do backup, com confirmação do usuário
void restaurar_backup(Pessoa pessoas[], int *total);

#endif
