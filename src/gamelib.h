// Equipo desarrollador - fundador
// Juego
// Viernes 07 de noviembre de 2026
// VERSIÓN 1.0
// ACTUALIZACIONES:
// 07-11-2026 -> Se creó la librería y se probaron funciones útiles.
// 20-11-2026 -> Se borraron las funciones y se optó por agregar sólo reutilizables.
// 25-11-2026 -> Se agregaron estructuras, funciones de colisión y movimiento.

#include <raylib.h>
#include <stdio.h>

// structs
enum armas
{
    cuchillo,
    magnum,
    escopeta1,
    escopeta2,
    tmp,
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

typedef struct _frames
{
    int frame_actual;
    int total_frames;
    float velAnim;
    Rectangle frameRec;
    float timer;
} sTframes;

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
    float timer;
    Vector2 pos;
    Vector2 dir;
    Texture2D zom;
    sTframes anim;
} sTenemy;

typedef struct _mapa
{
    Texture2D fondo;
    Rectangle paredes[4];
    int mParedes;
    Rectangle salidas[4];
    int mSalidas;
    int destSalida[4];
} sTmapa;

// PROTOTIPOS

// Jugador
void mov_jugador(Vector2 *pos);
bool chocaConParedes(Rectangle hitbox, Rectangle paredes[], int totalParedes);
void mov_jugador_colision(Vector2 *pos, Rectangle paredes[], int totalParedes);
// Menú
void mov_flechita(Vector2 *pos, sTband *band);
void batalla();
// Zombies
void init_zombies(sTenemy zombie[], int total, sTmapa map);
void mov_zombie_colision(sTenemy *zombie, float velocidad, Rectangle paredes[], int totalParedes);
// Animaciones generales
void animacion(sTenemy *z);

// No hay main.

// DESARROLLO DE FUNCIONES
//*********************************************************
// Funciones para jugador principal
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
bool chocaConParedes(Rectangle hitbox, Rectangle paredes[], int totalParedes)
{
    for (int i = 0; i < totalParedes; i++)
    {
        if (CheckCollisionRecs(hitbox, paredes[i]))
        {
            return true;
        }
    }
    return false;
}
//*********************************************************
void mov_jugador_colision(Vector2 *pos, Rectangle paredes[], int totalParedes)
{
    float ancho = 50.0f;
    float alto = 80.0f;
    float w = (float)GetScreenWidth();
    float h = (float)GetScreenHeight();
    float prevX = pos->x;
    float prevY = pos->y;

    mov_jugador(pos);

    // Se acomoda la hitbox del personaje para que esté en sus piernas.
    Rectangle hitboxX = {pos->x + 10.0f, pos->y + (alto * 0.5f), ancho - 20.0f, alto * 0.5f};
    // Se acomoda la hitbox en la cabeza del jugador.
    Rectangle hitboxY = {pos->x + 10.0f, pos->y + (alto * 0.5f), ancho - 20.0f, alto * 0.5f};

    // 1. Movimiento en Eje X
    if (chocaConParedes(hitboxX, paredes, totalParedes))
    {
        pos->x = prevX; // Cancela el movimiento en X si choca, regresando a su estado previo.
    }
    else
    {
        if (pos->x > w - ancho)
        {
            pos->x = prevX;
        }
        else
        {
            if (pos->x < 0)
            {
                pos->x = prevX;
            }
        }
    }

    // 2. Movimiento en Eje Y
    if (chocaConParedes(hitboxY, paredes, totalParedes))
    {
        pos->y = prevY; // Cancela el movimiento en Y si choca, regresando a su estado previo.
    }
    else
    {
        if (pos->y > h - alto)
        {
            pos->y = prevY;
        }
        else
        {
            if (pos->y < 0)
            {
                pos->y = prevY;
            }
        }
    }
}

//*********************************************************
// Funciones de menú
//*********************************************************
void mov_flechita(Vector2 *pos, sTband *band)
{
    float anchoPantalla = (float)GetScreenWidth();
    float altoPantalla = (float)GetScreenHeight();

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
        pos->x = anchoPantalla * 0.74f;
        pos->y = altoPantalla * 0.676f;
    }
    else
    {
        if (band->menu == 2)
        {
            pos->x = anchoPantalla * 0.82f;
            pos->y = altoPantalla * 0.775f;
        }
        else
        {
            pos->x = anchoPantalla * 0.78f;
            pos->y = altoPantalla * 0.870f;
        }
    }

    if (IsKeyPressed(KEY_ENTER))
    {
        if (band->menu == 1)
        {
            band->nivel = 1;
            pos->x = GetScreenWidth() / 2.0f;
            pos->y = GetScreenHeight() / 2.0f;
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
}
//*********************************************************
void batalla()
{
}

//*********************************************************
// Funciones para zombies
//*********************************************************
void init_zombies(sTenemy zombie[], int total, sTmapa map)
{
    float w = (float)GetScreenWidth();
    float h = (float)GetScreenHeight();
    float ancho = 50.0f;
    float alto = 80.0f;

    // Zona segura en el centro (donde aparece el jugador en mov_flechita)
    Rectangle zonaJugador = {(w / 2.0f) - 140.0f, (h / 2.0f) - 140.0f, 330.0f, 360.0f};

    for (int i = 0; i < total; i++)
    {
        zombie[i].timer = (float)GetRandomValue(0, 15) / 10.0f; // Desfase inicial para que no giren todos al mismo tiempo
        zombie[i].dir.x = (float)GetRandomValue(-1, 1);
        zombie[i].dir.y = (float)GetRandomValue(-1, 1);

        bool valida = false;
        while (!valida)
        {
            // Repartir entre calle vertical (pares) y calle horizontal (impares)
            if (i % 2 == 0)
            {
                zombie[i].pos.x = (float)GetRandomValue((int)(w * 0.37f), (int)(w * 0.58f));
                zombie[i].pos.y = (float)GetRandomValue((int)(h * 0.06f), (int)(h * 0.88f));
            }
            else
            {
                zombie[i].pos.x = (float)GetRandomValue((int)(w * 0.04f), (int)(w * 0.90f));
                zombie[i].pos.y = (float)GetRandomValue((int)(h * 0.39f), (int)(h * 0.48f));
            }

            Rectangle rectZom = {zombie[i].pos.x, zombie[i].pos.y, ancho, alto};
            valida = true;

            // 1. Verificar que esté lejos del personaje principal
            if (CheckCollisionRecs(rectZom, zonaJugador))
            {
                valida = false;
            }

            // 2. Verificar que no toque ninguna pared
            if (valida && chocaConParedes(rectZom, map.paredes, map.mParedes))
            {
                valida = false;
            }

            // 3. Verificar que no aparezca encima de otro zombi ya colocado
            for (int j = 0; j < i && valida; j++)
            {
                Rectangle otroZom = {zombie[j].pos.x, zombie[j].pos.y, ancho, alto};
                if (CheckCollisionRecs(rectZom, otroZom))
                {
                    valida = false;
                }
            }
        }
    }
}
//*********************************************************
void mov_zombie_colision(sTenemy *zombie, float velocidad, Rectangle paredes[], int totalParedes)
{
    zombie->timer += GetFrameTime();

    float ancho = 50.0f;
    float alto = 80.0f;
    float w = (float)GetScreenWidth();
    float h = (float)GetScreenHeight();

    // Mover en X y rebotar si toca pared o borde
    float prevX = zombie->pos.x;
    zombie->pos.x += zombie->dir.x * velocidad;
    Rectangle hitboxX = {zombie->pos.x + 10.0f, zombie->pos.y + (alto * 0.5f), ancho - 20.0f, alto * 0.5f};

    // Mover en Y y rebotar si toca pared o borde
    float prevY = zombie->pos.y;
    zombie->pos.y += zombie->dir.y * velocidad;
    Rectangle hitboxY = {zombie->pos.x + 10.0f, zombie->pos.y + (alto * 0.5f), ancho - 20.0f, alto * 0.5f};

    // Tiempo del zombie
    if (zombie->timer >= 1.5f)
    {
        zombie->dir.x = (float)GetRandomValue(-1, 1);
        zombie->dir.y = (float)GetRandomValue(-1, 1);

        // Evita que se quede completamente detenido
        if (zombie->dir.x == 0.0f && zombie->dir.y == 0.0f)
        {
            zombie->dir.x = 1.0f;
        }
        zombie->timer = 0.0f;
    }

    // Choque en X
    if (chocaConParedes(hitboxX, paredes, totalParedes))
    {
        zombie->pos.x = prevX;
        zombie->dir.x *= -1.0f;
    }
    else
    {
        if (zombie->pos.x > w - ancho)
        {
            zombie->pos.x = prevX;
            zombie->dir.x *= -1.0f;
        }
        else
        {
            if (zombie->pos.x < 0)
            {
                zombie->pos.x = prevX;
                zombie->dir.x *= -1.0f;
            }
        }
    }

    // Choque en Y
    if (chocaConParedes(hitboxY, paredes, totalParedes))
    {
        zombie->pos.y = prevY;
        zombie->dir.y *= -1.0f;
    }
    else
    {
        if (zombie->pos.y > h - alto)
        {
            zombie->pos.y = prevY;
            zombie->dir.y *= -1.0f;
        }
        else
        {
            if (zombie->pos.y < 0)
            {
                zombie->pos.y = prevY;
                zombie->dir.y *= -1.0f;
            }
        }
    }
}
//*********************************************************
void animacion(sTframes *z)
{
    z->timer += GetFrameTime();

    if (z->timer >= z->velAnim)
    {
        z->timer = 0.0f;
        z->frame_actual++;

        if (z->frame_actual >= z->total_frames)
        {
            // Hace el bucle de la animación.
            z->frame_actual = 0;
        }

        // Actualiza la posición X del rectángulo de recorte.
        z->frameRec.x = (float)z->frame_actual * z->frameRec.width;
    }

}