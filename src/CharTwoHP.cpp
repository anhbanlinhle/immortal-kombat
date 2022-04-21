#include "CharTwoHP.h"
#include "CommonFunc.h"

CharTwoHP::CharTwoHP(){
    number = 0;
}

CharTwoHP::~CharTwoHP(){

}

void CharTwoHP::AddPos(const int& xp){
    pos_list.push_back(xp);
}

void CharTwoHP::Init(SDL_Renderer* screen){
    LoadImg("./img/char_2_hp.jpg", screen);
    number = 10;
    if(pos_list.size() > 0){
        pos_list.clear();
    }

    for(int i = 0; i < 200; i+=2){
        AddPos(i);
    }
}

void CharTwoHP::Show(SDL_Renderer* screen){
    for(int i = 0; i < pos_list.size(); i++){
        rect_.x = SCREEN_WIDTH - pos_list.at(i) - 20;
        rect_.y = 20;
        Render(screen);
    }
}

void CharTwoHP::Decrease(){
    number--;
    pos_list.pop_back();
}