#ifndef GEOMETRIC_H_
#define GEOMETRIC_H_

#include "CommonFunc.h"

struct GeometricFormat{
    public:
        GeometricFormat(int left_, 
                        int top_, 
                        int width_, 
                        int height_){
                            left = left_,
                            top = top_,
                            width = width_,
                            height = height_;};
        int left;
        int top;
        int width;
        int height;
};

struct ColorData{
    
    

    public:
        ColorData(Uint8 r, Uint8 g, Uint8 b){red = r, green = g, blue = b;};

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