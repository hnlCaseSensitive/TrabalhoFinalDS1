#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "gameLogic.h"

int main(void){

    srand(time(NULL));

    GrafoLA* test = createMap();
    imprimeGrafoLA(test);
    imprimeCaminhoMinimoInversoGrafoLA(test, 0, findKey(test, END));
    destroiGrafoLA(test);

    return 0;
}