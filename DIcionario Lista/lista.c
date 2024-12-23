/***************************************************************
* Alunos: Cauan Pereira Ramos e Igor Damascena                 *
* Curso: Ciência da Computação                                 *
* Trabalho 1: Dicionário de Verbos Irregulares Inglês-Português*
* organizado com uma Lista encadeada dinâmica                  *
*                                                              * 
* Estrutura de Dados I-- 2024 -- DACC/UNIR, Profa. Carolina Watanabe *
* Compilador: gcc versão 11.4.0                                *
* Sistema Operacional: Ubuntu 22.04.2 LTS                      *
***************************************************************/

#include "lista.h"

#define MAX 100

void CriarVazia(Lista *L) {
  L->head = NULL;
}
void ImprimirVerbo(No *p) {
  if(!p){
    printf("Não foi possível imprimir\n");
    return;
  }
  printf("Verbo:%s, Passado simples:%s, Participio:%s, Significado:%s\n",
         p->info.verbo, p->info.passado_simples, p->info.participio_passado,
         p->info.significado);
}

int ListarDicionario(Lista *L) {

  if (Vazia(L)) {
    printf("Não há verbos no dicionário\n");
    return 0;
  }
  
  No *p = L->head;
  
  printf("--------Dicionario------\n");
  while (p != NULL) {
    ImprimirVerbo(p);
    p = p->prox;
  }
  printf("--------Fim do dicionario------\n");
  printf("\n");

  return 1;
}

int Vazia(Lista *L) { return L->head == NULL; }

int InserirVerbo(Lista *L, char *verbo, char *simples, char *participio,
                 char *significado) {

  No *p = malloc(sizeof(No));
  if (p == NULL) {
    return 0;
  }
  p->prox = NULL;

  p->info.verbo = malloc(sizeof(char) * MAX);
  p->info.passado_simples = malloc(sizeof(char) * MAX);
  p->info.participio_passado = malloc(sizeof(char) * MAX);
  p->info.significado = malloc(sizeof(char) * MAX);

  strcpy(p->info.verbo, verbo);
  strcpy(p->info.passado_simples, simples);
  strcpy(p->info.participio_passado, participio);
  strcpy(p->info.significado, significado);

  if(Vazia(L)) {
    L->head = p;
    return 1;
  }
  No *q = L->head;
  

  while (q != NULL) {
    if(strcmp(q->info.verbo, verbo) == 0 || strcmp(q->info.passado_simples, simples) == 0 || strcmp(q->info.participio_passado, participio) == 0) {
      printf("Uma das conjugações já existe no dicionário\n");
      return 0;
    }
    if(q->prox == NULL) {
      q->prox = p;
      break;
    }
    q = q->prox;
  }
  

  return 1;
}

// Da free em todas as strings, pois foram todas alocadas com malloc
int FreePalavra(No *p) {
  free(p->info.verbo);
  free(p->info.passado_simples);
  free(p->info.participio_passado);
  free(p->info.significado);
  free(p);
  return 1;
}

void DestruirDicionario(Lista *L) {
  No *p;
  while (L->head != NULL) {
    p = L->head;
    L->head = p->prox;
    FreePalavra(p);
  }
}

int RemoverVerbo(Lista *L, char *palavra) {

  if (Vazia(L))
    return 0;

  printf("Palavra a ser removida: %s\n", palavra);

  No *p = L->head;

  if (strcmp(p->info.verbo, palavra) == 0) {
    L->head = p->prox;
    FreePalavra(p);
    return 1;
  }

  No *q = p;

  while (p != NULL) {
    if (strcmp(p->info.verbo, palavra) == 0 ) {
      printf("Removendo do verbo: %s\n", p->info.verbo);
      q->prox = p->prox;
      FreePalavra(p);
      return 1;
    }
    q = p;
    p = p->prox;
  }

  return 0;
}

No *BuscarPalavra(Lista *L, char *palavra) {
  if (Vazia(L)){
    printf("Não há verbos no dicionário\n");
    return NULL;
  }

  No *p = L->head;
  while (p != NULL) {
    if (strcmp(p->info.verbo, palavra) == 0)
      return p;

    p = p->prox;
  }
  return NULL;
}

int CarregarArquivo(Lista* L, const char* nome_arquivo) {
    FILE* arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) {
        printf("Arquivo %s não encontrado (salve para criar um novo).\n", nome_arquivo);
        return 0;
    }

    char linha[512];
    while (fgets(linha, sizeof(linha), arquivo)) {
        // Remover \n
        linha[strcspn(linha, "\n")] = 0;

        // Separar as palavras usando ;
        char* verbo_base = strtok(linha, ";");
        char* passado_simples = strtok(NULL, ";");
        char* participio_passado = strtok(NULL, ";");
        char* significado = strtok(NULL, ";");

        if (verbo_base && passado_simples && participio_passado && significado) {
            InserirVerbo(L, verbo_base, passado_simples, participio_passado, significado);
        } else {
            printf("Linha inválida no arquivo: %s\n", linha);
        }
    }

    fclose(arquivo);
    printf("Dicionário carregado com sucesso!\n");
    return 1;
}

int SalvarArquivo(Lista *L) {

  FILE *fptr;
  fptr = fopen("dicionario.txt", "w");

  if (fptr == NULL) {
    printf("Criando arquivo dicionario.txt\n");
    fptr = fopen("dicionario.txt", "w+");
    if (fptr == NULL) {
      printf("Erro ao criar arquivo");
      return 0;
    }
  }

  No *p = L->head;
  //Percorrendo toda a lista
  while (p != NULL) {
    fprintf(fptr, "%s;%s;%s;%s\n", p->info.verbo, p->info.passado_simples,
          p->info.participio_passado, p->info.significado);
    p = p->prox;
  }

  fclose(fptr);
  return 1;
}