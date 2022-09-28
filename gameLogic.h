#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "grafo_la.h"

typedef struct LIFE_FORM
{
    float hp, qi;
    int lvl, sorc, str, dex, res; // sorc -> sorcery, str strength, dex dexterity, res resistances.
    float elemen_resis[3];
} mold;


GrafoLA *createMap(void);

GrafoLA *restartMap (GrafoLA* grafo);

void aplicaTipos(GrafoLA* grafo);

void criaCaminhos(GrafoLA* grafo);

#endif