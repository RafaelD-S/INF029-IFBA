// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  Cada aluno deve renomear esse arquivo para Aluno<MATRICULA>.c
//  O aluno deve preencher seus dados abaixo, e implementar as questões do
//  trabalho

//  ----- Dados do Aluno -----
//  Nome: Rafael Dantas Silva
//  email: 20241160016@ifba.edu.br
//  Matrícula: 20241160016
//  Semestre: 2024.2

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021 - 19/08/2016

// #################################################

#include "RafaelDantas20241160016.h"
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

DataQuebrada quebraData(char data[]);

/*
## função utilizada para testes  ##

 somar = somar dois valores
@objetivo
  Somar dois valores x e y e retonar o resultado da soma
@entrada
  dois inteiros x e y
@saida
  resultado da soma (x + y)
 */
int somar(int x, int y) {
  int soma;
  soma = x + y;
  return soma;
}

/*
## função utilizada para testes  ##

 fatorial = fatorial de um número
@objetivo
  calcular o fatorial de um número
@entrada
  um inteiro x
@saida
  fatorial de x -> x!
 */
int fatorial(int x) { // função utilizada para testes
  int i, fat = 1;

  for (i = x; i > 1; i--)
    fat = fat * i;

  return fat;
}

int teste(int a) {
  int val;
  if (a == 2)
    val = 3;
  else
    val = 4;

  return val;
}

/*
 Q1 = validar data
@objetivo
  Validar uma data
@entrada
  uma string data. Formatos que devem ser aceitos: dd/mm/aaaa, onde dd = dia, mm
= mês, e aaaa, igual ao ano. dd em mm podem ter apenas um digito, e aaaa podem
ter apenas dois digitos.
@saida
  0 -> se data inválida
  1 -> se data válida
 @restrições
  Não utilizar funções próprias de string (ex: strtok)
  pode utilizar strlen para pegar o tamanho da string
 */
int q1(char * data) {
  DataQuebrada dat = quebraData(data);

  int datavalida = 1;

  int anoBisexto = (dat.iAno % 4 == 0) && (dat.iAno % 100 != 0 && dat.iAno % 400 != 0);
  int diasFev = anoBisexto ? 29 : 28;

  if ((dat.iMes < 1 || dat.iMes > 12 || dat.iDia < 1) || dat.iAno < 1) 
    datavalida = 0;

  else if (dat.iMes == 2 && dat.iDia > diasFev) 
    datavalida =  0;

  else if (dat.iDia > 31)  
    datavalida = 0;

  else if (dat.iMes % 2 == (dat.iMes >= 8 ? 1 : 0) && dat.iDia > 30) 
    datavalida = 0;
  
  if (datavalida)
    return 1;
  else
    return 0;
}

/*
 Q2 = diferença entre duas datas
 @objetivo
  Calcular a diferença em anos, meses e dias entre duas datas
 @entrada
  uma string datainicial, uma string datafinal.
 @saida
  Retorna um tipo DiasMesesAnos. No atributo retorno, deve ter os possíveis
 valores abaixo 1 -> cálculo de diferença realizado com sucesso 2 -> datainicial
 inválida 3 -> datafinal inválida 4 -> datainicial > datafinal Caso o cálculo
 esteja correto, os atributos qtdDias, qtdMeses e qtdAnos devem ser preenchidos
 com os valores correspondentes.
 */
DiasMesesAnos q2(char *datainicial, char *datafinal) {
  
  DataQuebrada dataInicial = quebraData(datainicial);
  DataQuebrada dataFinal = quebraData(datafinal);
  //calcule os dados e armazene nas três variáveis a seguir
  DiasMesesAnos dma;

  if (q1(datainicial) == 0){
    dma.retorno = 2;
    return dma;
  } else if (q1(datafinal) == 0){
    dma.retorno = 3;
    return dma;
  } else {

  if (dataFinal.iAno < dataInicial.iAno) {
    dma.retorno = 4;
    return dma;
  } 
  else if (dataFinal.iAno == dataInicial.iAno && dataFinal.iMes < dataInicial.iMes) {
    dma.retorno = 4;
    return dma;
  } 
  else if (dataFinal.iAno == dataInicial.iAno && dataFinal.iMes == dataInicial.iMes && dataFinal.iDia < dataFinal.iDia) {
    dma.retorno = 4;
    return dma;
  }

    int diasNoMes = 0;
    int anoBisexto = (dataInicial.iAno % 4 == 0) && (dataFinal.iAno % 100 != 0 && dataFinal.iAno % 400 != 0);
    int diasFev = anoBisexto ? 29 : 28;
    dma.qtdDias = 0;

    if (dataInicial.iMes == 2) 
      diasNoMes = diasFev;
    else if (dataInicial.iMes % 2 == (dataInicial.iMes >= 8 ? 1 : 0)) 
      diasNoMes = 30;
    else
      diasNoMes = 31;


    dma.qtdAnos = dataFinal.iAno - dataInicial.iAno;
    if (dataFinal.iMes < dataInicial.iMes && dma.qtdAnos != 0) {
      dma.qtdAnos -= 1;
      dma.qtdMeses = 12 - (dataInicial.iMes - dataFinal.iMes);
    } 
    else if (dataFinal.iMes > dataInicial.iMes) {
      dma.qtdMeses = dataFinal.iMes - dataInicial.iMes;
    }

    if (dataFinal.iDia > dataInicial.iDia) {
      dma.qtdDias = dataFinal.iDia - dataInicial.iDia;
    }
    else if (dataInicial.iDia > dataFinal.iDia && dataFinal.iMes == dataInicial.iMes) {
      dma.qtdAnos -= 1;
      dma.qtdMeses = 11;
      dma.qtdDias = diasNoMes - (dataInicial.iDia - dataFinal.iDia);
    }
    else if (dataInicial.iDia > dataFinal.iDia) {
      dma.qtdMeses -= 1;
      dma.qtdDias = diasNoMes - (dataInicial.iDia - dataFinal.iDia);
    }

    
    
    dma.retorno = 1;
    return dma;
  }
}

/*
 Q3 = encontrar caracter em texto
 @objetivo
  Pesquisar quantas vezes um determinado caracter ocorre em um texto
 @entrada
  uma string texto, um caracter c e um inteiro que informa se é uma pesquisa
 Case Sensitive ou não. Se isCaseSensitive = 1, a pesquisa deve considerar
 diferenças entre maiúsculos e minúsculos. Se isCaseSensitive != 1, a pesquisa
 não deve  considerar diferenças entre maiúsculos e minúsculos.
 @saida
  Um número n >= 0.
 */

char normalizarChar(char c, int isCaseSensitive) {
  char charNormalizado = c;

  int isMinus = charNormalizado >= 97 && charNormalizado < 123;
  int isMais = charNormalizado >= 65 && charNormalizado <= 90;

  if (isCaseSensitive || isMinus)
    charNormalizado -= 32;
  
  if ((isMinus || isMais))
    return charNormalizado;
  
  char mais[6][6] = {
    "AÁÀÂÃÄ",
    "EÉÈÊË",
    "IÍÌÎÏ",
    "OÓÒÔÕÖ",
    "UÚÙÛÜ",
    "CÇ"
  };
  
  char minus[6][6] = {
    "aáàâãä",
    "eéèêë",
    "iíìîï",
    "oóòôõö",
    "uúùûü",
    "cç"
  };

  for (int i = 0; i < 6; i++) {
    for (int j = 1; j < 6; j++) {
      if (c == minus[i][j])
        charNormalizado = minus[i][0];
      if (c == mais[i][j])
        charNormalizado = mais[i][0];
    }
  }
  
  return charNormalizado;
}

int q3(char *texto, char c, int isCaseSensitive) {
  setlocale(LC_ALL,""); 
  int vezes = 0;


  for (int i = 0; texto[i] != '\0'; i++) {
    if (c == texto[i]) {
      vezes++;
      continue;
    }

    if (normalizarChar(texto[i], isCaseSensitive) == normalizarChar(c, isCaseSensitive))
      vezes++;
  }

  return vezes;
}

/*
 Q4 = encontrar palavra em texto
 @objetivo
  Pesquisar todas as ocorrências de uma palavra em um texto
 @entrada
  uma string texto base (strTexto), uma string strBusca e um vetor de inteiros
 (posicoes) que irá guardar as posições de início e fim de cada ocorrência da
 palavra (strBusca) no texto base (texto).
 @saida
  Um número n >= 0 correspondente a quantidade de ocorrências encontradas.
  O vetor posicoes deve ser preenchido com cada entrada e saída correspondente.
 Por exemplo, se tiver uma única ocorrência, a posição 0 do vetor deve ser
 preenchido com o índice de início do texto, e na posição 1, deve ser preenchido
 com o índice de fim da ocorrencias. Se tiver duas ocorrências, a segunda
 ocorrência será amazenado nas posições 2 e 3, e assim consecutivamente. Suponha
 a string "Instituto Federal da Bahia", e palavra de busca "dera". Como há uma
 ocorrência da palavra de busca no texto, deve-se armazenar no vetor, da
 seguinte forma: posicoes[0] = 13; posicoes[1] = 16; Observe que o índice da
 posição no texto deve começar ser contado a partir de 1. O retorno da função,
 n, nesse caso seria 1;

 */
int q4(char *strTexto, char *strBusca, int posicoes[30]) {
  setlocale(LC_ALL, "");

  char mais[6][5] = {
    "ÁÀÂÃÄ",
    "ÉÈÊË",
    "ÍÌÎÏ",
    "ÓÒÔÕÖ",
    "ÚÙÛÜ",
    "Ç"
  };

  char minus[6][5] = {
    "áàâãä",
    "éèêë",
    "íìîï",
    "óòôõö",
    "úùûü",
    "ç"
  };

  for (int i = 0; strlen(strTexto) > i; i++) {
    for (int k = 0; k < 5; k++) {
      if (strTexto[i] == mais[0][k] || strTexto[i] == minus[0][k]) {
        strTexto[i] = 'a';

        for (int j = i + 1; j < strlen(strTexto); j++) {
          strTexto[j] = strTexto[j + 1];
        }
      }

      else if (strTexto[i] == mais[1][k] ||
               strTexto[i] == minus[1][k]) {
        strTexto[i] = 'e';

        for (int j = i + 1; j < strlen(strTexto); j++) {
          strTexto[j] = strTexto[j + 1];
        }
      }

      else if (strTexto[i] == mais[2][k] ||
               strTexto[i] == minus[2][k]) {
        strTexto[i] = 'i';

        for (int j = i + 1; j < strlen(strTexto); j++) {
          strTexto[j] = strTexto[j + 1];
        }
      }

      else if (strTexto[i] == mais[3][k] ||
               strTexto[i] == minus[3][k]) {
        strTexto[i] = 'o';

        for (int j = i + 1; j < strlen(strTexto); j++) {
          strTexto[j] = strTexto[j + 1];
        }
      }

      else if (strTexto[i] == mais[4][k] ||
               strTexto[i] == minus[4][k]) {
        strTexto[i] = 'u';

        for (int j = i + 1; j < strlen(strTexto); j++) {
          strTexto[j] = strTexto[j + 1];
        }
      }

      else if (strTexto[i] == mais[5][k] ||
               strTexto[i] == minus[5][k]) {
        strTexto[i] = 'c';

        for (int j = i + 1; j < strlen(strTexto); j++) {
          strTexto[j] = strTexto[j + 1];
        }
      }
    }
  }

  int vezes = 0;
  int armazenamento = 0;

  for (int i = 0; strlen(strTexto) > i; i++) {
    if (strBusca[0] == strTexto[i]) {
      posicoes[armazenamento] = i + 1;

      for (int j = 1; strlen(strBusca) > j; j++) {
        for (int k = i + 1; strlen(strBusca) + i > k; k++) {

          if (strBusca[j] == strTexto[k]) {
            if (j + 1 == strlen(strBusca)) {
              posicoes[armazenamento + 1] = k + 1;
              vezes++;
              armazenamento = armazenamento + 2;

              i = k;
              break;
            }

            else {
              j++;
            }
          }

          else {
            posicoes[armazenamento] = -1;
            j = strlen(strBusca);

            i = k;
            break;
          }
        }
      }
    }
  }

  return vezes;
}

/*
 Q5 = inverte número
 @objetivo
  Inverter número inteiro
 @entrada
  uma int num.
 @saida
  Número invertido
 */

int q5(int num) {
  int count = 0;
  for (int i = num; i > 0; i = i / 10) {
    count++;
  }

  int contrario = 0;
  while (count != 0) {
    int valor = num % 10;
    contrario = (contrario * 10) + valor;
    num /= 10;

    count--;
  }

  num = contrario;

  return num;
}

/*
 Q6 = ocorrência de um número em outro
 @objetivo
  Verificar quantidade de vezes da ocorrência de um número em outro
 @entrada
  Um número base (numerobase) e um número de busca (numerobusca).
 @saida
  Quantidade de vezes que número de busca ocorre em número base
 */

int q6(int numerobase, int numerobusca) {
  int tam1 = 0;
  int tam2 = 0;
  for (int i = numerobase; i > 0; i = i / 10) {
    tam1++;
  }
  for (int i = numerobusca; i > 0; i = i / 10) {
    tam2++;
  }

  char numerobase_str[tam1];
  sprintf(numerobase_str, "%d", numerobase);
  char numerobusca_str[tam2];
  sprintf(numerobusca_str, "%d", numerobusca);
  
  int vezes;
  vezes = 0;

  for (int i = 0; tam1 > i; i++) {
    if (numerobusca_str[0] == numerobase_str[i]) {

      if (tam2 > 1) {
        for (int j = 1; tam2 > j; j++) {
          for (int k = i + 1; tam2 + i > k; k++) {
            
            if (numerobusca_str[j] == numerobase_str[k]) {
              if (j + 1 == tam2) {
                vezes++;
                break;
              }
              else {
                j++;
              }
            }          
          }
        }    
      }

      else {
        vezes++;
      }
      
    }
  }
  
  
  return vezes;
}

DataQuebrada quebraData(char * data) {
  DataQuebrada dataSeparada;
  char dataString[3][4];

  int j = 0, k = 0;
  for (int i = 0; data[i] != '\0'; i++) {
    if (data[i] != '/') {
      dataString[j][k] = data[i];
      k++;
    } else {
      dataString[j][k] = '\0';
      j++;
      k = 0;
    }
  }
  dataString[j][k] = '\0';

  dataSeparada.iDia = atoi(dataString[0]);
  dataSeparada.iMes = atoi(dataString[1]);
  dataSeparada.iAno = atoi(dataString[2]);

  return dataSeparada;
}
