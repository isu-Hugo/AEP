#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>


typedef struct {
    char nome[30];
    char senha[30];
} user;


void AdicionarUsuario() {
    FILE *file = fopen("usuarios.txt", "a");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    
    user usuario;
    printf("Digite o nome do usu�rio: ");
    scanf("%s", usuario.nome);
    printf("Digite a senha: ");
    scanf("%s", usuario.senha);

   //Aqui temos que achar algo para tentar cripografar esse carai 
   
    fprintf(file, "%s %s\n", usuario.nome, usuario.senha);
    fclose(file);
    printf("Usu�rio adicionado com sucesso.\n");
}

void ListaaUsuarios() {
    FILE *file = fopen("usuarios.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    
}
    
void deleteUser() {
    char NomeDeletar;
    printf("Digite o nome do usu�rio a ser deletado: ");
    scanf("%s", NomeDeletar);

    FILE *file = fopen("usuarios.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");
    if (file == NULL || tempFile == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
}
    
 void updateUser() {
    char NomeAtualizar;
    printf("Digite o nome do usu�rio a ser atualizado: ");
    scanf("%s", NomeAtualizar);

    FILE *file = fopen("usuarios.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");
    if (file == NULL || tempFile == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
}
   

int main(){
	setlocale(LC_ALL,"portuguese");
	
    int opcao;

    do {
        printf("\nSistema de Gerenciamento de Usu�rios\n");
        printf("1. Adicionar Usu�rio\n");
        printf("2. Listar Usu�rios\n");
        printf("3. Excluir Usu�rio\n");
        printf("4. Atualizar Usu�rio\n");
        printf("0. Sair\n");
        printf("Escolha uma op��o: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                AdicionarUsuario();
                break;
            case 2:
            	ListaaUsuarios();
                break;
            case 3:
                deleteUser();
                break;
            case 4:
            	updateUser();
                
                break;
            case 0:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Op��o inv�lida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
