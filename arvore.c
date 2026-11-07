#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

typedef struct No{
    char nome[50];
    char telefone[16];
    char email[50];
    struct No *direita;
    struct No *esquerda;
} No;

void copiarTexto(char *destino, char *origem, size_t tamanho){
    strncpy(destino, origem, tamanho);
    destino[tamanho - 1] = '\0';
}

No* criarNo(char *nome, char *telefone, char *email){
    No *novo = malloc(sizeof(No));
    if (novo == NULL){
        printf("Erro na criação do Nó.\n");
        return NULL;
    }
    copiarTexto(novo->nome, nome, sizeof(nome->nome));
    copiarTexto(novo->telefone, telefone, sizeof(nome->telefone));
    copiarTexto(novo->email, email, sizeof(nome->email));
    novo->direita = NULL;
    novo->esquerda = NULL;
    return novo;
}

No* buscar(No *raiz, char *nome) {

    if (raiz == NULL) {
        return NULL;
    }

    // Verifica se encontrou o contato
    if (strcmp(raiz->nome, nome) == 0) {
        return raiz;
    }

    // Procura na esquerda
    No *resultado = buscar(raiz->esquerda, nome);

    if (resultado != NULL) {
        return resultado;
    }

    // Procura na direita
    return buscar(raiz->direita, nome);
}

int main(){
    setlocale(LC_ALL, "Portuguese");
    printf("Olá, Mundo!");
    return 0;
}