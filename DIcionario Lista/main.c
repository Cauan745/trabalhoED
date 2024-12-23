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

#include "lista.h"

int verificaVaziaeEspaco(char *palavra){
  if(palavra[0] == '\0' || palavra[0] == ' '){
    printf("A palavra não pode ser em branco ou espaço!\n");
    return 1;
  }
  return 0;
}

int main() {
  Lista L;
  CriarVazia(&L);
  CarregarArquivo(&L, "dicionario.txt");

  char *palavra = "worn";
  int opcao = 0;

  char verbo[100], passado[100], participio[100], significado[500];

  do {
    printf("\n--- Dicionário de Verbos ---\n");
    printf("1. Inserir verbo\n");
    printf("2. Buscar palavra\n");
    printf("3. Imprimir todos os verbos\n");
    printf("4. Remover verbo\n");
    printf("5. Destruir dicionário\n");
    printf("6. Salvar dicionário\n");
    printf("0. Sair\n");

    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

    printf("\n");
    switch (opcao) {
    case 1:
      printf("Digite o verbo base:");
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
      //
      if(verificaVaziaeEspaco(significado)){
        break;
      }

      if (InserirVerbo(&L, verbo, passado, participio, significado)) {
        printf("Palavra '%s' inserida com sucesso.\n", verbo);
      } else {
        printf("Erro ao inserir a palavra '%s'.\n", verbo);
      }
      break;
    case 2:
      if(L.head == NULL){
        printf("Nao ha verbos no dicionario!\n");
        break;
      }
      printf("Digite a palavra para buscar: ");
      scanf(" %[^\n]", verbo);
      if(verificaVaziaeEspaco(verbo)){
        break;
      }
      No *resultado = BuscarPalavra(&L, verbo);
      if (resultado) {
        printf("Palavra encontrada: ");
        ImprimirVerbo(resultado);
        printf("\n");
      } else {
        printf("Palavra '%s' nao encontrada.\n", verbo);
      }
      break;
    case 3:
      if(L.head == NULL){
        printf("Nao ha verbos no dicionario!\n");
        break;
      }
      if(!ListarDicionario(&L))
        printf("Erro ao listar o dicionario\n");
      break;
    case 4:
      if(L.head == NULL){
        printf("Nao ha verbos no dicionario!\n");
        break;
      }
      printf("Digite a forma base do verbo a ser removido: ");
      scanf(" %[^\n]", verbo);
      if(verificaVaziaeEspaco(verbo)){
        break;
      }
      if (RemoverVerbo(&L, verbo)) {
        printf("Verbo '%s' e suas conjugações removido com sucesso.\n", verbo);
      } else {
        printf("Palavra '%s' nao encontrada.\n", verbo);
      }
      break;
    case 5:
      if(L.head == NULL){
        printf("Nao ha verbos no dicionario!\n");
        break;
      }
      DestruirDicionario(&L);
      printf("Dicionario destruido.\n");
      break;
    case 6:
    if(SalvarArquivo(&L))
      printf("Dicionario salvo com sucesso.\n");
    else
      printf("Erro ao salvar o dicionario\n");
    break;
    case 0:
      if(SalvarArquivo(&L)){
        printf("Dicionario salvo com sucesso.\n");
        DestruirDicionario(&L);
      }
      else {
        printf("Erro ao salvar o dicionario\n");
        printf("Deseja sair sem salvar o dicionario? 1 - Para sim; 2 - Para não\n");
        int escolha;
        scanf("%d", &escolha);
        if(escolha == 2){
          opcao = 10;
        }
      }
      break;
    default:
      printf("Opcao invalida! Tente novamente.\n");
    }
  } while (opcao != 0);

  printf("Encerrando programa.\n");
  return 0;
}