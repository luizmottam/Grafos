// https://github.com/luizmottam/Grafos/blob/master/atividade01.c
#include <stdio.h>
#include <stdlib.h>

// Definindo estrutura doo grafo (vertices e arestas)
typedef struct vertice {
  struct lista *adj;
  int visitado;
  int cor;
} vertice;

typedef struct lista {
  struct registro *inicio;
  struct registro *fim;
} lista;

typedef struct registro {
  int valor;
  struct registro *proximo;
} registro;

// Funções básicas
lista *aloca_lista() {
  lista *adj = (lista *)calloc(sizeof(lista), 1);
  return adj;
}

registro *aloca_registro() {
  registro *novo = (registro *)calloc(sizeof(registro), 1);
  return novo;
}

void mostra_lista(lista *adj) {
  if (adj == NULL) {
    printf("\n");
    return;
  }
  registro *aux;
  aux = adj->inicio;

  while (aux != NULL) {
    printf("%d", aux->valor);
    aux = aux->proximo;
  }
  printf("\n");
}

void incluir_vertice(vertice *v, int valor) {
  if (v->adj == NULL) {
    v->adj = aloca_lista();
  }
  registro *novo;
  novo = aloca_registro();
  novo->valor = valor;
  novo->proximo = NULL;

  if (v->adj->inicio == NULL) {
    v->adj->inicio = novo;
    v->adj->fim = novo;
  } else {
    v->adj->fim->proximo = novo;
    v->adj->fim = novo;
  }
}

int dfs(int raiz, vertice *vertices, int cor) {
  vertices[raiz].visitado = 1;
  vertices[raiz].cor = cor;
  printf("Vertice %d com cor %d\n", raiz, vertices[raiz].cor);
  registro *aux;
  if (vertices[raiz].adj != NULL) {
    aux = vertices[raiz].adj->inicio;
    while (aux != NULL) {
      if (vertices[aux->valor].visitado == 0) {
        if (!dfs(aux->valor, vertices, cor * (-1))) {
          return 0;
        } else {
          if (vertices[aux->valor].cor == cor) {
            return 0;
          }
        }

        aux = aux->proximo;
      }
    }
    return 1;
  }
}

int main() {

  int qtd_vertices, qtd_arestas, i, a, b, j, x, qnt_casos, cenarios;
  vertice *vertices;

  printf("Digite o número de cenários: ");
  scanf("%d", &cenarios);

  printf("Digite a qnt de vertices e depois a qnt de arestas (Ex: 3 2): \n");

  for (i = 0; i <= cenarios; i++) {
    scanf("%d %d", &qtd_vertices, &qtd_arestas);
    vertices = (vertice *)calloc(sizeof(vertice), qtd_vertices + 1);

    for (j = 0; i < qtd_arestas; i++) {
      scanf("%d %d", &a, &b);
      incluir_vertice(&vertices[a], b);
      incluir_vertice(&vertices[b], a);
    }
    printf("Cenario #%d", i);
    for (x = 0; i <= qtd_vertices; i++) {
      dfs(i, vertices, 1);
    }
    return 0;
  }
}