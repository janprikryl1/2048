#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h> //True type fonty
#include <stdbool.h>
#include <assert.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600



int main()
{
    if (SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Window* window = SDL_CreateWindow("2048", 100, 100, 800, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); //Renderer něco kreslí
    if (!renderer) {
        SDL_DestroyWindow(window);
        fprintf(stderr, "SDL_CreateRenderer Error: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Event e;
    bool quit = false;

 

    int score = 0;

    TTF_Init();

    TTF_Font * sans = TTF_OpenFont("AnonymousPro-Regular.ttf", 22);
    assert(sans); //Je-li to NULL, 0, False -> ukončí to program

    SDL_Color RGB_white = {255, 255, 255};
    char score_text[80];

    SDL_Rect score_rect = {.x = WINDOW_WIDTH / 2 - 50, .y = 50, .w = 100, .h = 20}; //V tomto obdélníku bude to score

    

    while (!quit) // Projdu všechny události (z klávesnice, myši) a zpracuju je. Poté jdu dál
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT) //Pokud je kliknut křížek, nebo Alt+F4
            {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN) { //Pokud je stisknuto tlačítko
                printf("%d\n", e.key.keysym.sym);
                score++;

                switch( e.key.keysym.sym ){
                    case SDLK_LEFT:
                        printf("Left\n");
                        break;
                    case SDLK_RIGHT:
                        printf("right\n");
                        break;
                    case SDLK_UP:
                        printf("up\n");
                        break;
                    case SDLK_DOWN:
                        printf("down\n");
                        break;
                    case 110:
                        printf("Nova hra\n");
                        break;
                    case 113:
                        printf("Konec\n");
                        quit = true;
                        break;
                    case 114:
                        printf("Pravidla\n");
                        break;
                    default:
                        break;
                }
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Nastavení barvy na černou
        SDL_RenderClear(renderer);                      // Vykreslení pozadí (vymazání obrazovky)

        
        //Update




        sprintf(score_text, "Score: %d", score);

        //Musíme si udělt surface - vyrobíme obrázek, který bude v paměti, z toho potom texturu
        SDL_Surface * score_surface = TTF_RenderText_Solid(sans, score_text, RGB_white);
        //Textura - "obrázky na zdech, postavách, které jsou natažené na geometriký model"
        //Vezeme texturu a natáhneme ji na čtverec
        SDL_Texture * score_texture = SDL_CreateTextureFromSurface(renderer, score_surface); //Vzali jsme texturu a překopírovali do grafické paměti
        //Texturu už můžeme zobrazit v rendereru
        SDL_RenderCopy(renderer, score_texture, NULL, &score_rect); //Texturu vyrenderovat do score_rect


        SDL_RenderPresent(renderer);  // Prezentace kreslítka (čáry)



        //Aby to neleakovalo paměť
        SDL_DestroyTexture(score_texture);
        SDL_FreeSurface(score_surface);
    }

    //Ubolnění paměti
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
// gcc main.c -o main  -lSDL2 -lSDL2_ttf
// n - new game 110
// q - quit 113
// r - rules    114