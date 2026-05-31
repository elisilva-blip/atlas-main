// Módulo responsável pela edição dos dados de pessoas já cadastradas no sistema

#include "edicao.h"
#include "pessoa.h"
#include "cadastrar.h"
#include "salvar.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Permite ao usuário editar os campos de uma pessoa existente, identificada pelo ID.
// Campos deixados em branco (Enter) mantêm o valor atual.
void editar_pessoa(Pessoa pessoas[], int total) {
    int id;
    int indice = -1;

    // Solicita o ID da pessoa a ser editada
    printf("\nID para editar: ");
    scanf("%d", &id);
    limpar_buffer_entrada();

    // Percorre o array procurando o registro com o ID informado
    for (int i = 0; i < total; i++) {
        if (pessoas[i].id == id) {
            indice = i;
            break;
        }
    }

    // Se não encontrado, encerra a função sem realizar alterações
    if (indice == -1) {
        printf("\nNao encontrado.\n");
        return;
    }

    // Ponteiro direto para o registro a ser editado e buffer temporário de leitura
    Pessoa *p = &pessoas[indice];
    char buf[100];

    // Edição do nome — mantém o valor atual se o usuário pressionar Enter
    do {
        printf("Novo nome (Enter para manter '%s'): ", p->nome);
        fgets(buf, sizeof(buf), stdin);

        if (strlen(buf) == sizeof(buf) - 1 && buf[sizeof(buf) - 2] != '\n') {
            limpar_buffer_entrada();
        }

        buf[strcspn(buf, "\n")] = '\0';

        if (buf[0] == '\0') {
            break;
        }

        if (strlen(buf) == 0) {
            printf("Nome nao pode ser vazio.\n");
            continue;
        }

        strcpy(p->nome, buf);
        break;
    } while (1);

    // Edição do CPF — valida 11 dígitos numéricos antes de atualizar
    do {
        printf("Novo CPF (Enter para manter '%s'): ", p->cpf);
        fgets(buf, sizeof(buf), stdin);
        buf[strcspn(buf, "\n")] = '\0';

        if (buf[0] == '\0') {
            break;
        }

        if (cpf_valido(buf)) {
            strcpy(p->cpf, buf);
            break;
        }

        printf("CPF invalido. Digite 11 digitos numericos.\n");
    } while (1);

    // Edição da idade — converte string para inteiro e valida o intervalo (0 a 100)
    do {
        printf("Nova idade (Enter para manter '%d'): ", p->idade);
        fgets(buf, sizeof(buf), stdin);
        buf[strcspn(buf, "\n")] = '\0';

        if (buf[0] == '\0') {
            break;
        }

        char *endptr;
        long val = strtol(buf, &endptr, 10);

        if (*endptr != '\0') {
            printf("Idade invalida. Digite apenas numeros.\n");
            continue;
        }

        if (!idade_valida((int)val)) {
            printf("Idade invalida. Deve ser entre 0 e 100.\n");
            continue;
        }

        p->idade = (int)val;
        break;
    } while (1);

    // Edição do email — valida presença do caractere '@' antes de atualizar
    do {
        printf("Novo email (Enter para manter '%s'): ", p->email);
        fgets(buf, sizeof(buf), stdin);
        buf[strcspn(buf, "\n")] = '\0';

        if (buf[0] == '\0') {
            break;
        }

        if (email_valido(buf)) {
            strcpy(p->email, buf);
            break;
        }

        printf("Email invalido. Deve conter '@'.\n");
    } while (1);

    // Edição do telefone — valida 11 dígitos numéricos antes de atualizar
    do {
        printf("Novo telefone (Enter para manter '%s'): ", p->telefone);
        fgets(buf, sizeof(buf), stdin);
        buf[strcspn(buf, "\n")] = '\0';

        if (buf[0] == '\0') {
            break;
        }

        if (telefone_valido(buf)) {
            strcpy(p->telefone, buf);
            break;
        }

        printf("Telefone invalido. Digite 11 digitos numericos.\n");
    } while (1);

    // Persiste as alterações no arquivo binário
    salvar_pessoas_em_binario(pessoas, total);
    printf("\nAtualizado com sucesso.\n");
}
