#ifndef CADASTRAR_H
#define CADASTRAR_H

#include "pessoa.h"

void limpar_buffer_entrada();
int texto_possui_apenas_numeros(char texto[]);
int cpf_valido(char cpf[]);
int email_valido(char email[]);
int telefone_valido(char telefone[]);
int idade_valida(int idade);
Pessoa cadastrar_pessoa(int proximo_id);

#endif
