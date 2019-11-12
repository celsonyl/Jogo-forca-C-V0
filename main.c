#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "forca.h"

void forca(int argc,char  *argv[]){
    NoSecreto * lstSecreta = inicializaListaSecreta();
    char fNameArq[255];
    NoSecreto * sorteada;
    int posSorteada=0;
    int tamanhoLista=0;
    int aux;

    strcpy(fNameArq,"palavras.dat");

    if(argc>1){
      strcpy(fNameArq,argv[1]);
    }

    printf("Arquivo de dados: %s\n\n\n",fNameArq);



    lstSecreta = carregaListaArquivo(lstSecreta,fNameArq);
    imprimeListaSecreta(lstSecreta);
    tamanhoLista = tamanhoListaSecreta(lstSecreta);

    do{
        system("cls");
        sorteada= sorteiaPalavra(lstSecreta);
        if(aux!=NULL){
            int perdeu;
            int tentativas = 0;
            char letra;
            int tamPlv = strlen(sorteada->palavra);
            char pSorteio[31] = " ";
            char viewPlv[tamPlv-1];
            for(int i = 0; i <= tamPlv; i++){
                viewPlv[i] = '_';
            }

            while((strcmp(sorteada->palavra, pSorteio) != 0)){
                system("cls");
                for(int i=0; i < tamPlv; i++){
                    printf("%c", viewPlv[i]);
                }
                printf(" \nAssunto: %s", sorteada->assunto);
                printf("\nDigite uma letra:\n");
                scanf("%c", &letra);
                for(int i=0; i <=tamPlv; i++){
                    if(letra == sorteada->palavra[i]){
                        pSorteio[i] = letra;
                        viewPlv[i] = letra;
                    }
                }

                tentativas++;
                if(tentativas/2 >= tamPlv*3){
                    strcpy(pSorteio, sorteada->palavra);
                    perdeu = 1;
                }else{
                    perdeu = 0;
                }
            }
            system("cls");
            if(perdeu == 1){
                printf("Perdeu, tentativas: %d\n", tentativas/2);
            }else{
                printf("Ganhou, tentativas: %d\n", tentativas/2);
            }

            system("pause");
            aux = NULL;
        }else{
            printf("Final de jogo, pressione F para sair\n\n");
        }
    }while(getchar()!='f');
}

char config(char nome[]){
    printf("Nome: \n");
    scanf("%s", nome);

    return nome;

}

void msg(char nome[]){
    system("cls");
    printf("Adeus, %s \n", nome);
}


int main(int argc, char *argv[])
{
    char nome[25] = "????";
    int aux=0;
    int escolha;
    do{
        system("cls");
        printf("1.Configuracao\n2.Jogar\n0.Sair\n\n");
        scanf("%d", &escolha);
            switch(escolha){
            case 1:
                printf("Digite seu nome: ");
                scanf("%s", nome);
                printf("Nome gravado com sucesso, %s!\n", nome);
                system("pause");
            break;

            case 2:
               forca(argc, argv);
            break;

            case 0:
               msg(nome);
               aux = 1;
            break;

            default:
                printf("Tecla invalida!\n");
                system("pause");
            }
    }while(aux==0);
    return 0;
}

