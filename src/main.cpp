// Equipo desarrollador
// Juego
// Fecha de inicio
// retos semanales - Semana 2
#include "gamelib.h"

// Prototipos
void menu_principal(Vector2 *pos, sTband *band, Color green, Texture2D flecha, Texture2D background);
void menu_interno();
void refugio(sTband *band, Vector2 *pos, Color green, Texture2D player, Texture2D fondoRefugio);
void nivel1(sTband *band, Vector2 *pos, Color green, Texture2D player, sTmapa map, sTenemy zombie[]);
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
    sTenemy zombie[12];
    sTmapa map;
    band.main = 0;
    band.menu = 1;
    band.nivel = 0;

    // En el menu
    // -> iniciar con 1450x y 730y, -> salir 1600x y 845y, -> creditos 1520x y 948y
    jugador.pos.x = 1450.0f;
    jugador.pos.y = 730.0f;
    Color green = {20, 160, 133, 255};

    InitWindow(0, 0, "Dead Pixel");
    SetTargetFPS(60);

    float w = (float)GetScreenWidth();
    float h = (float)GetScreenHeight();
    int i;

    // Inicialización de mapa
    map.mParedes = 4;
    map.mSalidas = 4;

    map.paredes[0] = (Rectangle){0.0f, 0.0f, w * 0.36f, h * 0.38f};
    map.paredes[1] = (Rectangle){w * 0.63f, 0.0f, w * 0.37f, h * 0.38f};
    map.paredes[2] = (Rectangle){0.0f, h * 0.55f, w * 0.36f, h * 0.50f};
    map.paredes[3] = (Rectangle){w * 0.63f, h * 0.55f, w * 0.37f, h * 0.50f};

    map.salidas[0] = (Rectangle){w * 0.36f, 0.0f, w * 0.27f, h * 0.03f};
    map.salidas[1] = (Rectangle){w * 0.36f, h * 0.97f, w * 0.27f, h * 0.03f};
    map.salidas[2] = (Rectangle){0.0f, h * 0.38f, w * 0.02f, h * 0.22f};
    map.salidas[3] = (Rectangle){w * 0.98f, h * 0.42f, w * 0.02f, h * 0.18f};

    // Imagenes cargadas como Texturas 2D
    jugador.player = LoadTexture("sprites/Spritee.png");
    map.fondo = LoadTexture("sprites/Fondou.png");
    Texture2D fondoRefugio = LoadTexture("sprites/Img.png");
    Texture2D flecha = LoadTexture("sprites/flecha.png");
    Texture2D back_menu = LoadTexture("sprites/back_menu.png");

    for (i = 0; i < 3; i++)
    {
        zombie[i].zom = LoadTexture("sprites/zom1.png");
        zombie[i].pos.x = GetScreenWidth() / 2.0f;
        zombie[i].pos.y = (GetScreenHeight() / 2.0f) - 250.0f;
    }
    for (i = 3; i < 6; i++)
    {
        zombie[i].zom = LoadTexture("sprites/zom2.png");
        zombie[i].pos.x = GetScreenWidth() / 2.0f;
        zombie[i].pos.y = (GetScreenHeight() / 2.0f) - 250.0f;
    }
    for (i = 6; i < 9; i++)
    {
        zombie[i].zom = LoadTexture("sprites/zom3.png");
        zombie[i].pos.x = GetScreenWidth() / 2.0f;
        zombie[i].pos.y = (GetScreenHeight() / 2.0f) - 250.0f;
    }
    for (i = 9; i < 12; i++)
    {
        zombie[i].zom = LoadTexture("sprites/zom4.png");
        zombie[i].pos.x = GetScreenWidth() / 2.0f;
        zombie[i].pos.y = (GetScreenHeight() / 2.0f) - 250.0f;
    }
    init_zombies(zombie, 12, map);

    // Loop principal
    while (WindowShouldClose() == false && band.main != 6)
    {

        if (band.nivel == 0)
        {
            menu_principal(&jugador.pos, &band, green, flecha, back_menu);
        }
        else
        {
            if (band.nivel >= 1)
            {
                switch (band.nivel)
                {
                case 1:
                    // Falta battalla
                    nivel1(&band, &jugador.pos, green, jugador.player, map, zombie);
                    break;
                case 2:
                    nivel2();
                    break;
                case 3:
                    nivel3();
                    break;
                case 4:
                    nivel4();
                    break;
                case 5:
                    nivel5();
                    break;
                case 7:
                    refugio(&band, &jugador.pos, green, jugador.player, fondoRefugio);
                    break;
                default:
                    break;
                }
            }
        }

        EndDrawing();
    }

    // Descarga de texturas
    UnloadTexture(jugador.player);
    UnloadTexture(flecha);
    UnloadTexture(back_menu);
    UnloadTexture(map.fondo);
    for (i = 0; i < 12; i++)
    {
        UnloadTexture(zombie[i].zom);
    }
    UnloadTexture(fondoRefugio);

    CloseWindow();
    return 0;
}
//*********************************************************************
void menu_principal(Vector2 *pos, sTband *band, Color green, Texture2D flecha, Texture2D background)
{
    float anchoFlecha = (float)GetScreenWidth() * 0.03f;
    float altoFlecha = (float)GetScreenHeight() * 0.06f;

    // Movimiento de seleccionador
    mov_flechita(pos, band);

    // Inicia el dibujado
    BeginDrawing();
    ClearBackground(green);

    Rectangle sourceRec = {0.0f, 0.0f, (float)flecha.width, (float)flecha.height};

    Rectangle destRec = {pos->x, pos->y, anchoFlecha, altoFlecha};

    // 1. Origen: Tomamos la imagen de fondo completa
    Rectangle sourceBackground = {0.0f, 0.0f, (float)background.width, (float)background.height};

    // 2. Destino: Forzamos que se dibuje desde la esquina (0,0) con un tamaño de 800x800
    Rectangle destBackground = {0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight()};

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
void refugio(sTband *band, Vector2 *pos, Color green, Texture2D player, Texture2D fondoRefugio)
{
    float w = (float)GetScreenWidth();
    float h = (float)GetScreenHeight();
    float anchoJ = 50.0f;
    float altoJ = 80.0f;

    // 1. Movimiento libre del jugador (pasamos NULL y 0 paredes)
    mov_jugador_colision(pos, NULL, 0);

    // 2. Zona de salida en la parte inferior para regresar a la calle (Nivel 1)
    Rectangle salidaRefugio = {w * 0.35f, h * 0.96f, w * 0.30f, h * 0.04f};
    Rectangle destRec = {pos->x, pos->y, anchoJ, altoJ};

    if (CheckCollisionRecs(destRec, salidaRefugio))
    {
        band->nivel = 1;
        pos->x = w * 0.48f; // Aparece en la calle de arriba del cruce
        pos->y = h * 0.06f; // Un poco más abajo de la salida 0 para no rebotar
    }

    // 3. Dibujado del refugio
    BeginDrawing();
    ClearBackground(green);

    Rectangle sourceBg = {0.0f, 0.0f, (float)fondoRefugio.width, (float)fondoRefugio.height};
    Rectangle destBg = {0.0f, 0.0f, w, h};
    DrawTexturePro(fondoRefugio, sourceBg, destBg, (Vector2){0.0f, 0.0f}, 0.0f, WHITE);

    // Dibujar al jugador
    Rectangle sourceRec = {0.0f, 0.0f, (float)player.width, (float)player.height};
    DrawTexturePro(player, sourceRec, destRec, (Vector2){0.0f, 0.0f}, 0.0f, WHITE);

    // Texto opcional de zona segura
    DrawText("ZONA SEGURA - REFUGIO", 30, 30, 30, GREEN);

    // (Opcional) Ver el rectángulo verde de salida del refugio
    DrawRectangleLinesEx(salidaRefugio, 3.0f, GREEN);
}
//*********************************************************************
void nivel1(sTband *band, Vector2 *pos, Color green, Texture2D player, sTmapa map, sTenemy zombie[])
{
    float w = (float)GetScreenWidth();
    float h = (float)GetScreenHeight();

    // Movimientos de jugador y zombis
    mov_jugador_colision(pos, map.paredes, map.mParedes);
    for (int i = 0; i < 12; i++)
    {
        mov_zombie_colision(&zombie[i], 1.0f, map.paredes, map.mParedes);
    }

    // Dibujado
    BeginDrawing();
    ClearBackground(green);


    Rectangle sourceRec = {0.0f, 0.0f, (float)player.width, (float)player.height};

    float nuevoAncho = 50.0f;
    float nuevoAlto = 80.0f;
    Rectangle destRec = {pos->x, pos->y, nuevoAncho, nuevoAlto};

    Rectangle sourceBackground = {0.0f, 0.0f, (float)map.fondo.width, (float)map.fondo.height};
    Rectangle destBackground = {0.0f, 0.0f, w, h};
    Vector2 origen = {0.0f, 0.0f};

    // 1. PRIMERO se dibujan el fondo y el jugador
    DrawTexturePro(map.fondo, sourceBackground, destBackground, origen, 0.0f, WHITE);
    DrawTexturePro(player, sourceRec, destRec, origen, 0.0f, WHITE);

    // 2. Se dibujan los zombis encima del fondo
    for (int j = 0; j < 12; j++)
    {
        Rectangle bloque = {0.0f, 0.0f, (float)zombie[j].zom.width, (float)zombie[j].zom.height};
        Rectangle destinoRec = {zombie[j].pos.x, zombie[j].pos.y, nuevoAncho, nuevoAlto};

        if (CheckCollisionRecs(destRec, destinoRec))
        {
            band->nivel = 0;
            init_zombies(zombie, 12, map); // Reubica los zombis
        }

        DrawTexturePro(zombie[j].zom, bloque, destinoRec, origen, 0.0f, WHITE);
    }

    // Si toca la salida de arriba (índice 0), entra al refugio
    if (CheckCollisionRecs(destRec, map.salidas[0]))
    {
        band->nivel = 7;
        pos->x = w * 0.50f; // Centrado horizontalmente
        pos->y = h * 0.80f; // Aparece en la parte de abajo del refugio
    }

    // --- MODO DEPURACIÓN: Borra este bloque cuando ya estén calibradas ---
    for (int i = 0; i < 4; i++)
    {
        DrawRectangleLinesEx(map.paredes[i], 3.0f, RED);
    }
    for (int i = 0; i < 4; i++)
    {
        DrawRectangleLinesEx(map.salidas[i], 3.0f, GREEN);
    }
    // ---------------------------------------------------------------------
    DrawText(TextFormat("X: %.2f  Y: %.2f", (float)GetMouseX() / w, (float)GetMouseY() / h), 20, 20, 25, YELLOW);
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