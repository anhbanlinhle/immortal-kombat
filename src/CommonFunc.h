
#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <cstring>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

// screen
    const int FRAME_PER_SEC = 20;
    const int SCREEN_WIDTH = 576;
    const int SCREEN_HEIGHT = 288;
    const int SCREEN_BPP = 32;
    
    const int COLOR_KEY_R = 167; 
    const int COLOR_KEY_G = 175;
    const int COLOR_KEY_B = 180;
    
    const int RENDER_DRAW_COLOR = 0xff;



#define BLANK_TILE 0
#define TILE_SIZE 8

#define MAX_MAP_X SCREEN_WIDTH/TILE_SIZE
#define MAX_MAP_Y SCREEN_HEIGHT/TILE_SIZE

struct Input{
    int left;
    int right;

    int jump;
    int down;
    
    int attack_left;
    int attack_right;

    int up_left;
    int up_right;
    
    int down_left;
    int down_right;
};

struct Map{
    int start_x;
    int start_y;

    int max_x;
    int max_y;

    int tile[MAX_MAP_Y][MAX_MAP_X];
    char* file_name;
};

#endif