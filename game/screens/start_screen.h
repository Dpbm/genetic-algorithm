#pragma once

#include "screens.h"
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>

using Screens::Screen;

namespace GameStartScreen {

  class StartScreen : public Screen{
    public:
      StartScreen(SDL_Renderer* render);
      ~StartScreen();
      void execute(SDL_Renderer* render, bool& game_loop);
      Screen* key_event(const SDL_Keycode& key);
    
    private:
      SDL_Renderer* render = nullptr;
      TTF_Font* font = TTF_OpenFont("./assets/pressstart.ttf", 35);
      SDL_Color text_color{ 255, 255, 255 };
      
      SDL_Texture* title_texture;
      SDL_Texture* ai_texture;
      SDL_Texture* player_texture;
      SDL_Texture* debug_texture;

      SDL_Rect title_shape;
      SDL_Rect ai_shape;
      SDL_Rect player_shape;
      SDL_Rect debug_shape;
  };

};
