#ifndef LISTAR_H
#define LISTAR_H

#include "pessoa.h"

void listar_todos(Pessoa pessoas[], int total);
Pessoa* buscar_por_id(Pessoa pessoas[], int total, int id);
Pessoa* buscar_por_nome(Pessoa pessoas[], int total, const char* nome);

#endif
