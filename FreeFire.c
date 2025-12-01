#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ITENS 100

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// Vetor
Item mochilaVetor[MAX_ITENS];
int totalVetor = 0;

// Contadores
int comparacoesSequencialV = 0;
int comparacoesBinariaV = 0;
int comparacoesSequencialL = 0;

// Lista Encadeada
No* inicio = NULL;

// Funções para Vetor
void inserirItemVetor(Item novo){
    if(totalVetor >= MAX_ITENS){
        printf("Mochila cheia!\n");
        return;
    }
    mochilaVetor[totalVetor++] = novo;
    printf("Item inserido no vetor!\n");
}

void removerItemVetor(char nome[]){
    for(int i = 0; i < totalVetor; i++){
        if(strcmp(mochilaVetor[i].nome, nome) == 0){
            for(int j = i; j < totalVetor-1; j++)
                mochilaVetor[j] = mochilaVetor[j+1];
            totalVetor--;
            printf("Item removido do vetor!\n");
            return;
        }
    }
    printf("Item nao encontrado no vetor!\n");
}

void listarVetor(){
    printf("--- Itens no Vetor ---\n");
    for(int i = 0; i < totalVetor; i++){
        printf("%s | %s | %d\n", mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
    }
}

Item* buscarSequencialVetor(char nome[]){
    comparacoesSequencialV = 0;
    for(int i = 0; i < totalVetor; i++){
        comparacoesSequencialV++;
        if(strcmp(mochilaVetor[i].nome, nome) == 0)
            return &mochilaVetor[i];
    }
    return NULL;
}

void ordenarVetor(){
    for(int i = 0; i < totalVetor-1; i++){
        for(int j = 0; j < totalVetor-1-i; j++){
            if(strcmp(mochilaVetor[j].nome, mochilaVetor[j+1].nome) > 0){
                Item temp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j+1];
                mochilaVetor[j+1] = temp;
            }
        }
    }
    printf("Vetor ordenado!\n");
}

Item* buscarBinariaVetor(char nome[]){
    int ini = 0, fim = totalVetor - 1;
    comparacoesBinariaV = 0;
    while(ini <= fim){
        int meio = (ini + fim) / 2;
        comparacoesBinariaV++;
        int cmp = strcmp(mochilaVetor[meio].nome, nome);

        if(cmp == 0) return &mochilaVetor[meio];
        else if(cmp < 0) ini = meio + 1;
        else fim = meio - 1;
    }
    return NULL;
}

// Funções para Lista Encadeada
void inserirItemLista(Item novo){
    No* n = (No*) malloc(sizeof(No));
    n->dados = novo;
    n->proximo = inicio;
    inicio = n;
    printf("Item inserido na lista!\n");
}

void removerItemLista(char nome[]){
    No* atual = inicio;
    No* anterior = NULL;

    while(atual != NULL){
        if(strcmp(atual->dados.nome, nome) == 0){
            if(anterior == NULL) inicio = atual->proximo;
            else anterior->proximo = atual->proximo;
            free(atual);
            printf("Item removido da lista!\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }

    printf("Item nao encontrado na lista!\n");
}

void listarLista(){
    No* aux = inicio;
    printf("--- Itens na Lista ---\n");
    while(aux != NULL){
        printf("%s | %s | %d\n", aux->dados.nome, aux->dados.tipo, aux->dados.quantidade);
        aux = aux->proximo;
    }
}

Item* buscarSequencialLista(char nome[]){
    No* aux = inicio;
    comparacoesSequencialL = 0;
    while(aux != NULL){
        comparacoesSequencialL++;
        if(strcmp(aux->dados.nome, nome) == 0)
            return &aux->dados;
        aux = aux->proximo;
    }
    return NULL;
}

// Menu Principal
int main(){
    int estrutura;

    while(1){
        printf("\nEscolha a estrutura:\n1 - Vetor\n2 - Lista Encadeada\n0 - Sair\n> ");
        scanf("%d", &estrutura);

        if(estrutura == 0) break;

        char nome[30];
        Item novo;
        int opc;

        switch(estrutura){
            case 1:
                do{
                    printf("\n--- Mochila Vetor ---\n1 - Inserir\n2 - Remover\n3 - Listar\n4 - Buscar Sequencial\n5 - Ordenar\n6 - Buscar Binaria\n0 - Voltar\n> ");
                    scanf("%d", &opc);

                    if(opc == 1){
                        printf("Nome: "); scanf("%s", novo.nome);
                        printf("Tipo: "); scanf("%s", novo.tipo);
                        printf("Qtd: "); scanf("%d", &novo.quantidade);
                        inserirItemVetor(novo);
                    }
                    else if(opc == 2){
                        printf("Nome para remover: "); scanf("%s", nome);
                        removerItemVetor(nome);
                    }
                    else if(opc == 3){ listarVetor(); }
                    else if(opc == 4){
                        printf("Nome da busca: "); scanf("%s", nome);
                        Item* r = buscarSequencialVetor(nome);
                        if(r) printf("Encontrado! Comparacoes: %d\n", comparacoesSequencialV);
                        else printf("Nao encontrado!\n");
                    }
                    else if(opc == 5){ ordenarVetor(); }
                    else if(opc == 6){
                        printf("Nome da busca: "); scanf("%s", nome);
                        Item* r = buscarBinariaVetor(nome);
                        if(r) printf("Encontrado! Comparacoes: %d\n", comparacoesBinariaV);
                        else printf("Nao encontrado!\n");
                    }
                } while(opc != 0);
                break;

            case 2:
                do{
                    printf("\n--- Mochila Lista ---\n1 - Inserir\n2 - Remover\n3 - Listar\n4 - Buscar Sequencial\n0 - Voltar\n> ");
                    scanf("%d", &opc);

                    if(opc == 1){
                        printf("Nome: "); scanf("%s", novo.nome);
                        printf("Tipo: "); scanf("%s", novo.tipo);
                        printf("Qtd: "); scanf("%d", &novo.quantidade);
                        inserirItemLista(novo);
                    }
                    else if(opc == 2){
                        printf("Nome para remover: "); scanf("%s", nome);
                        removerItemLista(nome);
                    }
                    else if(opc == 3){ listarLista(); }
                    else if(opc == 4){
                        printf("Nome da busca: "); scanf("%s", nome);
                        Item* r = buscarSequencialLista(nome);
                        if(r) printf("Encontrado! Comparacoes: %d\n", comparacoesSequencialL);
                        else printf("Nao encontrado!\n");
                    }
                } while(opc != 0);
                break;
        }
    }

    return 0;
}