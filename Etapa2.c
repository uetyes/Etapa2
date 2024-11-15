#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define TAM_STRING 50
#define TAM 3

typedef struct{
    char nome[TAM_STRING];
    int codigo;
}cadastro;

typedef struct{
    int codigo_prato;
    int codigo_resturante;
    char descricao[TAM_STRING];
    float preco;
}restaurante;

void Line(){
        for(int i = 0;i < 50;i++){
            printf("*");
        }
        printf("\n");
}

void CadastroPrato(restaurante *rest,cadastro  *cad,int i){
        printf("Cadastre codigo do prato, codigo do restaurante, descricao e preco dos pratos do restaurante %s\n",cad[i].nome);
        for(int j = 0; j < 4;j++){
          scanf("%d %d %[^\n]", &rest[i * 4 + j].codigo_prato, &rest[i * 4 +j].codigo_resturante, rest[i * 4 +j].descricao); 
                //encontrar o os ultimos espaços na string
                char *last_space = strrchr(rest[i * 4 + j].descricao, ' ');
                if(last_space != NULL){
                    rest[i * 4 +j].preco = atof(last_space + 1); //converter para float
                    *last_space = '\0'; //garantir que a string termine com o \0
            }
        }
}

void Cadastro(cadastro *cad,restaurante *rest){
    for(int i = 0;i < TAM;i++){
        printf("Digite o codigo e nome do restaurante %d:\n",i+1);
        scanf("%d %[^\n]",&cad[i].codigo,cad[i].nome);
        CadastroPrato(rest,cad,i);
    }
}

int Verifica(cadastro *cad,int codigo_rest){
    for(int i = 0;i < TAM;i++){
        if(codigo_rest == cad[i].codigo) {
            return i;
        }
    }
    return -1;
}

void RenomearRest(cadastro *cad,int index){
    printf("Digite o novo nome: ");
    scanf(" %[^\n]",cad[index].nome);
}

void DeletarRest(cadastro *cad,int index){
    cad[index].codigo = -1;
    strcpy(cad[index].nome, " ");
}

void RenomearPrato(restaurante *rest,int index,int opcao_prato){
    printf("Digite novo nome: ");
    scanf(" %[^\n]", rest[index * 4 + opcao_prato - 1].descricao);
}

void DeletarPrato(restaurante *rest,int index,int opcao_prato,cadastro *cad){ 
    rest[index * 4 + opcao_prato - 1].codigo_prato = -1;
    rest[index * 4 + opcao_prato - 1].codigo_resturante = -1;
    strcpy(rest[index * 4 + opcao_prato - 1].descricao, "");
    rest[index * 4 + opcao_prato - 1].preco = 0.0;
    cad[index].codigo = -1;
    rest[index * 4 + opcao_prato - 1].codigo_resturante = -1;
}


void AlterarPrecoPrato(restaurante *rest,int opcao_prato,int index){
    printf("%s - Digite novo preco: ",rest[index * 4 + opcao_prato - 1].descricao);
    scanf("%f",&rest[index * 4 + opcao_prato - 1].preco);
}

void MenuOpcaoPrato (restaurante *rest,int index,int opcao_prato,cadastro *cad){
    //menu de opçoes dos pratos
    int escolha_prato;
    printf("%s - Menu de opcoes:\n",rest[index * 4 + opcao_prato - 1].descricao);
    printf("1 - Renomear\n");
    printf("2 - Alterar preco\n");
    printf("3 - Deletar\n");
    printf("0 - Voltar ao menu anterior\n");
    scanf("%d",&escolha_prato);

      switch(escolha_prato){

        case 0: break;

        case 1: RenomearPrato(rest,index,opcao_prato); break;

        case 2: AlterarPrecoPrato(rest,opcao_prato,index); break;

        case 3: DeletarPrato(rest,index,opcao_prato,cad); break;

    }
}

void MenuPratos(restaurante *rest,int index,cadastro *cad){
    int opcao_prato;
    do{
        printf("%s - Pratos - Menu Opcoes\n",cad[index].nome);
        for(int i = 0;i < 4;i++){
        printf("%d - %s - Preco: R$%.2f\n",rest[index * 4 + i].codigo_prato,rest[index * 4 + i].descricao,rest[index * 4 + i].preco);
    }
    printf("0 - Voltar ao menu anterior\n");
    scanf("%d",&opcao_prato);
    if(opcao_prato != 0){
    MenuOpcaoPrato(rest,index,opcao_prato,cad);
    }
    } while(opcao_prato != 0);
}

int MenuOpcoes(cadastro *cad,restaurante *rest,int index){
    //menu de opçoes do restaurante
    int escolha;
    printf("\n%s - Menu Opcoes\n",cad[index].nome);
    printf("1 - Renomear\n");
    printf("2 - Deletar\n");
    printf("3 - Mostrar pratos\n");
    printf("0 - Logout\n");
    scanf("%d",&escolha);

    switch(escolha){

        case 1: RenomearRest(cad,index); break;

        case 2: DeletarRest(cad,index); break;

        case 3: MenuPratos(rest, index,cad); break;

        case 0: return escolha;break;

    }
    return (escolha);
}

int main(){
    //Cabeçalho
    Line();
    printf("uaiFood - Restaurante\n");
    Line();

    //declarar e alocar dinamicamente as variaveis do tipo struct
    restaurante *rest = malloc(sizeof(restaurante) * TAM * 4);
    cadastro *cad = malloc(sizeof(cadastro) * TAM);

    Cadastro(cad,rest); //exibir o cadastro dos pratos

    //laço de repetiçao para o login
    int codigo_rest;
    while(1){
        printf("\nLOGIN UAIFOOD RESTAURANTE\n");
        printf("\nDigite o codigo do restaurante (ou um numero negativo para sair):\n");
        scanf("%d",&codigo_rest);

        if(codigo_rest < 0) break;

        int index = (Verifica(cad,codigo_rest));

        if(index == -1){
            printf("Restaurante nao encontrado.Tente novamente.\n");
            continue;
        }   

        int escolha;
        do{
            escolha = MenuOpcoes(cad,rest,index);
        }while(escolha != 0 && escolha != 2);

    }
    free(cad);
    free(rest);
        return 0;
}