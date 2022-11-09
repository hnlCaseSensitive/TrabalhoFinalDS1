
#include "raylib.h"
#include "setup_inicio.h"
#include <unistd.h>
#include "gui.h"

Texture2D title;
Texture2D choose;
Texture2D over;
Texture2D heal;
Texture2D sucess;
Texture2D start;
Texture2D combat;

int main(void)
{

    // Init
    InitWindow(screenWidth, screenHeight, "jogo -  basic window");
    SetTargetFPS(60);

    player = (Player*) malloc(sizeof(Player));
    foe = (Inimigo*) malloc(sizeof(Inimigo));
    Mapa = createMap();
    curr = &Mapa->vertices[0];

    status = (Status*) malloc(sizeof(Status));

    Image titlescreen = LoadImage("./resources/TITLE.png");
    title = LoadTextureFromImage(titlescreen);
    UnloadImage(titlescreen);

    Image choosedest = LoadImage("./resources/CHOOSEDEST.png");
    choose = LoadTextureFromImage(choosedest);
    UnloadImage(choosedest);

    Image gameover = LoadImage("./resources/GAMEOVER.png");
    over = LoadTextureFromImage(gameover);
    UnloadImage(gameover);

    Image healscreen = LoadImage("./resources/HEAL.png");
    heal = LoadTextureFromImage(healscreen);
    UnloadImage(healscreen);

    Image success_screen = LoadImage("./resources/SUCCESS.png");
    sucess = LoadTextureFromImage(success_screen);
    UnloadImage(success_screen);

    Image start_screen = LoadImage("./resources/START.png");
    start = LoadTextureFromImage(start_screen);
    UnloadImage(start_screen);

    Image combate_screen = LoadImage("./resources/COMBATE.png");
    combat = LoadTextureFromImage(combate_screen);
    UnloadImage(combate_screen);

    // loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        Update_Window();
        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(RAYWHITE);
            Draw_Window();
        EndDrawing();
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    UnloadTexture(title);
    UnloadTexture(choose);
    UnloadTexture(over);
    UnloadTexture(heal);
    UnloadTexture(sucess);
    UnloadTexture(start);
    UnloadTexture(combat);

    return 0;
}

void Draw_Window()
{
    switch(currentScreen)
    {
        case TITLE:
        {

            DrawTexture(title, 0, 0, WHITE);
            DrawText("START", 180, 220, 40, corRetanguloPlay);
            DrawText("EXIT", 180, 260, 40, corRetanguloExit);
        } break;
        case GAMEPLAY:
        {
            DrawRectangle(0, 0, screenWidth, screenHeight, WHITE);


            if(curr->tipo == START){
                    DrawTexture(start, 0, 0, WHITE);
                }else if(curr->tipo == HEAL){
                    DrawTexture(heal, 0, 0, WHITE);
                }

                if(curr->tipo != END){
                    DrawText("Move", 180, 200, 40, RED);
                }


            if (IsKeyDown(KEY_TAB)) { // so testando coisas
                DrawRectangle(200, 200, screenWidth/4, screenHeight/5, YELLOW); DrawText("Vida", 200, 0, 20, MAROON);
            }



        } break;

        case ESCOLHEDEST:
        {
            DrawTexture(choose, 0, 0, WHITE);
            DrawText(TextFormat("%d", curr_dest->chaveDest), 600, 200, 40, RED);

        }break;

        case COMBATE:
        {
            DrawTexture(combat, 0, 0, WHITE);

            if(menuArmas>0) { //abre menu p escolher arma
                DrawRectangle(0, 0, screenWidth/4, screenHeight/5, corRetanguloArma1); DrawText("ARMA 1", 0, 0, 30, BLACK);
                DrawRectangle(200, 0, screenWidth/4, screenHeight/5, corRetanguloArma2); DrawText("ARMA 2", 200, 0, 30, BLACK);
                DrawRectangle(400, 0, screenWidth/4, screenHeight/5, corRetanguloArma3); DrawText("ARMA 3", 400, 0, 30, BLACK);
                DrawRectangle(600, 0, screenWidth/4, screenHeight/5, corRetanguloArma4); DrawText("ARMA 4", 600, 0, 30, BLACK);
            }
            DrawText(foe->nome, 20, 100, 20, DARKBLUE);
            DrawText(TextFormat("Vida: %i", foe->vida), 200, 100, 20, DARKBLUE);

            DrawText("Player", 20, 120, 20, DARKBLUE);
            DrawText(TextFormat("Vida: %i", player->vidaAtual), 200, 120, 20, DARKBLUE);

             DrawText(TextFormat("out: %s", status->textOutputJ), 180,140,20, corOutputJ);
             DrawText(TextFormat("out: %s", status->textOutputI), 180,160,20, corOutputI);


            DrawText(TextFormat("Arma:%s",status->armaEquipada), 10, 160, 10, DARKGREEN);
            DrawText("COMBATE", 20, 180, 20, DARKGREEN);
            DrawText("Aperte Y para atacar", 20, 220, 20, DARKGREEN);
            DrawText("Aperte F para tentar fugir", 20, 240, 20, DARKGREEN);
            DrawText("Aperte U para trocar armas", 20, 280, 20, DARKGREEN);


        } break;

        case ITEM_ESPECIAL:
        {
            DrawRectangle(0, 0, screenWidth, screenHeight, GREEN);
            DrawText("Seleção de item", 20, 20, 40, MAROON);
            DrawText("Escolha seu item especial", 20, 50, 40, MAROON);

            DrawRectangle(10, 130, 150, 50, corRetanguloLuva); DrawText("Luvas de Boxe", 10, 130, 20, MAROON);
            DrawRectangle(10, 180, 150, 50, corRetanguloLaser); DrawText("Mira a Laser", 10, 180, 20, MAROON);
            DrawRectangle(10, 230, 150, 50, corRetanguloSuco); DrawText("Suquinho", 10, 230, 20, MAROON);
            DrawRectangle(10, 280, 150, 50, corRetanguloFaca); DrawText("Faca", 10, 280, 20, MAROON);

            if (IsKeyPressed(KEY_F5))
                currentScreen = GAMEPLAY;

        } break;

        case ENDING:
        {

            if(player->vidaAtual > 0){
                DrawTexture(sucess, 0, 0, WHITE);
            }else{
                DrawTexture(over, 0, 0, WHITE);
            }

        } break;
        default: break;
    }
}

void Update_Window()
{
    switch(currentScreen)
    {
        case TITLE:
        {
            switch(menuSelection)
            {
                case PLAY:
                    corRetanguloPlay = RED;
                    if (IsKeyPressed(KEY_DOWN)) {
                        corRetanguloPlay = BLACK;
                        menuSelection = EXIT;
                    }
                    if (IsKeyPressed(KEY_ENTER)) {
                        currentScreen = GAMEPLAY;
                    }
                    break;
                case EXIT:
                    corRetanguloExit = RED;
                    if (IsKeyPressed(KEY_UP)) {
                        corRetanguloExit = BLACK;
                        menuSelection = PLAY;
                    }
                    if (IsKeyPressed(KEY_ENTER)) {
                        //currentScreen = GAMEPLAY;
                        CloseWindow();
                    }
                    break;
            }
        } break;

        case GAMEPLAY:
        {
            /* criando personagem */
            if (!jogadorExiste)
            {
                criaJogador(player, status);
                jogadorExiste = 1;
            }
            /* mapa */

            if (IsKeyPressed(KEY_C)) {emCombate*=-1; } // TEMP


            switch(curr->tipo){
                case START:
                    if (player->vidaAtual<=0) currentScreen = ENDING;
                    player->vidaAtual = player->vidaMaxima;

                    if(IsKeyPressed(KEY_ENTER)){
                        curr_dest = curr->lista;
                        currentScreen = ESCOLHEDEST;
                    }
                    break;
                case END:
                    currentScreen = ENDING;
                    break;
                case HEAL:
                    if(IsKeyPressed(KEY_ENTER)){
                        curr_dest = curr->lista;
                        currentScreen = ESCOLHEDEST;
                    }
                    break;
                case ATK:
                    curr_dest = curr->lista;
                    currentScreen = ESCOLHEDEST;
                    emCombate*=-1;
                    break;
            }


            if (emCombate>0) {
                foe = sorteiaInimigo();
                //printf("Inimigo encontrado:%s\n", foe->nome);
                currentScreen = COMBATE;
            }




            if (IsKeyPressed(KEY_F4))
                currentScreen = ITEM_ESPECIAL;
        } break;

        case ESCOLHEDEST:
            {
                if(IsKeyPressed(KEY_W)){
                    curr_dest = curr_dest->prox;
                }

                if(curr_dest == NULL){
                    curr_dest = curr->lista;
                }

                if(IsKeyPressed(KEY_ENTER)){
                    *curr = Mapa->vertices[curr_dest->chaveDest];
                    //if( ((rand() % 10) + 1) * curr_dest->distancia > 50){
                     //   emCombate*=-1;
                    //}else{
                    currentScreen = GAMEPLAY;
                    //}
                }

            } break;

        case COMBATE:
        {
            if (IsKeyPressed(KEY_U) && emCombate>0)
                menuArmas *= -1;

            if (IsKeyPressed(KEY_A)) printf("arma:%d\n", player->armaAtual.tipoDano);

            if (menuArmas>0) {

                switch (player->armaAtual.tipoDano)
                {
                    case ACIDO:
                        escolheArma(player, ARMA2, status);
                        menuArmas = -1;
                        break;
                    case ELETRICO:
                        escolheArma(player, ARMA3, status);
                        menuArmas = -1;
                        break;
                    case PERFURACAO:
                        escolheArma(player, ARMA4, status);
                        menuArmas = -1;

                        break;
                    case DESARMADO:
                        escolheArma(player, ARMA1, status);
                        menuArmas = -1;
                        break;
                }
            }

            if (IsKeyPressed(KEY_Y)) {
                if (foe->vida>0) {
//                     corOutputJ = DARKBLUE;
//                     corOutputI = DARKBLUE;
//                     if (ColorToInt(corOutputI)!=ColorToInt(corBackgroundCombate)) corOutputJ = corBackgroundCombate;
//                     if (ColorToInt(corOutputJ)!=ColorToInt(corBackgroundCombate)) corOutputI = corBackgroundCombate;
                    //currentOutput = status->textOutputJ;
                    turnoJogador(player,foe,status);
                    sleep(0.7);
                    //corOutputJ = corBackgroundCombate; // color backgroundcombate

                    turnoInimigo(player,foe,status);
                    //currentOutput = status->textOutputI;
                }
                    //ataque(player,foe);
            }
            //}



                if (foe->vida <= 0) {
                    printf("inimigo perdeu\n");
                    emCombate = -1;
                    free(foe);
                }
                if (player->vidaAtual <= 0) {
                    printf("vc perdeu\n");
                    currentScreen = ENDING;
                    free(foe);
                }

                if (emCombate<0) {
                    if (player->vidaAtual<=0) { currentScreen = ENDING; } // movido p controlar na nav do nodo por enquanto pelo menos
                    currentScreen = ESCOLHEDEST;

                }

            if (IsKeyPressed(KEY_F)) {
                emCombate = -1;
                foe = NULL;
                currentScreen = GAMEPLAY;
            }

        } break;

        case ITEM_ESPECIAL:
            switch(itemSelection)
            {
                case LUVA:
                    corRetanguloLuva = PURPLE;
                    if (IsKeyPressed(KEY_UP)) {
                        corRetanguloLuva = BLUE;
                        itemSelection = FACA;
                    }
                    if (IsKeyPressed(KEY_DOWN)) {
                        corRetanguloLuva = BLUE;
                        itemSelection = LASER;
                    }
                    if (IsKeyPressed(KEY_ENTER)) {
                        selecionaItem(LUVA,player);
                    } break;
                case LASER:
                    corRetanguloLaser = PURPLE;
                    if (IsKeyPressed(KEY_UP)) {
                        corRetanguloLaser = BLUE;
                        itemSelection = LUVA;
                    }
                    if (IsKeyPressed(KEY_DOWN)) {
                        corRetanguloLaser = BLUE;
                        itemSelection = SUCO;
                    }
                    if (IsKeyPressed(KEY_ENTER)) {
                        selecionaItem(LASER,player);
                    } break;
                case SUCO:
                    corRetanguloSuco = PURPLE;
                    if (IsKeyPressed(KEY_UP)) {
                        corRetanguloSuco = BLUE;
                        itemSelection = LASER;
                    }
                    if (IsKeyPressed(KEY_DOWN)) {
                        corRetanguloSuco = BLUE;
                        itemSelection = FACA;
                    }
                    if (IsKeyPressed(KEY_ENTER)) {
                        selecionaItem(SUCO,player);
                    } break;
                case FACA:
                    corRetanguloFaca = PURPLE;
                    if (IsKeyPressed(KEY_UP)) {
                        corRetanguloFaca = BLUE;
                        itemSelection = SUCO;
                    }
                    if (IsKeyPressed(KEY_DOWN)) {
                        corRetanguloFaca = BLUE;
                        itemSelection = LUVA;
                    }
                    if (IsKeyPressed(KEY_ENTER)) {
                        selecionaItem(FACA,player);
                    } break;
            } break;

        case ENDING:
        {
            // TODO: Update ENDING screen variables here!

            Mapa = restartMap(Mapa);
            curr = &Mapa->vertices[0];

            // Press enter to return to TITLE screen
            if (IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                currentScreen = TITLE;
            }
            if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                CloseWindow();
            }
        } break;
        default: break;
    }
}


