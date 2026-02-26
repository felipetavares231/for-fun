#include <SDL3/SDL_init.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>
#include <stdio.h>
#include <SDL3/SDL.h>
#include <stdlib.h>
#include <zlib.h>
//gcc PNGViewer.c -o PNGViewer $(pkg-config --cflags --libs sdl3)

int main (){
  //SDL_Init(SDL_INIT_VIDEO);

  FILE *file = fopen("image.png", "rb");

  int amountOfBytesToRead = 24;
  unsigned char buffer[amountOfBytesToRead];
  size_t bytes_read = fread(buffer, 1, amountOfBytesToRead, file);
  fclose(file);

  int width = (buffer[16] << 24) | (buffer[17] << 16) | (buffer[18] << 8) | (buffer[19]);
  int height = (buffer[20] << 24) | (buffer[21] << 16) | (buffer[22] << 8) | (buffer[23]);

  printf("%d, %d", width, height);


  SDL_Window *window = SDL_CreateWindow("PNGViewer", width, height, 0);
  SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
  
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < width; y++) {
      SDL_FRect rect = {
        x, y, 1, 1
      };

      int random_r = rand() % 256;
      int random_g = rand() % 256;
      int random_b = rand() % 256;
      SDL_SetRenderDrawColor(renderer, random_r, random_g, random_b, 255);
      SDL_RenderFillRect(renderer, &rect);
    }
  }

  SDL_RenderPresent(renderer);
  SDL_Delay(3000);

  return 0;
}
