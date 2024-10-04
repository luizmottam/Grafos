#include <stdio.h>
#include <stdlib.h>

// Definindo estrutura do grafo (vertices e arestas)
typedef struct vertice {
  struct lista *adj;
  int visitado;
  int pai;
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
lista *aloca_lista() { return (lista *)calloc(1, sizeof(lista)); }

registro *aloca_registro() { return (registro *)calloc(1, sizeof(registro)); }

void mostra_lista(lista *adj) {
  if (adj == NULL) {
    printf("\n");
    return;
  }
  registro *aux = adj->inicio;
  while (aux != NULL) {
    printf("%d ", aux->valor);
    aux = aux->proximo;
  }
  printf("\n");
}

void incluir_vertice(vertice *v, int valor) {
  if (v->adj == NULL) {
    v->adj = aloca_lista();
  }
  registro *novo = aloca_registro();
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

void dfs(int raiz, vertice *vertices) {
  vertices[raiz].visitado = 1;
  printf("%d\n", raiz);

  registro *aux = vertices[raiz].adj ? vertices[raiz].adj->inicio : NULL;
  while (aux != NULL) {
    if (vertices[aux->valor].visitado == 0) {
      vertices[aux->valor].pai = raiz;
      dfs(aux->valor, vertices);

      // Se ele for meu pai, classificar ele como "ida"
      // S ele não for marcar como "volta"
    }

    
    aux = aux->proximo;
  }
}

void liberar_memoria(vertice *vertices, int qtd_vertices) {
  for (int i = 1; i <= qtd_vertices; i++) {
    registro *aux = vertices[i].adj->inicio;
    while (aux != NULL) {
      registro *temp = aux;
      aux = aux->proximo;
      free(temp);
    }
    free(vertices[i].adj);
  }
  free(vertices);
}

int main() {
  int qtd_vertices, qtd_arestas, i, a, b;
  vertice *vertices;

  printf("Digite a quantidade de vertices e depois a quantidade de arestas "
         "(Ex: 3 2): \n");
  scanf("%d %d", &qtd_vertices, &qtd_arestas);

  vertices = (vertice *)calloc(qtd_vertices + 1, sizeof(vertice));

  printf("Digite as conexões das arestas: \n");
  for (i = 0; i < qtd_arestas; i++) {
    scanf("%d %d", &a, &b);
    if (a > 0 && a <= qtd_vertices && b > 0 && b <= qtd_vertices) {
      incluir_vertice(&vertices[a], b);
      incluir_vertice(&vertices[b], a);
    } else {
      printf("Erro: vertices %d e %d estão fora dos limites.\n", a, b);
    }
  }

  printf("Lista da Adjacencia: \n");
  for (i = 1; i <= qtd_vertices; i++) {
    printf("Vertice: %d -> ", i);
    mostra_lista(vertices[i].adj);
  }

  for (i = 1; i <= qtd_vertices; i++) {
    vertices[i].visitado = 0;
    vertices[i].pai = -1;
  }

  printf("DFS a partir do vértice 1:\n");
  dfs(1, vertices);

  liberar_memoria(vertices, qtd_vertices);

  return 0;
}
