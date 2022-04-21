#ifndef GEOMETRIC_H_
#define GEOMETRIC_H_

#include "CommonFunc.h"

struct GeometricFormat{
    public:
        GeometricFormat(int left_, 
                        int top_, 
                        int width_, 
                        int height_){
                            left_ = left,
                            top_ = top,
                            width_ = width,
                            height_ = height;};
        int left;
        int top;
        int width;
        int height;
};

struct ColorData{
    
    ColorData(Uint8 r, Uint8 g, Uint8 b){red = r, green = g, blue = b;}

    public:
        Uint8 red;
        Uint8 green;
        Uint8 blue;  
};

class Geometric{
  public:

        static void RenderRectangle(const GeometricFormat& geo_size, 
                                    const ColorData& color_data, 
                                    SDL_Renderer* screen);
        static void RenderOutline(const GeometricFormat& geo_size, 
                                  const ColorData& color_data,
                                  SDL_Renderer* screen);
};

#endif