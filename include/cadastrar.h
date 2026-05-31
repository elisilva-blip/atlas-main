// Cabeçalho do módulo de cadastro — declara as funções de validação e cadastro de pessoas

#ifndef CADASTRAR_H
#define CADASTRAR_H

#include "pessoa.h"

// Remove caracteres residuais do buffer de entrada
void limpar_buffer_entrada();

// Retorna 1 se todos os caracteres do texto forem dígitos, 0 caso contrário
int texto_possui_apenas_numeros(char texto[]);

// Retorna 1 se o CPF tiver exatamente 11 dígitos numéricos, 0 caso contrário
int cpf_valido(char cpf[]);

// Retorna 1 se o email contiver o caractere '@', 0 caso contrário
int email_valido(char email[]);

// Retorna 1 se o telefone tiver exatamente 11 dígitos numéricos, 0 caso contrário
int telefone_valido(char telefone[]);

// Retorna 1 se a idade estiver entre 0 e 100, 0 caso contrário
int idade_valida(int idade);

// Coleta os dados do usuário, valida e retorna uma nova Pessoa com o ID informado
Pessoa cadastrar_pessoa(int proximo_id);

#endif
