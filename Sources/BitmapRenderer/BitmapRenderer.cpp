#include "BitmapRenderer.hpp"

#include <SDL_image.h>

SDL_Renderer *BitmapRenderer::sdl_renderer = nullptr;

void BitmapRenderer::setup(SDL_Renderer *renderer) 
{
    sdl_renderer = renderer;
}

void BitmapRenderer::draw_bitmap(SDL_Texture *bitmap, int pos_x, int pos_y, int size_x, int size_y, float rot) 
{
    SDL_Rect rect;
    rect.x = pos_x;
    rect.y = pos_y;
    rect.w = size_x;
    rect.h = size_y;

    // For now it will always draw from the center
    SDL_RenderCopyEx( sdl_renderer, bitmap, NULL, &rect, rot, NULL, SDL_RendererFlip::SDL_FLIP_NONE );
}

void BitmapRenderer::draw_bitmap(SDL_Texture *bitmap, SDL_Rect clipRect, int pos_x, int pos_y, int size_x, int size_y, float rot) 
{
    SDL_Rect rect;
    rect.x = pos_x;
    rect.y = pos_y;
rect.w = size_x;
    rect.h = size_y;

    // For now it will always draw from the center
    SDL_RenderCopyEx( sdl_renderer, bitmap, &clipRect, &rect, rot, NULL, SDL_RendererFlip::SDL_FLIP_NONE );
}
