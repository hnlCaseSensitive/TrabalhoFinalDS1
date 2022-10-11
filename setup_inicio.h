#ifndef _SETUP_INICIO_H_
#define _SETUP_INICIO_H_

#include "gameLogic.h"

void inicioJogoCombate(playerCombate* player);

void statusPlayer(playerCombate player);

void statusInimigo(inimigo inimigo);

void selecionaItem(int input, playerCombate*);

void criaJogador(playerCombate*);

#endif
