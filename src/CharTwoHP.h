#ifndef CHAR_TWO_HP_
#define CHAR_TWO_HP_

#include "CommonFunc.h"
#include "BaseObject.h"

class CharTwoHP : public BaseObject{
    public:
        CharTwoHP();
        ~CharTwoHP();

        void SetNum(const int& num){number = num;};
        void AddPos(const int& xPos);
        void Show(SDL_Renderer* screen);
        void Init(SDL_Renderer* screen);

        void Decrease();
    private:
        int number;
        std::vector<int> pos_list;

};

class AvatarTwo : public BaseObject{
    public:
        AvatarTwo();
        ~AvatarTwo();

        void Init(SDL_Renderer* screen);
        void Show(SDL_Renderer* screen);
        void SetPos(const int& x, const int& y){x_pos = x, y_pos = y;};
    private:
        int x_pos;
        int y_pos;

};

#endif