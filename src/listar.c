// Módulo responsável pela listagem e busca de pessoas cadastradas no sistema

#include "listar.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Implementação própria de strcasestr para busca de substring sem diferenciar maiúsculas de minúsculas.
// Retorna ponteiro para a primeira ocorrência de needle em haystack, ou NULL se não encontrar.
static char* meu_strcasestr(const char *haystack, const char *needle) {
    if (!*needle) return (char*)haystack;
    for (; *haystack; haystack++) {
        const char *h = haystack, *n = needle;
        while (*h && *n && tolower((unsigned char)*h) == tolower((unsigned char)*n)) {
            h++; n++;
        }
        if (!*n) return (char*)haystack;
    }
    return NULL;
}

// Exibe todos os registros do array no terminal, um por um com separador visual.
// Se o array estiver vazio, informa o usuário e encerra.
void listar_todos(Pessoa pessoas[], int total) {
    // Verifica se há registros antes de tentar listar
    if (total == 0) {
        printf("Lista vazia.\n");
        return;
    }

    // Percorre e imprime os dados de cada pessoa cadastrada
    for (int i = 0; i < total; i++) {
        printf("\nID: %d\n", pessoas[i].id);
        printf("Nome: %s\n", pessoas[i].nome);
        printf("CPF: %s\n", pessoas[i].cpf);
        printf("Idade: %d\n", pessoas[i].idade);
        printf("Email: %s\n", pessoas[i].email);
        printf("Telefone: %s\n", pessoas[i].telefone);
        printf("------------------\n");
    }
}

// Busca um registro pelo ID exato.
// Retorna ponteiro para a Pessoa encontrada, ou NULL se não existir.
Pessoa* buscar_por_id(Pessoa pessoas[], int total, int id) {
    // Percorre o array comparando o ID de cada registro
    for (int i = 0; i < total; i++) {
        if (pessoas[i].id == id) {
            return &pessoas[i];
        }
    }
    return NULL;
}

// Busca um registro pelo nome, sem diferenciar maiúsculas de minúsculas.
// Retorna ponteiro para a primeira Pessoa cujo nome contenha a substring informada, ou NULL se não encontrar.
Pessoa* buscar_por_nome(Pessoa pessoas[], int total, const char* nome) {
    // Percorre o array usando meu_strcasestr para comparação case-insensitive
    for (int i = 0; i < total; i++) {
        if (meu_strcasestr(pessoas[i].nome, nome)) {
            return &pessoas[i];
        }
    }
    return NULL;
}
