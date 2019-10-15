#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "forca.h"

//gera um numero aleatorio entre 1 e 'maximo'
int geraAleatorio(int maximo)
{
    time_t t;
    int n=0;
    srand((unsigned) time(&t));
    n = (rand() % maximo)+1;
    return n;
}

NoSecreto * inicializaListaSecreta()
{
    return NULL;
}

NoSecreto * inserePalavraSecreta(NoSecreto *l,char word[31],char subject[100])
{
    NoSecreto * novo;
    novo = (NoSecreto *) malloc(sizeof(NoSecreto));
    novo->status=0;
    strcpy(novo->assunto,subject);
    strcpy(novo->palavra,word);
    novo->prox = l;
    l=novo;
    return l;
}

void imprimeListaSecreta(NoSecreto *l)
{
    for(NoSecreto *p=l; p!=NULL; p=p->prox)
    {
        printf("%d) %-30s\t%s\n", p->status,p->palavra,p->assunto);
    }
}

NoSecreto * carregaListaArquivo(NoSecreto * l, char nomeArq[255])
{
    const char ch[2]=";";
    char * token;
    int status;
    char palavra[31];
    char assunto[101];
    char * linha[1024];
    FILE * fWords;

    fWords = fopen(nomeArq,"r");
    if(fWords==NULL){
        printf("Falha ao acessar base de dados!!!\n\n");
        exit(0);
    }
    while(fgets(linha,1024,fWords))
    {
        token = strtok(linha,ch);
        if(token!=NULL)
        {
             strcpy(palavra,token);
        }
        token=strtok(NULL,ch);
        if(token!=NULL)
        {
            strcpy(assunto,token);
        }
        l = inserePalavraSecreta(l,palavra, assunto);
    }

    fclose(fWords);
    return l;
}

//
int tamanhoListaSecreta(NoSecreto *l)
{
    int n=0;
    for(NoSecreto *p=l;p!=NULL;p=p->prox,n++);
    return n;
}

int temPalavraNaoUsada(NoSecreto *l)
{
    NoSecreto *p;
    for(p=l;p!=NULL;p=p->prox){
        if(p->status==0) return 1;
    }
    return 0;
}

NoSecreto * sorteiaPalavra(NoSecreto *l)
{
    int tam = tamanhoListaSecreta(l);
    int aleatorio=0;
    int tentativas = 0;
    NoSecreto * p;

    while(temPalavraNaoUsada(l)){
        aleatorio = geraAleatorio(tam);
        p = retornaPalavraPos(l,aleatorio);
        if(p->status==0){
            p->status = 1;
            return p;
        }
    }
    return NULL;
}

//retorna a palavra que está na posicao 'pos' da lisata secreta
NoSecreto * retornaPalavraPos(NoSecreto *l, int pos)
{
    int n=1;
    NoSecreto *p;
    for(p=l; p!=NULL; p=p->prox)
    {
        if(n==pos) break;
        n++;
    }
    return p;
}
