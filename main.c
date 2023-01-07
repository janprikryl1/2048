#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h> //True type fonty
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

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

    SDL_Color RGB_yellow = {241, 174, 27};
    SDL_Color RGB_red = {255, 0, 0};
    SDL_Color RGB_green = {0, 255, 0};

    srand(time(0)); //Inicializace random čísel podle času v systému
    //Pole pro herná režim 1
    int pole_1[4][4];
    //Inicializace herního režimu 2
    int pole_2[8][12];
    //Inicializace herního režimu 3
    int pole_3[3][3];

    


    while (!quit) // Projdu všechny události (z klávesnice, myši) a zpracuju je. Poté jdu dál
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT) //Pokud je kliknut křížek, nebo Alt+F4
            {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN) { //Pokud je stisknuto tlačítko
                score++;

                switch( e.key.keysym.sym ){
                    case SDLK_LEFT:
                        printf("Left\n");
                        if (game_mode == 1) {
                            for (int r = 0; r < 4; r++)
                            {
                                if (pole_1[r][0] && (pole_1[r][0] == pole_1[r][1])){
                                    if (pole_1[r][0]*2 == 2048) {
                                        win = true;
                                        game = false;
                                        break;
                                    }                                    
                                    pole_1[r][0] = pole_1[r][0]*2;
                                    pole_1[r][1] = 0;
                                }
                                if (pole_1[r][1] && (pole_1[r][1] == pole_1[r][2])) {
                                    if (pole_1[r][1] * 2 == 2048) {
                                        win = true;
                                        game = false;
                                        break;
                                    }
                                    pole_1[r][1] = pole_1[r][1] * 2;
                                    pole_1[r][2] = 0;
                                }
                                if (pole_1[r][2] && (pole_1[r][2] == pole_1[r][3])) {
                                    if (pole_1[r][2] * 2 == 2048) {
                                        win = true;
                                        game = false;
                                        break;
                                    }
                                    pole_1[r][2] = pole_1[r][2] * 2;
                                    pole_1[r][3] = 0;
                                }                                

                                for (int i = 0; i < 3; i++)
                                {
                                    if (pole_1[r][0] == 0){
                                        pole_1[r][0] = pole_1[r][1];
                                        pole_1[r][1] = pole_1[r][2];    
                                        pole_1[r][2] = pole_1[r][3];
                                        pole_1[r][3] = 0;
                                    }
                                    else if (pole_1[r][1] == 0) {
                                        pole_1[r][1] = pole_1[r][2];    
                                        pole_1[r][2] = pole_1[r][3];
                                        pole_1[r][3] = 0;
                                    }  
                                    else if (pole_1[r][2] == 0) {
                                        pole_1[r][2] = pole_1[r][3]; 
                                        pole_1[r][3] = 0;  
                                    }
                                    else if (pole_1[r][3] == 0) {
                                        pole_1[r][3] = 0;
                                    }
                                }                            
                            }
                            if(pole_1[0][0] && pole_1[0][1] && pole_1[0][2] && pole_1[0][3] && pole_1[1][0] && pole_1[1][1] && pole_1[1][2] && pole_1[1][3] && pole_1[2][0] && pole_1[2][1] && pole_1[2][2] && pole_1[2][3] && pole_1[3][0] && pole_1[3][1] && pole_1[3][2] && pole_1[3][3]) {
                                game_over = true;
                                game = false;                            
                                break;
                            }
                            int new_x = rand() % 4 + 0;
                            int new_y = rand() % 4 + 0;
                            while (pole_1[new_x][new_y] != 0) {
                                new_x = rand() % 4 + 0;
                                new_y = rand() % 4 + 0;
                            }
                            if (rand() % 2 == 1) {
                                pole_1[new_x][new_y] = 2;
                            } else {
                                pole_1[new_x][new_y] = 4;
                            }
                        }                        
                        break;
                    case SDLK_RIGHT:
                        printf("right\n");        
                        if (game_mode == 1) {
                            for (int r = 0; r < 4; r++)
                            {
                               if (pole_1[r][2] && (pole_1[r][2] == pole_1[r][3])) {
                                    if (pole_1[r][3] * 2 == 2048) {
                                        win = true;
                                        game = false;
                                        break;
                                    }
                                    pole_1[r][3] = pole_1[r][3] * 2;
                                    pole_1[r][2] = 0;
                                }     
                                if (pole_1[r][1] && (pole_1[r][1] == pole_1[r][2])) {
                                    if (pole_1[r][2] * 2 == 2048) {
                                        win = true;
                                        game = false;
                                        break;
                                    }
                                    pole_1[r][2] = pole_1[r][2] * 2;
                                    pole_1[r][1] = 0;
                                }       
                                if (pole_1[r][0] && (pole_1[r][0] == pole_1[r][1])){
                                    if (pole_1[r][1]*2 == 2048) {
                                        win = true;
                                        game = false;
                                        break;
                                    }                                
                                    pole_1[r][1] = pole_1[r][1]*2;
                                    pole_1[r][0] = 0;
                                }                    

                                for (int i = 0; i < 3; i++)
                                {
                                    if (pole_1[r][3] == 0){
                                        pole_1[r][3] = pole_1[r][2];
                                        pole_1[r][2] = pole_1[r][1];    
                                        pole_1[r][1] = pole_1[r][0];
                                        pole_1[r][0] = 0;
                                    }
                                    else if (pole_1[r][2] == 0) {
                                        pole_1[r][2] = pole_1[r][1];    
                                        pole_1[r][1] = pole_1[r][0];
                                        pole_1[r][0] = 0;
                                    }  
                                    else if (pole_1[r][1] == 0) {
                                        pole_1[r][1] = pole_1[r][0]; 
                                        pole_1[r][0] = 0;  
                                    }
                                    else if (pole_1[r][0] == 0) {
                                        pole_1[r][0] = 0;
                                    }
                                }
                            }
                            if(pole_1[0][0] && pole_1[0][1] && pole_1[0][2] && pole_1[0][3] && pole_1[1][0] && pole_1[1][1] && pole_1[1][2] && pole_1[1][3] && pole_1[2][0] && pole_1[2][1] && pole_1[2][2] && pole_1[2][3] && pole_1[3][0] && pole_1[3][1] && pole_1[3][2] && pole_1[3][3]) {
                                game_over = true;
                                game = false;                            
                                break;
                            }
                            int new_x = rand() % 4 + 0;
                            int new_y = rand() % 4 + 0;
                            while (pole_1[new_x][new_y] != 0) {
                                new_x = rand() % 4 + 0;
                                new_y = rand() % 4 + 0;
                            }
                            if (rand() % 2 == 1) {
                                pole_1[new_x][new_y] = 2;
                            } else {
                                pole_1[new_x][new_y] = 4;
                            }        
                        }                  
                        break;
                    case SDLK_DOWN:                        
                        if (game_mode == 1) {
                            for (int r = 0; r < 4; r++)
                            {
                               if (pole_1[2][r] && (pole_1[2][r] == pole_1[3][r])) {
                                    if (pole_1[3][r] * 2 == 2048) {
                                        win = true;
                                        game = false;
                                        break;
                                    }
                                    pole_1[3][r] = pole_1[3][r] * 2;
                                    pole_1[2][r] = 0;
                                }     
                                if (pole_1[1][r] && (pole_1[1][r] == pole_1[2][r])) {
                                    if (pole_1[2][r] * 2 == 2048) {
                                        win = true;
                                        game = false;
                                        break;
                                    }
                                    pole_1[2][r] = pole_1[2][r] * 2;
                                    pole_1[1][r] = 0;
                                }       
                                if (pole_1[0][r] && (pole_1[0][r] == pole_1[1][r])){
                                    if (pole_1[1][r]*2 == 2048) {
                                        win = true;
                                        game = false;
                                        break;
                                    }                                
                                    pole_1[1][r] = pole_1[1][r]*2;
                                    pole_1[0][r] = 0;
                                }                    

                                for (int i = 0; i < 3; i++)
                                {
                                    if (pole_1[3][r] == 0){
                                        pole_1[3][r] = pole_1[2][r];
                                        pole_1[2][r] = pole_1[1][r];    
                                        pole_1[1][r] = pole_1[0][r];
                                        pole_1[0][r] = 0;
                                    }
                                    else if (pole_1[2][r] == 0) {
                                        pole_1[2][r] = pole_1[1][r];    
                                        pole_1[1][r] = pole_1[0][r];
                                        pole_1[0][r] = 0;
                                    }  
                                    else if (pole_1[1][r] == 0) {
                                        pole_1[1][r] = pole_1[0][r]; 
                                        pole_1[0][r] = 0;  
                                    }
                                    else if (pole_1[0][r] == 0) {
                                        pole_1[0][r] = 0;
                                    }
                                }
                            }
                            if(pole_1[0][0] && pole_1[0][1] && pole_1[0][2] && pole_1[0][3] && pole_1[1][0] && pole_1[1][1] && pole_1[1][2] && pole_1[1][3] && pole_1[2][0] && pole_1[2][1] && pole_1[2][2] && pole_1[2][3] && pole_1[3][0] && pole_1[3][1] && pole_1[3][2] && pole_1[3][3]) {
                                game_over = true;
                                game = false;                            
                                break;
                            }
                            int new_x = rand() % 4 + 0;
                            int new_y = rand() % 4 + 0;
                            while (pole_1[new_x][new_y] != 0) {
                                new_x = rand() % 4 + 0;
                                new_y = rand() % 4 + 0;
                            }
                            if (rand() % 2 == 1) {
                                pole_1[new_x][new_y] = 2;
                            } else {
                                pole_1[new_x][new_y] = 4;
                            }                       
                        }                   
                        break;
                    case SDLK_UP:
                        if (game_mode == 1) {
                            for (int r = 0; r < 4; r++)
                            {
                                if (pole_1[0][r] && (pole_1[0][r] == pole_1[1][r])){
                                    if (pole_1[0][r]*2 == 2048) {
                                        win = true;
                                        game = false;
                                        break;
                                    }                                    
                                    pole_1[0][r] = pole_1[0][r]*2;
                                    pole_1[1][r] = 0;
                                }
                                if (pole_1[1][r] && (pole_1[1][r] == pole_1[2][r])) {
                                    if (pole_1[1][r] * 2 == 2048) {
                                        win = true;
                                        game = false;
                                        break;
                                    }
                                    pole_1[1][r] = pole_1[1][r] * 2;
                                    pole_1[2][r] = 0;
                                }
                                if (pole_1[2][r] && (pole_1[2][r] == pole_1[3][r])) {
                                    if (pole_1[2][r] * 2 == 2048) {
                                        win = true;
                                        game = false;
                                        break;
                                    }
                                    pole_1[2][r] = pole_1[2][r] * 2;
                                    pole_1[3][r] = 0;
                                }                                

                                for (int i = 0; i < 3; i++)
                                {
                                    if (pole_1[0][r] == 0){
                                        pole_1[0][r] = pole_1[1][r];
                                        pole_1[1][r] = pole_1[2][r];    
                                        pole_1[2][r] = pole_1[3][r];
                                        pole_1[3][r] = 0;
                                    }
                                    else if (pole_1[1][r] == 0) {
                                        pole_1[1][r] = pole_1[2][r];    
                                        pole_1[2][r] = pole_1[3][r];
                                        pole_1[3][r] = 0;
                                    }  
                                    else if (pole_1[2][r] == 0) {
                                        pole_1[2][r] = pole_1[3][r]; 
                                        pole_1[3][r] = 0;  
                                    }
                                    else if (pole_1[3][r] == 0) {
                                        pole_1[3][r] = 0;
                                    }                              
                                }
                            }
                            if(pole_1[0][0] && pole_1[0][1] && pole_1[0][2] && pole_1[0][3] && pole_1[1][0] && pole_1[1][1] && pole_1[1][2] && pole_1[1][3] && pole_1[2][0] && pole_1[2][1] && pole_1[2][2] && pole_1[2][3] && pole_1[3][0] && pole_1[3][1] && pole_1[3][2] && pole_1[3][3]) {
                                game_over = true;
                                game = false;                            
                                break;
                            }
                            int new_x = rand() % 4 + 0;
                            int new_y = rand() % 4 + 0;
                            while (pole_1[new_x][new_y] != 0) {
                                new_x = rand() % 4 + 0;
                                new_y = rand() % 4 + 0;
                            }
                            if (rand() % 2 == 1) {
                                pole_1[new_x][new_y] = 2;
                            } else {
                                pole_1[new_x][new_y] = 4;
                            }
                        }
                        break;
                    case 110:
                        game = true;
                        rules = false;
                        game_mode = 1;
                        score = 0;
                        //Pole pro herná režim 1
                        for (int i = 0; i < 4; i++)
                        {
                            for (int x = 0; x < 4; x++)
                            {
                                pole_1[i][x] = 0;
                            }
                        }
                        if (rand() % 2 == 1) {
                            pole_1[rand() % 4 + 0][rand() % 4 + 0] = 2;
                        } else {
                            pole_1[rand() % 4 + 0][rand() % 4 + 0] = 4;
                        }
                        break;
                    case SDLK_m:
                        game = true;
                        rules = false;
                        game_mode = 2;
                        score = 0;
                        for (int i = 0; i < 8; i++)
                        {
                            for (int x = 0; x < 12; x++)
                            {
                                pole_2[i][x] = 0;
                            }
                        }
                        if (rand() % 2 == 1) {
                            pole_2[rand() % 8 + 0][rand() % 12 + 0] = 2;                        
                        } else {
                            pole_2[rand() % 8 + 0][rand() % 12 + 0] = 4;                        
                        }
                        break;    
                    case SDLK_b:
                        game = true;
                        rules = false;
                        game_mode = 3;
                        score = 0;
                        for (int i = 0; i < 3; i++)
                        {
                            for (int x = 0; x < 3; x++)
                            {
                                pole_3[i][x] = 0;
                            }
                        }
                        if (rand() % 2 == 1) {
                            pole_3[rand() % 3 + 0][rand() % 3 + 0] = 2;
                        } else {
                            pole_3[rand() % 3 + 0][rand() % 3 + 0] = 4;
                        }
                        break;
                    case 113:                        
                        quit = true;
                        break;
                    case 114:                        
                        if (rules) {
                            rules = false;
                        } else {
                            rules = true;
                        }
                        score--;
                        break;
                    default:
                        break;
                }
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Nastavení barvy na černou
        SDL_RenderClear(renderer);                      // Vykreslení pozadí (vymazání obrazovky)

        
        //Update
        if (!game && !game_over) {
            char text_menu[8] = "Nabidka";
            char text_help[68] = "Stisknete klavesu q pro ukonceni programu, r pro zobrazeni pravidel";
            char text_play[60] = "n - nova hra (4*4), m - nova hra (12*8), b - nova hra (3*3)";
            char game_help[36] = "Hra se ovlada sipkami na klavesnici";
            char score_info[23] = "Score udava pocet tahu";

            //Musíme si udělt surface - vyrobíme obrázek, který bude v paměti, z toho potom 
            SDL_Rect score_rect = {.x = WINDOW_WIDTH / 2 - 50, .y = 50, .w = 100, .h = 20}; //V tomto obdélníku bude to score
            SDL_Surface * menu_surface = TTF_RenderText_Solid(sans, text_menu, RGB_yellow);
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
            SDL_Surface * game_help_surface = TTF_RenderText_Solid(sans, game_help, RGB_red);
            SDL_Texture * game_help_texture = SDL_CreateTextureFromSurface(renderer, game_help_surface);
            SDL_RenderCopy(renderer, game_help_texture, NULL, &game_help_rect);

            SDL_Rect score_info_rect = {.x = WINDOW_WIDTH / 2 - 170, .y = 450, .w = 380, .h = 20};
            SDL_Surface * score_info_surface = TTF_RenderText_Solid(sans, score_info, RGB_white);
            SDL_Texture * score_info_texture = SDL_CreateTextureFromSurface(renderer, score_info_surface);
            SDL_RenderCopy(renderer, score_info_texture, NULL, &score_info_rect);

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
            SDL_DestroyTexture(score_info_texture);
            SDL_FreeSurface(score_info_surface);
        } else if (rules) {
            char text_menu[9] = "Pravidla";
            char text_help[65] = "Stisknete klavesu q pro ukonceni programu, r pro skryti pravidel";
            char text_play[60] = "n - nova hra (4*4), m - nova hra (12*8), b - nova hra (3*3)";
            char game_help[36] = "Hra se ovlada sipkami na klavesnici";
            char score_info[23] = "Score udava pocet tahu";

            //Musíme si udělt surface - vyrobíme obrázek, který bude v paměti, z toho potom 
            SDL_Rect score_rect = {.x = WINDOW_WIDTH / 2 - 50, .y = 50, .w = 100, .h = 20}; //V tomto obdélníku bude to score
            SDL_Surface * menu_surface = TTF_RenderText_Solid(sans, text_menu, RGB_yellow);
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
            SDL_Surface * game_help_surface = TTF_RenderText_Solid(sans, game_help, RGB_red);
            SDL_Texture * game_help_texture = SDL_CreateTextureFromSurface(renderer, game_help_surface);
            SDL_RenderCopy(renderer, game_help_texture, NULL, &game_help_rect);

            SDL_Rect score_info_rect = {.x = WINDOW_WIDTH / 2 - 170, .y = 450, .w = 380, .h = 20};
            SDL_Surface * score_info_surface = TTF_RenderText_Solid(sans, score_info, RGB_white);
            SDL_Texture * score_info_texture = SDL_CreateTextureFromSurface(renderer, score_info_surface);
            SDL_RenderCopy(renderer, score_info_texture, NULL, &score_info_rect);

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
            SDL_DestroyTexture(score_info_texture);
            SDL_FreeSurface(score_info_surface);
        } else if (game && !rules && (game_mode == 1)){ //Hra 4*4
            //Nápis se score
            SDL_Rect score_rect = {.x = WINDOW_WIDTH / 2 - 50, .y = 30, .w = 100, .h = 20}; //V tomto obdélníku bude to score
            sprintf(score_text, "Score: %d", score);
            //Musíme si udělt surface - vyrobíme obrázek, který bude v paměti, z toho potom texturu
            SDL_Surface * score_surface = TTF_RenderText_Solid(sans, score_text, RGB_green);
            //Textura - "obrázky na zdech, postavách, které jsou natažené na geometriký model"
            //Vezeme texturu a natáhneme ji na čtverec
            SDL_Texture * score_texture = SDL_CreateTextureFromSurface(renderer, score_surface); //Vzali jsme texturu a překopírovali do grafické paměti
            //Texturu už můžeme zobrazit v rendereru
            SDL_RenderCopy(renderer, score_texture, NULL, &score_rect); //Texturu vyrenderovat do score_rect

            //Čtverečky s čísly           
            //0
            SDL_Rect square_rect_0 = {.x = 20, .y = 70, .w = 137, .h = 110};
            SDL_Surface * square_surface_0;
            if (pole_1[0][0]) {
                char ch[5];
                sprintf(ch, "%d", pole_1[0][0]);
                square_surface_0 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_0 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_0 = SDL_CreateTextureFromSurface(renderer, square_surface_0);
            SDL_RenderCopy(renderer, square_texture_0, NULL, &square_rect_0);
            
            //1
            SDL_Rect square_rect_1 = {.x = 220, .y = 70, .w = 137, .h = 110};
            SDL_Surface * square_surface_1;
            if (pole_1[0][1]) {
                char ch[5];
                sprintf(ch, "%d", pole_1[0][1]);
                square_surface_1 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_1 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_1 = SDL_CreateTextureFromSurface(renderer, square_surface_1);
            SDL_RenderCopy(renderer, square_texture_1, NULL, &square_rect_1);
            
            //2
            SDL_Rect square_rect_2 = {.x = 420, .y = 70, .w = 137, .h = 110};
            SDL_Surface * square_surface_2;
            if (pole_1[0][2]) {
                char ch[5];
                sprintf(ch, "%d", pole_1[0][2]);
                square_surface_2 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_2 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_2 = SDL_CreateTextureFromSurface(renderer, square_surface_2);
            SDL_RenderCopy(renderer, square_texture_2, NULL, &square_rect_2);
            
            //3
            SDL_Rect square_rect_3 = {.x = 620, .y = 70, .w = 137, .h = 110};
            SDL_Surface * square_surface_3;
            if (pole_1[0][3]) {
                char ch[5];
                sprintf(ch, "%d", pole_1[0][3]);
                square_surface_3 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_3 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_3 = SDL_CreateTextureFromSurface(renderer, square_surface_3);
            SDL_RenderCopy(renderer, square_texture_3, NULL, &square_rect_3);
            
            //4
            SDL_Rect square_rect_4 = {.x = 20, .y = 210, .w = 137, .h = 110};
            SDL_Surface * square_surface_4;
            if (pole_1[1][0]) {
                char ch[5];
                sprintf(ch, "%d", pole_1[1][0]);
                square_surface_4 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_4 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_4 = SDL_CreateTextureFromSurface(renderer, square_surface_4);
            SDL_RenderCopy(renderer, square_texture_4, NULL, &square_rect_4);

            //5
            SDL_Rect square_rect_5 = {.x = 220, .y = 210, .w = 137, .h = 110};
            SDL_Surface * square_surface_5;
            if (pole_1[1][1]) {
                char ch[5];
                sprintf(ch, "%d", pole_1[1][1]);
                square_surface_5 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_5 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_5 = SDL_CreateTextureFromSurface(renderer, square_surface_5);
            SDL_RenderCopy(renderer, square_texture_5, NULL, &square_rect_5);

            //6
            SDL_Rect square_rect_6 = {.x = 420, .y = 210, .w = 137, .h = 110};
            SDL_Surface * square_surface_6;
            if (pole_1[1][2]) {
                char ch[5];
                sprintf(ch, "%d", pole_1[1][2]);
                square_surface_6 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_6 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_6 = SDL_CreateTextureFromSurface(renderer, square_surface_6);
            SDL_RenderCopy(renderer, square_texture_6, NULL, &square_rect_6);

            //7
            SDL_Rect square_rect_7 = {.x = 620, .y = 210, .w = 137, .h = 110};
            SDL_Surface * square_surface_7;
            if (pole_1[1][3]) {
                char ch[5];
                sprintf(ch, "%d", pole_1[1][3]);
                square_surface_7 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_7 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_7 = SDL_CreateTextureFromSurface(renderer, square_surface_7);
            SDL_RenderCopy(renderer, square_texture_7, NULL, &square_rect_7);

            //8
            SDL_Rect square_rect_8 = {.x = 20, .y = 355, .w = 137, .h = 110};
            SDL_Surface * square_surface_8;
            if (pole_1[2][0]) {
                char ch[5];
                sprintf(ch, "%d", pole_1[2][0]);
                square_surface_8 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_8 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_8 = SDL_CreateTextureFromSurface(renderer, square_surface_8);
            SDL_RenderCopy(renderer, square_texture_8, NULL, &square_rect_8);

            //9
            SDL_Rect square_rect_9 = {.x = 220, .y = 355, .w = 137, .h = 110};
            SDL_Surface * square_surface_9;
            if (pole_1[2][1]) {
                char ch[5];
                sprintf(ch, "%d", pole_1[2][1]);
                square_surface_9 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_9 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_9 = SDL_CreateTextureFromSurface(renderer, square_surface_9);
            SDL_RenderCopy(renderer, square_texture_9, NULL, &square_rect_9);
            
            //10
            SDL_Rect square_rect_10 = {.x = 420, .y = 355, .w = 137, .h = 110};
            SDL_Surface * square_surface_10;
            if (pole_1[2][2]) {
                char ch[5];
                sprintf(ch, "%d", pole_1[2][2]);
                square_surface_10 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_10 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_10 = SDL_CreateTextureFromSurface(renderer, square_surface_10);
            SDL_RenderCopy(renderer, square_texture_10, NULL, &square_rect_10);

            //11
            SDL_Rect square_rect_11 = {.x = 620, .y = 355, .w = 137, .h = 110};
            SDL_Surface * square_surface_11;
            if (pole_1[2][3]) {
                char ch[5];
                sprintf(ch, "%d", pole_1[2][3]);
                square_surface_11 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_11 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_11 = SDL_CreateTextureFromSurface(renderer, square_surface_11);
            SDL_RenderCopy(renderer, square_texture_11, NULL, &square_rect_11);

            //12
            SDL_Rect square_rect_12 = {.x = 20, .y = 480, .w = 137, .h = 110};
            SDL_Surface * square_surface_12;
            if (pole_1[3][0]) {
                char ch[5];
                sprintf(ch, "%d", pole_1[3][0]);
                square_surface_12 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_12 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_12 = SDL_CreateTextureFromSurface(renderer, square_surface_12);
            SDL_RenderCopy(renderer, square_texture_12, NULL, &square_rect_12);
            
            //13
            SDL_Rect square_rect_13 = {.x = 220, .y = 480, .w = 137, .h = 110};
            SDL_Surface * square_surface_13;
            if (pole_1[3][1]) {
                char ch[5];
                sprintf(ch, "%d", pole_1[3][1]);
                square_surface_13 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_13 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_13 = SDL_CreateTextureFromSurface(renderer, square_surface_13);
            SDL_RenderCopy(renderer, square_texture_13, NULL, &square_rect_13);

            //14
            SDL_Rect square_rect_14 = {.x = 420, .y = 480, .w = 137, .h = 110};
            SDL_Surface * square_surface_14;
            if (pole_1[3][2]) {
                char ch[5];
                sprintf(ch, "%d", pole_1[3][2]);
                square_surface_14 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_14 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_14 = SDL_CreateTextureFromSurface(renderer, square_surface_14);
            SDL_RenderCopy(renderer, square_texture_14, NULL, &square_rect_14);

            //15
            SDL_Rect square_rect_15 = {.x = 620, .y = 480, .w = 137, .h = 110};
            SDL_Surface * square_surface_15;
            if (pole_1[3][3]) {
                char ch[5];
                sprintf(ch, "%d", pole_1[3][3]);
                square_surface_15 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_15 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
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
            //Nápis se score
            SDL_Rect score_rect = {.x = WINDOW_WIDTH / 2 - 50, .y = 30, .w = 100, .h = 20}; //V tomto obdélníku bude to score
            sprintf(score_text, "Score: %d", score);
            //Musíme si udělt surface - vyrobíme obrázek, který bude v paměti, z toho potom texturu
            SDL_Surface * score_surface = TTF_RenderText_Solid(sans, score_text, RGB_green);
            //Textura - "obrázky na zdech, postavách, které jsou natažené na geometriký model"
            //Vezeme texturu a natáhneme ji na čtverec
            SDL_Texture * score_texture = SDL_CreateTextureFromSurface(renderer, score_surface); //Vzali jsme texturu a překopírovali do grafické paměti
            //Texturu už můžeme zobrazit v rendereru
            SDL_RenderCopy(renderer, score_texture, NULL, &score_rect); //Texturu vyrenderovat do score_rect

            //Čtverečky s čísly           
            //0
            SDL_Rect square_rect_0 = {.x = 10, .y = 70, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_0;
            if (pole_2[0][0]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[0][0]);
                square_surface_0 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_0 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_0 = SDL_CreateTextureFromSurface(renderer, square_surface_0);
            SDL_RenderCopy(renderer, square_texture_0, NULL, &square_rect_0);
            
            //1
            SDL_Rect square_rect_1 = {.x = 75.8, .y = 70, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_1;
            if (pole_2[0][1]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[0][1]);
                square_surface_1 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_1 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_1 = SDL_CreateTextureFromSurface(renderer, square_surface_1);
            SDL_RenderCopy(renderer, square_texture_1, NULL, &square_rect_1);
            
            //2
            SDL_Rect square_rect_2 = {.x = 141.6, .y = 70, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_2;
            if (pole_2[0][2]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[0][2]);
                square_surface_2 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_2 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_2 = SDL_CreateTextureFromSurface(renderer, square_surface_2);
            SDL_RenderCopy(renderer, square_texture_2, NULL, &square_rect_2);
            
            //3
            SDL_Rect square_rect_3 = {.x = 207.4, .y = 70, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_3;
            if (pole_2[0][3]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[0][3]);
                square_surface_3 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_3 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_3 = SDL_CreateTextureFromSurface(renderer, square_surface_3);
            SDL_RenderCopy(renderer, square_texture_3, NULL, &square_rect_3);
            
            //4
            SDL_Rect square_rect_4 = {.x = 273.2, .y = 70, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_4;
            if (pole_2[0][4]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[0][4]);
                square_surface_4 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_4 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_4 = SDL_CreateTextureFromSurface(renderer, square_surface_4);
            SDL_RenderCopy(renderer, square_texture_4, NULL, &square_rect_4);

            //5
            SDL_Rect square_rect_5 = {.x = 339, .y = 70, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_5;
            if (pole_2[0][5]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[0][5]);
                square_surface_5 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_5 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_5 = SDL_CreateTextureFromSurface(renderer, square_surface_5);
            SDL_RenderCopy(renderer, square_texture_5, NULL, &square_rect_5);

            //6
            SDL_Rect square_rect_6 = {.x = 404.8, .y = 70, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_6;
            if (pole_2[0][6]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[0][6]);
                square_surface_6 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_6 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_6 = SDL_CreateTextureFromSurface(renderer, square_surface_6);
            SDL_RenderCopy(renderer, square_texture_6, NULL, &square_rect_6);

            //7
            SDL_Rect square_rect_7 = {.x = 470.6, .y = 70, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_7;
            if (pole_2[0][7]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[0][7]);
                square_surface_7 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_7 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_7 = SDL_CreateTextureFromSurface(renderer, square_surface_7);
            SDL_RenderCopy(renderer, square_texture_7, NULL, &square_rect_7);

            //8
            SDL_Rect square_rect_8 = {.x = 536.4, .y = 70, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_8;
            if (pole_2[0][8]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[0][8]);
                square_surface_8 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_8 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_8 = SDL_CreateTextureFromSurface(renderer, square_surface_8);
            SDL_RenderCopy(renderer, square_texture_8, NULL, &square_rect_8);

            //9
            SDL_Rect square_rect_9 = {.x = 603.2, .y = 70, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_9;
            if (pole_2[0][9]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[0][9]);
                square_surface_9 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_9 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_9 = SDL_CreateTextureFromSurface(renderer, square_surface_9);
            SDL_RenderCopy(renderer, square_texture_9, NULL, &square_rect_9);
            
            //10
            SDL_Rect square_rect_10 = {.x = 669, .y = 70, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_10;
            if (pole_2[0][10]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[0][10]);
                square_surface_10 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_10 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_10 = SDL_CreateTextureFromSurface(renderer, square_surface_10);
            SDL_RenderCopy(renderer, square_texture_10, NULL, &square_rect_10);

            //11
            SDL_Rect square_rect_11 = {.x = 734.8, .y = 70, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_11;
            if (pole_2[0][11]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[0][11]);
                square_surface_11 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_11 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_11 = SDL_CreateTextureFromSurface(renderer, square_surface_11);
            SDL_RenderCopy(renderer, square_texture_11, NULL, &square_rect_11);

            //12
            SDL_Rect square_rect_12 = {.x = 10, .y = 136.25, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_12;
            if (pole_2[1][0]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[1][0]);
                square_surface_12 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_12 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_12 = SDL_CreateTextureFromSurface(renderer, square_surface_12);
            SDL_RenderCopy(renderer, square_texture_12, NULL, &square_rect_12);
            
            //13
            SDL_Rect square_rect_13 = {.x = 75.8, .y = 136.25, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_13;
            if (pole_2[1][1]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[1][1]);
                square_surface_13 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_13 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_13 = SDL_CreateTextureFromSurface(renderer, square_surface_13);
            SDL_RenderCopy(renderer, square_texture_13, NULL, &square_rect_13);

            //14
            SDL_Rect square_rect_14 = {.x = 141.6, .y = 136.25, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_14;
            if (pole_2[1][2]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[1][2]);
                square_surface_14 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_14 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_14 = SDL_CreateTextureFromSurface(renderer, square_surface_14);
            SDL_RenderCopy(renderer, square_texture_14, NULL, &square_rect_14);

            //15
            SDL_Rect square_rect_15 = {.x = 207.4, .y = 136.25, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_15;
            if (pole_2[1][3]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[1][3]);
                square_surface_15 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_15 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_15 = SDL_CreateTextureFromSurface(renderer, square_surface_15);
            SDL_RenderCopy(renderer, square_texture_15, NULL, &square_rect_15);

            //16
            SDL_Rect square_rect_16 = {.x = 273.2, .y = 136.25, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_16;
            if (pole_2[1][4]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[1][4]);
                square_surface_16 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_16 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_16 = SDL_CreateTextureFromSurface(renderer, square_surface_16);
            SDL_RenderCopy(renderer, square_texture_16, NULL, &square_rect_16);
            
            //17
            SDL_Rect square_rect_17 = {.x = 339, .y = 136.25, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_17;
            if (pole_2[1][5]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[1][5]);
                square_surface_17 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_17 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_17 = SDL_CreateTextureFromSurface(renderer, square_surface_17);
            SDL_RenderCopy(renderer, square_texture_17, NULL, &square_rect_17);

            //18
            SDL_Rect square_rect_18 = {.x = 404.8, .y = 136.25, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_18;
            if (pole_2[1][6]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[1][6]);
                square_surface_18 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_18 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_18 = SDL_CreateTextureFromSurface(renderer, square_surface_18);
            SDL_RenderCopy(renderer, square_texture_18, NULL, &square_rect_18);

            //19
            SDL_Rect square_rect_19 = {.x = 470.6, .y = 136.25, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_19;
            if (pole_2[1][7]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[1][7]);
                square_surface_19 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_19 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_19 = SDL_CreateTextureFromSurface(renderer, square_surface_19);
            SDL_RenderCopy(renderer, square_texture_19, NULL, &square_rect_19);

            //20
            SDL_Rect square_rect_20 = {.x = 536.4, .y = 136.25, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_20;
            if (pole_2[1][8]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[1][8]);
                square_surface_20 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_20 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_20 = SDL_CreateTextureFromSurface(renderer, square_surface_20);
            SDL_RenderCopy(renderer, square_texture_20, NULL, &square_rect_20);

            //21
            SDL_Rect square_rect_21 = {.x = 603.2, .y = 136.25, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_21;
            if (pole_2[1][9]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[1][9]);
                square_surface_21 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_21 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_21 = SDL_CreateTextureFromSurface(renderer, square_surface_21);
            SDL_RenderCopy(renderer, square_texture_21, NULL, &square_rect_21);

            //22
            SDL_Rect square_rect_22 = {.x = 669, .y = 136.25, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_22;
            if (pole_2[1][10]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[1][10]);
                square_surface_22 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_22 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_22 = SDL_CreateTextureFromSurface(renderer, square_surface_22);
            SDL_RenderCopy(renderer, square_texture_22, NULL, &square_rect_22);

            //23
            SDL_Rect square_rect_23 = {.x = 734.8, .y = 136.25, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_23;
            if (pole_2[1][11]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[1][11]);
                square_surface_23 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_23 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_23 = SDL_CreateTextureFromSurface(renderer, square_surface_23);
            SDL_RenderCopy(renderer, square_texture_23, NULL, &square_rect_23);

            //24
            SDL_Rect square_rect_24 = {.x = 10, .y = 202.5, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_24;
            if (pole_2[2][0]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[2][0]);
                square_surface_24 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_24 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_24 = SDL_CreateTextureFromSurface(renderer, square_surface_24);
            SDL_RenderCopy(renderer, square_texture_24, NULL, &square_rect_24);

            //25
            SDL_Rect square_rect_25 = {.x = 75.8, .y = 202.5, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_25;
            if (pole_2[2][1]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[2][1]);
                square_surface_25 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_25 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_25 = SDL_CreateTextureFromSurface(renderer, square_surface_25);
            SDL_RenderCopy(renderer, square_texture_25, NULL, &square_rect_25);

            //26
            SDL_Rect square_rect_26 = {.x = 141.6, .y = 202.5, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_26;
            if (pole_2[2][2]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[2][2]);
                square_surface_26 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_26 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_26 = SDL_CreateTextureFromSurface(renderer, square_surface_26);
            SDL_RenderCopy(renderer, square_texture_26, NULL, &square_rect_26);

            //27
            SDL_Rect square_rect_27 = {.x = 207.4, .y = 202.5, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_27;
            if (pole_2[2][3]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[2][3]);
                square_surface_27 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_27 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_27 = SDL_CreateTextureFromSurface(renderer, square_surface_27);
            SDL_RenderCopy(renderer, square_texture_27, NULL, &square_rect_27);

            //28
            SDL_Rect square_rect_28 = {.x = 273.2, .y = 202.5, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_28;
            if (pole_2[2][4]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[2][4]);
                square_surface_28 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_28 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_28 = SDL_CreateTextureFromSurface(renderer, square_surface_28);
            SDL_RenderCopy(renderer, square_texture_28, NULL, &square_rect_28);

            //29
            SDL_Rect square_rect_29 = {.x = 339, .y = 202.5, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_29;
            if (pole_2[2][5]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[2][5]);
                square_surface_29 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_29 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_29 = SDL_CreateTextureFromSurface(renderer, square_surface_29);
            SDL_RenderCopy(renderer, square_texture_29, NULL, &square_rect_29);

            //30
            SDL_Rect square_rect_30 = {.x = 404.8, .y = 202.5, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_30;
            if (pole_2[2][6]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[2][6]);
                square_surface_30 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_30 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_30 = SDL_CreateTextureFromSurface(renderer, square_surface_30);
            SDL_RenderCopy(renderer, square_texture_30, NULL, &square_rect_30);

            //31
            SDL_Rect square_rect_31 = {.x = 470.6, .y = 202.5, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_31;
            if (pole_2[2][7]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[2][7]);
                square_surface_31 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_31 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_31 = SDL_CreateTextureFromSurface(renderer, square_surface_31);
            SDL_RenderCopy(renderer, square_texture_31, NULL, &square_rect_31);

            //32
            SDL_Rect square_rect_32 = {.x = 536.4, .y = 202.5, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_32;
            if (pole_2[2][8]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[2][8]);
                square_surface_32 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_32 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_32 = SDL_CreateTextureFromSurface(renderer, square_surface_32);
            SDL_RenderCopy(renderer, square_texture_32, NULL, &square_rect_32);

            //33
            SDL_Rect square_rect_33 = {.x = 603.2, .y = 202.5, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_33;
            if (pole_2[2][9]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[2][9]);
                square_surface_33 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_33 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_33 = SDL_CreateTextureFromSurface(renderer, square_surface_33);
            SDL_RenderCopy(renderer, square_texture_33, NULL, &square_rect_33);

            //34
            SDL_Rect square_rect_34 = {.x = 669, .y = 202.5, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_34;
            if (pole_2[2][10]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[2][10]);
                square_surface_34 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_34 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_34 = SDL_CreateTextureFromSurface(renderer, square_surface_34);
            SDL_RenderCopy(renderer, square_texture_34, NULL, &square_rect_34);

            //35
            SDL_Rect square_rect_35 = {.x = 734.8, .y = 202.5, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_35;
            if (pole_2[2][11]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[2][11]);
                square_surface_35 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_35 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_35 = SDL_CreateTextureFromSurface(renderer, square_surface_35);
            SDL_RenderCopy(renderer, square_texture_35, NULL, &square_rect_35);

            //36
            SDL_Rect square_rect_36 = {.x = 10, .y = 268.75, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_36;
            if (pole_2[3][0]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[3][0]);
                square_surface_36 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_36 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_36 = SDL_CreateTextureFromSurface(renderer, square_surface_36);
            SDL_RenderCopy(renderer, square_texture_36, NULL, &square_rect_36);

            //37
            SDL_Rect square_rect_37 = {.x = 75.8, .y = 268.75, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_37;
            if (pole_2[3][1]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[3][1]);
                square_surface_37 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_37 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_37 = SDL_CreateTextureFromSurface(renderer, square_surface_37);
            SDL_RenderCopy(renderer, square_texture_37, NULL, &square_rect_37);

            //38
            SDL_Rect square_rect_38 = {.x = 141.6, .y = 268.75, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_38;
            if (pole_2[3][2]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[3][2]);
                square_surface_38 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_38 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_38 = SDL_CreateTextureFromSurface(renderer, square_surface_38);
            SDL_RenderCopy(renderer, square_texture_38, NULL, &square_rect_38);

            //39
            SDL_Rect square_rect_39 = {.x = 207.4, .y = 268.75, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_39;
            if (pole_2[3][3]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[3][3]);
                square_surface_39 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_39 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_39 = SDL_CreateTextureFromSurface(renderer, square_surface_39);
            SDL_RenderCopy(renderer, square_texture_39, NULL, &square_rect_39);

            //40
            SDL_Rect square_rect_40 = {.x = 273.2, .y = 268.75, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_40;
            if (pole_2[3][4]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[3][4]);
                square_surface_40 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_40 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_40 = SDL_CreateTextureFromSurface(renderer, square_surface_40);
            SDL_RenderCopy(renderer, square_texture_40, NULL, &square_rect_40);

            //41
            SDL_Rect square_rect_41 = {.x = 339, .y = 268.75, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_41;
            if (pole_2[3][5]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[3][5]);
                square_surface_41 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_41 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_41 = SDL_CreateTextureFromSurface(renderer, square_surface_41);
            SDL_RenderCopy(renderer, square_texture_41, NULL, &square_rect_41);

            //42
            SDL_Rect square_rect_42 = {.x = 404.8, .y = 268.75, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_42;
            if (pole_2[3][6]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[3][6]);
                square_surface_42 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_42 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_42 = SDL_CreateTextureFromSurface(renderer, square_surface_42);
            SDL_RenderCopy(renderer, square_texture_42, NULL, &square_rect_42);

            //43
            SDL_Rect square_rect_43 = {.x = 470.6, .y = 268.75, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_43;
            if (pole_2[3][7]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[3][7]);
                square_surface_43 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_43 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_43 = SDL_CreateTextureFromSurface(renderer, square_surface_43);
            SDL_RenderCopy(renderer, square_texture_43, NULL, &square_rect_43);

            //44
            SDL_Rect square_rect_44 = {.x = 536.4, .y = 268.75, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_44;
            if (pole_2[3][8]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[3][8]);
                square_surface_44 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_44 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_44 = SDL_CreateTextureFromSurface(renderer, square_surface_44);
            SDL_RenderCopy(renderer, square_texture_44, NULL, &square_rect_44);

            //45
            SDL_Rect square_rect_45 = {.x = 603.2, .y = 268.75, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_45;
            if (pole_2[3][9]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[3][9]);
                square_surface_45 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_45 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_45 = SDL_CreateTextureFromSurface(renderer, square_surface_45);
            SDL_RenderCopy(renderer, square_texture_45, NULL, &square_rect_45);

            //46
            SDL_Rect square_rect_46 = {.x = 669, .y = 268.75, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_46;
            if (pole_2[3][10]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[3][10]);
                square_surface_46 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_46 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_46 = SDL_CreateTextureFromSurface(renderer, square_surface_46);
            SDL_RenderCopy(renderer, square_texture_46, NULL, &square_rect_46);

            //47
            SDL_Rect square_rect_47 = {.x = 734.8, .y = 268.75, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_47;
            if (pole_2[3][11]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[3][11]);
                square_surface_47 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_47 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_47 = SDL_CreateTextureFromSurface(renderer, square_surface_47);
            SDL_RenderCopy(renderer, square_texture_47, NULL, &square_rect_47);

            //48
            SDL_Rect square_rect_48 = {.x = 10, .y = 335, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_48;
            if (pole_2[4][0]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[4][0]);
                square_surface_48 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_48 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_48 = SDL_CreateTextureFromSurface(renderer, square_surface_48);
            SDL_RenderCopy(renderer, square_texture_48, NULL, &square_rect_48);

            //49
            SDL_Rect square_rect_49 = {.x = 75.8, .y = 335, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_49;
            if (pole_2[4][1]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[4][1]);
                square_surface_49 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_49 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_49 = SDL_CreateTextureFromSurface(renderer, square_surface_49);
            SDL_RenderCopy(renderer, square_texture_49, NULL, &square_rect_49);

            //50
            SDL_Rect square_rect_50 = {.x = 141.6, .y = 335, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_50;
            if (pole_2[4][2]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[4][2]);
                square_surface_50 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_50 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_50 = SDL_CreateTextureFromSurface(renderer, square_surface_50);
            SDL_RenderCopy(renderer, square_texture_50, NULL, &square_rect_50);

            //51
            SDL_Rect square_rect_51 = {.x = 207.4, .y = 335, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_51;
            if (pole_2[4][3]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[4][3]);
                square_surface_51 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_51 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_51 = SDL_CreateTextureFromSurface(renderer, square_surface_51);
            SDL_RenderCopy(renderer, square_texture_51, NULL, &square_rect_51);

            //52
            SDL_Rect square_rect_52 = {.x = 273.2, .y = 335, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_52;
            if (pole_2[4][4]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[4][4]);
                square_surface_52 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_52 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_52 = SDL_CreateTextureFromSurface(renderer, square_surface_52);
            SDL_RenderCopy(renderer, square_texture_52, NULL, &square_rect_52);

            //53
            SDL_Rect square_rect_53 = {.x = 339, .y = 335, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_53;
            if (pole_2[4][5]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[4][5]);
                square_surface_53 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_53 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_53 = SDL_CreateTextureFromSurface(renderer, square_surface_53);
            SDL_RenderCopy(renderer, square_texture_53, NULL, &square_rect_53);

            //54
            SDL_Rect square_rect_54 = {.x = 404.8, .y = 335, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_54;
            if (pole_2[4][6]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[4][6]);
                square_surface_54 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_54 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_54 = SDL_CreateTextureFromSurface(renderer, square_surface_54);
            SDL_RenderCopy(renderer, square_texture_54, NULL, &square_rect_54);

            //55
            SDL_Rect square_rect_55 = {.x = 470.6, .y = 335, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_55;
            if (pole_2[4][7]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[4][7]);
                square_surface_55 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_55 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_55 = SDL_CreateTextureFromSurface(renderer, square_surface_55);
            SDL_RenderCopy(renderer, square_texture_55, NULL, &square_rect_55);

            //56
            SDL_Rect square_rect_56 = {.x = 536.4, .y = 335, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_56;
            if (pole_2[4][8]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[4][8]);
                square_surface_56 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_56 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_56 = SDL_CreateTextureFromSurface(renderer, square_surface_56);
            SDL_RenderCopy(renderer, square_texture_56, NULL, &square_rect_56);

            //57
            SDL_Rect square_rect_57 = {.x = 603.2, .y = 335, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_57;
            if (pole_2[4][9]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[4][9]);
                square_surface_57 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_57 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_57 = SDL_CreateTextureFromSurface(renderer, square_surface_57);
            SDL_RenderCopy(renderer, square_texture_57, NULL, &square_rect_57);

            //58
            SDL_Rect square_rect_58 = {.x = 669, .y = 335, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_58;
            if (pole_2[4][10]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[4][10]);
                square_surface_58 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_58 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_58 = SDL_CreateTextureFromSurface(renderer, square_surface_58);
            SDL_RenderCopy(renderer, square_texture_58, NULL, &square_rect_58);

            //59
            SDL_Rect square_rect_59 = {.x = 734.8, .y = 335, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_59;
            if (pole_2[4][11]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[4][11]);
                square_surface_59 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_59 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_59 = SDL_CreateTextureFromSurface(renderer, square_surface_59);
            SDL_RenderCopy(renderer, square_texture_59, NULL, &square_rect_59);

            //60
            SDL_Rect square_rect_60 = {.x = 10, .y = 401.25, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_60;
            if (pole_2[5][0]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[5][0]);
                square_surface_60 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_60 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_60 = SDL_CreateTextureFromSurface(renderer, square_surface_60);
            SDL_RenderCopy(renderer, square_texture_60, NULL, &square_rect_60);

            //61
            SDL_Rect square_rect_61 = {.x = 75.8, .y = 401.25, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_61;
            if (pole_2[5][1]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[5][1]);
                square_surface_61 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_61 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_61 = SDL_CreateTextureFromSurface(renderer, square_surface_61);
            SDL_RenderCopy(renderer, square_texture_61, NULL, &square_rect_61);

            //62
            SDL_Rect square_rect_62 = {.x = 141.6, .y = 401.25, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_62;
            if (pole_2[5][2]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[5][2]);
                square_surface_62 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_62 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_62 = SDL_CreateTextureFromSurface(renderer, square_surface_62);
            SDL_RenderCopy(renderer, square_texture_62, NULL, &square_rect_62);

            //63
            SDL_Rect square_rect_63 = {.x = 207.4, .y = 401.25, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_63;
            if (pole_2[5][3]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[5][3]);
                square_surface_63 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_63 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_63 = SDL_CreateTextureFromSurface(renderer, square_surface_63);
            SDL_RenderCopy(renderer, square_texture_63, NULL, &square_rect_63);

            //64
            SDL_Rect square_rect_64 = {.x = 273.2, .y = 401.25, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_64;
            if (pole_2[5][4]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[5][4]);
                square_surface_64 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_64 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_64 = SDL_CreateTextureFromSurface(renderer, square_surface_64);
            SDL_RenderCopy(renderer, square_texture_64, NULL, &square_rect_64);

            //65
            SDL_Rect square_rect_65 = {.x = 339, .y = 401.25, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_65;
            if (pole_2[5][5]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[5][5]);
                square_surface_65 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_65 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_65 = SDL_CreateTextureFromSurface(renderer, square_surface_65);
            SDL_RenderCopy(renderer, square_texture_65, NULL, &square_rect_65);

            //66
            SDL_Rect square_rect_66 = {.x = 404.8, .y = 401.25, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_66;
            if (pole_2[5][6]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[5][6]);
                square_surface_66 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_66 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_66 = SDL_CreateTextureFromSurface(renderer, square_surface_66);
            SDL_RenderCopy(renderer, square_texture_66, NULL, &square_rect_66);

            //67
            SDL_Rect square_rect_67 = {.x = 470.6, .y = 401.25, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_67;
            if (pole_2[5][7]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[5][7]);
                square_surface_67 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_67 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_67 = SDL_CreateTextureFromSurface(renderer, square_surface_67);
            SDL_RenderCopy(renderer, square_texture_67, NULL, &square_rect_67);

            //68
            SDL_Rect square_rect_68 = {.x = 536.4, .y = 401.25, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_68;
            if (pole_2[5][8]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[5][8]);
                square_surface_68 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_68 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_68 = SDL_CreateTextureFromSurface(renderer, square_surface_68);
            SDL_RenderCopy(renderer, square_texture_68, NULL, &square_rect_68);

            //69
            SDL_Rect square_rect_69 = {.x = 603.2, .y = 401.25, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_69;
            if (pole_2[5][9]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[5][9]);
                square_surface_69 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_69 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_69 = SDL_CreateTextureFromSurface(renderer, square_surface_69);
            SDL_RenderCopy(renderer, square_texture_69, NULL, &square_rect_69);

            //70
            SDL_Rect square_rect_70 = {.x = 669, .y = 401.25, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_70;
            if (pole_2[5][10]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[5][10]);
                square_surface_70 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_70 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_70 = SDL_CreateTextureFromSurface(renderer, square_surface_70);
            SDL_RenderCopy(renderer, square_texture_70, NULL, &square_rect_70);

            //71
            SDL_Rect square_rect_71 = {.x = 734.8, .y = 401.25, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_71;
            if (pole_2[5][11]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[5][11]);
                square_surface_71 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_71 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_71 = SDL_CreateTextureFromSurface(renderer, square_surface_71);
            SDL_RenderCopy(renderer, square_texture_71, NULL, &square_rect_71);

            //72
            SDL_Rect square_rect_72 = {.x = 10, .y = 467.5, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_72;
            if (pole_2[6][0]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[6][0]);
                square_surface_72 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_72 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_72 = SDL_CreateTextureFromSurface(renderer, square_surface_72);
            SDL_RenderCopy(renderer, square_texture_72, NULL, &square_rect_72);

            //73
            SDL_Rect square_rect_73 = {.x = 75.8, .y = 467.5, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_73;
            if (pole_2[6][1]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[6][1]);
                square_surface_73 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_73 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_73 = SDL_CreateTextureFromSurface(renderer, square_surface_73);
            SDL_RenderCopy(renderer, square_texture_73, NULL, &square_rect_73);

            //74
            SDL_Rect square_rect_74 = {.x = 141.6, .y = 467.5, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_74;
            if (pole_2[6][2]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[6][2]);
                square_surface_74 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_74 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_74 = SDL_CreateTextureFromSurface(renderer, square_surface_74);
            SDL_RenderCopy(renderer, square_texture_74, NULL, &square_rect_74);

            //75
            SDL_Rect square_rect_75 = {.x = 207.4, .y = 467.5, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_75;
            if (pole_2[6][3]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[6][3]);
                square_surface_75 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_75 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_75 = SDL_CreateTextureFromSurface(renderer, square_surface_75);
            SDL_RenderCopy(renderer, square_texture_75, NULL, &square_rect_75);

            //76
            SDL_Rect square_rect_76 = {.x = 273.2, .y = 467.5, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_76;
            if (pole_2[6][4]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[6][4]);
                square_surface_76 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_76 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_76 = SDL_CreateTextureFromSurface(renderer, square_surface_76);
            SDL_RenderCopy(renderer, square_texture_76, NULL, &square_rect_76);

            //77
            SDL_Rect square_rect_77 = {.x = 339, .y = 467.5, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_77;
            if (pole_2[6][5]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[6][5]);
                square_surface_77 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_77 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_77 = SDL_CreateTextureFromSurface(renderer, square_surface_77);
            SDL_RenderCopy(renderer, square_texture_77, NULL, &square_rect_77);

            //78
            SDL_Rect square_rect_78 = {.x = 404.8, .y = 467.5, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_78;
            if (pole_2[6][6]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[6][6]);
                square_surface_78 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_78 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_78 = SDL_CreateTextureFromSurface(renderer, square_surface_78);
            SDL_RenderCopy(renderer, square_texture_78, NULL, &square_rect_78);

            //79
            SDL_Rect square_rect_79 = {.x = 470.6, .y = 467.5, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_79;
            if (pole_2[6][7]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[6][7]);
                square_surface_79 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_79 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_79 = SDL_CreateTextureFromSurface(renderer, square_surface_79);
            SDL_RenderCopy(renderer, square_texture_79, NULL, &square_rect_79);

            //80
            SDL_Rect square_rect_80 = {.x = 536.4, .y = 467.5, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_80;
            if (pole_2[6][8]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[6][8]);
                square_surface_80 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_80 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_80 = SDL_CreateTextureFromSurface(renderer, square_surface_80);
            SDL_RenderCopy(renderer, square_texture_80, NULL, &square_rect_80);

            //81
            SDL_Rect square_rect_81 = {.x = 603.2, .y = 467.5, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_81;
            if (pole_2[6][9]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[6][9]);
                square_surface_81 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_81 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_81 = SDL_CreateTextureFromSurface(renderer, square_surface_81);
            SDL_RenderCopy(renderer, square_texture_81, NULL, &square_rect_81);

            //82
            SDL_Rect square_rect_82 = {.x = 669, .y = 467.5, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_82;
            if (pole_2[6][10]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[6][10]);
                square_surface_82 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_82 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_82 = SDL_CreateTextureFromSurface(renderer, square_surface_82);
            SDL_RenderCopy(renderer, square_texture_82, NULL, &square_rect_82);

            //83
            SDL_Rect square_rect_83 = {.x = 734.8, .y = 467.5, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_83;
            if (pole_2[6][11]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[6][11]);
                square_surface_83 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_83 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_83 = SDL_CreateTextureFromSurface(renderer, square_surface_83);
            SDL_RenderCopy(renderer, square_texture_83, NULL, &square_rect_83);

            //84
            SDL_Rect square_rect_84 = {.x = 10, .y = 533.75, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_84;
            if (pole_2[7][0]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[7][0]);
                square_surface_84 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_84 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_84 = SDL_CreateTextureFromSurface(renderer, square_surface_84);
            SDL_RenderCopy(renderer, square_texture_84, NULL, &square_rect_84);

            //85
            SDL_Rect square_rect_85 = {.x = 75.8, .y = 533.75, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_85;
            if (pole_2[7][1]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[7][1]);
                square_surface_85 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_85 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_85 = SDL_CreateTextureFromSurface(renderer, square_surface_85);
            SDL_RenderCopy(renderer, square_texture_85, NULL, &square_rect_85);

            //86
            SDL_Rect square_rect_86 = {.x = 141.6, .y = 533.75, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_86;
            if (pole_2[7][2]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[7][2]);
                square_surface_86 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_86 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_86 = SDL_CreateTextureFromSurface(renderer, square_surface_86);
            SDL_RenderCopy(renderer, square_texture_86, NULL, &square_rect_86);

            //87
            SDL_Rect square_rect_87 = {.x = 207.4, .y = 533.75, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_87;
            if (pole_2[7][3]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[7][3]);
                square_surface_87 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_87 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_87 = SDL_CreateTextureFromSurface(renderer, square_surface_87);
            SDL_RenderCopy(renderer, square_texture_87, NULL, &square_rect_87);

            //88
            SDL_Rect square_rect_88 = {.x = 273.2, .y = 533.75, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_88;
            if (pole_2[7][4]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[7][4]);
                square_surface_88 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_88 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_88 = SDL_CreateTextureFromSurface(renderer, square_surface_88);
            SDL_RenderCopy(renderer, square_texture_88, NULL, &square_rect_88);

            //89
            SDL_Rect square_rect_89 = {.x = 339, .y = 533.75, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_89;
            if (pole_2[7][5]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[7][5]);
                square_surface_89 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_89 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_89 = SDL_CreateTextureFromSurface(renderer, square_surface_89);
            SDL_RenderCopy(renderer, square_texture_89, NULL, &square_rect_89);

            //90
            SDL_Rect square_rect_90 = {.x = 404.8, .y = 533.75, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_90;
            if (pole_2[7][6]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[7][6]);
                square_surface_90 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_90 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_90 = SDL_CreateTextureFromSurface(renderer, square_surface_90);
            SDL_RenderCopy(renderer, square_texture_90, NULL, &square_rect_90);

            //91
            SDL_Rect square_rect_91 = {.x = 470.6, .y = 533.75, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_91;
            if (pole_2[7][7]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[7][7]);
                square_surface_91 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_91 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_91 = SDL_CreateTextureFromSurface(renderer, square_surface_91);
            SDL_RenderCopy(renderer, square_texture_91, NULL, &square_rect_91);

            //92
            SDL_Rect square_rect_92 = {.x = 536.4, .y = 533.75, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_92;
            if (pole_2[7][8]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[7][8]);
                square_surface_92 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_92 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_92 = SDL_CreateTextureFromSurface(renderer, square_surface_92);
            SDL_RenderCopy(renderer, square_texture_92, NULL, &square_rect_92);

            //93
            SDL_Rect square_rect_93 = {.x = 603.2, .y = 533.75, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_93;
            if (pole_2[7][9]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[7][9]);
                square_surface_93 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_93 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_93 = SDL_CreateTextureFromSurface(renderer, square_surface_93);
            SDL_RenderCopy(renderer, square_texture_93, NULL, &square_rect_93);

            //94
            SDL_Rect square_rect_94 = {.x = 669, .y = 533.75, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_94;
            if (pole_2[7][10]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[7][10]);
                square_surface_94 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_94 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_94 = SDL_CreateTextureFromSurface(renderer, square_surface_94);
            SDL_RenderCopy(renderer, square_texture_94, NULL, &square_rect_94);

            //95
            SDL_Rect square_rect_95 = {.x = 734.8, .y = 533.75, .w = 60.8, .h = 61.25};
            SDL_Surface * square_surface_95;
            if (pole_2[7][11]) {
                char ch[5];
                sprintf(ch, "%d", pole_2[7][11]);
                square_surface_95 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_95 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_95 = SDL_CreateTextureFromSurface(renderer, square_surface_95);
            SDL_RenderCopy(renderer, square_texture_95, NULL, &square_rect_95);



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
            SDL_DestroyTexture(square_texture_16);
            SDL_FreeSurface(square_surface_16);
            SDL_DestroyTexture(square_texture_17);
            SDL_FreeSurface(square_surface_17);
            SDL_DestroyTexture(square_texture_18);
            SDL_FreeSurface(square_surface_18);
            SDL_DestroyTexture(square_texture_19);
            SDL_FreeSurface(square_surface_19);
            SDL_DestroyTexture(square_texture_20);
            SDL_FreeSurface(square_surface_20);
            SDL_DestroyTexture(square_texture_21);
            SDL_FreeSurface(square_surface_21);
            SDL_DestroyTexture(square_texture_22);
            SDL_FreeSurface(square_surface_22);
            SDL_DestroyTexture(square_texture_23);
            SDL_FreeSurface(square_surface_23);
            SDL_DestroyTexture(square_texture_24);
            SDL_FreeSurface(square_surface_24);
            SDL_DestroyTexture(square_texture_25);
            SDL_FreeSurface(square_surface_25);
            SDL_DestroyTexture(square_texture_26);
            SDL_FreeSurface(square_surface_26);
            SDL_DestroyTexture(square_texture_27);
            SDL_FreeSurface(square_surface_27);
            SDL_DestroyTexture(square_texture_28);
            SDL_FreeSurface(square_surface_28);
            SDL_DestroyTexture(square_texture_29);
            SDL_FreeSurface(square_surface_29);
            SDL_DestroyTexture(square_texture_30);
            SDL_FreeSurface(square_surface_30);
            SDL_DestroyTexture(square_texture_31);
            SDL_FreeSurface(square_surface_31);
            SDL_DestroyTexture(square_texture_32);
            SDL_FreeSurface(square_surface_32);
            SDL_DestroyTexture(square_texture_33);
            SDL_FreeSurface(square_surface_33);
            SDL_DestroyTexture(square_texture_34);
            SDL_FreeSurface(square_surface_34);
            SDL_DestroyTexture(square_texture_35);
            SDL_FreeSurface(square_surface_35);
            SDL_DestroyTexture(square_texture_36);
            SDL_FreeSurface(square_surface_36);
            SDL_DestroyTexture(square_texture_37);
            SDL_FreeSurface(square_surface_37);
            SDL_DestroyTexture(square_texture_38);
            SDL_FreeSurface(square_surface_38);
            SDL_DestroyTexture(square_texture_39);
            SDL_FreeSurface(square_surface_39);
            SDL_DestroyTexture(square_texture_40);
            SDL_FreeSurface(square_surface_40);
            SDL_DestroyTexture(square_texture_41);
            SDL_FreeSurface(square_surface_41);
            SDL_DestroyTexture(square_texture_42);
            SDL_FreeSurface(square_surface_42);
            SDL_DestroyTexture(square_texture_43);
            SDL_FreeSurface(square_surface_43);
            SDL_DestroyTexture(square_texture_44);
            SDL_FreeSurface(square_surface_44);
            SDL_DestroyTexture(square_texture_45);
            SDL_FreeSurface(square_surface_45);
            SDL_DestroyTexture(square_texture_46);
            SDL_FreeSurface(square_surface_46);
            SDL_DestroyTexture(square_texture_47);
            SDL_FreeSurface(square_surface_47);
            SDL_DestroyTexture(square_texture_48);
            SDL_FreeSurface(square_surface_48);
            SDL_DestroyTexture(square_texture_49);
            SDL_FreeSurface(square_surface_49);
            SDL_DestroyTexture(square_texture_50);
            SDL_FreeSurface(square_surface_50);
            SDL_DestroyTexture(square_texture_51);
            SDL_FreeSurface(square_surface_51);
            SDL_DestroyTexture(square_texture_52);
            SDL_FreeSurface(square_surface_52);
            SDL_DestroyTexture(square_texture_53);
            SDL_FreeSurface(square_surface_53);
            SDL_DestroyTexture(square_texture_54);
            SDL_FreeSurface(square_surface_54);
            SDL_DestroyTexture(square_texture_55);
            SDL_FreeSurface(square_surface_55);
            SDL_DestroyTexture(square_texture_56);
            SDL_FreeSurface(square_surface_56);
            SDL_DestroyTexture(square_texture_57);
            SDL_FreeSurface(square_surface_57);
            SDL_DestroyTexture(square_texture_58);
            SDL_FreeSurface(square_surface_58);
            SDL_DestroyTexture(square_texture_59);
            SDL_FreeSurface(square_surface_59);
            SDL_DestroyTexture(square_texture_60);
            SDL_FreeSurface(square_surface_60);
            SDL_DestroyTexture(square_texture_61);
            SDL_FreeSurface(square_surface_61);
            SDL_DestroyTexture(square_texture_62);
            SDL_FreeSurface(square_surface_62);
            SDL_DestroyTexture(square_texture_63);
            SDL_FreeSurface(square_surface_63);
            SDL_DestroyTexture(square_texture_64);
            SDL_FreeSurface(square_surface_64);
            SDL_DestroyTexture(square_texture_65);
            SDL_FreeSurface(square_surface_65);
            SDL_DestroyTexture(square_texture_66);
            SDL_FreeSurface(square_surface_66);
            SDL_DestroyTexture(square_texture_67);
            SDL_FreeSurface(square_surface_67);
            SDL_DestroyTexture(square_texture_68);
            SDL_FreeSurface(square_surface_68);
            SDL_DestroyTexture(square_texture_69);
            SDL_FreeSurface(square_surface_69);
            SDL_DestroyTexture(square_texture_70);
            SDL_FreeSurface(square_surface_70);
            SDL_DestroyTexture(square_texture_71);
            SDL_FreeSurface(square_surface_71);
            SDL_DestroyTexture(square_texture_72);
            SDL_FreeSurface(square_surface_72);
            SDL_DestroyTexture(square_texture_73);
            SDL_FreeSurface(square_surface_73);
            SDL_DestroyTexture(square_texture_74);
            SDL_FreeSurface(square_surface_74);
            SDL_DestroyTexture(square_texture_75);
            SDL_FreeSurface(square_surface_75);
            SDL_DestroyTexture(square_texture_76);
            SDL_FreeSurface(square_surface_76);
            SDL_DestroyTexture(square_texture_77);
            SDL_FreeSurface(square_surface_77);
            SDL_DestroyTexture(square_texture_78);
            SDL_FreeSurface(square_surface_78);
            SDL_DestroyTexture(square_texture_79);
            SDL_FreeSurface(square_surface_79);
            SDL_DestroyTexture(square_texture_80);
            SDL_FreeSurface(square_surface_80);
            SDL_DestroyTexture(square_texture_81);
            SDL_FreeSurface(square_surface_81);
            SDL_DestroyTexture(square_texture_82);
            SDL_FreeSurface(square_surface_82);
            SDL_DestroyTexture(square_texture_83);
            SDL_FreeSurface(square_surface_83);
            SDL_DestroyTexture(square_texture_84);
            SDL_FreeSurface(square_surface_84);
            SDL_DestroyTexture(square_texture_85);
            SDL_FreeSurface(square_surface_85);
            SDL_DestroyTexture(square_texture_86);
            SDL_FreeSurface(square_surface_86);
            SDL_DestroyTexture(square_texture_87);
            SDL_FreeSurface(square_surface_87);
            SDL_DestroyTexture(square_texture_88);
            SDL_FreeSurface(square_surface_88);
            SDL_DestroyTexture(square_texture_89);
            SDL_FreeSurface(square_surface_89);
            SDL_DestroyTexture(square_texture_90);
            SDL_FreeSurface(square_surface_90);
            SDL_DestroyTexture(square_texture_91);
            SDL_FreeSurface(square_surface_91);
            SDL_DestroyTexture(square_texture_92);
            SDL_FreeSurface(square_surface_92);
            SDL_DestroyTexture(square_texture_93);
            SDL_FreeSurface(square_surface_93);
            SDL_DestroyTexture(square_texture_94);
            SDL_FreeSurface(square_surface_94);
            SDL_DestroyTexture(square_texture_95);
            SDL_FreeSurface(square_surface_95);
        } else if (game && !rules && (game_mode == 3)) { //Hra 3*3
            //Nápis se score
            SDL_Rect score_rect = {.x = WINDOW_WIDTH / 2 - 50, .y = 30, .w = 100, .h = 20}; //V tomto obdélníku bude to score
            sprintf(score_text, "Score: %d", score);
            //Musíme si udělt surface - vyrobíme obrázek, který bude v paměti, z toho potom texturu
            SDL_Surface * score_surface = TTF_RenderText_Solid(sans, score_text, RGB_green);
            //Textura - "obrázky na zdech, postavách, které jsou natažené na geometriký model"
            //Vezeme texturu a natáhneme ji na čtverec
            SDL_Texture * score_texture = SDL_CreateTextureFromSurface(renderer, score_surface); //Vzali jsme texturu a překopírovali do grafické paměti
            //Texturu už můžeme zobrazit v rendereru
            SDL_RenderCopy(renderer, score_texture, NULL, &score_rect); //Texturu vyrenderovat do score_rect

            //Čtverečky s čísly           
            //0
            SDL_Rect square_rect_0 = {.x = 20, .y = 70, .w = 160, .h = 110};
            SDL_Surface * square_surface_0;
            if (pole_3[0][0]) {
                char ch[5];
                sprintf(ch, "%d", pole_3[0][0]);
                square_surface_0 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_0 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_0 = SDL_CreateTextureFromSurface(renderer, square_surface_0);
            SDL_RenderCopy(renderer, square_texture_0, NULL, &square_rect_0);
            
            //1
            SDL_Rect square_rect_1 = {.x = 350, .y = 70, .w = 160, .h = 110};
            SDL_Surface * square_surface_1;
            if (pole_3[0][1]) {
                char ch[5];
                sprintf(ch, "%d", pole_3[0][1]);
                square_surface_1 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_1 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_1 = SDL_CreateTextureFromSurface(renderer, square_surface_1);
            SDL_RenderCopy(renderer, square_texture_1, NULL, &square_rect_1);
            
            //2
            SDL_Rect square_rect_2 = {.x = 550, .y = 70, .w = 160, .h = 110};
            SDL_Surface * square_surface_2;
            if (pole_3[0][2]) {
                char ch[5];
                sprintf(ch, "%d", pole_3[0][2]);
                square_surface_2 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_2 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_2 = SDL_CreateTextureFromSurface(renderer, square_surface_2);
            SDL_RenderCopy(renderer, square_texture_2, NULL, &square_rect_2);
            
            //3
            SDL_Rect square_rect_3 = {.x = 20, .y = 210, .w = 160, .h = 110};
            SDL_Surface * square_surface_3;
            if (pole_3[1][0]) {
                char ch[5];
                sprintf(ch, "%d", pole_3[1][0]);
                square_surface_3 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_3 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_3 = SDL_CreateTextureFromSurface(renderer, square_surface_3);
            SDL_RenderCopy(renderer, square_texture_3, NULL, &square_rect_3);
            
            //4
            SDL_Rect square_rect_4 = {.x = 350, .y = 210, .w = 160, .h = 110};
            SDL_Surface * square_surface_4;
            if (pole_3[1][1]) {
                char ch[5];
                sprintf(ch, "%d", pole_3[1][1]);
                square_surface_4 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_4 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_4 = SDL_CreateTextureFromSurface(renderer, square_surface_4);
            SDL_RenderCopy(renderer, square_texture_4, NULL, &square_rect_4);

            //5
            SDL_Rect square_rect_5 = {.x = 550, .y = 210, .w = 160, .h = 110};
            SDL_Surface * square_surface_5;
            if (pole_3[1][2]) {
                char ch[5];
                sprintf(ch, "%d", pole_3[1][2]);
                square_surface_5 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_5 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_5 = SDL_CreateTextureFromSurface(renderer, square_surface_5);
            SDL_RenderCopy(renderer, square_texture_5, NULL, &square_rect_5);

            //6
            SDL_Rect square_rect_6 = {.x = 20, .y = 355, .w = 160, .h = 110};
            SDL_Surface * square_surface_6;
            if (pole_3[2][0]) {
                char ch[5];
                sprintf(ch, "%d", pole_3[2][0]);
                square_surface_6 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_6 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_6 = SDL_CreateTextureFromSurface(renderer, square_surface_6);
            SDL_RenderCopy(renderer, square_texture_6, NULL, &square_rect_6);

            //7
            SDL_Rect square_rect_7 = {.x = 350, .y = 355, .w = 160, .h = 110};
            SDL_Surface * square_surface_7;
            if (pole_3[2][1]) {
                char ch[5];
                sprintf(ch, "%d", pole_3[2][1]);
                square_surface_7 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_7 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_7 = SDL_CreateTextureFromSurface(renderer, square_surface_7);
            SDL_RenderCopy(renderer, square_texture_7, NULL, &square_rect_7);

            //8
            SDL_Rect square_rect_8 = {.x = 550, .y = 355, .w = 137, .h = 110};
            SDL_Surface * square_surface_8;
            if (pole_3[2][2]) {
                char ch[5];
                sprintf(ch, "%d", pole_3[2][2]);
                square_surface_8 = TTF_RenderText_Solid(sans, ch, RGB_yellow);
            } else {
                square_surface_8 = TTF_RenderText_Solid(sans, "", RGB_yellow);
            }
            SDL_Texture * square_texture_8 = SDL_CreateTextureFromSurface(renderer, square_surface_8);
            SDL_RenderCopy(renderer, square_texture_8, NULL, &square_rect_8);



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
        } else if (game_over) {
            char text_menu[13] = "Hra skoncila";
            char text_help[65] = "Stisknete klavesu q pro ukonceni programu, r pro skryti pravidel";
            char text_play[60] = "n - nova hra (4*4), m - nova hra (12*8), b - nova hra (3*3)";
            char game_help[36] = "Hra se ovlada sipkami na klavesnici";

            //Musíme si udělt surface - vyrobíme obrázek, který bude v paměti, z toho potom 
            SDL_Rect score_rect = {.x = WINDOW_WIDTH / 2 - 50, .y = 50, .w = 150, .h = 20}; //V tomto obdélníku bude to score
            SDL_Surface * menu_surface = TTF_RenderText_Solid(sans, text_menu, RGB_red);
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
            SDL_Surface * menu_surface = TTF_RenderText_Solid(sans, text_menu, RGB_green);
            //Textura - "obrázky na zdech, postavách, které jsou natažené na geometriký model"
            //Vezeme texturu a natáhneme ji na čtverec
            SDL_Texture * menu_texture = SDL_CreateTextureFromSurface(renderer, menu_surface); //Vzali jsme texturu a překopírovali do grafické paměti
            //Texturu už můžeme zobrazit v rendereru
            SDL_RenderCopy(renderer, menu_texture, NULL, &score_rect); //Texturu vyrenderovat do score_rect

            SDL_Rect help_rect = {.x = 5, .y = 150, .w = 795, .h = 20};
            SDL_Surface * help_surface = TTF_RenderText_Solid(sans, text_help, RGB_yellow);
            SDL_Texture * help_texture = SDL_CreateTextureFromSurface(renderer, help_surface);
            SDL_RenderCopy(renderer, help_texture, NULL, &help_rect);

            SDL_Rect play_rect = {.x = 20, .y = 250, .w = 760, .h = 20};
            SDL_Surface * play_surface = TTF_RenderText_Solid(sans, text_play, RGB_yellow);
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