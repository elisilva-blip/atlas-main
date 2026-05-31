#ifndef SALVAR_H
#define SALVAR_H

#include "pessoa.h"

void fazer_backup(void);
void salvar_em_arquivo(const char* path, Pessoa pessoas[], int total);
void salvar_pessoas_em_binario(Pessoa pessoas[], int total);
void salvar_sem_backup(Pessoa pessoas[], int total);
void restaurar_backup(Pessoa pessoas[], int *total);

#endif
