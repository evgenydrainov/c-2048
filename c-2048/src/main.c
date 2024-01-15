#include <SDL.h>
#include <SDL_image.h>

#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "font.h"

#define GAME_W 640
#define GAME_H 480

#define FONT_SIZE 8
#define FONT_W 16

#define BOARD_SIZE 4
int board[BOARD_SIZE * BOARD_SIZE];
int board_prev_x[BOARD_SIZE * BOARD_SIZE];
int board_prev_y[BOARD_SIZE * BOARD_SIZE];
int board_new[BOARD_SIZE * BOARD_SIZE];
int board_just_merged[BOARD_SIZE * BOARD_SIZE];
float animation;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* tex_font;

void spawn_cell(int val, int count) {
	while (count--) {
		int pos = rand() % (BOARD_SIZE * BOARD_SIZE);

		if (board[pos] == 0) {
			board[pos] = val;
			board_new[pos] = 1;
		} else {
			int i = BOARD_SIZE * BOARD_SIZE;
			while (i--) {
				pos++;
				pos %= BOARD_SIZE * BOARD_SIZE;

				if (board[pos] == 0) {
					board[pos] = val;
					board_new[pos] = 1;
					break;
				}
			}
		}
	}
}

void go_down(void) {
	for (int y = 0; y < BOARD_SIZE; y++) {
		for (int x = 0; x < BOARD_SIZE; x++) {
			board_prev_x[x + y * BOARD_SIZE] = x;
			board_prev_y[x + y * BOARD_SIZE] = y;
		}
	}

	animation = 0.0f;
	int any_moved = 0;

	memset(board_new, 0, sizeof board_new);
	memset(board_just_merged, 0, sizeof board_just_merged);

	for (int y = BOARD_SIZE - 1; y >= 0; y--) {
		for (int x = 0; x < BOARD_SIZE; x++) {

			if (board[x + y * BOARD_SIZE] != 0) {

				int val = board[x + y * BOARD_SIZE];
				board[x + y * BOARD_SIZE] = 0;

				int summed = 0;

				int yy = y + 1;
				for (; yy < BOARD_SIZE; yy++) {
					if (board[x + yy * BOARD_SIZE] != 0) {
						if (board[x + yy * BOARD_SIZE] == val && !board_just_merged[x + yy * BOARD_SIZE]) {

							board[x + yy * BOARD_SIZE] += val;
							board_prev_x[x + yy * BOARD_SIZE] = x;
							board_prev_y[x + yy * BOARD_SIZE] = y;
							board_just_merged[x + yy * BOARD_SIZE] = 1;
							any_moved = 1;

							summed = 1;
							break;
						}

						break;
					}
				}

				if (!summed) {
					yy--;

					board[x + yy * BOARD_SIZE] = val;
					board_prev_x[x + yy * BOARD_SIZE] = x;
					board_prev_y[x + yy * BOARD_SIZE] = y;
					if (yy != y) any_moved = 1;
				}
			}

		}
	}

	if (any_moved) {
		spawn_cell(2, 1);
	}
}

void go_up(void) {
	for (int y = 0; y < BOARD_SIZE; y++) {
		for (int x = 0; x < BOARD_SIZE; x++) {
			board_prev_x[x + y * BOARD_SIZE] = x;
			board_prev_y[x + y * BOARD_SIZE] = y;
		}
	}

	animation = 0.0f;
	int any_moved = 0;

	memset(board_new, 0, sizeof board_new);
	memset(board_just_merged, 0, sizeof board_just_merged);

	for (int y = 0; y < BOARD_SIZE; y++) {
		for (int x = 0; x < BOARD_SIZE; x++) {

			if (board[x + y * BOARD_SIZE] != 0) {

				int val = board[x + y * BOARD_SIZE];
				board[x + y * BOARD_SIZE] = 0;

				int summed = 0;

				int yy = y - 1;
				for (; yy >= 0; yy--) {
					if (board[x + yy * BOARD_SIZE] != 0) {
						if (board[x + yy * BOARD_SIZE] == val && !board_just_merged[x + yy * BOARD_SIZE]) {

							board[x + yy * BOARD_SIZE] += val;
							board_prev_x[x + yy * BOARD_SIZE] = x;
							board_prev_y[x + yy * BOARD_SIZE] = y;
							board_just_merged[x + yy * BOARD_SIZE] = 1;
							any_moved = 1;

							summed = 1;
							break;
						}

						break;
					}
				}

				if (!summed) {
					yy++;

					board[x + yy * BOARD_SIZE] = val;
					board_prev_x[x + yy * BOARD_SIZE] = x;
					board_prev_y[x + yy * BOARD_SIZE] = y;
					if (yy != y) any_moved = 1;
				}
			}

		}
	}

	if (any_moved) {
		spawn_cell(2, 1);
	}
}

void go_left(void) {
	for (int y = 0; y < BOARD_SIZE; y++) {
		for (int x = 0; x < BOARD_SIZE; x++) {
			board_prev_x[x + y * BOARD_SIZE] = x;
			board_prev_y[x + y * BOARD_SIZE] = y;
		}
	}

	animation = 0.0f;
	int any_moved = 0;

	memset(board_new, 0, sizeof board_new);
	memset(board_just_merged, 0, sizeof board_just_merged);

	for (int x = 0; x < BOARD_SIZE; x++) {
		for (int y = 0; y < BOARD_SIZE; y++) {

			if (board[x + y * BOARD_SIZE] != 0) {

				int val = board[x + y * BOARD_SIZE];
				board[x + y * BOARD_SIZE] = 0;

				int summed = 0;

				int xx = x - 1;
				for (; xx >= 0; xx--) {
					if (board[xx + y * BOARD_SIZE] != 0) {
						if (board[xx + y * BOARD_SIZE] == val && !board_just_merged[xx + y * BOARD_SIZE]) {

							board[xx + y * BOARD_SIZE] += val;
							board_prev_x[xx + y * BOARD_SIZE] = x;
							board_prev_y[xx + y * BOARD_SIZE] = y;
							board_just_merged[xx + y * BOARD_SIZE] = 1;
							any_moved = 1;

							summed = 1;
							break;
						}

						break;
					}
				}

				if (!summed) {
					xx++;

					board[xx + y * BOARD_SIZE] = val;
					board_prev_x[xx + y * BOARD_SIZE] = x;
					board_prev_y[xx + y * BOARD_SIZE] = y;
					if (xx != x) any_moved = 1;
				}
			}

		}
	}

	if (any_moved) {
		spawn_cell(2, 1);
	}
}

void go_right(void) {
	for (int y = 0; y < BOARD_SIZE; y++) {
		for (int x = 0; x < BOARD_SIZE; x++) {
			board_prev_x[x + y * BOARD_SIZE] = x;
			board_prev_y[x + y * BOARD_SIZE] = y;
		}
	}

	animation = 0.0f;
	int any_moved = 0;

	memset(board_new, 0, sizeof board_new);
	memset(board_just_merged, 0, sizeof board_just_merged);

	for (int x = BOARD_SIZE - 1; x >= 0; x--) {
		for (int y = 0; y < BOARD_SIZE; y++) {

			if (board[x + y * BOARD_SIZE] != 0) {

				int val = board[x + y * BOARD_SIZE];
				board[x + y * BOARD_SIZE] = 0;

				int summed = 0;

				int xx = x + 1;
				for (; xx < BOARD_SIZE; xx++) {
					if (board[xx + y * BOARD_SIZE] != 0) {
						if (board[xx + y * BOARD_SIZE] == val && !board_just_merged[xx + y * BOARD_SIZE]) {

							board[xx + y * BOARD_SIZE] += val;
							board_prev_x[xx + y * BOARD_SIZE] = x;
							board_prev_y[xx + y * BOARD_SIZE] = y;
							board_just_merged[xx + y * BOARD_SIZE] = 1;
							any_moved = 1;

							summed = 1;
							break;
						}

						break;
					}
				}

				if (!summed) {
					xx--;

					board[xx + y * BOARD_SIZE] = val;
					board_prev_x[xx + y * BOARD_SIZE] = x;
					board_prev_y[xx + y * BOARD_SIZE] = y;
					if (xx != x) any_moved = 1;
				}
			}

		}
	}

	if (any_moved) {
		spawn_cell(2, 1);
	}
}

void draw_text(int x, int y, char* buf, SDL_Color col) {
	for (char* ch = buf; *ch != 0; ch++) {
		char c = *ch;

		int scale = 4;

		if (c != ' ') {
			SDL_Rect src = {(c % FONT_W) * FONT_SIZE, (c / FONT_W) * FONT_SIZE, FONT_SIZE, FONT_SIZE};
			SDL_Rect dest = {x, y, FONT_SIZE * scale, FONT_SIZE * scale};

			SDL_SetTextureColorMod(tex_font, col.r, col.g, col.b);
			SDL_SetTextureAlphaMod(tex_font, col.a);
			SDL_SetTextureBlendMode(tex_font, SDL_BLENDMODE_BLEND);

			SDL_RenderCopy(renderer, tex_font, &src, &dest);
		}

		x += FONT_SIZE * scale;
	}
}

void draw_text_centered(int x, int y, char* buf, SDL_Color col) {
	int scale = 4;

	draw_text(x - strlen(buf) * FONT_SIZE * scale / 2, y - FONT_SIZE * scale / 2, buf, col);
}

int lerp(int a, int b, float f) {
	return a + (b - a) * f;
}

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);

	window = SDL_CreateWindow("c-2048",
							  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
							  GAME_W, GAME_H,
							  SDL_WINDOW_RESIZABLE);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_RenderSetLogicalSize(renderer, GAME_W, GAME_H);

	// tex_font = IMG_LoadTexture(renderer, "font.png");
	tex_font = IMG_LoadTexture_RW(renderer, SDL_RWFromConstMem(FONT_IMAGE_DATA, sizeof FONT_IMAGE_DATA), 1);

	memset(board, 0, sizeof board);

	for (int y = 0; y < BOARD_SIZE; y++) {
		for (int x = 0; x < BOARD_SIZE; x++) {
			board_prev_x[x + y * BOARD_SIZE] = x;
			board_prev_y[x + y * BOARD_SIZE] = y;
		}
	}

	srand(time(NULL));

	animation = 1.0f;
	memset(board_new, 0, sizeof board_new);

	// {
	// 	spawn_cell(2, 2);
	// }

	// {
	// 	board[0 + 0 * BOARD_SIZE] = 2;
	// 	board[0 + 2 * BOARD_SIZE] = 2;
	// }

	{
		board[0 + 0 * BOARD_SIZE] = 4;
		board[0 + 1 * BOARD_SIZE] = 2;
		board[0 + 2 * BOARD_SIZE] = 2;
	}

	int quit = 0;
	while (!quit) {
		SDL_Event ev;
		while (SDL_PollEvent(&ev)) {
			switch (ev.type) {
				case SDL_QUIT: quit = 1; break;

				case SDL_KEYDOWN: {
					int scancode = ev.key.keysym.scancode;

					if (scancode == SDL_SCANCODE_DOWN) {
						go_down();
					} else if (scancode == SDL_SCANCODE_UP) {
						go_up();
					} else if (scancode == SDL_SCANCODE_LEFT) {
						go_left();
					} else if (scancode == SDL_SCANCODE_RIGHT) {
						go_right();
					}
				}
			}
		}

		animation += 0.05f;
		if (animation > 1.0f) animation = 1.0f;

		SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
		SDL_RenderClear(renderer);

		int cell_w = GAME_W / BOARD_SIZE;
		int cell_h = GAME_H / BOARD_SIZE;

		for (int y = 0; y < BOARD_SIZE; y++) {
			for (int x = 0; x < BOARD_SIZE; x++) {
				int val = board[x + y * BOARD_SIZE];

				float anim1 = 2.0f * animation;
				float anim2 = 2.0f * (animation - 0.5f);

				if (anim1 > 1.0f) anim1 = 1.0f;
				if (anim2 < 0.0f) anim2 = 0.0f;

				int cell_x = lerp(board_prev_x[x + y * BOARD_SIZE] * cell_w, x * cell_w, anim1);
				int cell_y = lerp(board_prev_y[x + y * BOARD_SIZE] * cell_h, y * cell_h, anim1);

				int alpha = 255;
				if (board_new[x + y * BOARD_SIZE]) {
					alpha = lerp(0, 255, anim2);
				}

				if (val != 0) {
					{
						SDL_Rect r = {cell_x + 5, cell_y + 5, cell_w - 10, cell_h - 10};
						SDL_SetRenderDrawColor(renderer, 50, 50, 50, alpha);
						SDL_RenderFillRect(renderer, &r);
					}

					{
						char buf[10];
						SDL_snprintf(buf, sizeof buf, "%d", val);
						draw_text_centered(cell_x + cell_w / 2, cell_y + cell_h / 2, buf, (SDL_Color) {255, 255, 255, alpha});
					}
				}
			}
		}

		SDL_RenderPresent(renderer);

		// SDL_Delay(100);
	}

	SDL_DestroyTexture(tex_font);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	IMG_Quit();
	SDL_Quit();

	return 0;
}
