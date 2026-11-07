# Gerenciamento de Contatos — Árvore Binária em C

Projeto em C que implementa um sistema de gerenciamento de contatos utilizando uma estrutura de **árvore binária**.

---

## Estrutura de Dados

### `No`

Cada nó da árvore representa um contato e armazena:

| Campo       | Tipo     | Tamanho | Descrição                  |
|-------------|----------|---------|----------------------------|
| `nome`      | `char[]` | 50      | Nome do contato            |
| `telefone`  | `char[]` | 16      | Número de telefone         |
| `email`     | `char[]` | 50      | Endereço de e-mail         |
| `esquerda`  | `No*`    | —       | Ponteiro para filho esquerdo |
| `direita`   | `No*`    | —       | Ponteiro para filho direito  |

```c
typedef struct No {
    char nome[50];
    char telefone[16];
    char email[50];
    struct No *direita;
    struct No *esquerda;
} No;
```

---

## Funções Implementadas

### `copiarTexto`

```c
void copiarTexto(char *destino, char *origem, size_t tamanho);
```

Copia uma string de `origem` para `destino` com segurança, limitando ao tamanho máximo informado e garantindo o terminador nulo (`\0`) ao final. Utiliza `strncpy` internamente.

---

### `criarNo`

```c
No* criarNo(char *nome, char *telefone, char *email);
```

Aloca dinamicamente um novo nó na memória e inicializa seus campos com os dados fornecidos. Os ponteiros `esquerda` e `direita` são inicializados como `NULL`.

Retorna:
- Ponteiro para o novo `No` em caso de sucesso.
- `NULL` se a alocação de memória falhar.

---

### `buscar`

```c
No* buscar(No *raiz, char *nome);
```

Realiza uma busca **recursiva** na árvore pelo contato com o nome informado. A busca percorre primeiro a subárvore esquerda e, caso não encontre, percorre a subárvore direita.

Retorna:
- Ponteiro para o `No` encontrado, se existir.
- `NULL` se o contato não for encontrado.