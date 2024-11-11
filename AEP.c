#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

#define MAX_USERS 100
#define FILE_NAME "usuarios.txt"
#define SHIFT 3  // Shift para cifra de César (criptografia simples)

typedef struct {
    int id;
    char nome[50];
    char senha[50];
} Usuario;

// Função para criptografar a senha usando cifra de César
void criptografar(char *texto) {
    int i;
    for (i = 0; i < strlen(texto); i++) {
        texto[i] = texto[i] + SHIFT;
    }
}

// Função para descriptografar a senha
void descriptografar(char *texto) {
    int i;
    for (i = 0; i < strlen(texto); i++) {
        texto[i] = texto[i] - SHIFT;
    }
}

// Função para salvar usuário no arquivo
void salvarUsuario(Usuario usuario) {
    FILE *file = fopen(FILE_NAME, "a");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
    fprintf(file, "%d %s %s\n", usuario.id, usuario.nome, usuario.senha);
    fclose(file);
}

// Função para carregar todos os usuários do arquivo
int carregarUsuarios(Usuario usuarios[]) {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 0;
    }

    int i = 0;
    while (fscanf(file, "%d %s %s", &usuarios[i].id, usuarios[i].nome, usuarios[i].senha) != EOF) {
        descriptografar(usuarios[i].senha); // Descriptografa a senha ao carregar
        i++;
    }
    fclose(file);
    return i;
}

// Função para listar usuários
void listarUsuarios() {
    Usuario usuarios[MAX_USERS];
    int total;
	total = carregarUsuarios(usuarios);

    printf("Lista de Usuários:\n");
    int i;
    for (i = 0; i < total; i++) {
        printf("ID: %d, Nome: %s\n", usuarios[i].id, usuarios[i].nome);
    }
}

// Função para adicionar um novo usuário
void adicionarUsuario() {
    Usuario usuario;
    printf("ID do Usuário: ");
    scanf("%d", &usuario.id);
    printf("Nome do Usuário: ");
    scanf("%s", usuario.nome);
    printf("Senha do Usuário: ");
    scanf("%s", usuario.senha);

    criptografar(usuario.senha); // Criptografa a senha antes de salvar
    salvarUsuario(usuario);

    printf("Usuário adicionado com sucesso!\n");
}

// Função para alterar um usuário existente
void alterarUsuario() {
    Usuario usuarios[MAX_USERS];
    int total = carregarUsuarios(usuarios);
    int id, encontrado = 0;

    printf("ID do Usuário a ser alterado: ");
    scanf("%d", &id);

    int i;
    for (i = 0; i < total; i++) {
        if (usuarios[i].id == id) {
            encontrado = 1;
            printf("Novo Nome do Usuário: ");
            scanf("%s", usuarios[i].nome);
            printf("Nova Senha do Usuário: ");
            scanf("%s", usuarios[i].senha);

            // Criptografa a nova senha
            criptografar(usuarios[i].senha);
            break;
        }
    }

    if (!encontrado) {
        printf("Usuário não encontrado!\n");
        return;
    }

    // Reescreve o arquivo com os dados atualizados
    FILE *file = fopen(FILE_NAME, "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    for (i = 0; i < total; i++) {
        fprintf(file, "%d %s %s\n", usuarios[i].id, usuarios[i].nome, usuarios[i].senha);
    }
    fclose(file);
    printf("Usuário alterado com sucesso!\n");
}

// Função para excluir um usuário
void excluirUsuario() {
    Usuario usuarios[MAX_USERS];
    int total = carregarUsuarios(usuarios);
    int id, encontrado = 0;

    printf("ID do Usuário a ser excluído: ");
    scanf("%d", &id);

    FILE *file = fopen(FILE_NAME, "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    int i;
    for (i = 0; i < total; i++) {
        if (usuarios[i].id == id) {
            encontrado = 1;
            continue;
        }
        fprintf(file, "%d %s %s\n", usuarios[i].id, usuarios[i].nome, usuarios[i].senha);
    }
    fclose(file);

    if (encontrado) {
        printf("Usuário excluído com sucesso!\n");
    } else {
        printf("Usuário não encontrado!\n");
    }
}

// Menu principal
void menu() {
    int opcao;

    do {
        printf("\n--- Sistema de Gerenciamento de Usuários ---\n");
        printf("1. Incluir novo usuário\n");
        printf("2. Alterar usuário\n");
        printf("3. Excluir usuário\n");
        printf("4. Listar usuários\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarUsuario();
                system("cls");
                break;
            case 2:
                alterarUsuario();
                system("cls");
                break;
            case 3:
                excluirUsuario();
                system("cls");
                break;
            case 4:
                listarUsuarios();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);
}

int main() {
    setlocale(LC_ALL, "portuguese");
    menu();
    return 0;
}
