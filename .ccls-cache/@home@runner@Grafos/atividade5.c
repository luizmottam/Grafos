typedef struct vertice {
  struct lista *adj;
  int visitado;
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

void dfs(int raiz, vertice *vertices) {
  vertices[raiz].visitado = 1;
  registro *aux;
  if (vertices[raiz].adj != NULL) {
    aux = vertices[raiz].adj->inicio;
    while (aux != NULL) {
      if (vertices[aux->valor].visitado == 0) {
        dfs(aux->valor, vertices);
      }
      aux = aux->proximo;
    }
  }
}

int main() {

  int qtd_vertices, qtd_arestas, i, a, b, testes;
  int componente = 0;
  vertice *vertices;

  scanf("%d", &testes);
  for (i = 0; i < testes; i++) {
    scanf("%d %d", &qtd_vertices, &qtd_arestas);

    vertices = (vertice *)calloc(sizeof(vertice), qtd_vertices + 1);

    for (i = 0; i < qtd_arestas; i++) {
      scanf("%d %d", &a, &b);
      incluir_vertice(&vertices[a], b);
      incluir_vertice(&vertices[b], a);
    }

    for (i = 1; i <= qtd_vertices; i++) {
      if (vertices[i].visitado == 0) {
        dfs(i, vertices);
        componente++;
      }
    }
    printf("O número de componentes no grafo é igual %d\n", componente);
  }
  return 0;
}