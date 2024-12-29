#include <stdio.h>
#include <stdlib.h>
#define TAM 10

#include "EstruturaVetores.h"

typedef struct {
  int *vetor;
  int tamanho;
  int ocupado;
} estrutura;

estrutura vetorPrincipal[TAM];

void inicializar() {
  for (int i = 0; i < TAM; i++) {
    vetorPrincipal[i].vetor = NULL;
    vetorPrincipal[i].tamanho = 0;
    vetorPrincipal[i].ocupado = 0;
  }
}

void insertionSort(int vetor[], int vetorOrdenado[], int n) {
  for (int i = 0; i < n; i++) {
    vetorOrdenado[i] = vetor[i];
  }

  for (int i = 1; i < n; i++) {
    int chave = vetorOrdenado[i];
    int j = i - 1;

    while (j >= 0 && vetorOrdenado[j] > chave) {
      vetorOrdenado[j + 1] = vetorOrdenado[j];
      j = j - 1;
    }

    vetorOrdenado[j + 1] = chave;
  }
}

/*
Objetivo: criar estrutura auxiliar na posição 'posicao'.
com tamanho 'tamanho'

Rertono (int)
    SUCESSO - criado com sucesso
    JA_TEM_ESTRUTURA_AUXILIAR - já tem estrutura na posição
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    SEM_ESPACO_DE_MEMORIA - Sem espaço de memória
    TAMANHO_INVALIDO - o tamanho deve ser maior ou igual a 1
*/
int criarEstruturaAuxiliar(int posicao, int tamanho) {
  posicao -= 1;

  if (posicao < 0 || posicao >= TAM) {
    return POSICAO_INVALIDA;
  }

  if (vetorPrincipal[posicao].vetor != NULL) {
    return JA_TEM_ESTRUTURA_AUXILIAR;
  }

  if (tamanho < 1) {
    return TAMANHO_INVALIDO;
  }

  vetorPrincipal[posicao].vetor = (int *)malloc(tamanho * sizeof(int));
  if (vetorPrincipal[posicao].vetor == NULL) {
    return SEM_ESPACO_DE_MEMORIA;
  }

  vetorPrincipal[posicao].tamanho = tamanho;
  vetorPrincipal[posicao].ocupado = 0;

  return SUCESSO;
}

/*
Objetivo: inserir número 'valor' em estrutura auxiliar da posição 'posicao'
Rertono (int)
    SUCESSO - inserido com sucesso
    SEM_ESPACO - não tem espaço
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
CONSTANTES
*/
int inserirNumeroEmEstrutura(int posicao, int valor) {
  int retorno = 0;
  posicao -= 1;

  if (posicao < 0 || posicao >= TAM)
    retorno = POSICAO_INVALIDA;
  else {
    if (vetorPrincipal[posicao].vetor != NULL) {
      if (vetorPrincipal[posicao].ocupado < vetorPrincipal[posicao].tamanho) {
        vetorPrincipal[posicao].vetor[vetorPrincipal[posicao].ocupado] = valor;
        vetorPrincipal[posicao].ocupado++;
        retorno = SUCESSO;
      } else {
        retorno = SEM_ESPACO;
      }
    } else {
      retorno = SEM_ESTRUTURA_AUXILIAR;
    }
  }

  return retorno;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar no final da estrutura.
ex: suponha os valores [3, 8, 7, 9,  ,  ]. Após excluir, a estrutura deve ficar
da seguinte forma [3, 8, 7,  ,  ,  ]. Obs. Esta é uma exclusão lógica

Rertono (int)
    SUCESSO - excluido com sucesso
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int excluirNumeroDoFinaldaEstrutura(int posicao) {
  int retorno = SUCESSO;

  if (posicao < 1 || posicao > 10) {
    retorno = POSICAO_INVALIDA;
  } else {
    posicao -= 1;

    if (vetorPrincipal[posicao].vetor != NULL) {
      if (vetorPrincipal[posicao].ocupado == 0) {
        retorno = ESTRUTURA_AUXILIAR_VAZIA;
      } else {
        vetorPrincipal[posicao].ocupado--;
      }
    } else {
      retorno = SEM_ESTRUTURA_AUXILIAR;
    }
  }

  return retorno;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar da posição 'posicao'.
Caso seja excluido, os números posteriores devem ser movidos para as posições
anteriores ex: suponha os valores [3, 8, 7, 9,  ,  ] onde deve ser excluido o
valor 8. A estrutura deve ficar da seguinte forma [3, 7, 9,  ,  ,  ] Obs. Esta é
uma exclusão lógica
Rertono (int)
    SUCESSO - excluido com sucesso 'valor' da estrutura na posição 'posicao'
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    NUMERO_INEXISTENTE - Número não existe
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar

*/
int excluirNumeroEspecificoDeEstrutura(int posicao, int valor) {
  int retorno = SUCESSO;
  int achou = 0;

  if (posicao < 1 || posicao > 10) {
    retorno = POSICAO_INVALIDA;
  } else {
    posicao -= 1;
    if (vetorPrincipal[posicao].vetor != NULL) {
      for (int i = 0; i < vetorPrincipal[posicao].ocupado; i++) {
        if (vetorPrincipal[posicao].vetor[i] == valor) {
          for (int j = i; j < vetorPrincipal[posicao].ocupado - 1; j++) {
            vetorPrincipal[posicao].vetor[j] =
                vetorPrincipal[posicao].vetor[j + 1];
          }
          vetorPrincipal[posicao].ocupado--;
          achou = 1;
          break;
        }
      }
      if (achou == 0)
        retorno = NUMERO_INEXISTENTE;
    } else {
      retorno = SEM_ESTRUTURA_AUXILIAR;
    }
  }

  return retorno;
}

int ehPosicaoValida(int posicao) {
  int retorno = 0;
  if (posicao < 1 || posicao > 10) {
    retorno = POSICAO_INVALIDA;
  } else
    retorno = SUCESSO;

  return retorno;
}

/*
Objetivo: retorna os números da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Retorno (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição'posicao'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosEstruturaAuxiliar(int posicao, int vetorAux[]) {
  int retorno = SUCESSO;

  if (posicao < 1 || posicao > 10) {
    retorno = POSICAO_INVALIDA;
  } else {
    posicao -= 1;
    if (vetorPrincipal[posicao].vetor != NULL) {
      for (int i = 0; i < vetorPrincipal[posicao].ocupado; i++) {
        vetorAux[i] = vetorPrincipal[posicao].vetor[i];
      }
    } else {
      retorno = SEM_ESTRUTURA_AUXILIAR;
    }
  }

  return retorno;
}

/*
Objetivo: retorna os números ordenados da estrutura auxiliar da posição 'posicao
(1..10)'. os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição
'posicao(1..10)' SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[]) {
  int retorno = SUCESSO;

  if (posicao < 1 || posicao > 10) {
    retorno = POSICAO_INVALIDA;
  } else {
    posicao -= 1;
    if (vetorPrincipal[posicao].vetor != NULL) {
      insertionSort(vetorPrincipal[posicao].vetor, vetorAux,
                    vetorPrincipal[posicao].ocupado);
      retorno = SUCESSO;
    } else {
      retorno = SEM_ESTRUTURA_AUXILIAR;
    }
  }

  return retorno;
}

/*
Objetivo: retorna os números de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição
'posicao' TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares
estão vazias
*/
int getDadosDeTodasEstruturasAuxiliares(int vetorAux[]) {
  int retorno = SUCESSO;
  int count = 0, temNum = 0;

  for (int i = 0; i < TAM; i++) {
    if (vetorPrincipal[i].vetor != NULL) {
      for (int j = 0; j < vetorPrincipal[i].ocupado; j++) {
        vetorAux[count] = vetorPrincipal[i].vetor[j];
        count++;
        temNum = 1;
      }
    }
  }
  if (temNum == 0)
    retorno = TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;

  return retorno;
}

/*
Objetivo: retorna os números ordenados de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição
'posicao' TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares
estão vazias
*/
int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[]) {
  int retorno = SUCESSO;
  int count = 0, temNum = 0;

  for (int i = 0; i < TAM; i++) {
    if (vetorPrincipal[i].vetor != NULL) {
      for (int j = 0; j < vetorPrincipal[i].ocupado; j++) {
        vetorAux[count] = vetorPrincipal[i].vetor[j];
        count++;
        temNum = 1;
      }
    }
  }
  insertionSort(vetorAux, vetorAux, count);

  if (temNum == 0)
    retorno = TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;

  return retorno;
}

/*
Objetivo: modificar o tamanho da estrutura auxiliar da posição 'posicao' para o
novo tamanho 'novoTamanho' + tamanho atual Suponha o tamanho inicial = x, e novo
tamanho = n. O tamanho resultante deve ser x + n. Sendo que x + n deve ser
sempre >= 1

Rertono (int)
    SUCESSO - foi modificado corretamente o tamanho da estrutura auxiliar
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    NOVO_TAMANHO_INVALIDO - novo tamanho não pode ser negativo
    SEM_ESPACO_DE_MEMORIA - erro na alocação do novo valor
*/
int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho) {
  int retorno = SUCESSO;

  if (posicao < 1 || posicao > TAM) {
    return POSICAO_INVALIDA;
  }

  posicao -= 1;
  if (vetorPrincipal[posicao].vetor == NULL)
    return SEM_ESTRUTURA_AUXILIAR;

  int tamanhoAtual = vetorPrincipal[posicao].tamanho;
  int tamanhoFinal = tamanhoAtual + novoTamanho;

  if (tamanhoFinal < 1) {
    return NOVO_TAMANHO_INVALIDO;
  }

  int *novoVetor =
      (int *)realloc(vetorPrincipal[posicao].vetor, tamanhoFinal * sizeof(int));
  if (novoVetor == NULL) {
    return SEM_ESPACO_DE_MEMORIA;
  }

  vetorPrincipal[posicao].vetor = novoVetor;
  vetorPrincipal[posicao].tamanho = tamanhoFinal;

  if (vetorPrincipal[posicao].ocupado > tamanhoFinal) {
    vetorPrincipal[posicao].ocupado = tamanhoFinal;
  }

  return retorno;
}

/*
Objetivo: retorna a quantidade de elementos preenchidos da estrutura auxiliar da
posição 'posicao'.

Retorno (int)
    POSICAO_INVALIDA - posição inválida
    SEM_ESTRUTURA_AUXILIAR - sem estrutura auxiliar
    ESTRUTURA_AUXILIAR_VAZIA - estrutura auxiliar vazia
    Um número int > 0 correpondente a quantidade de elementos preenchidos da
estrutura
*/
int getQuantidadeElementosEstruturaAuxiliar(int posicao) {
  int retorno = SUCESSO;

  if (posicao < 1 || posicao > 10) {
    retorno = POSICAO_INVALIDA;
  } else {
    if (vetorPrincipal[posicao].vetor != NULL) {
      if (vetorPrincipal[posicao].ocupado == 0) {
        retorno = ESTRUTURA_AUXILIAR_VAZIA;
      } else {
        retorno = vetorPrincipal[posicao].ocupado;
      }
    } else {
      retorno = SEM_ESTRUTURA_AUXILIAR;
    }
  }

  return retorno;
}

/*
Objetivo: montar a lista encadeada com cabeçote com todos os números presentes
em todas as estruturas.

Retorno (No*)
    NULL, caso não tenha nenhum número nas listas
    No*, ponteiro para o início da lista com cabeçote
*/
No *montarListaEncadeadaComCabecote() {
  No *cabecote = (No *)malloc(sizeof(No));
  if (cabecote == NULL) {
    return NULL;
  }
  cabecote->prox = NULL;

  No *atual = cabecote;
  for (int i = 0; i < TAM; i++) {
    if (vetorPrincipal[i].vetor != NULL) {
      for (int j = 0; j < vetorPrincipal[i].ocupado; j++) {
        No *novoNo = (No *)malloc(sizeof(No));
        if (novoNo == NULL) {
          return NULL;
        }
        novoNo->conteudo = vetorPrincipal[i].vetor[j];
        novoNo->prox = NULL;
        atual->prox = novoNo;
        atual = novoNo;
      }
    }
  }

  return cabecote;
}

/*
Objetivo: retorna os números da lista enceada com cabeçote armazenando em
vetorAux. Retorno void
*/
void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[]) {
  No *atual = inicio->prox;
  int count = 0;

  while (atual != NULL) {
    vetorAux[count] = atual->conteudo;
    count++;
    atual = atual->prox;
  }
}

/*
Objetivo: Destruir a lista encadeada com cabeçote a partir de início.
O ponteiro inicio deve ficar com NULL.

Retorno
    void.
*/
void destruirListaEncadeadaComCabecote(No **inicio) {
  No *atual = *inicio;
  while (atual != NULL) {
    No *temp = atual;
    atual = atual->prox;
    free(temp);
  }
  *inicio = NULL;
}

/*
Objetivo: finaliza o programa. deve ser chamado ao final do programa
para poder liberar todos os espaços de memória das estruturas auxiliares.

*/
void finalizar() {
  for (int i = 0; i < TAM; i++) {
    if (vetorPrincipal[i].vetor != NULL) {
      free(vetorPrincipal[i].vetor);
      vetorPrincipal[i].vetor = NULL;
      vetorPrincipal[i].tamanho = 0;
      vetorPrincipal[i].ocupado = 0;
    }
  }
}
