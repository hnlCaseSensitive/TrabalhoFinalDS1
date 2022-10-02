#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "grafo_la.h"

enum{
    ATK = 0,
    HEAL,
    DEF
} skill_type;

typedef struct SKILL {
    char nome[20];
    float dmg, crit_chance, acc, cost;
    skill_type tipo;
} skills;

typedef struct ITEM{
    char nome[20];
    skills funcao;
} item;

typedef struct LIFE_FORM
{
    float hp, mana;
    skills special_atks[3];
    item inventory[5];
} mold;

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
