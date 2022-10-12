#ifndef _GRAFO_LA_H_
#define _GRAFO_LA_H_

typedef enum{
  EXPLORATORIA = 0,
  OUTRA /* Nao Exploratoria */
} tipoAresta;

typedef enum{
  BRANCO = 0, /* Nao Explorado */
  CINZA, /* Sob Exploracao */
  PRETO /* Explorado */
} corVertice;

typedef enum{
   START = 0,
   END,
   HEAL,
   ATK
} style;

typedef struct arGrafo{
   int chaveDest; // Chave do nodo destino

   int distancia;

   struct arGrafo *prox; // Proxima aresta
   tipoAresta tipo; // Util para DFS e BFS
} ArestaGrafo;

typedef struct noGrafo{
   ArestaGrafo *lista; // Lista de arestas
   corVertice cor; // Util para DFS e BFS
   int tEntrada; // Util para DFS e BFS
   int tSaida; // Util para DFS e BFS
   int pai; // Util para DFS e BFS
   int distInicio; // Util para BFS

   style tipo;


} NoGrafo;

typedef struct{
   int numVertices; // Numero de vertices
   NoGrafo *vertices; // Vetor de vertices
   int timestamp; // Util para DFS e BFS
} GrafoLA;


// Funcao que cria um grafo
GrafoLA *criaGrafoLA(int tamanho);

// Funcao que insere uma aresta em um grafo
void insereArestaGrafoLA(GrafoLA *grafo, int chave1, int chave2);

// Funcao que destroi um grafo
void destroiGrafoLA(GrafoLA *grafo);

// Funcao que imprime vertices e arcos
void imprimeGrafoLA(GrafoLA *grafo);

// Alg. para Caminhamento em Profundidade
void DFSGrafoLA(GrafoLA *grafo, int chaveInicial);

// Alg. para Caminhamento em Amplitude
void BFSGrafoLA(GrafoLA *grafo, int chaveInicial);

int removeArestaGrafoLA(GrafoLA* grafo, int origem, int destino);

int haCaminhoGrafoLA(GrafoLA *grafo, int origem, int destino);

void imprimeCaminhoMinimoInversoGrafoLA(GrafoLA *grafo, int origem, int destino);

#endif
