#include "raylib.h"
#include "setup_inicio.h"
#include <unistd.h>
#include "gui.h"

int main(void)
{

    // Init
    InitWindow(screenWidth, screenHeight, "jogo -  basic window");
    SetTargetFPS(60);

    player = criaJogador();
    Mapa = createMap();
    curr = &Mapa->vertices[0];

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

    currentScreen = TITLE;
   // Screen_title_init();

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        switch(currentScreen)
            {
                case TITLE: Screen_title_update(); break;
                case GAMEPLAY: Screen_gameplay_update(); break;
                case ESCOLHEDEST: Screen_escolhedest_update(); break;
                case COMBATE: Screen_combate_update(); break;
                case ENDING: Screen_ending_update(); break;
                default: break;
            }
        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(RAYWHITE);
            switch(currentScreen)
            {
                case TITLE: Screen_title_draw(); break;
                case GAMEPLAY: Screen_gameplay_draw(); break;
                case ESCOLHEDEST: Screen_escolhedest_draw(); break;
                case COMBATE: Screen_combate_draw(); break;
                case ENDING: Screen_ending_draw(); break;
                default: break;
            }
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
    destroiJogador(player);

    return 0;
}
// =============== init TODO


// =============== draw functions
void Screen_title_draw()
{
    DrawTexture(title, 0, 0, WHITE);
    //DrawText("START", 180, 220, 40, corRetanguloPlay);
    //DrawText("EXIT", 180, 260, 40, corRetanguloExit);
    DrawCenteredText(130, "START", ButtonFontSize, RED);
    DrawCenteredText(220, "EXIT", ButtonFontSize, RED);
}

void Screen_gameplay_draw()
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
}

void Screen_escolhedest_draw()
{
    DrawTexture(choose, 0, 0, WHITE);
    DrawText(TextFormat("%d", curr_dest->chaveDest), 600, 200, 40, RED);
}

void Screen_combate_draw()
{
    DrawTexture(combat, 0, 0, WHITE);

    DrawText(foe->name, 20, 100, 20, DARKBLUE);
    DrawText(TextFormat("Vida: %i", foe->hp), 200, 100, 20, DARKBLUE);

    DrawText("Player", 20, 120, 20, DARKBLUE);
    DrawText(TextFormat("Vida: %i", player->hp), 200, 120, 20, DARKBLUE);

        //DrawText(TextFormat("out: %s", status->textOutputJ), 180,140,20, corOutputJ);
        //DrawText(TextFormat("out: %s", status->textOutputI), 180,160,20, corOutputI);


    //DrawText(TextFormat("Arma:%s",status->armaEquipada), 10, 160, 10, DARKGREEN);
    DrawText("COMBATE", 20, 180, 20, DARKGREEN);
    DrawText("Aperte Y para atacar", 20, 220, 20, DARKGREEN);
    DrawText("Aperte F para tentar fugir", 20, 240, 20, DARKGREEN);
    DrawText("Aperte U para trocar armas", 20, 280, 20, DARKGREEN);
}

void Screen_ending_draw()
{
    if(player->hp > 0){
        DrawTexture(sucess, 0, 0, WHITE);
    }else{
        DrawTexture(over, 0, 0, WHITE);
    }

}


// ========================== screen update functions
void Screen_title_update()
{
    if (Button_is_selected(GetScreenHeight()/4, "START") || IsKeyPressed(KEY_ENTER)) currentScreen = GAMEPLAY;
    //if (Button_is_selected(GetScreenHeight()/2, "OPTIONS")) currentScreen = OPTIONS;
    if (Button_is_selected(GetScreenHeight() - (GetScreenHeight() / 2), "QUIT")) CloseWindow(); // unload resources something something sai do loop
}

void Screen_gameplay_update()
{

    switch(curr->tipo){
        case START:
            if (player->hp <=0) currentScreen = ENDING;
            player->hp = player->max_hp;

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
        case FIGHT:
            curr_dest = curr->lista;
            currentScreen = ESCOLHEDEST;
            emCombate*=-1;
            break;
    }


    if (emCombate>0) {
        currentScreen = COMBATE;
    }
}

void Screen_escolhedest_update()
{
    if(IsKeyPressed(KEY_W)){
        curr_dest = curr_dest->prox;
    }

    if(curr_dest == NULL){
        curr_dest = curr->lista;
    }

    if(IsKeyPressed(KEY_ENTER)){
        *curr = Mapa->vertices[curr_dest->chaveDest];

        currentScreen = GAMEPLAY;
    }
}

void Screen_combate_update()
{

}

void Screen_ending_update()
{
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
}


// =================================== menu handling
bool Rectangle_is_hovered(Rectangle rectangle)
{
	return CheckCollisionPointRec(GetMousePosition(), rectangle);
}

bool Button_is_selected(int y, const char* text)
{
	float rectHeight = ButtonFontSize + (ButtonBorder * 2.0f);
	float textWidth = (float) (MeasureText(text, ButtonFontSize));

	float textXOrigin = GetScreenWidth() / 2.0f - textWidth / 2.0f;
	float textYOrigin = y - ButtonFontSize / 2.0f;

	Rectangle buttonRect = { textXOrigin - ButtonBorder, textYOrigin - ButtonBorder, textWidth + (ButtonBorder * 2.0f), ButtonFontSize + (ButtonBorder * 2.0f) };

	bool hovered = Rectangle_is_hovered(buttonRect);
	bool down = hovered & IsMouseButtonDown(MOUSE_BUTTON_LEFT);

	Color color = hovered ? (down ? ButtonPressColor : ButtonHighlight) : (ButtonColor);

	DrawRectangleRec(buttonRect, ColorAlpha(color, 0.25f));
	DrawText(text, (int) textXOrigin, (int) textYOrigin, ButtonFontSize, color);
	DrawRectangleLinesEx(buttonRect, 2, color);

	bool clicked = hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

	return clicked;
}

void DrawCenteredText(int y, const char* text, int fontSize, Color color)
{
	int textWidth = MeasureText(text, fontSize);
	DrawText(text, GetScreenWidth() / 2 - textWidth / 2, y - fontSize / 2, fontSize, color);
}
