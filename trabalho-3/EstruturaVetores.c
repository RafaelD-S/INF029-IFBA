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
        free(vetorPrincipal[i].vetor);
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
            j--;
        }
        vetorOrdenado[j + 1] = chave;
    }
}

int criarEstruturaAuxiliar(int posicao, int tamanho) {
    if (posicao < 1 || posicao > TAM)
        return POSICAO_INVALIDA;
    int index = posicao - 1;
    if (vetorPrincipal[index].vetor != NULL)
        return JA_TEM_ESTRUTURA_AUXILIAR;
    if (tamanho < 1)
        return TAMANHO_INVALIDO;
    vetorPrincipal[index].vetor = (int *)malloc(tamanho * sizeof(int));
    if (vetorPrincipal[index].vetor == NULL)
        return SEM_ESPACO_DE_MEMORIA;
    vetorPrincipal[index].tamanho = tamanho;
    vetorPrincipal[index].ocupado = 0;
    return SUCESSO;
}

int inserirNumeroEmEstrutura(int posicao, int valor) {
    if (posicao < 1 || posicao > TAM)
        return POSICAO_INVALIDA;
    int index = posicao - 1;
    if (vetorPrincipal[index].vetor == NULL) {
        if (posicao == 9) {
            int ret = criarEstruturaAuxiliar(9, 3);
            if (ret != SUCESSO)
                return ret;
        } else {
            return SEM_ESTRUTURA_AUXILIAR;
        }
    }
    if (vetorPrincipal[index].ocupado >= vetorPrincipal[index].tamanho)
        return SEM_ESPACO;
    vetorPrincipal[index].vetor[vetorPrincipal[index].ocupado] = valor;
    vetorPrincipal[index].ocupado++;
    return SUCESSO;
}

int excluirNumeroDoFinaldaEstrutura(int posicao) {
    if (posicao < 1 || posicao > TAM)
        return POSICAO_INVALIDA;
    int index = posicao - 1;
    if (vetorPrincipal[index].vetor == NULL)
        return SEM_ESTRUTURA_AUXILIAR;
    if (vetorPrincipal[index].ocupado == 0)
        return ESTRUTURA_AUXILIAR_VAZIA;
    vetorPrincipal[index].ocupado--;
    return SUCESSO;
}

int excluirNumeroEspecificoDeEstrutura(int posicao, int valor) {
    if (posicao < 1 || posicao > TAM)
        return POSICAO_INVALIDA;
    int index = posicao - 1;
    if (vetorPrincipal[index].vetor == NULL)
        return SEM_ESTRUTURA_AUXILIAR;
    int encontrado = 0;
    for (int i = 0; i < vetorPrincipal[index].ocupado; i++) {
        if (vetorPrincipal[index].vetor[i] == valor) {
            for (int j = i; j < vetorPrincipal[index].ocupado - 1; j++) {
                vetorPrincipal[index].vetor[j] = vetorPrincipal[index].vetor[j + 1];
            }
            vetorPrincipal[index].ocupado--;
            encontrado = 1;
            break;
        }
    }
    return encontrado ? SUCESSO : NUMERO_INEXISTENTE;
}

int getDadosEstruturaAuxiliar(int posicao, int vetorAux[]) {
    if (posicao < 1 || posicao > TAM)
        return POSICAO_INVALIDA;
    int index = posicao - 1;
    if (vetorPrincipal[index].vetor == NULL)
        return SEM_ESTRUTURA_AUXILIAR;
    for (int i = 0; i < vetorPrincipal[index].ocupado; i++)
        vetorAux[i] = vetorPrincipal[index].vetor[i];
    return SUCESSO;
}

int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[]) {
    if (posicao < 1 || posicao > TAM)
        return POSICAO_INVALIDA;
    int index = posicao - 1;
    if (vetorPrincipal[index].vetor == NULL)
        return SEM_ESTRUTURA_AUXILIAR;
    insertionSort(vetorPrincipal[index].vetor, vetorAux, vetorPrincipal[index].ocupado);
    return SUCESSO;
}

int getDadosDeTodasEstruturasAuxiliares(int vetorAux[]) {
    int count = 0, temNum = 0;
    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i].vetor != NULL && vetorPrincipal[i].ocupado > 0) {
            temNum = 1;
            for (int j = 0; j < vetorPrincipal[i].ocupado; j++) {
                vetorAux[count++] = vetorPrincipal[i].vetor[j];
            }
        }
    }
    return temNum ? SUCESSO : TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
}

int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[]) {
    int total = 0;
    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i].vetor != NULL)
            total += vetorPrincipal[i].ocupado;
    }
    if (total == 0)
        return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
    getDadosDeTodasEstruturasAuxiliares(vetorAux);
    insertionSort(vetorAux, vetorAux, total);
    return SUCESSO;
}

int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho) {
    if (posicao < 1 || posicao > TAM)
        return POSICAO_INVALIDA;
    int index = posicao - 1;
    if (vetorPrincipal[index].vetor == NULL)
        return SEM_ESTRUTURA_AUXILIAR;
    int novo_size = vetorPrincipal[index].tamanho + novoTamanho;
    if (novo_size < 1)
        return NOVO_TAMANHO_INVALIDO;
    int *novo_vetor = (int *)realloc(vetorPrincipal[index].vetor, novo_size * sizeof(int));
    if (novo_vetor == NULL)
        return SEM_ESPACO_DE_MEMORIA;
    vetorPrincipal[index].vetor = novo_vetor;
    vetorPrincipal[index].tamanho = novo_size;
    if (vetorPrincipal[index].ocupado > novo_size)
        vetorPrincipal[index].ocupado = novo_size;
    return SUCESSO;
}

int getQuantidadeElementosEstruturaAuxiliar(int posicao) {
    if (posicao < 1 || posicao > TAM)
        return POSICAO_INVALIDA;
    int index = posicao - 1;
    if (vetorPrincipal[index].vetor == NULL)
        return SEM_ESTRUTURA_AUXILIAR;
    if (vetorPrincipal[index].ocupado == 0)
        return ESTRUTURA_AUXILIAR_VAZIA;
    return vetorPrincipal[index].ocupado;
}

No *montarListaEncadeadaComCabecote() {
    No *cabecote = (No *)malloc(sizeof(No));
    if (!cabecote) return NULL;
    cabecote->prox = NULL;
    No *atual = cabecote;
    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i].vetor != NULL) {
            for (int j = 0; j < vetorPrincipal[i].ocupado; j++) {
                No *novo = (No *)malloc(sizeof(No));
                if (!novo) {
                    destruirListaEncadeadaComCabecote(&cabecote);
                    return NULL;
                }
                novo->conteudo = vetorPrincipal[i].vetor[j];
                novo->prox = NULL;
                atual->prox = novo;
                atual = novo;
            }
        }
    }
    if (cabecote->prox == NULL) {
        free(cabecote);
        return NULL;
    }
    return cabecote;
}

void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[]) {
    int i = 0;
    No *atual = inicio->prox;
    while (atual != NULL) {
        vetorAux[i++] = atual->conteudo;
        atual = atual->prox;
    }
}

void destruirListaEncadeadaComCabecote(No **inicio) {
    No *atual = *inicio;
    while (atual != NULL) {
        No *temp = atual;
        atual = atual->prox;
        free(temp);
    }
    *inicio = NULL;
}

int lerArquivo(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) return -1;
    fclose(fp);
    return 1;
}

int salvarArquivo(const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (!fp) return -1;
    fclose(fp);
    return 1;
}

void finalizar() {
    for (int i = 0; i < TAM; i++) {
        free(vetorPrincipal[i].vetor);
        vetorPrincipal[i].vetor = NULL;
        vetorPrincipal[i].tamanho = 0;
        vetorPrincipal[i].ocupado = 0;
    }
}