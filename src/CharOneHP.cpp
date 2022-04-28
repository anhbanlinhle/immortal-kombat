#include "CharOneHP.h"

CharOneHP::CharOneHP(){
    number = 0;
}

CharOneHP::~CharOneHP(){

}

void CharOneHP::AddPos(const int& xp){
    pos_list.push_back(xp);
}

void CharOneHP::Init(SDL_Renderer* screen){
    LoadImg("./img/char_1_hp.jpg", screen);
    number = 100;
    if(pos_list.size() > 0){
        pos_list.clear();
    }

    for(int i = 0; i < 200; i+=2){
        AddPos(i);
    }
}

void CharOneHP::Show(SDL_Renderer* screen){
    for(int i = 0; i < pos_list.size(); i++){
        rect_.x = pos_list.at(i) + 75;
        rect_.y = 10;
        Render(screen);
    }
}

void CharOneHP::Decrease(){
    for(int i = 0; i < 1; i++){
        number--;
        pos_list.pop_back();
    }
}

AvatarOne::AvatarOne(){
    x_pos = 0;
    y_pos = 0;
}

AvatarOne::~AvatarOne(){

}

void AvatarOne::Init(SDL_Renderer* screen){
    LoadImg("./img/char_1_avatar.jpg", screen);
}

void AvatarOne::Show(SDL_Renderer* screen){
    rect_.x = x_pos;
    rect_.y = y_pos; 
    Render(screen);
}