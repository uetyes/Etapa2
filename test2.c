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
          scanf("%d %d %[^\n]", &rest[i * 4 + j].codigo_prato, &rest[i * 4 +j].codigo_resturante, rest[i * 4 +j].descricao); //nao está lendo o preço

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
        if(codigo_rest == cad[i].codigo){
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
    strcpy(cad[index].nome," ");
}

void RenomearPrato(restaurante *rest,int index,int opcao_prato){
    printf("Digite novo nome:");
    scanf(" %[^\n]",rest[index * 4 + opcao_prato - 1]);
}

void DeletarPrato(restaurante *rest,int index){
    rest[index].codigo_prato = -1;
    rest[index].preco = 0.0;
    strcpy(rest[index].descricao," ");
}

void AlterarPrecoPrato(restaurante *rest,int opcao_prato,int index){
    printf("%s - Digite novo preco:\n",rest[index * 4 + opcao_prato - 1].descricao);
    scanf("%f",&rest[index * 4 + opcao_prato - 1].preco);
}

int MenuOpcaoPrato(restaurante *rest,int index,int opcao_prato){
    int escolha_prato;
    printf("%s - Menu de opcoes:\n",rest[index * 4 + opcao_prato - 1].descricao);
    printf("1 - Renomear\n");
    printf("2 - Alterar preco\n");
    printf("3 - Deletar\n");
    printf("0 - Voltar ao menu anterior");
    scanf("%d",&escolha_prato);

    if(escolha_prato == 1){
        RenomearPrato(rest,index,opcao_prato);
    }
    else if(escolha_prato == 2){
        AlterarPrecoPrato(rest,opcao_prato,index);
    }
    else if(escolha_prato == 3){
        DeletarPrato(rest,index);
    }
    else if(escolha_prato == 0){
        return(0);
    }
    return 1;
}

void MenuPratos(restaurante *rest,int index){
    int opcao_prato;
    for(int i = 0;i < 4;i++){
        printf("%d - %s - Preco: R$%.2f\n",rest[index * 4 + i].codigo_prato,rest[index * 4 + i].descricao,rest[index * 4 + i].preco);
    }
     scanf("%d",&opcao_prato);
    MenuOpcaoPrato(rest,index,opcao_prato);
}




int MenuOpcoes(cadastro *cad,restaurante *rest,int index){
    int escolha;
    int opcao_prato_temp;
    printf("%s - Menu Opcoes\n",cad[index].nome);
    printf("1 - Renomear\n");
    printf("2 - Deletar\n");
    printf("3 - Mostrar pratos\n");
    printf("0 - Logout\n");
    scanf("%d",&escolha);

    if(escolha == 1){
        RenomearRest(cad,index);
    }
    else if(escolha == 2){
        DeletarRest(cad,index);
    }
    else if(escolha == 3){
        MenuPratos(rest,index);
    }
    else if(escolha == 0){

    }
    return (escolha);
}

int main(){
    //Cabeçalho
    Line();
    printf("uaiFood - Restaurante\n");
    Line();

    //declarar e alocar dinamicamente as variaveis do tipo struct
    restaurante *rest;
    cadastro *cad;
    cad = malloc(sizeof(cadastro) * TAM);
    rest = malloc(sizeof(restaurante) * TAM * 4);

    Cadastro(cad,rest);

    int codigo_rest;

    while(1){
        printf("\nLOGIN UAIFOOD RESTAURANTE\n");
        printf("Digite o codigo do restaurante (ou um numero negativo para sair):\n");
        scanf("%d",&codigo_rest);
        if(codigo_rest < 0)
        break;

        int index = (Verifica(cad,codigo_rest));
        int continuar = 1;

        while(continuar){
            if(index != -1){
                if(MenuOpcoes(cad,rest,index) != 1){
                    continuar = 0;
                }
            } 
            else{
                printf("Restaurante nao econtrado.Tente novamente.\n");
                break;
            }
        }

    }
        

    return 0;
}

