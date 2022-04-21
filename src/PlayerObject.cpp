

#include "PlayerObject.h"

PlayerObject::PlayerObject(){
    frame = 0;
    x_pos = 0;
    y_pos = 0;
    horizon_distance = 0;
    vertical_distance = 0;
    width_frame = 0;
    height_frame = 0;
    PlayerStatus = -1;
    
    input_type.left = 0;
    input_type.right = 0;

    input_type.jump = 0;
    input_type.down = 0;

    input_type.attack_left = 0;
    input_type.attack_right = 0;

    input_type.up_left = 0;
    input_type.up_right = 0;

    input_type.down_left = 0;
    input_type.down_right = 0;

    OnGround = 0;
    map_x = 0;
    map_y = 0;
    come_back_time = 0;

    CheatLock = 0;
    Counter = 0;
}

PlayerObject::~PlayerObject(){

}

bool PlayerObject::LoadImg(std::string path, SDL_Renderer* screen){
    bool return_ = BaseObject::LoadImg(path, screen);

    if(return_ == true){
        width_frame = rect_.w/12;
        height_frame = rect_.h;
    }

    return return_;
}

SDL_Rect PlayerObject::GetRectFrame(){
    SDL_Rect rect;
    rect.x = rect_.x;
    rect.y = rect_.y;
    rect.w = width_frame;
    rect.h = height_frame;

    return rect;
}

void PlayerObject::SetClips(){
    if(width_frame > 0 && height_frame > 0){
        for(int i = 0; i < 12; i++){
            frame_clip[i].x = i*width_frame;
            frame_clip[i].y = 0;
            frame_clip[i].w = width_frame;
            frame_clip[i].h = height_frame;
        }
    }
}

void PlayerObject::Show(SDL_Renderer* des){
    RefreshFrame(des);

    frame++;
    AntiCheat();

    if(frame >= 12){
        frame = 0;
    }

    rect_.x = x_pos - map_x;
    rect_.y = y_pos - map_y;

    SDL_Rect* current_clip = &frame_clip[frame];

    SDL_Rect render_quad = {
        rect_.x,
        rect_.y,
        width_frame,
        height_frame
    };

    SDL_RenderCopy(des, p_object, current_clip, &render_quad);
}

void PlayerObject::HandleInputAction(SDL_Event events, SDL_Renderer* screen){
    if(events.type == SDL_KEYDOWN){
            switch(events.key.keysym.sym){
                case SDLK_d:{
                    PlayerStatus = WALK_RIGHT;
                    input_type.right = 1;
                    input_type.left = 0;
                    RefreshFrame(screen);
                }
                break;

                case SDLK_a:{
                    PlayerStatus = WALK_LEFT;
                    input_type.left = 1;
                    input_type.right = 0;
                    RefreshFrame(screen);
                }
                break;

                case SDLK_w:{
                    input_type.jump = 1;
                }
                break;

                case SDLK_s:{
                    input_type.down = 1;
                }
                break;

                case SDLK_r:{
                    if(CheatLock != 1){
                        input_type.attack_left = 1;
                        Counter++;
                    }
                }
                break;

                case SDLK_t:{
                    if(CheatLock != 1){
                        input_type.attack_right = 1;
                        Counter++;
                    }
                }
                break;

                case SDLK_q:{
                    if(CheatLock != 1){
                        if(PlayerStatus == WALK_LEFT)
                        input_type.up_left = 1;
                        Counter++;
                    }
                }
                break;

                case SDLK_e:{
                    if(CheatLock != 1){
                        if(PlayerStatus == WALK_RIGHT)
                        input_type.up_right = 1;
                        Counter++;
                    }
                }
                break;

                case SDLK_f:{
                    if(CheatLock != 1)
                    if(PlayerStatus == WALK_LEFT)
                        input_type.down_left = 1;
                }
                break;

                case SDLK_g:{
                    if(CheatLock != 1)
                    if(PlayerStatus == WALK_RIGHT)
                        input_type.down_right = 1;
                }
                break;
            }
        
    }
    else if(events.type == SDL_KEYUP){
        switch(events.key.keysym.sym){
            case SDLK_d:{
                input_type.right = 0;
                
            }
            break;

            case SDLK_a:{
                input_type.left = 0;
                
            }
            break;

            case SDLK_w:{
                
            }
            break;

            case SDLK_s:{
                input_type.down = 0;
                Counter = 0;
                CheatLock = 0;
            }
            break;

            case SDLK_r:{
                input_type.attack_left = 0;
                Counter = 0;
                CheatLock = 0;
            }
            break;

            case SDLK_t:{
                input_type.attack_right = 0;
                Counter = 0;
                CheatLock = 0;
            }
            break;

            case SDLK_q:{
                input_type.up_left = 0;
                Counter = 0;
                CheatLock = 0;
            }
            break;

            case SDLK_e:{
                input_type.up_right = 0;
                Counter = 0;
                CheatLock = 0;
            }
            break;

            case SDLK_f:{
                input_type.down_left = 0;
                Counter = 0;
                CheatLock = 0;
            }
            break;

            case SDLK_g:{
                input_type.down_right = 0;
                Counter = 0;
                CheatLock = 0;
            }
            break;
        }
        frame = 0;
    }
}

void PlayerObject::DoPlayer(Map& map_data){
    if(come_back_time == 0){
        horizon_distance = 0;
        vertical_distance += GRAVITY_VELOCITY;

        if(vertical_distance == MAX_FALL_SPEED){
            vertical_distance = MAX_FALL_SPEED;
        }

        if(input_type.left == 1){
            horizon_distance -= PLAYER_SPEED;
        }
        else if(input_type.right == 1){
            horizon_distance += PLAYER_SPEED;
        }

        if(input_type.jump == 1){
            if(OnGround == 1){
                vertical_distance = - MAX_JUMP;
            }
            OnGround = 0;
            input_type.jump = 0;
        }

        CheckCollideMap(map_data);
        CenterEntityOnMap(map_data);
    }
    if(come_back_time > 0){
        come_back_time--;
        if(come_back_time == 0){
            OnGround = 0;
            x_pos = 0;
            y_pos = 0;

            horizon_distance = 0;
            vertical_distance = 0;

        }
    }
}

void PlayerObject::CenterEntityOnMap(Map& map_data){
    map_data.start_x = x_pos - SCREEN_WIDTH/2;
    if(map_data.start_x < 0){
        map_data.start_x = 0;

    }
    else if(map_data.start_x + SCREEN_WIDTH >= map_data.max_x){
        map_data.start_x = map_data.max_x - SCREEN_WIDTH;
    }

    map_data.start_y = y_pos - SCREEN_HEIGHT/2;
    if(map_data.start_y <0){
        map_data.start_y = 0;
    }
    else if(map_data.start_y + SCREEN_HEIGHT >= map_data.max_y){
        map_data.start_y = map_data.max_y - SCREEN_HEIGHT;
    }
}

void PlayerObject::CheckCollideMap(Map& map_data){
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    // Check horizontal
    int height_min = height_frame < TILE_SIZE ? height_frame : TILE_SIZE;

    x1 = (x_pos + horizon_distance)/TILE_SIZE;
    x2 = (x_pos + horizon_distance + width_frame - 1)/TILE_SIZE;

    y1 = y_pos/TILE_SIZE;
    y2 = (y_pos + height_min - 1)/TILE_SIZE;

    if(x1 >= 0 && x2 <= MAX_MAP_X && y1 >= 0 && y2 <= MAX_MAP_Y){
        if(horizon_distance > 0){
            if(map_data.tile[y1][x2] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE){
               x_pos = x2*TILE_SIZE;
               x_pos -= (width_frame + 1);
               horizon_distance = 0; 
            }
        }
        else if(horizon_distance < 0){
            if(map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y2][x1] != BLANK_TILE){
                x_pos = (x1 + 1)*TILE_SIZE;
                horizon_distance = 0;
            }
        }
    }

    // Check vertical
    int width_min = width_frame < TILE_SIZE ? width_frame : TILE_SIZE;
    x1 = x_pos/TILE_SIZE;
    x2 = (x_pos + width_min)/TILE_SIZE;

    y1 = (y_pos + vertical_distance)/TILE_SIZE;
    y2 = (y_pos + vertical_distance + height_frame - 1)/TILE_SIZE;

    if(x1 >= 0 && x2 <= MAX_MAP_X && y1 >= 0 && y2 <= MAX_MAP_Y){
        if(vertical_distance >= 0){
            if(map_data.tile[y2][x1] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE){
                y_pos = y2*TILE_SIZE;
                y_pos -= (height_frame + 1);
                vertical_distance = 0;
                OnGround = 1;
            }
        }
        else if(vertical_distance < 0){
            if(map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y1][x2] != BLANK_TILE){
                y_pos = (y1 + 1)*TILE_SIZE;
                vertical_distance = 0; 
            }
        }
    }

    x_pos += horizon_distance;
    y_pos += vertical_distance;

    if(x_pos < 0){
        x_pos = 0;
    }
    else if(x_pos + width_frame > map_data.max_x){
        x_pos = map_data.max_x - width_frame - 1;
    }

    if(y_pos + height_frame >= map_data.max_y){
        y_pos = map_data.max_y - height_frame - TILE_SIZE - 1;
        OnGround = 1;
    }
}

std::string PlayerObject::HitState(){
    if(input_type.attack_right == 1) return "right";

    if(input_type.attack_left == 1) return "left";

    if(input_type.up_right == 1) return "up_right";

    if(input_type.up_left == 1) return "up_left";

    if(input_type.down_right == 1) return "down_right";

    if(input_type.down_left == 1) return "down_left";

    return "idle";
}

bool PlayerObject::Defend(){
    return input_type.down;
}

void PlayerObject::RefreshFrame(SDL_Renderer* des){
    if(OnGround == 1){
        if(PlayerStatus == WALK_LEFT){

            if(input_type.left == 1){
                LoadImg("./img/char_1/walk_left.png", des);
            }
            else if(input_type.down == 1){
                LoadImg("./img/char_1/defense_left.png", des);
            }
            else{
                LoadImg("./img/char_1/idle_left.png", des);
            }

            if(input_type.attack_left){
                LoadImg("./img/char_1/punch_left.png", des);
            }
            else if(input_type.attack_right){
                LoadImg("./img/char_1/back_left.png", des);
            }

            if(input_type.up_left == 1){
                LoadImg("./img/char_1/kick_left.png", des);
            }

            if(input_type.down_left == 1){
                LoadImg("./img/char_1/low_left.png", des);
            }
        }
        else{
            if(input_type.right == 1){
                LoadImg("./img/char_1/walk_right.png", des);
            }
            else if(input_type.down == 1){
                LoadImg("./img/char_1/defense_right.png", des);
            }
            else{
                LoadImg("./img/char_1/idle_right.png", des);
            }

            if(input_type.attack_left){
                LoadImg("./img/char_1/back_right.png", des);
            }
            else if(input_type.attack_right){
                LoadImg("./img/char_1/punch_right.png", des);
            }

            if(input_type.up_right == 1){
                LoadImg("./img/char_1/kick_right.png", des);
            }

            if(input_type.down_right == 1){
                LoadImg("./img/char_1/low_right.png", des);
            }
        }
    }
    else{
        if(PlayerStatus == WALK_LEFT){
            if(input_type.attack_left == 1){
                LoadImg("./img/char_1/up_left.png", des);
            }
            else if(input_type.down_left == 1){
                LoadImg("./img/char_1/strike_left.png", des);
            }
            else{
                LoadImg("./img/char_1/jump_left.png", des);
            }
        }
        else{
            if(input_type.attack_right == 1){
                LoadImg("./img/char_1/up_right.png", des);
            }
            else if(input_type.down_right == 1){
                LoadImg("./img/char_1/strike_right.png", des);
            }
            else{
                LoadImg("./img/char_1/jump_right.png", des);
            }
        }
    }
}

void PlayerObject::AntiCheat(){
    if(Counter >= 6){
        input_type.jump = 0;
        input_type.down = 0;

        input_type.attack_left = 0;
        input_type.attack_right = 0;

        input_type.up_left = 0;
        input_type.up_right = 0;

        input_type.down_left = 0;
        input_type.down_right = 0;

        CheatLock = 1;
    }
}