// Módulo responsável pelo cadastro de novas pessoas no sistema

#include "cadastrar.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

// Remove caracteres residuais do buffer de entrada (evita leituras incorretas após scanf)
void limpar_buffer_entrada() {
    int caractere;
    // Lê e descarta caracteres até encontrar '\n' ou fim de arquivo
    while ((caractere = getchar()) != '\n' && caractere != EOF);
}

// Retorna 1 se todos os caracteres do texto forem dígitos, 0 caso contrário
int texto_possui_apenas_numeros(char texto[]) {
    int tamanho = strlen(texto);

    for (int i = 0; i < tamanho; i++) {
        if (!isdigit(texto[i])) {
            return 0; // Encontrou caractere não numérico: retorna falso imediatamente
        }
    }

    return 1;
}

// Valida CPF: deve ter exatamente 11 dígitos numéricos
int cpf_valido(char cpf[]) {
    return strlen(cpf) == 11 && texto_possui_apenas_numeros(cpf);
}

// Valida email: deve conter o caractere '@'
int email_valido(char email[]) {
    return strchr(email, '@') != NULL;
}

// Valida telefone: deve ter exatamente 11 dígitos numéricos
int telefone_valido(char telefone[]) {
    return strlen(telefone) == 11 && texto_possui_apenas_numeros(telefone);
}

// Valida idade: deve estar entre 0 e 100
int idade_valida(int idade) {
    return idade >= 0 && idade <= 100;
}

// Preenche e retorna uma nova Pessoa com ID sequencial e data/hora do cadastro
Pessoa cadastrar_pessoa(int proximo_id) {
    Pessoa p;

    p.id = proximo_id;
    p.data_cadastro = time(NULL); // Registra o momento exato do cadastro

    printf("\nDigite o nome: ");
    fgets(p.nome, MAX_NOME, stdin);
    p.nome[strcspn(p.nome, "\n")] = '\0'; // Remove o '\n' que fgets captura ao final

    // Loop repete até o usuário fornecer um CPF válido
    do {
        printf("Digite o CPF (11 digitos): ");
        scanf("%11s", p.cpf);
        if (!cpf_valido(p.cpf)) {
            printf("CPF invalido.\n");
        }
    } while (!cpf_valido(p.cpf));

    // Loop repete até a idade ser um número inteiro válido entre 0 e 100
    do {
        printf("Digite a idade: ");
        if (scanf("%d", &p.idade) != 1) { // Verifica se a leitura foi bem-sucedida (evita loop infinito com entrada textual)
            printf("Idade invalida.\n");
            limpar_buffer_entrada();
            p.idade = -1;
        } else {
            limpar_buffer_entrada();
            if (!idade_valida(p.idade)) {
                printf("Idade invalida.\n");
            }
        }
    } while (!idade_valida(p.idade));

    // Loop repete até o email conter '@'
    do {
        printf("Digite o email: ");
        scanf("%49s", p.email);
        if (!email_valido(p.email)) {
            printf("Email invalido.\n");
        }
    } while (!email_valido(p.email));

    // Loop repete até o telefone ter exatamente 11 dígitos
    do {
        printf("Digite o telefone (11 digitos): ");
        scanf("%11s", p.telefone);
        if (!telefone_valido(p.telefone)) {
            printf("Telefone invalido.\n");
        }
    } while (!telefone_valido(p.telefone));

    limpar_buffer_entrada();

    return p;
}
