/***************************************************************
* Alunos: Cauan Pereira Ramos e Igor Damascena                 *
* Curso: Ciência da Computação                                 *
* Trabalho 1: Dicionário de Verbos Irregulares Inglês-Português*
* organizado com uma AVL                                       *
*                                                              * 
* Estrutura de Dados I-- 2024 -- DACC/UNIR, Profa. Carolina Watanabe *
* Compilador: gcc versão 11.4.0                                *
* Sistema Operacional: Ubuntu 22.04 LTS                        *
***************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef AVL_H
#define AVL_H

struct tipo_elem {
  char verbo[100];            // Verbo base
  char passado_simples[100];    // Conjugação no passado simples
  char participio_passado[100]; // Conjugação no particípio passado
  char significado[500];        // Significado do verbo
};

// Estrutura do nó AVL
typedef struct No {
  struct tipo_elem info;
  struct No *esquerda;       // Subárvore esquerda
  struct No *direita;        // Subárvore direita
  int altura;                   // Altura do nó
} No;


int Max(int a, int b);

int Altura(No *no);

int Balanceamento(No *no);

No* Min(No* raiz);

No *RotacaoDireita(No *y);

No *RotacaoEsquerda(No *x);

No *NovoNo(char palavra[], char passado_simples[],
               char participio_passado[], char significado[]);

No *Inserir(No *no, char palavra[], char passado_simples[], char participio_passado[], char significado[]);

No* Buscar(No* no, char palavra[]);

No* Remover(No* raiz, const char* palavra);

No *InserirComConjugacoes(No *raiz, char palavra[], char passado_simples[], char participio_passado[], char significado[]);
// Imprimir todos os verbos
void Imprimir(No *no);

void ImprimirAVL(No *no, int nivel);

void SalvarNo(FILE *arquivo, No *no);

void SalvarArquivo(No *raiz);

void DestruirArvore(No* raiz);
void DestruirDicionario(No** raiz);
No* CarregarArquivo(No* raiz, const char* nome_arquivo);

#endif