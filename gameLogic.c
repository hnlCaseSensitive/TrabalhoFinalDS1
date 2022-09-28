#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "gameLogic.h"

GrafoLA *createMap(void){
    int size = (rand() % 13) + 2;

    GrafoLA* map = criaGrafoLA(size);

    aplicaTipos(map);
    criaCaminhos(map);

    return map;
}

int noArs(GrafoLA* grafo, int key){
    return (grafo->vertices[key].lista == NULL);
}

int findKey(GrafoLA* grafo, int tipo){
    for(int i = 0; i < grafo->numVertices; i++){
        if(grafo->vertices[i].tipo == tipo){
            return i;
        }
    }
    return -1;
}

// criaCaminhos : GrafoLA -> void
/* Conecta todos os nodos do grafo garantindo que o nodo do tipo END seja alcançavel a partir do nodo START
    Aplica os valores das distancias entre cada nodo no valor distancia da struct arestas
*/
void criaCaminhos(GrafoLA* grafo){
    srand(time(NULL));

    int chave1 = 0, chave2 = rand() % grafo->numVertices;
    int end_key = findKey(grafo, END);
    while(grafo->vertices[end_key].pai == -1){
        printf("%d %d",chave1, chave2);
        if(chave1 != chave2){
            if(chave1 == START && noArs(grafo, chave1)){
                insereArestaGrafoLA(grafo, chave1, chave2);
            }else if(chave2 == END){
                insereArestaGrafoLA(grafo, chave1, chave2);
            }else if(chave2 != START && chave1 != END){
                insereArestaGrafoLA(grafo, chave1, chave2);
                insereArestaGrafoLA(grafo, chave2, chave1);
            }
        }
        BFSGrafoLA(grafo, 0);
        chave1 = chave2;
        chave2 = rand() % grafo->numVertices;
    }
}

// aplicaTipos : GrafoLA -> void
/*
    Aplica os tipos para cada nodo do grafo respeitando a quantidade ideal para cada tipo. START & END só podem exister 1
    Usar style enum
*/
void aplicaTipos(GrafoLA* grafo){
    int key = (rand() % (grafo->numVertices - 1)) + 1;
    grafo->vertices[0].tipo = START;

    grafo->vertices[key].tipo = END;

    for(int i = 0; i < grafo->numVertices; i++){
        if(grafo->vertices[i].tipo == -1){
            grafo->vertices[i].tipo = (rand() % 2) + 2;
        }
    }
}

GrafoLA *restartMap (GrafoLA* grafo){
    destroiGrafoLA(grafo);
    return createMap();
}