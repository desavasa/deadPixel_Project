// Equipo desarrollador
// Juego
// Fecha de inicio
// retos semanales - Semana 2
#include "gamelib.h"

// Prototipos
void menu_principal(Vector2 *pos, sTband *band, Color green, Texture2D flecha, Texture2D background);
void menu_interno();
void nivel1(sTband *band, Vector2 *pos, Color green, Texture2D player, Texture2D background, Texture2D zombie);
void nivel2();
void nivel3();
void nivel4();
void nivel5();

int main()
{
    // Pantalla completa
    SetConfigFlags(FLAG_FULLSCREEN_MODE);

    sTband band;
    sTplayer jugador;
    sTenemy zombie;
    band.main = 0;
    band.menu = 1;
    band.nivel = 0;

    // En el menu
    // -> iniciar con 1450x y 730y, -> salir 1600x y 845y, -> creditos 1520x y 948y
    jugador.pos.x = 1450.0f;
    jugador.pos.y = 730.0f;
    Color green = {20, 160, 133, 255};

    InitWindow(1920, 1080, "Dead Pixel");
    SetTargetFPS(60);

    // Imagenes cargadas como Texturas 2D
    jugador.player = LoadTexture("sprites/Spritee.png");
    Texture2D background2 = LoadTexture("sprites/Fondou.png");
    Texture2D flecha = LoadTexture("sprites/flecha.png");
    Texture2D back_menu = LoadTexture("sprites/menu.png");
    zombie.zom = LoadTexture("sprites/Zom1cpy.png");

    // Loop principal
    while (WindowShouldClose() == false && band.main != 6)
    {
        if (band.nivel == 0)
        {
            menu_principal(&jugador.pos, &band, green, flecha, back_menu);
        }
        else
        {
            if (band.nivel == 1)
            {
                // Falta battalla
                nivel1(&band, &jugador.pos, green, jugador.player, background2, zombie.zom);
            }
            else
            {
                if(band.nivel == 2)
                {
                    nivel2();
                }
                else
                {
                    if(band.nivel == 3)
                    {
                        nivel3();
                    }
                    else
                    {
                        if(band.nivel == 4)
                        {
                            nivel4();
                        }
                        else
                        {
                            if(band.nivel == 5)
                            {
                                nivel5();
                            }
                        }
                    }
                }
            }
        }

        EndDrawing();
    }

    // Descarga de texturas
    UnloadTexture(jugador.player);
    UnloadTexture(flecha);
    UnloadTexture(back_menu);
    UnloadTexture(background2);
    UnloadTexture(zombie.zom);

    CloseWindow();
    return 0;
}
//*********************************************************************
void menu_principal(Vector2 *pos, sTband *band, Color green, Texture2D flecha, Texture2D background)
{

    // Movimiento de seleccionador
    if (IsKeyPressed(KEY_UP))
    {
        (band->menu)--;
        if (band->menu < 1)
        {
            (band->menu) = 3;
        }
        else
        {
            if (band->menu > 3)
            {
                (band->menu) = 1;
            }
        }
    }
    else
    {
        if (IsKeyPressed(KEY_DOWN))
        {
            (band->menu)++;
            if (band->menu > 3)
            {
                (band->menu) = 1;
            }
            else
            {
                if (band->menu < 1)
                {
                    (band->menu) = 3;
                }
            }
        }
    }

    if (band->menu == 1)
    {
        pos->y = 730.0f;
        pos->x = 1450.0f;
    }
    else
    {
        if (band->menu == 2)
        {
            pos->y = 845.0f;
            pos->x = 1600.0f;
        }
        else
        {
            pos->y = 948.0f;
            pos->x = 1520.0f;
        }
    }

    if (IsKeyPressed(KEY_ENTER))
    {
        if (band->menu == 1)
        {
            band->nivel = 1;
            pos->x = 975.0f;
            pos->y = 550.0f;
        }
        else
        {
            if (band->menu == 2)
            {
                band->main = 6;
            }
            else
            {
                band->main = 3;
            }
        }
    }

    // Inicia el dibujado
    BeginDrawing();
    ClearBackground(green);

    Rectangle sourceRec = {0.0f, 0.0f, (float)flecha.width, (float)flecha.height};

    float nuevoAncho = 50.0f;
    float nuevoAlto = 80.0f;
    Rectangle destRec = {pos->x, pos->y, nuevoAncho, nuevoAlto};

    // 1. Origen: Tomamos la imagen de fondo completa
    Rectangle sourceBackground = {0.0f, 0.0f, (float)background.width, (float)background.height};

    // 2. Destino: Forzamos que se dibuje desde la esquina (0,0) con un tamaño de 800x800
    Rectangle destBackground = {0.0f, 0.0f, 1950.0f, 1100.0f};

    // 3. Origen de rotación (esquina superior izquierda)
    Vector2 bgOrigin = {0.0f, 0.0f};

    // 4. Dibujar el fondo estirado/ajustado a 800x800
    DrawTexturePro(background, sourceBackground, destBackground, bgOrigin, 0.0f, WHITE);

    // Dibujar el sprite usando DrawTextureRec en lugar de DrawCircle
    Vector2 origin = {0.0f, 0.0f};
    DrawTexturePro(flecha, sourceRec, destRec, origin, 0.0f, WHITE);
}
//*********************************************************************
void menu_interno()
{
}
//*********************************************************************
void nivel1(sTband *band, Vector2 *pos, Color green, Texture2D player, Texture2D background, Texture2D zombie)
{
    // Movimientos de jugador
    mov_jugador(pos);

    // Dibujado
    BeginDrawing();
    ClearBackground(green);

    // Interacción
    Rectangle sourceRec = {0.0f, 0.0f, (float)player.width, (float)player.height};
    Rectangle bloque = {0.0f, 0.0f, (float)zombie.width, (float)zombie.height};

    float nuevoAncho = 50.0f;
    float nuevoAlto = 80.0f;
    Rectangle destRec = {pos->x, pos->y, nuevoAncho, nuevoAlto};
    Rectangle destinoRec = {1000.0f, 950.0f, 50.0f, 80.0f};

    Rectangle sourceBackground = {0.0f, 0.0f, (float)background.width, (float)background.height};

    Rectangle destBackground = {0.0f, 0.0f, 1950.0f, 1100.0f};

    Vector2 origen = {0.0f, 0.0f};

    if (CheckCollisionRecs(destRec, destinoRec))
    {
        band->nivel = 0;
    }

    DrawTexturePro(background, sourceBackground, destBackground, origen, 0.0f, WHITE);
    DrawTexturePro(player, sourceRec, destRec, origen, 0.0f, WHITE);
    DrawTexturePro(zombie, bloque, destinoRec, origen, 0.0f, WHITE);
}
//*********************************************************************
void nivel2()
{
}
//*********************************************************************
void nivel3()
{
}
//*********************************************************************
void nivel4()
{
}
//*********************************************************************
void nivel5()
{
}
//*********************************************************************