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

#include "avl.h"

int Max(int a, int b) { 
  if(a>b) return a;
  return b;
}

int Altura(No *no) { 
  if(no) return no->altura;
  return -1;
}

int Balanceamento(No *no) {
  if(no) 
    return Altura(no->esquerda) - Altura(no->direita);
  return 0;
}

No* Min(No* raiz) {
    No* atual = raiz;
    while (atual && atual->esquerda != NULL) {
        atual = atual->esquerda;
    }
    return atual;
}


No *RotacaoDireita(No *y) {
  No *x = y->esquerda;
  No *T2 = x->direita;

  // filho da esquerda de y vira filho da direita de x
  x->direita = y;
  // filho da direita de x vira filho da esquerda de y
  y->esquerda = T2;

  y->altura = Max(Altura(y->esquerda), Altura(y->direita)) + 1;
  x->altura = Max(Altura(x->esquerda), Altura(x->direita)) + 1;

  // x é a nova raiz
  return x;
}

No *RotacaoEsquerda(No *x) {
  No *y = x->direita;
  No *T2 = y->esquerda;

  // filho da direita de x vira filho da esquerda de y
  y->esquerda = x;

  // filho da esquerda de y vira filho da direita de x
  x->direita = T2;

  x->altura = Max(Altura(x->esquerda), Altura(x->direita)) + 1;
  y->altura = Max(Altura(y->esquerda), Altura(y->direita)) + 1;

  // y é a nova raiz
  return y;
}

No *NovoNo(char palavra[], char passado_simples[],
               char participio_passado[], char significado[]) {
  No *novo = (No *)malloc(sizeof(No));
  strcpy(novo->info.verbo, palavra);
  strcpy(novo->info.passado_simples, passado_simples);
  strcpy(novo->info.participio_passado, participio_passado);
  strcpy(novo->info.significado, significado);
  novo->esquerda = NULL;
  novo->direita = NULL;
  novo->altura = 0;
  return novo;
}

// Inserir um nó na árvore
No *Inserir(No *no, char palavra[], char passado_simples[],
               char participio_passado[], char significado[]) {

  if (!no) {
    return NovoNo(palavra, passado_simples, participio_passado, significado);
  }

  if (strcmp(palavra, no->info.verbo) < 0) {
    no->esquerda = Inserir(no->esquerda, palavra, passado_simples,
                           participio_passado, significado);
  } else if (strcmp(palavra, no->info.verbo) > 0) {
    no->direita = Inserir(no->direita, palavra, passado_simples,
                          participio_passado, significado);
  } else if(strcmp(palavra, no->info.verbo) == 0){
    printf("Verbo já existente no dicionário!\n");
    return no;
  }

  no->altura = 1 + Max(Altura(no->esquerda), Altura(no->direita));

  int balanco = Balanceamento(no);

  // Caso 1: Rotação à direita
  if (balanco > 1 && strcmp(palavra, no->esquerda->info.verbo) < 0)
    return RotacaoDireita(no);

  // Caso 2: Rotação à esquerda
  if (balanco < -1 && strcmp(palavra, no->direita->info.verbo) > 0)
    return RotacaoEsquerda(no);

  // Caso 3: Rotação esquerda-direita
  if (balanco > 1 && strcmp(palavra, no->esquerda->info.verbo) > 0) {
    no->esquerda = RotacaoEsquerda(no->esquerda);
    return RotacaoDireita(no);
  }

  // Caso 4: Rotação direita-esquerda
  if (balanco < -1 && strcmp(palavra, no->direita->info.verbo) < 0) {
    no->direita = RotacaoDireita(no->direita);
    return RotacaoEsquerda(no);
  }

  return no;
}


No* Buscar(No* no, char palavra[]) {
    if (!no) return NULL;

    int comp_verbo = strcmp(palavra, no->info.verbo);

    // Se a palavra for encontrada em qualquer forma do verbo
    if (comp_verbo == 0) {
        return no;
    }

    // Se a palavra for menor que o verbo, busque à esquerda
    if (comp_verbo < 0) {
        return Buscar(no->esquerda, palavra);
    }

    // Se a palavra for maior que o verbo, busque à direita
    return Buscar(no->direita, palavra);
}

No* Remover(No* raiz, const char* palavra) {
    if (raiz == NULL) {
        return raiz;
    }

    if (strcmp(palavra, raiz->info.verbo) < 0) {
        raiz->esquerda = Remover(raiz->esquerda, palavra);
    } else if (strcmp(palavra, raiz->info.verbo) > 0) {
        raiz->direita = Remover(raiz->direita, palavra);
    }
    else {
        if (strcmp(palavra, raiz->info.verbo) == 0) {

            // Caso 1: O nó tem no máximo um filho
            if (raiz->esquerda == NULL || raiz->direita == NULL) {
                No* temp = raiz->esquerda ? raiz->esquerda : raiz->direita;
                if (temp == NULL) { 
                    temp = raiz;
                    raiz = NULL;
                } else {
                    *raiz = *temp; // Copia os dados do filho para o nó
                }
                free(temp);
            }
            // Caso 2: O nó tem dois filhos
            else {
                // Encontrar o sucessor in-ordem ( vou utilizar o menor valor na subárvore direita)
                No* temp = Min(raiz->direita);

                // Copiar os dados do sucessor in-orde, para o nó a ser removido
                strcpy(raiz->info.verbo, temp->info.verbo);
                strcpy(raiz->info.passado_simples, temp->info.passado_simples);
                strcpy(raiz->info.participio_passado, temp->info.participio_passado);
                strcpy(raiz->info.significado, temp->info.significado);

                // Remover o sucessor in-ordem
                raiz->direita = Remover(raiz->direita, temp->info.verbo);
            }
        }
    }

    if (raiz == NULL) {
        return raiz;
    }

    raiz->altura = 1 + Max(Altura(raiz->esquerda), Altura(raiz->direita));

    int fator_balanceamento = Balanceamento(raiz);

    // Caso 1: Desbalanceamento à esquerda
    if (fator_balanceamento > 1 && Balanceamento(raiz->esquerda) >= 0) {
        return RotacaoDireita(raiz);
    }

    // Caso 2: Desbalanceamento à direita
    if (fator_balanceamento < -1 && Balanceamento(raiz->direita) <= 0) {
        return RotacaoEsquerda(raiz);
    }

    // Caso 3: Desbalanceamento à esquerda-direita
    if (fator_balanceamento > 1 && Balanceamento(raiz->esquerda) < 0) {
        raiz->esquerda = RotacaoEsquerda(raiz->esquerda);
        return RotacaoDireita(raiz);
    }

    // Caso 4: Desbalanceamento à direita-esquerda
    if (fator_balanceamento < -1 && Balanceamento(raiz->direita) > 0) {
        raiz->direita = RotacaoDireita(raiz->direita);
        return RotacaoEsquerda(raiz);
    }
    return raiz;
}

// Imprimir todos os verbos
void Imprimir(No *no) {
  if (no) {
    Imprimir(no->esquerda);

    printf("Verbo:%s, ", no->info.verbo);
    printf("Passado simples:%s, ", no->info.passado_simples);
    printf("Particípio passado:%s, ", no->info.participio_passado);
    printf("Significado:%s\n", no->info.significado);

    Imprimir(no->direita);
  }
}

void ImprimirAVL(No *no, int nivel) {
  if (no == NULL)
    return;

  // Imprimir a subárvore direita
  ImprimirAVL(no->direita, nivel + 1);

  // Imprimir o nó atual com indentação
  for (int i = 0; i < nivel; i++) {
    printf("    "); // 4 espaços por nível
  }
  printf("%s\n", no->info.verbo);

  ImprimirAVL(no->esquerda, nivel + 1);
}

void SalvarNo(FILE *arquivo, No *no) {
  if (!no)
    return;

  SalvarNo(arquivo, no->esquerda);

  fprintf(arquivo, "%s;%s;%s;%s\n", no->info.verbo, no->info.passado_simples,
          no->info.participio_passado, no->info.significado);

  SalvarNo(arquivo, no->direita);

}

void SalvarArquivo(No *raiz) {
  FILE *arquivo = fopen("dicionario.txt", "w");
  if (!arquivo) {
    printf("Erro ao abrir o arquivo para salvar!\n");
    return;
  }

  SalvarNo(arquivo, raiz);
  fclose(arquivo);
}

void DestruirArvore(No* raiz) {
    if (raiz == NULL) return;

    // Primeiro, destrói recursivamente as subárvores esquerda e direita
    DestruirArvore(raiz->esquerda);
    DestruirArvore(raiz->direita);

    // Libera o nó atual
    free(raiz);
}

void DestruirDicionario(No** raiz) {
    if (*raiz == NULL) return;

    DestruirArvore(*raiz);

    *raiz = NULL;

    raiz = NULL;
}

No* CarregarArquivo(No* raiz, const char* nome_arquivo) {
    FILE* arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) {
        printf("Arquivo %s não encontrado (salve para criar um novo).\n", nome_arquivo);
        return raiz;
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
            raiz = Inserir(raiz, verbo_base, passado_simples, participio_passado, significado);
        } else {
            printf("Linha inválida no arquivo: %s\n", linha);
        }
    }

    fclose(arquivo);
    printf("Dicionário carregado com sucesso!\n");
    return raiz;
}