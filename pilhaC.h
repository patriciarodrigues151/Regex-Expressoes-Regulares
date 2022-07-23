#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


typedef struct pilha Pilha;
Pilha * pilha_cria(void);
void pilha_push(Pilha * p, float a);
float pilha_pop(Pilha * p);
int pilha_vazia(Pilha * p);
void pilha_libera(Pilha * p);
void pilha_imprime(Pilha * p);

struct elemento
{
    char info;
    struct elemento * prox;
};
typedef struct elemento Elemento;
struct pilha
{
    Elemento * prim;
};
Pilha * pilha_cria(void)
{
    Pilha * p = (Pilha *) malloc(sizeof(Pilha));
    p->prim = NULL;
    return p;
}
int pilha_vazia(Pilha * p)
{
    return (p->prim == NULL);
}
void pilha_push(Pilha * p, float a)
{
    Elemento * novo = (Elemento *)malloc(sizeof(Elemento));
    if (novo==NULL) exit(1);
    novo->info = a;
    novo->prox = p->prim;
    p->prim = novo;
}
float pilha_pop(Pilha * p)
{
    Elemento * t;
    float a;
    assert(!pilha_vazia(p));
    t = p->prim;
    a = t->info;
    p->prim = t->prox;
    free(t);
    return a;
}
void pilha_libera(Pilha * p)
{
    Elemento *t, * q = p->prim;
    while (q != NULL)
    {
        t = q->prox;
        free(q);
        q = t;
    }
    free(p);
}
void pilha_imprime(Pilha * p)
{
    Elemento * q;
    for (q=p->prim; q != NULL; q=q->prox)
        printf("%c\n",q->info);
}

int pilha_tam(Pilha * p)
{
    int tam = 0;
    Elemento * q;
    for (q=p->prim; q != NULL; q=q->prox)
        tam = tam +1;
    return tam;
}