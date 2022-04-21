#ifndef CHAR_ONE_HP_
#define CHAR_ONE_HP_

#include "CommonFunc.h"
#include "BaseObject.h"

class CharOneHP : public BaseObject{
    public:
        CharOneHP();
        ~CharOneHP();

        void SetNum(const int& num){number = num;};
        void AddPos(const int& xPos);
        void Show(SDL_Renderer* screen);
        void Init(SDL_Renderer* screen);

        void Decrease();
    private:
        int number;
        std::vector<int> pos_list;

};

#endif