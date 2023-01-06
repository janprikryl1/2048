#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h> //True type fonty
#include <stdbool.h>
#include <assert.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int game_mode = 1;


int main()
{
    printf("Vítejte\n\nStiskněte klávesu n pro novou hru s parametry 4*4, m pro novou hru s parametry 12*8, b pro novou hru s parametry 3*3, pro ukončení programu q, pro zobrazení pravidel r.\n\nHra se ovládá šipkami na klávesnici.\n\n");
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

    bool game = false;
    bool rules = false;
    bool game_over = false;
    bool win = false;

    int score = 0;

    TTF_Init();

    TTF_Font * sans = TTF_OpenFont("AnonymousPro-Regular.ttf", 22);
    assert(sans); //Je-li to NULL, 0, False -> ukončí to program

    SDL_Color RGB_white = {255, 255, 255};
    char score_text[80] = "";
    

    while (!quit) // Projdu všechny události (z klávesnice, myši) a zpracuju je. Poté jdu dál
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT) //Pokud je kliknut křížek, nebo Alt+F4
            {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN) { //Pokud je stisknuto tlačítko
                //printf("%d\n", e.key.keysym.sym);
                score++;

                switch( e.key.keysym.sym ){
                    case SDLK_LEFT:
                        printf("Left\n");
                        rules = false;
                        break;
                    case SDLK_RIGHT:
                        printf("right\n");
                        rules = false;
                        break;
                    case SDLK_UP:
                        printf("up\n");
                        rules = false;
                        break;
                    case SDLK_DOWN:
                        printf("down\n");
                        rules = false;
                        break;
                    case 110:
                        game = true;
                        rules = false;
                        game_mode = 1;
                        score = 0;
                        printf("Nova hra\n");
                        break;
                    case SDLK_m:
                        game = true;
                        rules = false;
                        game_mode = 2;
                        score = 0;
                        break;    
                    case SDLK_b:
                        game = true;
                        rules = false;
                        game_mode = 3;
                        score = 0;
                        break;
                    case 113:
                        printf("Konec\n");
                        quit = true;
                        break;
                    case 114:
                        printf("Pravidla\n");
                        if (rules) {
                            rules = false;
                        } else {
                            rules = true;
                        }
                        break;
                    default:
                        break;
                }
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Nastavení barvy na černou
        SDL_RenderClear(renderer);                      // Vykreslení pozadí (vymazání obrazovky)

        
        //Update
        if (!game) {
            char text_menu[8] = "Nabidka";
            char text_help[68] = "Stisknete klavesu q pro ukonceni programu, r pro zobrazeni pravidel";
            char text_play[60] = "n - nova hra (4*4), m - nova hra (12*8), b - nova hra (3*3)";
            char game_help[36] = "Hra se ovlada sipkami na klavesnici";

            //Musíme si udělt surface - vyrobíme obrázek, který bude v paměti, z toho potom 
            SDL_Rect score_rect = {.x = WINDOW_WIDTH / 2 - 50, .y = 50, .w = 100, .h = 20}; //V tomto obdélníku bude to score
            SDL_Surface * menu_surface = TTF_RenderText_Solid(sans, text_menu, RGB_white);
            //Textura - "obrázky na zdech, postavách, které jsou natažené na geometriký model"
            //Vezeme texturu a natáhneme ji na čtverec
            SDL_Texture * menu_texture = SDL_CreateTextureFromSurface(renderer, menu_surface); //Vzali jsme texturu a překopírovali do grafické paměti
            //Texturu už můžeme zobrazit v rendereru
            SDL_RenderCopy(renderer, menu_texture, NULL, &score_rect); //Texturu vyrenderovat do score_rect


            SDL_Rect help_rect = {.x = 5, .y = 150, .w = 795, .h = 20};
            SDL_Surface * help_surface = TTF_RenderText_Solid(sans, text_help, RGB_white);
            SDL_Texture * help_texture = SDL_CreateTextureFromSurface(renderer, help_surface);
            SDL_RenderCopy(renderer, help_texture, NULL, &help_rect);

            SDL_Rect play_rect = {.x = 20, .y = 250, .w = 760, .h = 20};
            SDL_Surface * play_surface = TTF_RenderText_Solid(sans, text_play, RGB_white);
            SDL_Texture * play_texture = SDL_CreateTextureFromSurface(renderer, play_surface);
            SDL_RenderCopy(renderer, play_texture, NULL, &play_rect);

            SDL_Rect game_help_rect = {.x = WINDOW_WIDTH / 2 - 170, .y = 350, .w = 400, .h = 20};
            SDL_Surface * game_help_surface = TTF_RenderText_Solid(sans, game_help, RGB_white);
            SDL_Texture * game_help_texture = SDL_CreateTextureFromSurface(renderer, game_help_surface);
            SDL_RenderCopy(renderer, game_help_texture, NULL, &game_help_rect);

            SDL_RenderPresent(renderer);  // Prezentace objektu



            //Aby to neleakovalo paměť
            SDL_DestroyTexture(menu_texture);
            SDL_FreeSurface(menu_surface);
            SDL_DestroyTexture(help_texture);
            SDL_FreeSurface(help_surface);
            SDL_DestroyTexture(game_help_texture);
            SDL_FreeSurface(game_help_surface);
            SDL_DestroyTexture(play_texture);
            SDL_FreeSurface(play_surface);
        } else if (rules) {
            char text_menu[9] = "Pravidla";
            char text_help[65] = "Stisknete klavesu q pro ukonceni programu, r pro skryti pravidel";
            char text_play[60] = "n - nova hra (4*4), m - nova hra (12*8), b - nova hra (3*3)";
            char game_help[36] = "Hra se ovlada sipkami na klavesnici";

            //Musíme si udělt surface - vyrobíme obrázek, který bude v paměti, z toho potom 
            SDL_Rect score_rect = {.x = WINDOW_WIDTH / 2 - 50, .y = 50, .w = 100, .h = 20}; //V tomto obdélníku bude to score
            SDL_Surface * menu_surface = TTF_RenderText_Solid(sans, text_menu, RGB_white);
            //Textura - "obrázky na zdech, postavách, které jsou natažené na geometriký model"
            //Vezeme texturu a natáhneme ji na čtverec
            SDL_Texture * menu_texture = SDL_CreateTextureFromSurface(renderer, menu_surface); //Vzali jsme texturu a překopírovali do grafické paměti
            //Texturu už můžeme zobrazit v rendereru
            SDL_RenderCopy(renderer, menu_texture, NULL, &score_rect); //Texturu vyrenderovat do score_rect

            SDL_Rect help_rect = {.x = 5, .y = 150, .w = 795, .h = 20};
            SDL_Surface * help_surface = TTF_RenderText_Solid(sans, text_help, RGB_white);
            SDL_Texture * help_texture = SDL_CreateTextureFromSurface(renderer, help_surface);
            SDL_RenderCopy(renderer, help_texture, NULL, &help_rect);

            SDL_Rect play_rect = {.x = 20, .y = 250, .w = 760, .h = 20};
            SDL_Surface * play_surface = TTF_RenderText_Solid(sans, text_play, RGB_white);
            SDL_Texture * play_texture = SDL_CreateTextureFromSurface(renderer, play_surface);
            SDL_RenderCopy(renderer, play_texture, NULL, &play_rect);

            SDL_Rect game_help_rect = {.x = WINDOW_WIDTH / 2 - 170, .y = 350, .w = 400, .h = 20};
            SDL_Surface * game_help_surface = TTF_RenderText_Solid(sans, game_help, RGB_white);
            SDL_Texture * game_help_texture = SDL_CreateTextureFromSurface(renderer, game_help_surface);
            SDL_RenderCopy(renderer, game_help_texture, NULL, &game_help_rect);

            SDL_RenderPresent(renderer);  // Prezentace objektu



            //Aby to neleakovalo paměť
            SDL_DestroyTexture(menu_texture);
            SDL_FreeSurface(menu_surface);
            SDL_DestroyTexture(help_texture);
            SDL_FreeSurface(help_surface);
            SDL_DestroyTexture(game_help_texture);
            SDL_FreeSurface(game_help_surface);
            SDL_DestroyTexture(play_texture);
            SDL_FreeSurface(play_surface);
        } else if (game && !rules && (game_mode == 1)){ //Hra 4*4
            //Nápis se score
            SDL_Rect score_rect = {.x = WINDOW_WIDTH / 2 - 50, .y = 30, .w = 100, .h = 20}; //V tomto obdélníku bude to score
            sprintf(score_text, "Score: %d", score);
            //Musíme si udělt surface - vyrobíme obrázek, který bude v paměti, z toho potom texturu
            SDL_Surface * score_surface = TTF_RenderText_Solid(sans, score_text, RGB_white);
            //Textura - "obrázky na zdech, postavách, které jsou natažené na geometriký model"
            //Vezeme texturu a natáhneme ji na čtverec
            SDL_Texture * score_texture = SDL_CreateTextureFromSurface(renderer, score_surface); //Vzali jsme texturu a překopírovali do grafické paměti
            //Texturu už můžeme zobrazit v rendereru
            SDL_RenderCopy(renderer, score_texture, NULL, &score_rect); //Texturu vyrenderovat do score_rect

            //Čtverečky s čísly           
            //0
            SDL_Rect square_rect_0 = {.x = 20, .y = 70, .w = 137, .h = 110};
            SDL_Surface * square_surface_0 = TTF_RenderText_Solid(sans, "202", RGB_white);
            SDL_Texture * square_texture_0 = SDL_CreateTextureFromSurface(renderer, square_surface_0);
            SDL_RenderCopy(renderer, square_texture_0, NULL, &square_rect_0);
            
            //1
            SDL_Rect square_rect_1 = {.x = 220, .y = 70, .w = 137, .h = 110};
            SDL_Surface * square_surface_1 = TTF_RenderText_Solid(sans, "20", RGB_white);
            SDL_Texture * square_texture_1 = SDL_CreateTextureFromSurface(renderer, square_surface_1);
            SDL_RenderCopy(renderer, square_texture_1, NULL, &square_rect_1);
            
            //2
            SDL_Rect square_rect_2 = {.x = 420, .y = 70, .w = 137, .h = 110};
            SDL_Surface * square_surface_2 = TTF_RenderText_Solid(sans, "20", RGB_white);
            SDL_Texture * square_texture_2 = SDL_CreateTextureFromSurface(renderer, square_surface_2);
            SDL_RenderCopy(renderer, square_texture_2, NULL, &square_rect_2);
            
            //3
            SDL_Rect square_rect_3 = {.x = 620, .y = 70, .w = 137, .h = 110};
            SDL_Surface * square_surface_3 = TTF_RenderText_Solid(sans, "20", RGB_white);
            SDL_Texture * square_texture_3 = SDL_CreateTextureFromSurface(renderer, square_surface_3);
            SDL_RenderCopy(renderer, square_texture_3, NULL, &square_rect_3);
            
            //4
            SDL_Rect square_rect_4 = {.x = 20, .y = 210, .w = 137, .h = 110};
            SDL_Surface * square_surface_4 = TTF_RenderText_Solid(sans, "20", RGB_white);
            SDL_Texture * square_texture_4 = SDL_CreateTextureFromSurface(renderer, square_surface_4);
            SDL_RenderCopy(renderer, square_texture_4, NULL, &square_rect_4);

            //5
            SDL_Rect square_rect_5 = {.x = 220, .y = 210, .w = 137, .h = 110};
            SDL_Surface * square_surface_5 = TTF_RenderText_Solid(sans, "20", RGB_white);
            SDL_Texture * square_texture_5 = SDL_CreateTextureFromSurface(renderer, square_surface_5);
            SDL_RenderCopy(renderer, square_texture_5, NULL, &square_rect_5);

            //6
            SDL_Rect square_rect_6 = {.x = 420, .y = 210, .w = 137, .h = 110};
            SDL_Surface * square_surface_6 = TTF_RenderText_Solid(sans, "20", RGB_white);
            SDL_Texture * square_texture_6 = SDL_CreateTextureFromSurface(renderer, square_surface_6);
            SDL_RenderCopy(renderer, square_texture_6, NULL, &square_rect_6);

            //7
            SDL_Rect square_rect_7 = {.x = 620, .y = 210, .w = 137, .h = 110};
            SDL_Surface * square_surface_7 = TTF_RenderText_Solid(sans, "20", RGB_white);
            SDL_Texture * square_texture_7 = SDL_CreateTextureFromSurface(renderer, square_surface_7);
            SDL_RenderCopy(renderer, square_texture_7, NULL, &square_rect_7);

            //8
            SDL_Rect square_rect_8 = {.x = 20, .y = 355, .w = 137, .h = 110};
            SDL_Surface * square_surface_8 = TTF_RenderText_Solid(sans, "20", RGB_white);
            SDL_Texture * square_texture_8 = SDL_CreateTextureFromSurface(renderer, square_surface_8);
            SDL_RenderCopy(renderer, square_texture_8, NULL, &square_rect_8);

            //9
            SDL_Rect square_rect_9 = {.x = 220, .y = 355, .w = 137, .h = 110};
            SDL_Surface * square_surface_9 = TTF_RenderText_Solid(sans, "20", RGB_white);
            SDL_Texture * square_texture_9 = SDL_CreateTextureFromSurface(renderer, square_surface_9);
            SDL_RenderCopy(renderer, square_texture_9, NULL, &square_rect_9);
            
            //10
            SDL_Rect square_rect_10 = {.x = 420, .y = 355, .w = 137, .h = 110};
            SDL_Surface * square_surface_10 = TTF_RenderText_Solid(sans, "20", RGB_white);
            SDL_Texture * square_texture_10 = SDL_CreateTextureFromSurface(renderer, square_surface_10);
            SDL_RenderCopy(renderer, square_texture_10, NULL, &square_rect_10);

            //11
            SDL_Rect square_rect_11 = {.x = 620, .y = 355, .w = 137, .h = 110};
            SDL_Surface * square_surface_11 = TTF_RenderText_Solid(sans, "20", RGB_white);
            SDL_Texture * square_texture_11 = SDL_CreateTextureFromSurface(renderer, square_surface_11);
            SDL_RenderCopy(renderer, square_texture_11, NULL, &square_rect_11);

            //12
            SDL_Rect square_rect_12 = {.x = 20, .y = 480, .w = 137, .h = 110};
            SDL_Surface * square_surface_12 = TTF_RenderText_Solid(sans, "20", RGB_white);
            SDL_Texture * square_texture_12 = SDL_CreateTextureFromSurface(renderer, square_surface_12);
            SDL_RenderCopy(renderer, square_texture_12, NULL, &square_rect_12);
            
            //13
            SDL_Rect square_rect_13 = {.x = 220, .y = 480, .w = 137, .h = 110};
            SDL_Surface * square_surface_13 = TTF_RenderText_Solid(sans, "20", RGB_white);
            SDL_Texture * square_texture_13 = SDL_CreateTextureFromSurface(renderer, square_surface_13);
            SDL_RenderCopy(renderer, square_texture_13, NULL, &square_rect_13);

            //14
            SDL_Rect square_rect_14 = {.x = 420, .y = 480, .w = 137, .h = 110};
            SDL_Surface * square_surface_14 = TTF_RenderText_Solid(sans, "20", RGB_white);
            SDL_Texture * square_texture_14 = SDL_CreateTextureFromSurface(renderer, square_surface_14);
            SDL_RenderCopy(renderer, square_texture_14, NULL, &square_rect_14);

            //15
            SDL_Rect square_rect_15 = {.x = 620, .y = 480, .w = 137, .h = 110};
            SDL_Surface * square_surface_15 = TTF_RenderText_Solid(sans, "20", RGB_white);
            SDL_Texture * square_texture_15 = SDL_CreateTextureFromSurface(renderer, square_surface_15);
            SDL_RenderCopy(renderer, square_texture_15, NULL, &square_rect_15);




            SDL_RenderPresent(renderer);  // Prezentace objektu


            //Aby to neleakovalo paměť
            SDL_DestroyTexture(score_texture);
            SDL_FreeSurface(score_surface);


            SDL_DestroyTexture(square_texture_0);
            SDL_FreeSurface(square_surface_0);
            SDL_DestroyTexture(square_texture_1);
            SDL_FreeSurface(square_surface_1);
            SDL_DestroyTexture(square_texture_2);
            SDL_FreeSurface(square_surface_2);
            SDL_DestroyTexture(square_texture_3);
            SDL_FreeSurface(square_surface_3);
            SDL_DestroyTexture(square_texture_4);
            SDL_FreeSurface(square_surface_4);
            SDL_DestroyTexture(square_texture_5);
            SDL_FreeSurface(square_surface_5);
            SDL_DestroyTexture(square_texture_6);
            SDL_FreeSurface(square_surface_6);
            SDL_DestroyTexture(square_texture_7);
            SDL_FreeSurface(square_surface_7);
            SDL_DestroyTexture(square_texture_8);
            SDL_FreeSurface(square_surface_8);
            SDL_DestroyTexture(square_texture_9);
            SDL_FreeSurface(square_surface_9);
            SDL_DestroyTexture(square_texture_10);
            SDL_FreeSurface(square_surface_10);
            SDL_DestroyTexture(square_texture_11);
            SDL_FreeSurface(square_surface_11);
            SDL_DestroyTexture(square_texture_12);
            SDL_FreeSurface(square_surface_12);
            SDL_DestroyTexture(square_texture_13);
            SDL_FreeSurface(square_surface_13);
            SDL_DestroyTexture(square_texture_14);
            SDL_FreeSurface(square_surface_14);
            SDL_DestroyTexture(square_texture_15);
            SDL_FreeSurface(square_surface_15);

        } else if (game && !rules && (game_mode == 2)) { //Hra 12*8
            
        } else if (game && !rules && (game_mode == 3)) { //Hra 3*3

        } else if (game_over) {
            char text_menu[13] = "Hra skoncila";
            char text_help[65] = "Stisknete klavesu q pro ukonceni programu, r pro skryti pravidel";
            char text_play[60] = "n - nova hra (4*4), m - nova hra (12*8), b - nova hra (3*3)";
            char game_help[36] = "Hra se ovlada sipkami na klavesnici";

            //Musíme si udělt surface - vyrobíme obrázek, který bude v paměti, z toho potom 
            SDL_Rect score_rect = {.x = WINDOW_WIDTH / 2 - 50, .y = 50, .w = 100, .h = 20}; //V tomto obdélníku bude to score
            SDL_Surface * menu_surface = TTF_RenderText_Solid(sans, text_menu, RGB_white);
            //Textura - "obrázky na zdech, postavách, které jsou natažené na geometriký model"
            //Vezeme texturu a natáhneme ji na čtverec
            SDL_Texture * menu_texture = SDL_CreateTextureFromSurface(renderer, menu_surface); //Vzali jsme texturu a překopírovali do grafické paměti
            //Texturu už můžeme zobrazit v rendereru
            SDL_RenderCopy(renderer, menu_texture, NULL, &score_rect); //Texturu vyrenderovat do score_rect

            SDL_Rect help_rect = {.x = 5, .y = 150, .w = 795, .h = 20};
            SDL_Surface * help_surface = TTF_RenderText_Solid(sans, text_help, RGB_white);
            SDL_Texture * help_texture = SDL_CreateTextureFromSurface(renderer, help_surface);
            SDL_RenderCopy(renderer, help_texture, NULL, &help_rect);

            SDL_Rect play_rect = {.x = 20, .y = 250, .w = 760, .h = 20};
            SDL_Surface * play_surface = TTF_RenderText_Solid(sans, text_play, RGB_white);
            SDL_Texture * play_texture = SDL_CreateTextureFromSurface(renderer, play_surface);
            SDL_RenderCopy(renderer, play_texture, NULL, &play_rect);

            SDL_Rect game_help_rect = {.x = WINDOW_WIDTH / 2 - 170, .y = 350, .w = 400, .h = 20};
            SDL_Surface * game_help_surface = TTF_RenderText_Solid(sans, game_help, RGB_white);
            SDL_Texture * game_help_texture = SDL_CreateTextureFromSurface(renderer, game_help_surface);
            SDL_RenderCopy(renderer, game_help_texture, NULL, &game_help_rect);

            SDL_RenderPresent(renderer);  // Prezentace objektu



            //Aby to neleakovalo paměť
            SDL_DestroyTexture(menu_texture);
            SDL_FreeSurface(menu_surface);
            SDL_DestroyTexture(help_texture);
            SDL_FreeSurface(help_surface);
            SDL_DestroyTexture(game_help_texture);
            SDL_FreeSurface(game_help_surface);
            SDL_DestroyTexture(play_texture);
            SDL_FreeSurface(play_surface);
        } else if (win) {
            char text_menu[13] = "Vyhrali jste";
            char text_help[65] = "Stisknete klavesu q pro ukonceni programu, r pro skryti pravidel";
            char text_play[60] = "n - nova hra (4*4), m - nova hra (12*8), b - nova hra (3*3)";
            char game_help[36] = "Hra se ovlada sipkami na klavesnici";

            //Musíme si udělt surface - vyrobíme obrázek, který bude v paměti, z toho potom 
            SDL_Rect score_rect = {.x = WINDOW_WIDTH / 2 - 50, .y = 50, .w = 100, .h = 20}; //V tomto obdélníku bude to score
            SDL_Surface * menu_surface = TTF_RenderText_Solid(sans, text_menu, RGB_white);
            //Textura - "obrázky na zdech, postavách, které jsou natažené na geometriký model"
            //Vezeme texturu a natáhneme ji na čtverec
            SDL_Texture * menu_texture = SDL_CreateTextureFromSurface(renderer, menu_surface); //Vzali jsme texturu a překopírovali do grafické paměti
            //Texturu už můžeme zobrazit v rendereru
            SDL_RenderCopy(renderer, menu_texture, NULL, &score_rect); //Texturu vyrenderovat do score_rect

            SDL_Rect help_rect = {.x = 5, .y = 150, .w = 795, .h = 20};
            SDL_Surface * help_surface = TTF_RenderText_Solid(sans, text_help, RGB_white);
            SDL_Texture * help_texture = SDL_CreateTextureFromSurface(renderer, help_surface);
            SDL_RenderCopy(renderer, help_texture, NULL, &help_rect);

            SDL_Rect play_rect = {.x = 20, .y = 250, .w = 760, .h = 20};
            SDL_Surface * play_surface = TTF_RenderText_Solid(sans, text_play, RGB_white);
            SDL_Texture * play_texture = SDL_CreateTextureFromSurface(renderer, play_surface);
            SDL_RenderCopy(renderer, play_texture, NULL, &play_rect);

            SDL_Rect game_help_rect = {.x = WINDOW_WIDTH / 2 - 170, .y = 350, .w = 400, .h = 20};
            SDL_Surface * game_help_surface = TTF_RenderText_Solid(sans, game_help, RGB_white);
            SDL_Texture * game_help_texture = SDL_CreateTextureFromSurface(renderer, game_help_surface);
            SDL_RenderCopy(renderer, game_help_texture, NULL, &game_help_rect);

            SDL_RenderPresent(renderer);  // Prezentace objektu



            //Aby to neleakovalo paměť
            SDL_DestroyTexture(menu_texture);
            SDL_FreeSurface(menu_surface);
            SDL_DestroyTexture(help_texture);
            SDL_FreeSurface(help_surface);
            SDL_DestroyTexture(game_help_texture);
            SDL_FreeSurface(game_help_surface);
            SDL_DestroyTexture(play_texture);
            SDL_FreeSurface(play_surface);
        }
        
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