#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <windows.h>

typedef struct No
{
    char nome[100];
    char telefone[17];
    char email[100];
    struct No *direita;
    struct No *esquerda;
} No;

void resposta(char *mensagem);
void copiarTexto(char *destino, char *origem, size_t tamanho);
void lerTexto(char *mensagem, char *destino, size_t tamanho);
No *criarNo(char *nome, char *telefone, char *email);
No *inserir(No *raiz, char *nome, char *telefone, char *email);
No *buscar(No *raiz, char *nome);
void listarEmOrdem(No *raiz);
void listarContatos(No *raiz);
No *menorNo(No *no);
No *removerNo(No *raiz, char *nome, int *removido);
void liberar(No *raiz);

int main()
{
    setlocale(LC_ALL, "Portuguese");
    int escolha;
    char opcao[17];
    char nome[100], telefone[100], email[100];
    No *raiz = NULL;
    do
    {
        printf("====== Sistema de Gerenciamento de Contatos ======\n\n1 - Inserir contato\n2 - Buscar contato\n3 - Remover contato\n4 - Listar contatos\n5 - Sair do programa\n\n");
        lerTexto("Op��o: ", opcao, sizeof(opcao));
        escolha = atoi(opcao);
        switch (escolha)
        {
        case 1:
            system("cls");
            lerTexto("Digite o nome do contato: ", nome, sizeof(nome));
            if (nome[0] == '\0')
            {
                resposta("O nome n�o pode ser vazio.\n");
                break;
            }
            if (buscar(raiz, nome) != NULL)
            {
                resposta("O contato j� est� Cadastrado.\n");
                break;
            }
            lerTexto("\nDigite o telefone do contato: ", telefone, sizeof(telefone));
            lerTexto("\nDigite o email do contato: ", email, sizeof(email));
            raiz = inserir(raiz, nome, telefone, email);
            break;
        case 2:
        {
            system("cls");
            lerTexto("Digite o nome que deseja procurar: ", nome, sizeof(nome));
            No *encontrado = buscar(raiz, nome);
            if (encontrado == NULL)
            {
                resposta("Contato n�o encontrado.\n");
            }
            else
            {
                system("cls");
                printf("Contato Encontrado:\nNome: %s | Telefone: %s | EmaiL: %s\n\n", encontrado->nome, encontrado->telefone, encontrado->email);
                system("Pause");
                system("cls");
            }
            break;
        }
        case 3:
        {
            system("cls");
            lerTexto("Digite o nome do contato que deseja remover: ", nome, sizeof(nome));
            int removido = 0;
            raiz = removerNo(raiz, nome, &removido);
            if (removido)
            {
                resposta("Contato removido com sucesso.\n");
            }
            else
            {
                resposta("Contato n�o encontrado.\n");
            }
            break;
        }
        case 4:
            listarContatos(raiz);
            break;
        case 5:
            system("cls");
            printf("------ Programa Finalizado ------\n");
            break;
        default:
            resposta("Escolha Inv�lida.\n");
            break;
        }
    } while (escolha != 5);
    liberar(raiz);
    return 0;
}

void resposta(char *mensagem)
{
    system("cls");
    printf("%s", mensagem);
    system("Pause");
    system("cls");
}

void copiarTexto(char *destino, char *origem, size_t tamanho)
{
    strncpy(destino, origem, tamanho);
    destino[tamanho - 1] = '\0';
}

void lerTexto(char *mensagem, char *destino, size_t tamanho)
{
    printf("%s", mensagem);
    if (fgets(destino, tamanho, stdin) == NULL)
    {
        destino[0] = '\0';
        return;
    }
    destino[strcspn(destino, "\n")] = '\0';
}

void liberar(No *raiz)
{
    if (raiz == NULL)
    {
        return;
    }
    liberar(raiz->esquerda);
    liberar(raiz->direita);
    free(raiz);
}

No *criarNo(char *nome, char *telefone, char *email)
{
    No *novo = malloc(sizeof(No));
    if (novo == NULL)
    {
        return NULL;
    }
    copiarTexto(novo->nome, nome, sizeof(novo->nome));
    copiarTexto(novo->telefone, telefone, sizeof(novo->telefone));
    copiarTexto(novo->email, email, sizeof(novo->email));
    novo->direita = NULL;
    novo->esquerda = NULL;
    return novo;
}

No *inserir(No *raiz, char *nome, char *telefone, char *email)
{
    if (raiz == NULL)
    {
        No *novo = criarNo(nome, telefone, email);
        if (novo == NULL)
        {
            resposta("Erro na cria��o do N�.\n");
            return NULL;
        }
        else
        {
            resposta("Contato inserido com sucesso.\n");
            return novo;
        }
    }
    int cmp = _stricmp(nome, raiz->nome);

    if (cmp < 0)
    {
        raiz->esquerda = inserir(raiz->esquerda, nome, telefone, email);
    }
    else if (cmp > 0)
    {
        raiz->direita = inserir(raiz->direita, nome, telefone, email);
    }
    return raiz;
}

No *buscar(No *raiz, char *nome)
{
    if (raiz == NULL)
    {
        return NULL;
    }
    int cmp = _stricmp(nome, raiz->nome);
    if (cmp == 0)
    {
        return raiz;
    }
    if (cmp < 0)
    {
        return buscar(raiz->esquerda, nome);
    }
    return buscar(raiz->direita, nome);
}

void listarEmOrdem(No *raiz)
{
    if (raiz == NULL)
    {
        return;
    }
    listarEmOrdem(raiz->esquerda);
    printf("Nome: %s | Telefone: %s | E-mail: %s\n",
           raiz->nome, raiz->telefone, raiz->email);
    listarEmOrdem(raiz->direita);
}

void listarContatos(No *raiz)
{
    if (raiz == NULL)
    {
        resposta("Nenhum contato cadastrado.\n");
        return;
    }
    system("cls");
    printf("=== Contatos em ordem alfabetica ===\n");
    listarEmOrdem(raiz);
    printf("\n");
    system("Pause");
    system("cls");
}

No *menorNo(No *no)
{
    while (no->esquerda != NULL)
    {
        no = no->esquerda;
    }
    return no;
}

No *removerNo(No *raiz, char *nome, int *removido)
{
    if (raiz == NULL)
    {
        return NULL;
    }
    int cmp = _stricmp(nome, raiz->nome);
    if (cmp < 0)
    {
        raiz->esquerda = removerNo(raiz->esquerda, nome, removido);
    }
    else if (cmp > 0)
    {
        raiz->direita = removerNo(raiz->direita, nome, removido);
    }
    else
    {
        *removido = 1;
        if (raiz->esquerda == NULL)
        {
            No *filho = raiz->direita;
            free(raiz);
            return filho;
        }
        if (raiz->direita == NULL)
        {
            No *filho = raiz->esquerda;
            free(raiz);
            return filho;
        }
        No *sucessor = menorNo(raiz->direita);
        copiarTexto(raiz->nome, sucessor->nome, sizeof(raiz->nome));
        copiarTexto(raiz->telefone, sucessor->telefone, sizeof(raiz->telefone));
        copiarTexto(raiz->email, sucessor->email, sizeof(raiz->email));
        raiz->direita = removerNo(raiz->direita, sucessor->nome, removido);
    }
    return raiz;
}