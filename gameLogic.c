#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "gameLogic.h"

// createMap : void -> *GrafoLa
// cria um mapa de tamanho aleatorio entre 2 e 15 aplicando os tipos aleatorios a cada um e criando 
// caminhos aleatorios entre o start e o end
GrafoLA *createMap(void){
    int size = (rand() % 13) + 2;

    GrafoLA* map = criaGrafoLA(size);

    aplicaTipos(map);
    criaCaminhos(map);

    return map;
}

// noArs : *GrafoLA int -> int
// verifica se o nodo passado nao contem nenhuma aresta
int noArs(GrafoLA* grafo, int key){
    return (grafo->vertices[key].lista == NULL);
}

// findKey : *GrafoLA tipo -> int
// dado um tipo retorna o primeiro elemento do nodo que pertence a dado tipo
int findKey(GrafoLA* grafo, int tipo){
    for(int i = 0; i < grafo->numVertices; i++){
        if(grafo->vertices[i].tipo == tipo){
            return i;
        }
    }
    return -1;
}

// criaCaminhos : *GrafoLA -> void
/* Conecta todos os nodos do grafo garantindo que o nodo do tipo END seja alcançavel a partir do nodo START
    Aplica os valores das distancias entre cada nodo no valor distancia da struct arestas
*/
void criaCaminhos(GrafoLA* grafo){
    srand(time(NULL));

    int chave1 = 0, chave2 = rand() % grafo->numVertices;
    int end_key = findKey(grafo, END);
    while(grafo->vertices[end_key].pai == -1){
       //printf("%d %d",chave1, chave2);
        if(chave1 != chave2){
            if(grafo->vertices[chave1].tipo == START && noArs(grafo, chave1)){
                insereArestaGrafoLA(grafo, chave1, chave2);
            }else if(grafo->vertices[chave2].tipo == END){
                insereArestaGrafoLA(grafo, chave1, chave2);
            }else if(grafo->vertices[chave2].tipo != START && grafo->vertices[chave1].tipo != END){
                insereArestaGrafoLA(grafo, chave1, chave2);
                insereArestaGrafoLA(grafo, chave2, chave1);
            }
        }
        BFSGrafoLA(grafo, 0);
        chave1 = chave2;
        chave2 = rand() % grafo->numVertices;
    }
}

// aplicaTipos : *GrafoLA -> void
/*
    Aplica os tipos para cada nodo do grafo respeitando a quantidade ideal para cada tipo. START & END só podem exister 1
    Usar style enum
*/
void aplicaTipos(GrafoLA* grafo){
    grafo->vertices[0].tipo = START;
    grafo->vertices[grafo->numVertices - 1].tipo = END;

    for(int i = 0; i < grafo->numVertices; i++){
        if(grafo->vertices[i].tipo == -1){
            grafo->vertices[i].tipo = (rand() % 2) + 2;
        }
    }
}

// restartMap : *GrafoLA -> *GrafoLA
// deleta o mapa dado e cria um novo retornando um ponteiro para tal
GrafoLA *restartMap (GrafoLA* grafo){
    destroiGrafoLA(grafo);
    return createMap();
}
