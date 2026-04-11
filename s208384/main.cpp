#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

extern "C"
{
#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
}

// glowna konfiguracja
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 680
#define LEVEL_WIDTH 2000
#define PLAYER_SPEED 800.0
#define MAX_ENEMIES 6

// ustawienia sterowania
#define KEY_UP SDL_SCANCODE_W
#define KEY_DOWN SDL_SCANCODE_S
#define KEY_LEFT SDL_SCANCODE_A
#define KEY_RIGHT SDL_SCANCODE_D
#define KEY_ATTACK_FAST SDL_SCANCODE_I
#define KEY_ATTACK_HEAVY SDL_SCANCODE_P
#define KEY_EXIT SDL_SCANCODE_ESCAPE
#define KEY_RESTART SDL_SCANCODE_N

// interfejs i mapa
#define UI_HEIGHT 50
#define WALK_TOP_LIMIT 300
#define WALK_BOTTOM_LIMIT 620

enum GameState
{
	STATE_MENU,
	STATE_GAME,
	STATE_GAMEOVER
};

struct Entity
{
	double x, y;
	int w, h;
	int hp, max_hp;
	int type;
	bool active;
	double stun; // czas zablokowania ruchu
};

// zmienne globalne
Entity player;
Entity enemies[MAX_ENEMIES];
int gameState = STATE_MENU;
double worldTime = 0.0;
double cameraX = 0.0;
char nickname[32] = "Gracz";
char actionStatus[64] = "Gotowy";

// wynik i combo
int score = 0;
int comboMultiplier = 1;
double comboTimer = 0.0;

SDL_Surface *background = NULL;
SDL_Surface *charset = NULL;
SDL_Surface *mboxer = NULL;
SDL_Surface *qboxer = NULL;
SDL_Surface *sboxer = NULL;

// funkcje pomocnicze
void DrawString(SDL_Surface *screen, int x, int y, const char *text, SDL_Surface *charset)
{
	int px, py, c;
	SDL_Rect s, d;
	s.w = 8;
	s.h = 8;
	d.w = 8;
	d.h = 8;
	while (*text)
	{
		c = *text & 255;
		px = (c % 16) * 8;
		py = (c / 16) * 8;
		s.x = px;
		s.y = py;
		d.x = x;
		d.y = y;
		SDL_BlitSurface(charset, &s, screen, &d);
		x += 8;
		text++;
	}
}

void DrawSurface(SDL_Surface *screen, SDL_Surface *sprite, int x, int y)
{
	SDL_Rect dest;
	dest.x = x - sprite->w / 2;
	dest.y = y - sprite->h / 2;
	dest.w = sprite->w;
	dest.h = sprite->h;
	SDL_BlitSurface(sprite, NULL, screen, &dest);
}

void DrawRectangle(SDL_Surface *screen, int x, int y, int w, int h, Uint32 color)
{
	SDL_Rect r = {x, y, w, h};
	SDL_FillRect(screen, &r, color);
}

// logika gry
void InitGame()
{
	worldTime = 0.0;
	cameraX = 0.0;
	score = 0;
	comboMultiplier = 1;
	strcpy(actionStatus, "Gotowy");

	player.x = 100;
	player.y = 450;
	player.w = 40;
	player.h = 60;
	player.hp = 100;
	player.max_hp = 100;
	player.active = true;
	player.stun = 0;

	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		enemies[i].active = true;
		if (i % 2 == 0)
		{
			enemies[i].type = 1; // szybki
			enemies[i].w = 40;
			enemies[i].h = 60;
			enemies[i].hp = 40;
			enemies[i].max_hp = 40;
		}
		else
		{
			enemies[i].type = 2; // silny
			enemies[i].w = 50;
			enemies[i].h = 70;
			enemies[i].hp = 100;
			enemies[i].max_hp = 100;
		}
		enemies[i].stun = 0;
		enemies[i].x = 600 + (rand() % (LEVEL_WIDTH - 700));
		enemies[i].y = WALK_TOP_LIMIT + 10 + (rand() % (WALK_BOTTOM_LIMIT - WALK_TOP_LIMIT - 20));
	}
}

void UpdateGame(double delta)
{
	const Uint8 *state = SDL_GetKeyboardState(NULL);

	// licznik combo
	if (comboTimer > 0)
		comboTimer -= delta;
	else
		comboMultiplier = 1;

	// obsluga gracza
	if (player.stun > 0)
	{
		player.stun -= delta;
		if (player.stun <= 0)
			strcpy(actionStatus, "Gotowy");
	}
	else
	{
		// ataki
		bool attacked = false;
		int damage = 0;
		double attackRangeX = 0;
		double attackRangeY = 0;
		double attackDuration = 0;

		// szybki atak
		if (state[KEY_ATTACK_FAST])
		{
			attacked = true;
			damage = 10;
			attackRangeX = 50;
			attackRangeY = 20;
			attackDuration = 0.2;
			strcpy(actionStatus, "SZYBKI (I)");
			player.stun = attackDuration;
		}
		// silny atak
		else if (state[KEY_ATTACK_HEAVY])
		{
			attacked = true;
			damage = 30;
			attackRangeX = 90;
			attackRangeY = 40;
			attackDuration = 0.6;
			strcpy(actionStatus, "SILNY (P)");
			player.stun = attackDuration;
		}

		// kolizja ataku
		if (attacked)
		{
			SDL_Rect attackBox = {
				(int)player.x + 20, (int)player.y - (int)attackRangeY / 2,
				(int)attackRangeX, (int)attackRangeY};

			for (int i = 0; i < MAX_ENEMIES; i++)
			{
				if (!enemies[i].active)
					continue;

				// sprawdzanie trafienia
				if (attackBox.x < enemies[i].x + enemies[i].w &&
					attackBox.x + attackBox.w > enemies[i].x &&
					attackBox.y < enemies[i].y + enemies[i].h &&
					attackBox.y + attackBox.h > enemies[i].y)
				{

					enemies[i].hp -= damage;
					enemies[i].stun = 0.5;
					enemies[i].x += 30;

					// dodawanie punktow
					score += 10 * comboMultiplier;
					comboMultiplier++;
					comboTimer = 2.0;

					if (enemies[i].hp <= 0)
					{
						enemies[i].active = false;
						score += 100;
					}
				}
			}
		}

		// poruszanie sie
		if (player.stun <= 0)
		{
			if (state[KEY_UP] && player.y > WALK_TOP_LIMIT)
				player.y -= PLAYER_SPEED * delta;
			if (state[KEY_DOWN] && player.y < WALK_BOTTOM_LIMIT)
				player.y += PLAYER_SPEED * delta;
			if (state[KEY_LEFT] && player.x > 0)
				player.x -= PLAYER_SPEED * delta;
			if (state[KEY_RIGHT] && player.x < LEVEL_WIDTH)
				player.x += PLAYER_SPEED * delta;
		}
	}

	// kamera
	cameraX = player.x - (SCREEN_WIDTH / 2);
	if (cameraX < 0)
		cameraX = 0;
	if (cameraX > LEVEL_WIDTH - SCREEN_WIDTH)
		cameraX = LEVEL_WIDTH - SCREEN_WIDTH;

	// logika wrogow
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		if (!enemies[i].active)
			continue;
		if (enemies[i].stun > 0)
		{
			enemies[i].stun -= delta;
			continue;
		}

		double dx = player.x - enemies[i].x;
		double dy = player.y - enemies[i].y;

		if (fabs(dx) < 800)
		{
			if (enemies[i].type == 1)
			{
				if (fabs(dx) > 35)
					enemies[i].x += (dx > 0 ? 120 : -120) * delta;
				if (fabs(dy) > 5)
					enemies[i].y += (dy > 0 ? 80 : -80) * delta;
			}
			else
			{
				if (fabs(dy) < 15)
					enemies[i].x += (dx > 0 ? 200 : -200) * delta;
				else
					enemies[i].y += (dy > 0 ? 60 : -60) * delta;
			}

			// kolizja z graczem
			if (player.x < enemies[i].x + enemies[i].w && player.x + player.w > enemies[i].x &&
				player.y < enemies[i].y + enemies[i].h && player.y + player.h > enemies[i].y)
			{

				player.hp -= 1;
				comboMultiplier = 1;
				player.x += (player.x < enemies[i].x ? -2 : 2);
				strcpy(actionStatus, "OBRYWA!");
				if (player.hp <= 0)
					gameState = STATE_GAMEOVER;
			}
		}
	}
}

void RenderGame(SDL_Surface *screen)
{
	// rysowanie tla
	if (background)
	{
		SDL_Rect srcRect = {(int)cameraX, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
		SDL_Rect destRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
		SDL_BlitSurface(background, &srcRect, screen, &destRect);
	}
	else
	{
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 100, 100, 255));
		DrawRectangle(screen, 0, WALK_TOP_LIMIT, SCREEN_WIDTH, SCREEN_HEIGHT - WALK_TOP_LIMIT, SDL_MapRGB(screen->format, 0, 150, 0));
	}

	int px = (int)player.x - (int)cameraX;

	// cien gracza
	DrawRectangle(screen, px + 5, (int)player.y + player.h - 4, player.w - 10, 4, SDL_MapRGB(screen->format, 0, 50, 0));

	// rysowanie gracza
	if (mboxer)
		DrawSurface(screen, mboxer, px + player.w / 2, (int)player.y + player.h / 2);
	else
		DrawRectangle(screen, px, (int)player.y, player.w, player.h, SDL_MapRGB(screen->format, 0, 0, 255));

	// rysowanie wrogow
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		if (!enemies[i].active)
			continue;
		int ex = (int)enemies[i].x - (int)cameraX;

		if (enemies[i].type == 1 && qboxer)
			DrawSurface(screen, qboxer, ex + enemies[i].w / 2, (int)enemies[i].y + enemies[i].h / 2);
		else if (enemies[i].type == 2 && sboxer)
			DrawSurface(screen, sboxer, ex + enemies[i].w / 2, (int)enemies[i].y + enemies[i].h / 2);
		else
		{
			Uint32 color = (enemies[i].type == 1) ? SDL_MapRGB(screen->format, 255, 0, 0) : SDL_MapRGB(screen->format, 255, 255, 0);
			if (enemies[i].stun > 0)
				color = SDL_MapRGB(screen->format, 255, 255, 255);
			DrawRectangle(screen, ex, (int)enemies[i].y, enemies[i].w, enemies[i].h, color);
		}

		DrawRectangle(screen, ex, (int)enemies[i].y - 8, enemies[i].w, 4, SDL_MapRGB(screen->format, 50, 0, 0));
		DrawRectangle(screen, ex, (int)enemies[i].y - 8, (int)((float)enemies[i].hp / enemies[i].max_hp * enemies[i].w), 4, SDL_MapRGB(screen->format, 0, 255, 0));
	}

	// interfejs
	DrawRectangle(screen, 0, 0, SCREEN_WIDTH, UI_HEIGHT, SDL_MapRGB(screen->format, 0, 0, 0));
	DrawRectangle(screen, 0, UI_HEIGHT - 2, SCREEN_WIDTH, 2, SDL_MapRGB(screen->format, 255, 255, 255));

	char buf[128];
	snprintf(buf, sizeof(buf), "GRACZ: %s", nickname);
	DrawString(screen, 10, 10, buf, charset);

	DrawString(screen, 10, 25, "HP:", charset);
	DrawRectangle(screen, 40, 25, 204, 10, SDL_MapRGB(screen->format, 50, 50, 50));
	DrawRectangle(screen, 42, 27, player.hp * 2, 6, SDL_MapRGB(screen->format, 255, 50, 50));

	// wynik i czas
	snprintf(buf, sizeof(buf), "PKT: %d (x%d)", score, comboMultiplier);
	DrawString(screen, 300, 10, buf, charset);
	snprintf(buf, sizeof(buf), "CZAS: %.1f", worldTime);
	DrawString(screen, 300, 25, buf, charset);

	// status akcji
	snprintf(buf, sizeof(buf), "AKCJA: %s", actionStatus);
	int textLen = strlen(buf) * 8;
	DrawString(screen, SCREEN_WIDTH - textLen - 10, 20, buf, charset);

	DrawString(screen, 10, SCREEN_HEIGHT - 15, "I - Szybki | P - Silny | N - Reset | ESC - Wyjscie Zrobione: 1,2,3,4, A, E", charset);
}

// glowna funkcja
int main(int argc, char **argv)
{
	srand(time(NULL));
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		return 1;

	SDL_Window *window = SDL_CreateWindow("Beat'em Up", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (!window)
		return 1;

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_Surface *screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	SDL_Texture *scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_ShowCursor(SDL_DISABLE);

	charset = SDL_LoadBMP("./cs8x8.bmp");
	if (charset)
		SDL_SetColorKey(charset, true, 0x000000);

	mboxer = SDL_LoadBMP("./mboxer.bmp");
	if (mboxer)
		SDL_SetColorKey(mboxer, true, 0xFFFFFF);
	qboxer = SDL_LoadBMP("./qboxer.bmp");
	if (qboxer)
		SDL_SetColorKey(qboxer, true, 0xFFFFFF);
	sboxer = SDL_LoadBMP("./sboxer.bmp");
	if (sboxer)
		SDL_SetColorKey(sboxer, true, 0xFFFFFF);
	background = SDL_LoadBMP("./background.bmp");

	InitGame();
	SDL_StartTextInput();

	int t1 = SDL_GetTicks();
	int quit = 0;
	SDL_Event event;

	while (!quit)
	{
		int t2 = SDL_GetTicks();
		double delta = (t2 - t1) * 0.001;
		t1 = t2;

		if (gameState == STATE_GAME)
		{
			worldTime += delta;
			UpdateGame(delta);
		}

		SDL_FillRect(screen, NULL, 0);

		if (gameState == STATE_MENU)
		{
			DrawString(screen, 320, 250, "BEAT'EM UP", charset);
			DrawString(screen, 300, 300, "ENTER - Start Gry", charset);
			char menuBuf[64];
			snprintf(menuBuf, sizeof(menuBuf), "Nick: %s_", nickname);
			DrawString(screen, 300, 350, menuBuf, charset);
		}
		else if (gameState == STATE_GAME)
			RenderGame(screen);
		else if (gameState == STATE_GAMEOVER)
		{
			DrawString(screen, 350, 300, "KONIEC GRY", charset);
			char scoreBuf[64];
			snprintf(scoreBuf, sizeof(scoreBuf), "Wynik: %d | Czas: %.2f", score, worldTime);
			DrawString(screen, 300, 330, scoreBuf, charset);
			DrawString(screen, 300, 400, "'N' - Nowa gra", charset);
		}

		SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
		SDL_RenderCopy(renderer, scrtex, NULL, NULL);
		SDL_RenderPresent(renderer);

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				quit = 1;
			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_ESCAPE)
					quit = 1;

				if (gameState == STATE_MENU)
				{
					if (event.key.keysym.sym == SDLK_RETURN)
						gameState = STATE_GAME;
					if (event.key.keysym.sym == SDLK_BACKSPACE && strlen(nickname) > 0)
						nickname[strlen(nickname) - 1] = 0;
				}
				else if (gameState == STATE_GAME)
				{
					if (event.key.keysym.sym == SDLK_n)
						InitGame();
				}
				else if (gameState == STATE_GAMEOVER)
				{
					if (event.key.keysym.sym == SDLK_n)
					{
						InitGame();
						gameState = STATE_GAME;
					}
				}
			}
			if (event.type == SDL_TEXTINPUT && gameState == STATE_MENU)
				if (strlen(nickname) < 20)
					strcat(nickname, event.text.text);
		}
	}

	SDL_FreeSurface(charset);
	SDL_FreeSurface(screen);
	if (background)
		SDL_FreeSurface(background);
	if (mboxer)
		SDL_FreeSurface(mboxer);
	if (qboxer)
		SDL_FreeSurface(qboxer);
	if (sboxer)
		SDL_FreeSurface(sboxer);

	SDL_DestroyTexture(scrtex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}