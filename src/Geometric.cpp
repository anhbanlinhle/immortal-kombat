#include "Geometric.h"

void Geometric::RenderRectangle(const GeometricFormat& geo_size, const ColorData& color_data, SDL_Renderer* screen){
    SDL_Rect fill_rect = {geo_size.left,
                          geo_size.top,
                          geo_size.width,
                          geo_size.height};

    SDL_SetRenderDrawColor(screen, color_data.red, color_data.green, color_data.blue, 0xFF);

    SDL_RenderFillRect(screen, &fill_rect);

}

void Geometric::RenderOutline(const GeometricFormat& geo_size, const ColorData& color_data, SDL_Renderer* screen){
    SDL_Rect outRect = {geo_size.left,
                          geo_size.top,
                          geo_size.width,
                          geo_size.height};
                
    SDL_SetRenderDrawColor(screen, color_data.red, color_data.green, color_data.blue, 0xFF);

    SDL_RenderDrawRect(screen, &outRect);
}