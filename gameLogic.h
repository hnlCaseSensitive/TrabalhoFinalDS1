#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "grafo_la.h"
#include "combate.h"
#include "setup_inicio.h"

//funcao que cria um mapa aleatorio para o jogo.
GrafoLA *createMap(void);

//funcao que reinicia o mapa deletando o antigo e criando um novo.
GrafoLA *restartMap (GrafoLA* grafo);

//funcao que aplica tipo aos nodo.
void aplicaTipos(GrafoLA* grafo);

//funcao que cria caminhos aleatorios entre o start e o end.
void criaCaminhos(GrafoLA* grafo);

//funcao que acha a chave do primeiro nodo que é do tipo passado.
int findKey(GrafoLA* grafo, int tipo);

//MONSTROS

#endif
