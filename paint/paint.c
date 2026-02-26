#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_render.h>
//gcc shadow-cast.c -o shadow-cast $(pkg-config sdl3 --cflags --libs)

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("SDL3 Loop", 800, 600, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);

    bool is_running = true;
    SDL_Event event;
    float mouseX;
    float mouseY;
    bool isDrawing = false;
    SDL_FRect rect;

    while (is_running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                is_running = false;
            }
            if (event.type == SDL_EVENT_MOUSE_MOTION) {
              mouseX = event.motion.x;
              mouseY = event.motion.y;
              SDL_Log("Mouse Motion: %f, %f", mouseX, mouseY);
            }
            if(event.type == SDL_EVENT_MOUSE_BUTTON_DOWN){
              isDrawing = true;
              rect = (SDL_FRect){mouseX, mouseY, 50, 50};
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black
        SDL_RenderClear(renderer);

        if(isDrawing){
          SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
          SDL_RenderRect(renderer, &rect);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
