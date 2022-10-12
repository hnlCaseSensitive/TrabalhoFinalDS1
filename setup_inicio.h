#ifndef _SETUP_INICIO_H_
#define _SETUP_INICIO_H_

#include "gameLogic.h"

void inicioJogoCombate(Player* player);

void statusPlayer(Player player);

void statusInimigo(Inimigo inimigo);

void selecionaItem(int input, Player*);

void criaJogador(Player*, Status*);

#endif
