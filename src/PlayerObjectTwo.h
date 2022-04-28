

#ifndef PLAYER_OBJECT_TWO_H
#define PLAYER_OBJECT_TWO_H

#include "CommonFunc.h"
#include "BaseObject.h"

#define GRAVITY_VELOCITY 4
#define MAX_FALL_SPEED 16
#define PLAYER_SPEED 8
#define MAX_JUMP 24

class PlayerObjectTwo : public BaseObject{
    public:
        PlayerObjectTwo();
        ~PlayerObjectTwo();

        enum WalkType{
            WALK_RIGHT = 0,
            WALK_LEFT = 1,
        };

        std::string HitState();
        bool Defend();
        void AntiCheat();

        bool LoadImg(std::string path, SDL_Renderer* screen);
        void Show(SDL_Renderer* des);
        void HandleInputAction(SDL_Event events, SDL_Renderer* screen);
        void SetClips();

        void DoPlayer(Map& map_data);
        void CheckCollideMap(Map& map_data);
        void SetMapXY(const int map_x_, const int map_y_){
            map_x = map_x_;
            map_y = map_y_;
        };
        void CenterEntityOnMap(Map& map_data);

        void RefreshFrame(SDL_Renderer* des);
        
        SDL_Rect GetRectFrame();

        void ComeBackTime(const int& cb_time){
            come_back_time = cb_time;
        };


    private:
        float horizon_distance;
        float vertical_distance;

        float x_pos;
        float y_pos;

        int width_frame;
        int height_frame;

        SDL_Rect frame_clip[12];

        Input input_type;

        int frame;

        int PlayerStatus;

        bool OnGround;

        int map_x;
        int map_y; 

        int come_back_time;

        bool CheatLock;
        int Counter;
};










#endif