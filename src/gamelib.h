// Equipo desarrollador - fundador
// Juego
// Viernes 07 de noviembre de 2026
// VERSIÓN 1.0
// ACTUALIZACIONES:
// 07-11-2026 -> Se creó la librería y se probaron funciones útiles.
// 20-11-2026 -> Se borraron las funciones y se optó por agregar sólo reutilizables.
//
#include <raylib.h>
#include <stdio.h>

// structs
enum armas
{
    cuchillo,
    pistola,
    escopeta,
    rifle
};

enum objetos
{
    botiquin,
    comida,
    cartuchos
};

typedef struct _banderas
{
    int main;
    int nivel;
    int batalla;
    int menu;
} sTband;

typedef struct _player
{
    int vida;
    int nivel;
    int arma;
    int inventario[4][4];
    Vector2 pos;
    Texture2D player;
} sTplayer;

typedef struct _enemy
{
    int vida;
    int ataque;
    int tipo;
    Texture2D zom;
} sTenemy;

// Prototipos
void mov_player(float *pX, float *pY);
void mov_jugador(Vector2 *pos);

void batalla();

// No hay main.

// Desarrollo
void mov_player(float *pX, float *pY)
{
    if (IsKeyDown(KEY_RIGHT))
    {
        *pX += 3.0f;
    }
    else
    {
        if (IsKeyDown(KEY_LEFT))
        {
            *pX -= 3.0f;
        }
        else
        {
            if (IsKeyDown(KEY_UP))
            {
                *pY -= 3.0f;
            }
            else
            {
                if (IsKeyDown(KEY_DOWN))
                {
                    *pY += 3.0f;
                }
            }
        }
    }
}
//*********************************************************
void batalla()
{
}
//*********************************************************
void mov_jugador(Vector2 *pos)
{
    if (IsKeyDown(KEY_RIGHT))
    {
        pos->x += 3.0f;
    }
    else
    {
        if (IsKeyDown(KEY_LEFT))
        {
            pos->x -= 3.0f;
        }
        else
        {
            if (IsKeyDown(KEY_UP))
            {
                pos->y -= 3.0f;
            }
            else
            {
                if (IsKeyDown(KEY_DOWN))
                {
                    pos->y += 3.0f;
                }
            }
        }
    }
}
//*********************************************************
