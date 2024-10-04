// https://github.com/luizmottam/Grafos/blob/master/atividade01.c
#include <stdio.h>
#include <stdlib.h>

// Definindo estrutura doo grafo (vertices e arestas)
typedef struct vertice {
  struct lista *adj;
  int visitado;
  int distancia;
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


// DFS principal
void dfs(int raiz, vertice *vertices, int dis) {
  vertices[raiz].visitado = 1;
  vertices[raiz].distancia = dis;
  registro *aux;
  if (vertices[raiz].adj != NULL) {
    aux = vertices[raiz].adj->inicio;
    while (aux != NULL) {
      if (vertices[aux->valor].visitado == 0) {
        dfs(aux->valor, vertices, dis + 1);
      }
      aux = aux->proximo;
    }
  }  
}

void calcula_distancia(int qtd_vertices, vertice *vertices) {
  int dist = 0;
  int no = 0;
  for(int i = 0; i <= qtd_vertices; i++) {
    if(vertices[i].distancia > dist) {
      dist = vertices[i].distancia;
      no = i;
    }
  }

  for (int i = 1; i <= qtd_vertices; i++) {
    vertices[i].visitado =0;
    }
}


// Main
int main() {

  int qtd_vertices, qtd_arestas, i, a, b;
  vertice *vertices;
  int dis = 0;

  printf("Digite a qnt de vertices: \n");
  scanf("%d", &qtd_vertices);

  vertices = (vertice *)calloc(sizeof(vertice), qtd_vertices + 1);

  printf("Digite as conexões das arestas: \n");
  for (i = 1; i < qtd_vertices; i++) {
    scanf("%d %d", &a, &b);
    incluir_vertice(&vertices[a], b);
    incluir_vertice(&vertices[b], a);
  }

  printf("Lista da Adjacencia: \n");
  for (i = 1; i <= qtd_vertices; i++) {
    printf("Vertice: %d -> ", i);
    mostra_lista(vertices[i].adj);
  }

  dfs (1,vertices, 0);
  calcula_distancia(qtd_vertices, *vertices, dist);
  dfs (i,vertices, 0);

  printf("Maior distanica e %d", dist);
  return 0;
}