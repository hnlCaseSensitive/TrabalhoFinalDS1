#include <stdio.h>
#include <stdlib.h>
#include "grafo_la.h"
#include "fila_enc.h"

// Funcao que cria um grafo 
GrafoLA *criaGrafoLA(int numVertices){
   int chave;
   GrafoLA * grafo = (GrafoLA*)malloc(sizeof(GrafoLA));
   grafo->vertices = (NoGrafo*)malloc(sizeof(NoGrafo)*numVertices);
   for (chave = 0; chave < numVertices; chave++){
      grafo->vertices[chave].lista = NULL;
      grafo->vertices[chave].tipo = -1;
      grafo->vertices[chave].pai = -1;
   }
   grafo->numVertices = numVertices;
   return grafo;
}

// Funcao que insere uma aresta em um grafo
void insereArestaGrafoLA(GrafoLA *grafo, int chave1, int chave2){

   for(ArestaGrafo* arr = grafo->vertices[chave1].lista; arr != NULL; arr = arr->prox){
      if(arr->chaveDest == chave2){
         return;
      }
   }

   ArestaGrafo *arestaAux = (ArestaGrafo*)malloc(sizeof(ArestaGrafo));
   arestaAux->chaveDest = chave2;
   arestaAux->distancia = (rand() % 10) + 1; 
   arestaAux->prox = grafo->vertices[chave1].lista;
   grafo->vertices[chave1].lista = arestaAux;
   
}

// Funcao que imprime vertices e arcos
void imprimeGrafoLA(GrafoLA *grafo){
   int chave;
   for (chave = 0; chave < grafo->numVertices; chave++){
      printf("%d [%d/%d] %d\n", chave, grafo->vertices[chave].tEntrada, grafo->vertices[chave].tSaida, grafo->vertices[chave].tipo);
      // Mostra distInicio no resultado do BFS
      // printf("%d [%d/%d] %d\n", chave, grafo->vertices[chave].tEntrada, grafo->vertices[chave].tSaida, grafo->vertices[chave].distInicio); 
   }
   for (chave = 0; chave < grafo->numVertices; chave++){
      for (ArestaGrafo *arestaAux = grafo->vertices[chave].lista; 
           arestaAux != NULL; arestaAux = arestaAux->prox){
           printf("(%d,%d) : %d\n", chave, arestaAux->chaveDest, arestaAux->tipo);
      }     
   }
}

// Funcao que destroi um grafo
void destroiGrafoLA(GrafoLA *grafo){
   int chave;
   for (chave = 0; chave < grafo->numVertices; chave++) {
      ArestaGrafo *arestaAux = grafo->vertices[chave].lista;
      while(arestaAux != NULL){
         ArestaGrafo *arestaTmp = arestaAux->prox;
         free(arestaAux); 
         arestaAux = arestaTmp;
      }
   }
   free(grafo->vertices);
   free(grafo);
}

// Funcao auxiliar para Algs. de Caminhamento
void inicializaCaminhamentoGrafoLA(GrafoLA *grafo){
   int chave;
   grafo->timestamp = 0;
   for (chave = 0; chave < grafo->numVertices; chave++){
      grafo->vertices[chave].cor = BRANCO;
      grafo->vertices[chave].tEntrada = -1; 
      grafo->vertices[chave].tSaida = -1; 
      grafo->vertices[chave].pai = -1; 
   }
   for (chave = 0; chave < grafo->numVertices; chave++)
      for (ArestaGrafo *arestaAux = grafo->vertices[chave].lista; 
           arestaAux != NULL; arestaAux = arestaAux->prox){
           arestaAux->tipo = OUTRA;
      }
}

// Funcao auxiliar recursiva para o Caminhamento em Profundidade
void visitaNodoDFSGrafoLA(GrafoLA *grafo, int chave){
   grafo->vertices[chave].cor = CINZA;
   grafo->vertices[chave].tEntrada = grafo->timestamp++; 
   for(ArestaGrafo *arestaAux = grafo->vertices[chave].lista;
       arestaAux != NULL; arestaAux = arestaAux->prox){
       int chaveAux = arestaAux->chaveDest;
       if(grafo->vertices[chaveAux].cor == BRANCO){
          grafo->vertices[chaveAux].pai = chave; 
          arestaAux->tipo = EXPLORATORIA; 
          visitaNodoDFSGrafoLA(grafo, chaveAux);     
       }
   }
   grafo->vertices[chave].cor = PRETO;
   grafo->vertices[chave].tSaida = grafo->timestamp++; 
}

// Alg. para Caminhamento em Profundidade
void DFSGrafoLA(GrafoLA *grafo, int chaveInicial){
   inicializaCaminhamentoGrafoLA(grafo);
   visitaNodoDFSGrafoLA(grafo, chaveInicial); 
}

// Alg. para Caminhamento em Amplitude
void BFSGrafoLA(GrafoLA *grafo, int chaveInicial){
   inicializaCaminhamentoGrafoLA(grafo);
   FilaEnc *fila = criaFila();
   enfileiraFila(fila, chaveInicial); 
   grafo->vertices[chaveInicial].tEntrada = grafo->timestamp++;
   grafo->vertices[chaveInicial].cor = CINZA;
   grafo->vertices[chaveInicial].distInicio = 0;
   while(!vaziaFila(fila)){
      int chave1 = desenfileiraFila(fila);
      for(ArestaGrafo *arestaAux = grafo->vertices[chave1].lista;
          arestaAux != NULL; arestaAux = arestaAux->prox){
          int chave2 = arestaAux->chaveDest;
          if(grafo->vertices[chave2].cor == BRANCO){
             grafo->vertices[chave2].pai = chave1;
             grafo->vertices[chave2].distInicio = grafo->vertices[chave1].distInicio + 1;
             grafo->vertices[chave2].tEntrada = grafo->timestamp++;
             grafo->vertices[chave2].cor = CINZA;
             arestaAux->tipo = EXPLORATORIA;
             enfileiraFila(fila, chave2); 
          }
      }
      grafo->vertices[chave1].cor = PRETO;
      grafo->vertices[chave1].tSaida = grafo->timestamp++;
   }
   destroiFila(fila);
}

int removeArestaGrafoLA(GrafoLA* grafo, int origem, int destino){
   ArestaGrafo* aux2 = NULL;
   for(ArestaGrafo* aux = grafo->vertices[origem].lista; aux != NULL; aux = aux->prox){
      if(aux->chaveDest == destino){
         if(aux2 == NULL){
            grafo->vertices[origem].lista = aux->prox;
         } else{
            aux2->prox = aux->prox;
         }
         free(aux);
         return 1;
      }
      aux2 = aux;
   }
   return 1;
}

int haCaminhoGrafoLA(GrafoLA *grafo, int origem, int destino){
   return (grafo->vertices[destino].pai != -1);
}

void imprimeCaminhoMinimoInversoGrafoLA(GrafoLA *grafo, int origem, int destino){
   int node = destino;
   if(haCaminhoGrafoLA(grafo, origem, destino)){
      for(NoGrafo aux = grafo->vertices[destino]; aux.distInicio != 0; aux = grafo->vertices[aux.pai]){
         printf("%d - ", node);
         node = aux.pai;
      }
   }
   printf("%d\n", origem);
}
























