#include "listar.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>


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

void listar_todos(Pessoa pessoas[], int total) {
    if (total == 0) {
        printf("Lista vazia.\n");
        return;
    }

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

Pessoa* buscar_por_id(Pessoa pessoas[], int total, int id) {
    for (int i = 0; i < total; i++) {
        if (pessoas[i].id == id) {
            return &pessoas[i];
        }
    }
    return NULL;
}

Pessoa* buscar_por_nome(Pessoa pessoas[], int total, const char* nome) {
    for (int i = 0; i < total; i++) {
        if (meu_strcasestr(pessoas[i].nome, nome)) {
            return &pessoas[i];
        }
    }
    return NULL;
}
