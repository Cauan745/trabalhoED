/***************************************************************
* Alunos: Cauan Pereira Ramos e Igor Damascena                 *
* Curso: Ciência da Computação                                 *
* Trabalho 1: Dicionário de Verbos Irregulares Inglês-Português*
* organizado com uma Lista encadeada dinâmica                  *
*                                                              * 
* Estrutura de Dados I-- 2024 -- DACC/UNIR, Profa. Carolina Watanabe *
* Compilador: gcc versão 11.4.0                                *
* Sistema Operacional: Ubuntu 22.04 LTS                        *
***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef LISTA_H
#define LISTA_H

struct tipo_elem {
  char *verbo;
  char *passado_simples;
  char *participio_passado;
  char *significado;
};

typedef struct no {
  struct tipo_elem info;
  struct no *prox;
} No;

typedef struct {
  No *head;
} Lista;


void CriarVazia(Lista *L);

void ImprimirVerbo(No *p);

int ListarDicionario(Lista *L);
int Vazia(Lista *L);

int InserirVerbo(Lista *L, char *verbo, char *simples, char *participio,
                 char *significado);

// Da free em todas as strings, pois foram todas alocadas com malloc
int FreePalavra(No *p);

void DestruirDicionario(Lista *L);

int RemoverVerbo(Lista *L, char *palavra);

No *BuscarPalavra(Lista *L, char *palavra);

int CarregarArquivo(Lista* L, const char* nome_arquivo);

int SalvarArquivo(Lista *L);

#endif