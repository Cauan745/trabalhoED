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

int verificaVaziaeEspaco(char *palavra){
  if(palavra[0] == '\0' || palavra[0] == ' '){
    return 1;
  }
  return 0;
}

int main(){
  No *raiz = NULL;

  raiz = CarregarArquivo(raiz, "dicionario.txt");

  int opcao;
  char verbo[100], passado[100], participio[100], significado[500];
  No *resultado;

  do{
    printf("\n--- Dicionário de Verbos ---\n");
    printf("1. Inserir verbo\n");
    printf("2. Buscar palavra\n");
    printf("3. Imprimir todos os verbos\n");
    printf("4. Imprimir árvore de forma gráfica\n");
    printf("5. Remover verbo\n");
    printf("6. Destruir dicionario\n");
    printf("7. Salvar dicionário\n");
    printf("0. Sair\n");

    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

    switch (opcao){
    case 1:
      printf("Digite o verbo base: ");
      scanf(" %[^\n]", verbo);
      if(verificaVaziaeEspaco(verbo)){
        break;
      }
      printf("Digite o passado simples: ");
      scanf(" %[^\n]", passado);
      if(verificaVaziaeEspaco(passado)){
        break;
      }
      printf("Digite o participio passado: ");
      scanf(" %[^\n]", participio);
      if(verificaVaziaeEspaco(participio)){
        break;
      }
      printf("Digite o significado: ");

      // Garantir que a string seja lida (c é horrível)
      getchar();
      fgets(significado, sizeof(significado), stdin);
      significado[strcspn(significado, "\n")] = 0;
      if(verificaVaziaeEspaco(significado)){
        break;
      }
      //

      raiz = Inserir(raiz, verbo, passado, participio, significado);
      break;

    case 2:
      if(raiz == NULL){
        printf("Não há verbos no dicionário!\n");
        break;
      }
      printf("Digite a palavra a ser buscada: ");
      scanf(" %[^\n]", verbo);
      if(verificaVaziaeEspaco(verbo)){
        break;
      }

      resultado = Buscar(raiz, verbo);
      printf("--- Resultado ---\n");
      if (resultado){
        printf("Palavra encontrada!\n");

        printf("Verbo base: %s\n", resultado->info.verbo);
        printf("Passado simples: %s\n", resultado->info.passado_simples);
        printf("participio passado: %s\n", resultado->info.participio_passado);
        printf("Significado: %s\n", resultado->info.significado);
      }
      else{
        printf("Palavra '%s' não encontrada!\n", verbo);
      }
      printf("--- Fim do Resultado ---\n\n");
      break;

    case 3:
      if(raiz == NULL){
        printf("Não há verbos no dicionário!\n");
        break;
      }
      printf("\n--- Dicionario---\n");
      Imprimir(raiz);
      printf("\n --- Fim do dicionario ---\n\n");
      break;
    case 4:
      if(raiz == NULL){
        printf("Não há verbos no dicionário!\n");
        break;
      }
      printf("\n--- Árvore AVL ---\n");
      ImprimirAVL(raiz, 0);
      printf("\n --- Fim da Árvore ---\n\n");
      break;
    case 5:
      if(raiz == NULL){
        printf("Não há verbos no dicionário!\n");
        break;
      }
      printf("Digite a forma base do verbo a ser removido: ");
      scanf(" %[^\n]", verbo);
      if(verificaVaziaeEspaco(verbo)){
        break;
      }
      No *res = Buscar(raiz, verbo);

      if (res != NULL && strcmp(res->info.verbo, verbo) == 0){
        raiz = Remover(raiz, verbo);
        printf("Verbo '%s' removido com sucesso!\n", verbo);
      }
      else
        printf("Verbo não encontrado!\n");
      break;
    case 6:
      if(raiz == NULL){
        printf("Não há verbos no dicionário!\n");
        break;
      }
      DestruirDicionario(&raiz);
      printf("Dicionário destruído com sucesso!\n");
      break;
    case 7:
      SalvarArquivo(raiz);
      printf("Dicionário salvo com sucesso!\n");
      break;
    case 0:
      printf("Salvando dicionário e destruindo...\n");
      SalvarArquivo(raiz);
      DestruirDicionario(&raiz);
      break;

    default:
      printf("Opção inválida! Tente novamente.\n");
    }
  } while (opcao != 0);

  printf("Encerrando programa.\n");


  return 0;
}
