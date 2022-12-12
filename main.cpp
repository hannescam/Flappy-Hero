#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <random>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <cstring>

bool pressed_1 = false;
SDL_Surface *surface;
bool coin_other = false;
double coin_angle;
int coin_cnt;
int height = 600;
int witdh = 800;
bool coin_move = true;

int height_old = 600;
int witdh_old = 800;
int coin_h;
int coin_w;
int score;
int jump;
bool collected = false;
bool gameover = false;
bool restart = false;
int cnt;

int genrand(int min, int max)
{
    int val = 0;
    min = max - min;
    max = max - min;
    val = rand() % min + max;
    return val;
}

char *intToStr(int data)
{
    std::string strData = std::to_string(data);

    char *temp = new char[strData.length() + 1];
    strcpy(temp, strData.c_str());

    return temp;
}

int main(int argc, char *argv[])
{
    TTF_Init();
    TTF_Font *font = TTF_OpenFont("arial.ttf", 25);
    // returns zero on success else non-zero
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }
    // SDL_Window *win = SDL_CreateWindow("F-Bird", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, witdh, height, 0);
    SDL_Window *win = SDL_CreateWindow("Flappy Hero", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, witdh, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    // triggers the program that controls
    // your graphics hardware and sets flags
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;

    // creates a renderer to render our images
    SDL_Renderer *rend = SDL_CreateRenderer(win, -1, render_flags);

    // creates a surface to load an image into the main memory
    SDL_Surface *surface;
    SDL_Surface *background;
    SDL_Surface *pipe_import;
    SDL_Surface *coin_import;
    SDL_Surface *bad_import;
    // please provide a path for your image
    SDL_Texture *bad_tex;
    SDL_Texture *back_tex;
    SDL_Texture *bird_tex;
    SDL_Texture *pipe_tex;
    SDL_Texture *coin_tex;
    // loads image to our graphics hardware memory.
    background = IMG_Load("back.png");
    back_tex = SDL_CreateTextureFromSurface(rend, background);
    SDL_FreeSurface(background);
    surface = IMG_Load("hero.png");
    bird_tex = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);
    pipe_import = IMG_Load("pipe.png");
    if (!pipe_import)
    {
        printf("Failed to load image pipe. Error: %s", IMG_GetError());
    }
    pipe_tex = SDL_CreateTextureFromSurface(rend, pipe_import);
    if (!pipe_tex)
    {
        printf("Failed to load texture pipe. Error: %s", SDL_GetError());
    }
    SDL_FreeSurface(pipe_import);
    coin_import = IMG_Load("coin.png");
    coin_tex = SDL_CreateTextureFromSurface(rend, coin_import);
    SDL_FreeSurface(coin_import);
    bad_import = IMG_Load("bad.png");
    bad_tex = SDL_CreateTextureFromSurface(rend, bad_import);
    SDL_FreeSurface(bad_import);
    // clears main-memory
    // let us control our image position
    // so that we can move it with our keyboard.
    SDL_Rect dest;
    SDL_Rect back;
    SDL_Rect pipe;
    SDL_Rect coin;
    SDL_Rect bad;
    SDL_zero(dest);
    SDL_zero(back);
    SDL_zero(pipe);
    SDL_zero(coin);
    SDL_zero(bad);
    // connects our texture with dest to control position
    SDL_QueryTexture(bird_tex, NULL, NULL, &dest.w, &dest.h);
    SDL_QueryTexture(back_tex, NULL, NULL, &back.w, &back.h);
    SDL_QueryTexture(pipe_tex, NULL, NULL, &pipe.w, &pipe.h);
    SDL_QueryTexture(coin_tex, NULL, NULL, &coin.w, &coin.h);
    SDL_QueryTexture(bad_tex, NULL, NULL, &bad.w, &bad.h);
    SDL_GetWindowSize(win, &witdh, &height);
    back.x = back.x - 60;
    pipe.x = witdh + 150;
    pipe.y = genrand(250, height - 100);
    dest.x = (witdh - dest.w) / 2;
    dest.y = (height - dest.h) / 2;
    back.w = witdh + 100;
    back.h = height + 100;
    pipe.w = 150;
    pipe.h = 4000;
    dest.w /= 6;
    dest.h /= 6;
    coin.w /= 15;
    coin.h /= 15;
    bad.w /= 12;
    bad.h /= 12;
    // std::uniform_int_distribution<int> coin_rand_x((witdh / 2) + (witdh / 10), witdh - coin.w);
    // std::uniform_int_distribution<int> coin_rand_y(0, height - coin.h);
    /*Randomer coin_rand_x{0, witdh - coin.w};
    Randomer coin_rand_y{0, height - coin.h};
    coin.x = coin_rand_x();
    coin.y = coin_rand_y();*/

    int close = 0;
    int speed = 200;

    while (!close)
    {
        SDL_Event event;

        // Events management
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_WINDOWEVENT && event.window.windowID == SDL_GetWindowID(win) && event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
            {
                SDL_GetWindowSize(win, &witdh, &height);
                back.w = witdh + 100;
                back.h = height + 100;
                SDL_Rect dest;
                SDL_Rect back;
                SDL_Rect pipe;
                SDL_Rect coin;
                SDL_Rect bad;
                // connects our texture with dest to control position
                SDL_QueryTexture(bird_tex, NULL, NULL, &dest.w, &dest.h);
                SDL_QueryTexture(back_tex, NULL, NULL, &back.w, &back.h);
                SDL_QueryTexture(pipe_tex, NULL, NULL, &pipe.w, &pipe.h);
                SDL_QueryTexture(coin_tex, NULL, NULL, &coin.w, &coin.h);
                SDL_QueryTexture(bad_tex, NULL, NULL, &bad.w, &bad.h);
                back.x = back.x - 60;
                pipe.x = witdh + 150;
                pipe.y = genrand(250, height - 100);
                dest.x = (witdh - dest.w) / 2;
                dest.y = (height - dest.h) / 2;
                pipe.w = 150;
                pipe.h = 4000;
                dest.w /= 6;
                dest.h /= 6;
                coin.w /= 15;
                coin.h /= 15;
                bad.w /= 12;
                bad.h /= 12;
                height_old = height;
                witdh_old = witdh;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT && jump == 0) jump += 15;
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.scancode != SDL_SCANCODE_ESCAPE)
                {
                    if (jump == 0)
                        jump += 15;
                }
                else
                {
                    close = 1;
                }
            }
            else if (event.type == SDL_QUIT)
            {
                close++;
            }
        }
        pipe.x -= 3;
        if (coin_move)
        {
            coin.x -= 3;
        }
        else
        {
            if (coin_cnt < 90)
            {
                coin_cnt++;
                coin_angle += 10;
                coin.h -= 1;
                coin.w -= 1;
                coin_other = true;
                if (coin.h <= 0)
                    coin_cnt = 37;
                if (coin.w <= 0)
                    coin_cnt = 37;
            }
            else
            {
                score++;
                coin_move = true;
                coin_cnt = 0;
                coin_angle = 0;
                coin_other = false;
                coin.h = coin_h;
                coin.w = coin_w;
                coin.x = genrand((witdh / 2) + (witdh / 8), witdh - coin.w);
                coin.y = genrand(0, height - coin.h);
            }
        }
        bad.x -= 3;
        if (pipe.x < -pipe.w)
        {
            collected = false;
            pipe.x += witdh + pipe.w;
            pipe.y = genrand(250, height - 100);
        }
        if (coin.x + coin.w < 0 && !coin_other)
        {
            // collected = false;
            coin.x = genrand((witdh / 2) + (witdh / 8), witdh - coin.w);
            coin.y = genrand(0, height - coin.h);
        }
        if (coin.x + coin_w < 0 && coin_other)
        {
            // collected = false;
            coin.x = genrand((witdh / 2) + (witdh / 8), witdh - coin_w);
            coin.y = genrand(0, height - coin_h);
        }
        if (bad.x < 0)
        {
            // collected = false;
            bad.x = genrand((witdh / 2) + (witdh / 8), witdh - bad.w);
            bad.y = genrand(0, height - bad.h);
        }
        if (pipe.y < dest.y + dest.h && pipe.x <= dest.x + dest.w - 30 && pipe.x + pipe.w >= dest.x)
        {
            gameover = true;
        }

        if (coin.y < dest.y + dest.h && coin.y + coin.h >= dest.y && coin.x <= dest.x + dest.w - 30 && coin.x + coin.w >= dest.x && !coin_other)
        {
            coin_h = coin.h;
            coin_w = coin.w;
            coin_move = false;
        }
        if (bad.y < dest.y + dest.h && bad.y + bad.h >= dest.y && bad.x <= dest.x + dest.w - 30 && bad.x + bad.w >= dest.x)
        {
            score--;
            bad.x = genrand((witdh / 2) + (witdh / 8), witdh - bad.w);
            bad.y = genrand(0, height - bad.h);
        }
        if (score == -1)
        {
            gameover = true;
            score++;
        }
        else if (pipe.x + pipe.w >= dest.x + 75 && pipe.x + pipe.w <= dest.x + 85 && !collected)
        {
            score++;
            collected = true;
        }
        if (dest.y < 1)
        {
            jump = 0;
            dest.y++;
        }
        else if (jump > 0 && dest.y > 0)
        {
            dest.y -= speed / 30;
            jump--;
        }
        if (jump == 0 && dest.y > 0)
        {

            dest.y += speed / 45;
        }
        // right boundary
        if (dest.x + dest.w > witdh)
            dest.x = witdh - dest.w;

        // left boundary
        if (dest.x < 0)
            dest.x = 0;

        // bottom boundary
        if (dest.y + dest.h > height)
        {
            gameover = true;
            printf("game over\n");
        }
        // upper boundary
        if (dest.y < 0)
        {
            gameover = true;
            printf("game over\n");
        }

        if (gameover)
        {
            //TTF_Font *font = TTF_OpenFont("arial.ttf", 25);
            SDL_Color color = {255, 255, 255};
            SDL_Surface *surface = TTF_RenderText_Solid(font, "Game over! press R or touch the screen to restart, score:", color);
            SDL_Surface *sctext = TTF_RenderText_Solid(font, intToStr(score), color);
            SDL_Texture *texture = SDL_CreateTextureFromSurface(rend, surface);
            SDL_Texture *sc = SDL_CreateTextureFromSurface(rend, sctext);
            int texW1 = 0;
            int texH1 = 0;
            int texW = 0;
            int texH = 0;
            SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
            SDL_QueryTexture(sc, NULL, NULL, &texW1, &texH1);
            SDL_Rect dstrect = {0, 0, texW, texH};
            SDL_Rect scpos = {0, 30, texW1, texH1};
            dstrect.x = (witdh - dstrect.w) / 2;
            scpos.x = (witdh - scpos.w) / 2;
            SDL_RenderClear(rend);
            SDL_RenderCopy(rend, texture, NULL, &dstrect);
            SDL_RenderCopy(rend, sc, NULL, &scpos);
            SDL_RenderPresent(rend);
            while (!close)
            {
                while (SDL_PollEvent(&event))
                {
                    if (event.type == SDL_WINDOWEVENT && event.window.windowID == SDL_GetWindowID(win) && event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                    {
                        SDL_GetWindowSize(win, &witdh, &height);
                        //TTF_Font *font = TTF_OpenFont("Bebas.ttf", 25);
                        SDL_Color color = {255, 255, 255};
                        surface = TTF_RenderText_Solid(font, "Game over! press R or touch the screen to restart, score:", color);
                        SDL_Surface *sctext = TTF_RenderText_Solid(font, intToStr(score), color);
                        SDL_Texture *texture = SDL_CreateTextureFromSurface(rend, surface);
                        SDL_Texture *sc = SDL_CreateTextureFromSurface(rend, sctext);
	    		SDL_FreeSurface(sctext);
			//SDL_FreeSurface(surface);
                        int texW1 = 0;
                        int texH1 = 0;
                        int texW = 0;
                        int texH = 0;
                        SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
                        SDL_QueryTexture(sc, NULL, NULL, &texW1, &texH1);
                        SDL_Rect dstrect = {0, 0, texW, texH};
                        SDL_Rect scpos = {0, 30, texW1, texH1};
                        dstrect.x = (witdh - dstrect.w) / 2;
                        scpos.x = (witdh - scpos.w) / 2;
                        SDL_RenderClear(rend);
                        SDL_RenderCopy(rend, texture, NULL, &dstrect);
                        SDL_RenderCopy(rend, sc, NULL, &scpos);
                        SDL_RenderPresent(rend);
                    }
                    if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                        close++;
                    if (event.type == SDL_QUIT)
                        close++;
                    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
                    {
                        close++;
                        score = 0;
                        restart = true;
                    }
                    if (event.key.keysym.scancode == SDL_SCANCODE_R)
                    {
                        close++;
                        score = 0;
                        restart = true;
                    }
                }
            }
            if (!restart)
            {
                break;
            }
            else
            {
                gameover = false;
                restart = false;
                close = 0;
                pipe.x = witdh + 150;
                pipe.y = genrand(250, height - 100);
                dest.x = (witdh - dest.w) / 2;
                dest.y = (height - dest.h) / 2;
                jump = 0;
            }
        }
        else
        {
            // clears the screen
            //TTF_Font *font = TTF_OpenFont("Bebas.ttf", 25);
            SDL_Color color = {255, 255, 255};
	    surface = TTF_RenderText_Solid(font, intToStr(score), color);
            if (!font)
            {
                printf("Failed to load font 'arial'. Error: %s \n", TTF_GetError());
            }
            if (!surface)
            {
                printf("Failed to load Surface 'text'. Error: %s \n", IMG_GetError());
            }
            SDL_Texture *texture = SDL_CreateTextureFromSurface(rend, surface);
	    //SDL_FreeSurface(surface);
            if (!texture)
            {
                printf("Failed to load Texture 'text'. Error: %s \n", SDL_GetError());
            }
            int texW = 0;
            int texH = 0;
            SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
            SDL_Rect dstrect = {0, 0, texW, texH};
            dstrect.x = (witdh - dstrect.w) / 2;
            SDL_RenderClear(rend);
            SDL_RenderCopy(rend, back_tex, NULL, &back);
            SDL_RenderCopy(rend, pipe_tex, NULL, &pipe);
            SDL_RenderCopy(rend, bird_tex, NULL, &dest);
            SDL_RenderCopyEx(rend, coin_tex, NULL, &coin, coin_angle, NULL, SDL_FLIP_NONE);
            // coin_angle += 10;
            if (coin_angle >= 360.0)
                coin_angle -= 0.01;
            SDL_RenderCopy(rend, bad_tex, NULL, &bad);
            SDL_RenderCopy(rend, texture, NULL, &dstrect);
	    //SDL_DestroyTexture(texture);
        }
        // triggers the double buffers
        // for multiple rendering
        SDL_RenderPresent(rend);

        // calculates to 60 fps
        SDL_Delay(1000 / 60);
    }

    // destroy texture
    SDL_DestroyTexture(bird_tex);
    SDL_DestroyTexture(pipe_tex);
    SDL_DestroyTexture(coin_tex);
    SDL_DestroyTexture(back_tex);
    SDL_DestroyTexture(bad_tex);
    //  destroy renderer
    SDL_DestroyRenderer(rend);

    // destroy window
    SDL_DestroyWindow(win);

    // close SDL
    SDL_Quit();
    return 0;
}
