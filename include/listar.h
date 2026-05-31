// Cabeçalho do módulo de listagem — declara as funções de exibição e busca de pessoas cadastradas

#ifndef LISTAR_H
#define LISTAR_H

#include "pessoa.h"

// Exibe todos os registros cadastrados no terminal
void listar_todos(Pessoa pessoas[], int total);

// Busca um registro pelo ID exato — retorna ponteiro para a Pessoa ou NULL se não encontrar
Pessoa* buscar_por_id(Pessoa pessoas[], int total, int id);

// Busca um registro pelo nome sem diferenciar maiúsculas de minúsculas — retorna ponteiro para a primeira ocorrência ou NULL se não encontrar
Pessoa* buscar_por_nome(Pessoa pessoas[], int total, const char* nome);

#endif
