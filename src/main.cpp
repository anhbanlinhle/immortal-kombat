#include <iostream>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
using namespace std;

//colors
namespace Colors{
    const SDL_Color BLACK = {0, 0, 0, SDL_ALPHA_OPAQUE};
    const SDL_Color GREEN = {0, 255, 0, SDL_ALPHA_OPAQUE};

}


//graphics
namespace Graphics{
    struct Screen{
        const int WIDTH = 512;
        const int HEIGHT = 284;
        const int center_x = WIDTH/2;
        const int center_y = HEIGHT/2;
    };
};

//game object
enum SquareState{
    IDLE,
    MOVING_UP,
    MOVING_DOWN,
    MOVING_LEFT,
    MOVING_RIGHT,
};

struct Square{
    int WIDTH, HEIGHT, x, y;
    SquareState state;
    int step;
};


//application
struct App{
    const int DEFAULT_STEP = 2;
    SDL_Window* window;
    SDL_Renderer* renderer;

    Graphics::Screen screen;


    Square square = {
        64, 
        64, 
        screen.center_x, 
        screen.center_y,
        IDLE,
        DEFAULT_STEP,
    };
} app;


//sdl routines
bool InitSDL(){
    if( SDL_Init(SDL_INIT_EVERYTHING) > 0){
        cout << "Error: " << SDL_GetError() << endl;
        return 0;
    }
    return 1;
}

//graphics routines

void ClearScreen(SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer, Colors::BLACK.r, Colors::BLACK.g, Colors::BLACK.b, Colors::BLACK.a);
    SDL_RenderClear(renderer);
}

void DrawSquare(int x, int y){
    SDL_Rect rect;
    rect.x =  x - (app.square.WIDTH/2);
    rect.y =  y - (app.square.HEIGHT/2);
    rect.w =  app.square.WIDTH/2;
    rect.h =  app.square.HEIGHT/2;

    //define the green color on the renderer
    SDL_SetRenderDrawColor(app.renderer, Colors::GREEN.r, Colors::GREEN.g, Colors::GREEN.b, Colors::GREEN.a);
    //ask the renderer to fill rect with green color
    SDL_RenderFillRect(app.renderer, &rect);
}



//application routines
void ShutdownApplication(){
    if(app.window != nullptr){
        SDL_DestroyWindow(app.window);
         app.window = nullptr;
    }
    
    if(app.renderer != nullptr){
        SDL_DestroyRenderer(app.renderer);
         app.renderer = nullptr;
    }

    SDL_Quit();
}


bool InitApplication(){
    if(InitSDL() == 0){
        ShutdownApplication();
        return 0;
    }    

    app.window = SDL_CreateWindow(
        "Moving Square (512x284)",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        app.screen.WIDTH,
        app.screen.HEIGHT,
        SDL_WINDOW_OPENGL
    );

    if(app.window == nullptr){
        cout << "Unable to create the main window. Error: " << SDL_GetError() << endl;
        ShutdownApplication();
        return 0;
    }

    app.renderer = SDL_CreateRenderer(app.window, -1, SDL_RENDERER_PRESENTVSYNC);

    return 1;
}

void SetState(SquareState new_state){
    app.square.state = new_state;
}

void IncreaseSteps(){
    app.square.step *= app.DEFAULT_STEP;
}

void DecreaseSteps(){
    int new_step = app.square.step / app.DEFAULT_STEP;
    if(new_step > app.DEFAULT_STEP)
        app.square.step = new_step;
    else
        app.square.step = app.DEFAULT_STEP;
}

int main(int argc, char *argv[]){
    if(InitApplication() == 0){
        ShutdownApplication();
        return EXIT_FAILURE;
    }

    //draw loop
    SDL_Event event;
    bool running = 1;

    while(running){
        ClearScreen(app.renderer);

        //check the square state
        switch(app.square.state){
            case MOVING_UP:{
                int new_y = app.square.y - app.square.step;
                if(new_y > app.square.HEIGHT/2)
                    app.square.y -= app.square.step;
                else{
                    app.square.y = app.square.HEIGHT/2;
                    SetState(MOVING_DOWN);
                }
                break;
            }
            case MOVING_DOWN:{
                int new_y = app.square.y + app.square.step;
                if(new_y < app.screen.HEIGHT)
                    app.square.y += app.square.step;
                else{
                    app.square.y = app.screen.HEIGHT;
                    SetState(MOVING_UP);
                }
                break;
            }
            case MOVING_LEFT:{
                int new_top_left = app.square.x - app.square.step - app.square.WIDTH/2;
                if(new_top_left > app.square.step)
                    app.square.x -= app.square.step;
                else{
                    app.square.x = app.square.WIDTH/2;
                    SetState(MOVING_RIGHT);
                }
                break;
            }
            case MOVING_RIGHT:{
                int new_top_left = app.square.x + app.square.step;
                if(new_top_left <= app.screen.WIDTH)
                    app.square.x += app.square.step;
                else
                    SetState(MOVING_LEFT);
                break;
            }
        }

        //check n process i/o event
        if(SDL_PollEvent(&event)){
            switch (event.type){
                case SDL_KEYDOWN:{
                    running = event.key.keysym.scancode != SDL_SCANCODE_ESCAPE;
                    
                    if(event.key.keysym.scancode == SDL_SCANCODE_UP){
                        SetState(MOVING_UP);
                    }

                    if(event.key.keysym.scancode == SDL_SCANCODE_DOWN){
                        SetState(MOVING_DOWN);
                    }

                    if(event.key.keysym.scancode == SDL_SCANCODE_LEFT){
                        SetState(MOVING_LEFT);
                    }

                    if(event.key.keysym.scancode == SDL_SCANCODE_RIGHT){
                        SetState(MOVING_RIGHT);
                    }

                    if(event.key.keysym.scancode == SDL_SCANCODE_SPACE){
                        SetState(IDLE);
                    }

                    if(event.key.keysym.scancode == SDL_SCANCODE_PAGEUP){
                        IncreaseSteps();
                    }

                    if(event.key.keysym.scancode == SDL_SCANCODE_PAGEDOWN){
                        DecreaseSteps();
                    }

                    break;
                }
                case SDL_QUIT:{
                    running = 0;
                    break;
                }
                default: break;
            }
        }
        //draw the new content on the renderer
        DrawSquare(app.square.x, app.square.y);

        //update the screen with content rendered
        SDL_RenderPresent(app.renderer);
    }

    ShutdownApplication();
    return EXIT_SUCCESS;
}