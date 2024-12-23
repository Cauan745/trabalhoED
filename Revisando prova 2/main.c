#include <stdio.h>
#include <stdlib.h>

struct tipo_elem{
    int chave;
};

typedef struct no {
    struct tipo_elem info;
    struct no* esq;
    struct no* dir;
    int fb;
} No;

typedef struct no *Arvore; // Arvore é um ponteiro para No

void criarVazia(Arvore *T){
    *T = NULL;
}

No* busca(Arvore T, int x){
    if(T == NULL){
        return NULL;
    }
    if(T->info.chave == x)
        return T;
    if(T->info.chave > x)
        return busca(T->esq, x);
    else
        return busca(T->dir, x);
}


void rot_esq(No **r){
    No *a = *r;
    No *b = a->dir;
    a->dir = b->esq; //Os filhos da esquerda do elemento que vai subir viram filhos da direita do elemento que vai descer
    b->esq = a;
    a->fb = 0;
    b->fb = 0;
    *r = b; // Agora o ponteiro aponta para o elemento que subiu, e não mais para o elemento que desceu
}

void rot_dir(No **r){
    No *b = *r;
    No *a = b->esq;
    b->esq = a->dir;
    a->dir = b;
    a->fb = 0;
    b->fb = 0;
    *r = a;
}

void rot_esq_dir(No **r){
    No *c=*r;
    No *a=c->esq;
    No *b=a->dir;

    c->esq=a->dir;
    a->dir=b->esq;
    b->esq=a;
    b->dir=c;

    switch(b->fb){
        case -1:
            a->fb=0;
            c->fb=1;
            break;
        case 0:
            a->fb=0;
            c->fb=0;
            break;
        case 1:
            a->fb=-1;
            c->fb= 0;
            break;
    }

    b->fb=0;
    *r=b;

}     

void rot_dir_esq(No **r){
    No *a=*r;
    No *c=a->dir;
    No *b=c->esq;
   
    c->esq=b->dir;
    a->dir=b->esq;
    
    b->esq=a;
    b->dir=c;

    switch(b->fb){
        case -1:
            a->fb=0;
            c->fb=1;
            break;
        case 0:
            a->fb=0;
            c->fb=0;
            break;
        case 1:
            a->fb=-1;
            c->fb=0;
            break;
    }

    b->fb=0;
    *r=b;
}


No* inserirAUX(No *p, struct tipo_elem x, int* cresceu){
    if(p == NULL){
        p = (No*)malloc(sizeof(No));
        p->info = x;
        p->fb = 0;
        p->esq = NULL;
        p->dir = NULL;
        *cresceu = 1;
        return p;
    }
    
    if(x.chave < p->info.chave){
        p->esq = inserirAUX(p->esq, x, cresceu);
        if(*cresceu){ 
            switch (p->fb) {
                case -1:
                    if(p->esq->fb == -1){
                        rot_dir(&p);
                    }
                    else rot_dir_esq(&p);
                    *cresceu = 0;
                    break;
                case 0:
                    p->fb = -1;
                    *cresceu = 1;
                    break;
                case 1:
                    p->fb = 0;
                    *cresceu = 0;
                    break;
            }
        }
        return p;
    } 
    else if(x.chave > p->info.chave){
        p->dir = inserirAUX(p->dir, x, cresceu);
        if(*cresceu){
            switch(p->fb){
                case -1:
                    p->fb = 0;
                    *cresceu = 0;
                    break;
                case 0:
                    p->fb = 1;
                    *cresceu = 1;
                    break;
                case 1:
                    if(p->dir->fb==1){
                        rot_esq(&p);
                    }
                    else rot_esq_dir(&p);
                    *cresceu = 0;
                    break;
            }
        }
        return p;
    }
    *cresceu = 0;
    return p;
}

void inserir(Arvore *T, int x){
    int cresceu = 0;
    struct tipo_elem* a = malloc(sizeof(struct tipo_elem));
    a->chave = x;
    *T = inserirAUX(*T, *a, &cresceu);
}

void imprimir(Arvore T){
    if(T != NULL){
        imprimir(T->esq);
        printf("%d ", T->info.chave);
        imprimir(T->dir);
    }
}

void imprimirArvore(Arvore T, int nivel) {
    if(T != NULL) {
        imprimirArvore(T->dir, nivel + 1);
        for(int i = 0; i < nivel; i++) {
            printf("    ");
        }
        printf("%d\n", T->info.chave);
        imprimirArvore(T->esq, nivel + 1);
    }
}

int main(){
    Arvore T;
    criarVazia(&T);
    int n, x;
    printf("Digite a quantidade de elementos da arvore: ");
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        printf("Digite o %d elemento : ", i+1);
        scanf("%d", &x);
        inserir(&T, x);
        imprimirArvore(T,1);
        imprimir(T);
        printf("\n");
    }
    return 0;
}