// Cabeçalho do módulo de exclusão — declara as funções de remoção de pessoas cadastradas

#ifndef EXCLUIR_H
#define EXCLUIR_H

#include "pessoa.h"

// Remove uma pessoa pelo ID com backup automático — exclusão pode ser desfeita pela opção 8
void excluir_pessoa(Pessoa pessoas[], int *total);

// Remove uma pessoa pelo ID permanentemente de todos os arquivos — operação irreversível
void excluir_permanente(Pessoa pessoas[], int *total);

#endif
