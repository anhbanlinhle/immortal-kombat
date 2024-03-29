// #include <iostream>
// #define SDL_MAIN_HANDLED

// #include <SDL2/SDL.h>
// #include <SDL2/SDL_image.h>
// #include <SDL2/SDL_mixer.h>
// #include <SDL2/SDL_ttf.h>
// #include <string>

// using namespace std;


// // colors
// namespace Colors{
//     const SDL_Color RED = {255, 0, 0, SDL_ALPHA_OPAQUE};
// }


// // graphics
// namespace Graphics{
//     struct Screen{
//         const int WIDTH = 1980/2;
//         const int HEIGHT = 720/2;
//         const int center_x = WIDTH/2;
//         const int center_y = HEIGHT/2;
//     };
// };

// // game object
// enum SquareState{
//     IDLE,
//     MOVING_UP,
//     MOVING_DOWN,
//     MOVING_LEFT,
//     MOVING_RIGHT,
// };

// struct Square{
//     int WIDTH, HEIGHT, x, y;
//     SquareState state;
//     int step;
// };


// // application
// struct App{
//     const int DEFAULT_STEP = 2;
//     SDL_Window* window;
//     SDL_Renderer* renderer;

//     Graphics::Screen screen;


//     Square square = {
//         64, 
//         64, 
//         screen.center_x, 
//         screen.center_y,
//         IDLE,
//         DEFAULT_STEP,
//     };
// } app;


// // sdl routines
// bool InitSDL(){
//     if(SDL_Init(SDL_INIT_EVERYTHING) > 0){
//         cout << "Error: " << SDL_GetError() << endl;
//         return 0;
//     }
//     return 1;
// }

// // graphics routines

// void ClearScreen(SDL_Renderer* renderer){
//     // SDL_SetRenderDrawColor(renderer, Colors::BLACK.r, Colors::BLACK.g, Colors::BLACK.b, Colors::BLACK.a);
//     SDL_RenderClear(renderer);
//     SDL_Surface* image;
//     image = IMG_Load("./src/images/background.jpeg");
//     SDL_Texture* background = SDL_CreateTextureFromSurface(app.renderer, image);
//     SDL_RenderCopy(app.renderer, background, NULL, NULL);
// }

// void DrawSquare(int x, int y){
//     SDL_Rect rect;
//     rect.x =  x - (app.square.WIDTH/2);
//     rect.y =  y - (app.square.HEIGHT/2);
//     rect.w =  app.square.WIDTH/2;
//     rect.h =  app.square.HEIGHT/2;

//     // define the green color on the renderer
//     // SDL_SetRenderDrawColor(app.renderer, Colors::GREEN.r, Colors::GREEN.g, Colors::GREEN.b, Colors::GREEN.a);

//     // define the red color on the renderer
//     SDL_SetRenderDrawColor(app.renderer, Colors::RED.r, Colors::RED.g, Colors::RED.b, Colors::RED.a);
//     // ask the renderer to fill rect with green color
//     SDL_RenderFillRect(app.renderer, &rect);
// }



// // application routines
// void ShutdownApplication(){
//     if(app.window != nullptr){
//         SDL_DestroyWindow(app.window);
//          app.window = nullptr;
//     }
    
//     if(app.renderer != nullptr){
//         SDL_DestroyRenderer(app.renderer);
//          app.renderer = nullptr;
//     }

//     SDL_Quit();
// }


// bool InitApplication(){
//     if(InitSDL() == 0){
//         ShutdownApplication();
//         return 0;
//     }    

//     app.window = SDL_CreateWindow(
//         "Immortal Combat",
//         SDL_WINDOWPOS_CENTERED,
//         SDL_WINDOWPOS_CENTERED,
//         app.screen.WIDTH,
//         app.screen.HEIGHT,
//         SDL_WINDOW_OPENGL
//     );

//     if(app.window == nullptr){
//         cout << "Unable to create the main window. Error: " << SDL_GetError() << endl;
//         ShutdownApplication();
//         return 0;
//     }

//     app.renderer = SDL_CreateRenderer(app.window, -1, SDL_RENDERER_PRESENTVSYNC);

//     return 1;
// }

// void SetState(SquareState new_state){
//     app.square.state = new_state;
// }

// void IncreaseSteps(){
//     app.square.step *= app.DEFAULT_STEP;
// }

// void DecreaseSteps(){
//     int new_step = app.square.step / app.DEFAULT_STEP;
//     if(new_step > app.DEFAULT_STEP)
//         app.square.step = new_step;
//     else
//         app.square.step = app.DEFAULT_STEP;
// }

// int main(int argc, char *argv[]){
//     if(InitApplication() == 0){
//         ShutdownApplication();
//         return EXIT_FAILURE;
//     }

//     // load background
//     // SDL_Surface* image;
//     // image = IMG_Load("./src/images/background.jpeg");
//     // SDL_Texture* background = SDL_CreateTextureFromSurface(app.renderer, image);



//     // draw loop
//     SDL_Event event;
//     bool running = 1;

//     while(running){
//         ClearScreen(app.renderer);

//         // check the square state
//         switch(app.square.state){
//             case MOVING_UP:{
//                 int new_y = app.square.y - app.square.step;
//                 if(new_y > app.square.HEIGHT/2)
//                     app.square.y -= app.square.step;
//                 else{
//                     app.square.y = app.square.HEIGHT/2;
//                     SetState(MOVING_DOWN);
//                 }
//                 break;
//             }
//             case MOVING_DOWN:{
//                 int new_y = app.square.y + app.square.step;
//                 if(new_y < app.screen.HEIGHT)
//                     app.square.y += app.square.step;
//                 else{
//                     app.square.y = app.screen.HEIGHT;
//                     SetState(MOVING_UP);
//                 }
//                 break;
//             }
//             case MOVING_LEFT:{
//                 int new_top_left = app.square.x - app.square.step - app.square.WIDTH/2;
//                 if(new_top_left > app.square.step)
//                     app.square.x -= app.square.step;
//                 else{
//                     app.square.x = app.square.WIDTH/2;
//                     SetState(MOVING_RIGHT);
//                 }
//                 break;
//             }
//             case MOVING_RIGHT:{
//                 int new_top_left = app.square.x + app.square.step;
//                 if(new_top_left <= app.screen.WIDTH)
//                     app.square.x += app.square.step;
//                 else
//                     SetState(MOVING_LEFT);
//                 break;
//             }
//         }

//         // check n process i/o event
//         if(SDL_PollEvent(&event)){
//             switch (event.type){
//                 case SDL_KEYDOWN:{
//                     running = event.key.keysym.scancode != SDL_SCANCODE_ESCAPE;
                    
//                     if(event.key.keysym.scancode == SDL_SCANCODE_UP){
//                         SetState(MOVING_UP);
//                     }

//                     if(event.key.keysym.scancode == SDL_SCANCODE_DOWN){
//                         SetState(MOVING_DOWN);
//                     }

//                     if(event.key.keysym.scancode == SDL_SCANCODE_LEFT){
//                         SetState(MOVING_LEFT);
//                     }

//                     if(event.key.keysym.scancode == SDL_SCANCODE_RIGHT){
//                         SetState(MOVING_RIGHT);
//                     }

//                     if(event.key.keysym.scancode == SDL_SCANCODE_SPACE){
//                         SetState(IDLE);
//                     }

//                     if(event.key.keysym.scancode == SDL_SCANCODE_PAGEUP){
//                         IncreaseSteps();
//                     }

//                     if(event.key.keysym.scancode == SDL_SCANCODE_PAGEDOWN){
//                         DecreaseSteps();
//                     }

//                     break;
//                 }
//                 case SDL_QUIT:{
//                     running = 0;
//                     break;
//                 }
//                 default: break;
//             }
//         }
//         // draw the new content on the renderer
//         DrawSquare(app.square.x, app.square.y);

//         // update the screen with content rendered
//         SDL_RenderPresent(app.renderer);
//     }

//     // SDL_DestroyTexture(background);
//     // SDL_FreeSurface(image);

//     ShutdownApplication();
//     return EXIT_SUCCESS;
// }



// Program seperate

#include "CommonFunc.h"
#include "BaseObject.h"
#include "game_map.h"
#include "PlayerObject.h"
#include "PlayerObjectTwo.h"
#include "Timer.h"
#include "TextObject.h"
#include "Geometric.h"
#include "CharOneHP.h"
#include "CharTwoHP.h"

BaseObject g_background;
TTF_Font* font_time = NULL;

// Init program
bool InitData();

// Load background
bool LoadBackground();

// Close application
void CloseApp();

// Check collision
bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);

// Check position
std::string CheckPosition(const SDL_Rect& objectA, const SDL_Rect& objectB);

// Check hit
std::string HitConfirm(std::string HitState, std::string Position);

int main(int argc, char* argv[]){

    if(InitData() == false)
        return -1;
    if(LoadBackground() == false)
        return -1;

    GameMap game_map;
    game_map.LoadMap((char*)"./map/map01.dat");
    game_map.LoadTiles(g_screen);

    // Spawn player one
    PlayerObject p_player;
    p_player.LoadImg("./img/char_1/walk_right.png", g_screen);
    p_player.SetClips();
    int HitTaken_1 = 0;
    int Lives_1 = 3;

    // Player one hp
    CharOneHP player_one_hp;
    player_one_hp.Init(g_screen);
    
   // Player one ava
    AvatarOne player_one_ava;
    player_one_ava.Init(g_screen);
    
   
    // Spawn player two
    PlayerObjectTwo p_player_two;
    p_player_two.LoadImg("./img/char_2/walk_left.png", g_screen);
    p_player_two.SetClips();
    int HitTaken_2 = 0;
    int Lives_2 = 3;

    // Player two hp
    CharTwoHP player_two_hp;
    player_two_hp.Init(g_screen);

    // Player two ava
    AvatarTwo player_two_ava;
    player_two_ava.Init(g_screen);

    // Time
    Timer fps_timer;

    TextObject time_game;
    time_game.SetColor(TextObject::BLACK_TEXT);

    TextObject Char1;
    Char1.SetColor(TextObject::BLUE_TEXT);

    TextObject Char2;
    Char2.SetColor(TextObject::RED_TEXT);

    TextObject Lives1;
    Lives1.SetColor(TextObject::BLUE_TEXT);

    TextObject Lives2;
    Lives2.SetColor(TextObject::RED_TEXT);
    

    TextObject Position;
    Position.SetColor(TextObject::WHITE_TEXT);

    TextObject Position2;
    Position2.SetColor(TextObject::WHITE_TEXT);

    bool Quit_Game = false;

    // Game events
    while(!Quit_Game){
        fps_timer.start();

        while(SDL_PollEvent(&g_event) != 0){
            if(g_event.type == SDL_QUIT)
                Quit_Game = true;

            p_player.HandleInputAction(g_event, g_screen);
            p_player_two.HandleInputAction(g_event, g_screen);
        }

        SDL_SetRenderDrawColor(g_screen, 
                               RENDER_DRAW_COLOR,
                               RENDER_DRAW_COLOR,
                               RENDER_DRAW_COLOR,
                               RENDER_DRAW_COLOR);

        SDL_RenderClear(g_screen);

        g_background.Render(g_screen, NULL);

        game_map.DrawMap(g_screen);
        Map map_data = game_map.GetMap();

        // Set player one
        p_player.SetMapXY(map_data.start_x, map_data.start_y);
        p_player.DoPlayer(map_data);
        p_player.Show(g_screen);

        // Set player two
        p_player_two.SetMapXY(map_data.start_x, map_data.start_y);
        p_player_two.DoPlayer(map_data);
        p_player_two.Show(g_screen);

        game_map.SetMap(map_data);
        game_map.DrawMap(g_screen);

        // Draw basics
        ColorData white(255, 255, 255);
        ColorData black(0, 0, 0);

        GeometricFormat health_bar_one(75, 9, 200, 12);
        GeometricFormat health_one_outline(75, 9, 201, 12);

        GeometricFormat health_bar_two(SCREEN_WIDTH - 200 - 76, 9, 201, 12);
        GeometricFormat health_two_outline(SCREEN_WIDTH - 200 - 76, 9, 201, 12);

        GeometricFormat ava_one_outline(0, 1, 76, 50);
        GeometricFormat ava_two_outline(SCREEN_WIDTH - 76, 1, 76, 50);


        // Show ava
        Geometric::RenderOutline(ava_one_outline, black, g_screen);
        Geometric::RenderOutline(ava_two_outline, black, g_screen);

        player_one_ava.Show(g_screen);
        player_two_ava.Show(g_screen);

        // Show health
        Geometric::RenderRectangle(health_bar_one, white, g_screen);
        Geometric::RenderRectangle(health_bar_two, white, g_screen);

        player_one_hp.Show(g_screen);
        player_two_hp.Show(g_screen);

        Geometric::RenderOutline(health_one_outline, black, g_screen);
        Geometric::RenderOutline(health_two_outline, black, g_screen);

        // Check combat
        SDL_Rect rect_player_one = p_player.GetRectFrame();
        SDL_Rect rect_player_two = p_player_two.GetRectFrame();

        bool InRange = CheckCollision(rect_player_one, rect_player_two);
        if(InRange){
            if(p_player.HitState() != "idle"){
                if(!p_player_two.Defend()){
                    if(HitConfirm(p_player.HitState(),
                       CheckPosition(rect_player_one, rect_player_two))
                       != "No"){
                        
                        HitTaken_2+=2;
                        
                        if(HitTaken_2 < 100){
                            player_two_hp.Decrease();
                            player_two_hp.Render(g_screen);
                            
                        }
                        else{
                            if(Lives_2 > 0){
                                HitTaken_2 = 0;
                                Lives_2--;
                                
                                p_player_two.SetRect(SCREEN_WIDTH,0);
                                p_player_two.ComeBackTime(1);
                                
                                player_two_hp.Init(g_screen);
                                SDL_Delay(100);
                                continue;
                            }
                            else{
                                SDL_Quit();
                                return 0;
                            }
                        }
                    }
                }
            }
            if(p_player_two.HitState()!= "idle"){
                
                if(!p_player.Defend()){
                    
                        HitTaken_1+=1;
   
                    if(HitTaken_1 < 100){
                        player_one_hp.Decrease();
                        player_one_hp.Render(g_screen);
                        
                    }
                    else{
                        if(Lives_1 > 0){
                            HitTaken_1 = 0;
                            Lives_1--;
                            
                            p_player.SetRect(0,0);
                            p_player.ComeBackTime(1);
                            
                            player_one_hp.Init(g_screen);
                            SDL_Delay(100);
                            continue;
                        }
                        else{
                            SDL_Quit();
                            return 0;
                        }
                    }
                }
            }
        }
        // Show time
        std::string string_time = "Time: ";
        Uint32 time_value = SDL_GetTicks()/1000;
        Uint32 time_display = 180 - time_value;

        if(time_display <= 0){
            Quit_Game = true;
            return 0;
        }
        else{
            std::string display_time = std::to_string(time_display);
            string_time += display_time;

            time_game.SetText(string_time);
            time_game.LoadFromRenderText(font_time, g_screen);
            time_game.RenderText(g_screen, SCREEN_WIDTH/2 - 50, 30);
        }

        // Show HP & Lives
        std::string char_1_lives = "Lives: ";
        if(HitTaken_1 < 100){
            std::string display_lives_1 = std::to_string(Lives_1);
            char_1_lives += display_lives_1;

            Lives1.SetText(char_1_lives);
            Lives1.LoadFromRenderText(font_time, g_screen);
            Lives1.RenderText(g_screen, 5, 55);
        }

        std::string char_2_lives = "Lives: ";
        if(HitTaken_2 < 100){
            std::string display_lives_2 = std::to_string(Lives_2);
            char_2_lives += display_lives_2;

            Lives2.SetText(char_2_lives);
            Lives2.LoadFromRenderText(font_time, g_screen);
            Lives2.RenderText(g_screen, SCREEN_WIDTH - 95, 55);
        }

        std::string char_1_hp = "HP: ";
        if(HitTaken_1 < 100){
            std::string display_hp_1 = std::to_string(100 - HitTaken_1);
            char_1_hp += display_hp_1 + "%";

            Char1.SetText(char_1_hp);
            Char1.LoadFromRenderText(font_time, g_screen);
            Char1.RenderText(g_screen, 125, 30);
        }

        std::string char_2_hp = "HP: ";
        if(HitTaken_2 < 100){
            std::string display_hp_2 = std::to_string(100 - HitTaken_2);
            char_2_hp += display_hp_2 + "%";

            Char2.SetText(char_2_hp);
            Char2.LoadFromRenderText(font_time, g_screen);
            Char2.RenderText(g_screen, SCREEN_WIDTH - 200, 30);
        }


        // Demo test             
        std::string hitable = "";
        if(InRange) hitable = " (in range)";
        std::string checkpos = "P2 to P1: " +
                                CheckPosition(rect_player_one, rect_player_two) +
                                hitable +
                                "       " +
                                "P1 Action:  " +
                                p_player.HitState();

        std::string checkpos2 = "P1 to P2: " +
                                CheckPosition(rect_player_two, rect_player_one) +
                                hitable +
                                "       " +
                                "P2 Action:  " +
                                p_player_two.HitState();
        
        Position.SetText(checkpos);
        Position.LoadFromRenderText(font_time, g_screen);
        Position.RenderText(g_screen, 0, 100);

        Position2.SetText(checkpos2);
        Position2.LoadFromRenderText(font_time, g_screen);
        Position2.RenderText(g_screen, 0, 140);         


        SDL_RenderPresent(g_screen);

        int real_time = fps_timer.get_ticks();

        int frame_duration = 1000/FRAME_PER_SEC;

        if(real_time < frame_duration){
            int delay_time = frame_duration - real_time;
            SDL_Delay(delay_time);
        }
        
    }    

    CloseApp();

    return 0;
}

// Close application
void CloseApp(){
    g_background.Free();

    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;

    IMG_Quit();
    SDL_Quit();
}

bool LoadBackground(){
    bool LoadReturn = g_background.LoadImg("./img/background.jpg", g_screen);
    if(LoadReturn == false)
        return false;
    
    return true;
}

// Init program
bool InitData(){
    bool InitSuccess = true;
    int InitReturn = SDL_Init(SDL_INIT_VIDEO);
    if(InitReturn < 0)
        return false;
    
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    g_window = SDL_CreateWindow("Immortal Combat (Demo)", 
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if(g_window == NULL){
        InitSuccess = false;
    }
    else{
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if(g_screen == NULL)
            InitSuccess = false;
        else{
            SDL_SetRenderDrawColor(g_screen, 
                                   RENDER_DRAW_COLOR, 
                                   RENDER_DRAW_COLOR, 
                                   RENDER_DRAW_COLOR, 
                                   RENDER_DRAW_COLOR);
            
            int imgFlags = IMG_INIT_PNG;
            if( !(IMG_Init(imgFlags) && imgFlags) )
                InitSuccess = false;
        }

        if(TTF_Init() == -1){
            InitSuccess = false;
        }

        font_time = TTF_OpenFont("./font/font1.ttf", 15);

        if(font_time == NULL){
             InitSuccess = false;
        }
    }
    return InitSuccess;
}

// Check collision
bool CheckCollision(const SDL_Rect& objectA, const SDL_Rect& objectB){
    int center_a_x = objectA.x + objectA.w/2;
    int center_a_y = objectA.y + objectA.h/2;

    int center_b_x = objectB.x + objectB.w/2;
    int center_b_y = objectB.y + objectB.h/2;

  int dis_x = abs(center_a_x-center_b_x)+10;
  int dis_y = abs(center_a_y-center_b_y)+20;

  if(dis_x <= objectB.w && dis_y <= objectB.h)
    return 1;
 
  return 0;
}

std::string CheckPosition(const SDL_Rect& objectA, const SDL_Rect& objectB){
    int center_a_x = objectA.x + objectA.w/2;
    int center_a_y = objectA.y + objectA.h/2;

    int center_b_x = objectB.x + objectB.w/2;
    int center_b_y = objectB.y + objectB.h/2;
    
    std::string pos_x = "";
    std::string pos_y = "";

    if(center_a_x > center_b_x){
        pos_x = "left";
    }
    else if(center_a_x < center_b_x){
        pos_x = "right";
    }

    if(center_a_y < center_b_y){
        pos_y = "down_";
    }
    else if(center_a_y > center_b_y){
        pos_y = "up_";
    }

    if(center_a_x == center_b_x && 
       center_a_y == center_b_y) 
       return "same spot";
    
    return pos_y + pos_x;
}

std::string HitConfirm(std::string HitState, std::string Position){
    std::string Confirm = "No";
        if(HitState == "right"){
            if(Position == "right"){
                Confirm = "Yes";
            }
        }
        else if(HitState == "left"){
            if(Position == "left"){
                Confirm = "Yes";
            }
        }
        else if(HitState == "up_right"){
            if(Position == "up_right"){
                Confirm = "Yes";
            }
        }
        else if(HitState == "up_left"){
            if(Position == "up_left"){
                Confirm = "Yes";
            }
        }
        else if(HitState == "down_right"){
            if(Position == "down_right" || Position == "right"){
                Confirm = "Yes";
            }
        }
        else if(HitState == "down_left"){
            if(Position == "down_left" || Position == "left"){
                Confirm = "Yes";
            }
        }       

    return Confirm;
}