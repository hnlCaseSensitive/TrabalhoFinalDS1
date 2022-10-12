
#include "raylib.h"
#include "setup_inicio.h"
#include <unistd.h>
#include "gui.h"

int main(void)
{
    
    // Init
    InitWindow(screenWidth, screenHeight, "jogo -  basic window");
    SetTargetFPS(60); 
    
    player = (Player*) malloc(sizeof(Player));
    foe = (Inimigo*) malloc(sizeof(Inimigo));
    Mapa = createMap();

    
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
    
    return 0;
}

void Draw_Window()
{
    switch(currentScreen)
    {
        case TITLE:
        {
            DrawRectangle(0, 0, screenWidth, screenHeight, GREEN);
            DrawText("DUNGEON CRAWLER", 20, 20, 40, DARKGREEN);
            DrawRectangle(150, 100, 300, 50, corRetanguloPlay); DrawText("START", 180, 120, 20, WHITE);
            DrawRectangle(150, 150, 300, 50, corRetanguloExit); DrawText("EXIT", 180, 160, 20, WHITE);
        } break;
        case GAMEPLAY:
        {
            DrawRectangle(0, 0, screenWidth, screenHeight, PURPLE);
   


            if (IsKeyDown(KEY_TAB)) { // so testando coisas
                DrawRectangle(200, 200, screenWidth/4, screenHeight/5, YELLOW); DrawText("Vida", 200, 0, 20, MAROON);
            }

            // TODO
            if (emCombate>0) {
                DrawRectangle(0, 0, screenWidth, screenHeight/4, GREEN); DrawText("INIMIGO!!!", 20, 20, 40, DARKGREEN);
                //currentScreen = COMBATE;
            }
        } break;
        case COMBATE:
        {
            //printf("Tela do combate\n");
            if(menuArmas>0) { //abre menu p escolher arma
                DrawRectangle(0, 0, screenWidth/4, screenHeight/5, corRetanguloArma1);
                DrawRectangle(200, 0, screenWidth/4, screenHeight/5, corRetanguloArma2);
                DrawRectangle(400, 0, screenWidth/4, screenHeight/5, corRetanguloArma3);
                DrawRectangle(600, 0, screenWidth/4, screenHeight/5, corRetanguloArma4);
            }
            //DrawRectangle(0, 0, screenWidth, screenHeight, GREEN);
            DrawText("COMBATE (f pra voltar)", 20, 20, 40, DARKGREEN);
            DrawText("Aperte Y para atacar", 20, 50, 40, DARKGREEN); // opcao de trocar armas
            DrawText("Aperte U para trocar armas", 20, 90, 40, DARKGREEN);
            if (!emCombate) currentScreen = GAMEPLAY;
            if (IsKeyPressed(KEY_F)) currentScreen = GAMEPLAY;
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
            // TODO: Draw ENDING screen here!
            DrawRectangle(0, 0, screenWidth, screenHeight, BLUE);
            DrawText("GAMEOVER", 20, 20, 40, DARKBLUE);
            DrawText("Jogar novamente?", 120, 220, 20, DARKBLUE);

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
                    corRetanguloPlay = DARKBLUE;
                    if (IsKeyPressed(KEY_DOWN)) {
                        corRetanguloPlay = BLUE;
                        menuSelection = EXIT;
                    }
                    if (IsKeyPressed(KEY_ENTER)) {
                        currentScreen = GAMEPLAY;
                    }
                    break;
                case EXIT:
                    corRetanguloExit = DARKBLUE;
                    if (IsKeyPressed(KEY_UP)) {
                        corRetanguloExit = BLUE;
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
                criaJogador(player);
                jogadorExiste = 1;
            }
            /* mapa */
            
            if (IsKeyPressed(KEY_C)) {emCombate*=-1; } // TEMP
                        
            if (emCombate>0) {
                printf("combm\n");
                foe = sorteiaInimigo();
                printf("Inimigo encontrado:%s\n", foe->nome);
                currentScreen = COMBATE;
            }

            
            
            
            if (IsKeyPressed(KEY_F4))
                currentScreen = ITEM_ESPECIAL;
            
            if (IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
            {
                currentScreen = ENDING;
            }
        } break;
        
        case COMBATE:
        {
            if (!emCombate) currentScreen = GAMEPLAY;
            // MENU DE ARMAS
            if (IsKeyPressed(KEY_F1)) {
                printf("Abriu menu armas\n");
                menuArmas *= -1;
            }
            
            if (menuArmas>0) {
                switch (armaSelection)
                {
                    case ARMA1:
                        corRetanguloArma1 = destaque;
                        if (IsKeyPressed(KEY_RIGHT)) {
                            corRetanguloArma1 = DARKGREEN;
                            armaSelection = ARMA2;
                        }
                        if (IsKeyPressed(KEY_LEFT)) {
                            corRetanguloArma1 = DARKGREEN;
                            armaSelection = ARMA4;
                        }
                        if (IsKeyPressed(KEY_ENTER))
                            escolheArma(player,ARMA1);
                        break;
                    case ARMA2:
                        corRetanguloArma2 = destaque;
                        if (IsKeyPressed(KEY_RIGHT)) {
                            corRetanguloArma2 = GREEN;
                            armaSelection = ARMA3;
                        }
                        if (IsKeyPressed(KEY_LEFT)) {
                            corRetanguloArma2 = GREEN;
                            armaSelection = ARMA1;
                        } 
                        if (IsKeyPressed(KEY_ENTER))
                            escolheArma(player,ARMA2);
                        break;
                    case ARMA3:
                        corRetanguloArma3 = destaque;
                        if (IsKeyPressed(KEY_RIGHT)) {
                            corRetanguloArma3 = DARKGREEN;
                            armaSelection = ARMA4;
                        }
                        if (IsKeyPressed(KEY_LEFT)) {
                            corRetanguloArma3 = DARKGREEN;
                            armaSelection = ARMA2;
                        } 
                        if (IsKeyPressed(KEY_ENTER))
                            escolheArma(player,ARMA3);
                        break;
                    case ARMA4:
                        corRetanguloArma4 = destaque;
                        if (IsKeyPressed(KEY_RIGHT)) {
                            corRetanguloArma4 = GREEN;
                            armaSelection = ARMA1;
                        }
                        if (IsKeyPressed(KEY_LEFT)) {
                            corRetanguloArma4 = GREEN;
                            armaSelection = ARMA3;
                        }
                        if (IsKeyPressed(KEY_ENTER))
                            escolheArma(player,ARMA4);
                        break;
                }
            }
            
            //escolheArma(player,0);
            //printf("Arma atual:%s\n", player->armaAtual.desc);
            
            // flag p ver se ta em combate em vez disso
            if (IsKeyPressed(KEY_Y)) {
                if (foe->vida>0)
                    ataque(player,foe);
                    if (foe->vida<=0 && emCombate>0) {
                        printf("inimigo perdeu\n");
                        emCombate = -1;
                    }
                    if (player->vidaAtual<=0 && emCombate>0) {
                        printf("vc perdeu\n");
                        emCombate = -1;
                    }
                if (emCombate<0) // arrumar pra gameover se o jogador morrer dps
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


