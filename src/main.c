#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <stdint.h>
#include <string.h>
#include <stdint.h>

typedef struct {
  int *array;
  int tam;
} args;

void mergesort(int *v, int n);
void sort(int *v, int *c, int i, int f);
void merge(int *v, int *c, int i, int m, int f);
void* funcao_thread(void *arg);

int main (void) {
  int i = 0, tam;
  pthread_t threads[2];
  args parte1, parte2;
  
  int entrada[10000];  

  while( scanf("%d", &entrada[i]) == 1 ){
      i++;
      if((entrada[i]!=' ')||(entrada[i]!= '\n')){
            tam++;
      }
  }

  parte1.array = entrada;
  parte1.tam = tam;
  parte2.array = entrada;
  

  pthread_create(&(threads[0]), NULL, funcao_thread, (void*) &parte1 );
  pthread_create(&(threads[1]), NULL, funcao_thread, (void*) &parte2 );

  pthread_join(threads[0], NULL);
  pthread_join(threads[1], NULL);

  for (i = 0; i < tam-1; i++) {
    printf("%d ", entrada[i]);
  }
  printf("%d\n",entrada[tam-1]);
  
  return 0;
}

/*
  Dado um vetor de inteiros v e um inteiro n >= 0, ordena o vetor v[0..n-1] em ordem crescente.
*/

void mergesort(int *v, int n) {
  int *c = malloc(sizeof(int) * n);
  sort(v, c, 0, n - 1);
  free(c);
}

void* funcao_thread(void *arg) {
  args *parametros = (args*)arg;
  int *vet =  parametros->array;
  int tam =   parametros->tam;

  mergesort(vet, tam);
}

/*
  Dado um vetor de inteiros v e dois inteiros i e f, ordena o vetor v[i..f] em ordem crescente.
  O vetor c é utilizado internamente durante a ordenação.
*/
void sort(int *v, int *c, int i, int f) {
  if (i >= f) return;

  int m = (i + f) / 2;

  sort(v, c, i, m);
  sort(v, c, m + 1, f);

  /* Se v[m] <= v[m + 1], então v[i..f] já está ordenado. */
  if (v[m] <= v[m + 1]) return;

  merge(v, c, i, m, f);
}

/*
  Dado um vetor v e três inteiros i, m e f, sendo v[i..m] e v[m+1..f] vetores ordenados,
  coloca os elementos destes vetores, em ordem crescente, no vetor em v[i..f].
*/
void merge(int *v, int *c, int i, int m, int f) {
  int z,
      iv = i, ic = m + 1;

  for (z = i; z <= f; z++) c[z] = v[z];

  z = i;

  while (iv <= m && ic <= f) {
    /* Invariante: v[i..z] possui os valores de v[iv..m] e v[ic..f] em ordem crescente. */

    if (c[iv] < c[ic]) v[z++] = c[iv++];
    else /* if (c[iv] > c[ic]) */ v[z++] = c[ic++];
  }

  while (iv <= m) v[z++] = c[iv++];

  while (ic <= f) v[z++] = c[ic++];
}