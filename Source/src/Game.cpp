#include "Game.h"

SDL_Surface *load_image(string filename )
{
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized image that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image using SDL_image
    loadedImage = IMG_Load( filename.c_str() );

    //If the image loaded
    if( loadedImage != NULL )
    {
        //Create an optimized image
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Free the old image
        SDL_FreeSurface( loadedImage );
    }

    //Return the optimized image
    return optimizedImage;
}

Game::Game()
    :TICK_RATE(20),
     TIME_PER_TICK(1000 / TICK_RATE),
     FRACTION_TIME_PER_TICK(TIME_PER_TICK / 1000.0f),
     iScreenWidth(580),
     iScreenHeight(380),
     bIsGameRunning(true)
{

    SDL_Init( SDL_INIT_EVERYTHING );
    screen = SDL_SetVideoMode( iScreenWidth, iScreenHeight, 32, SDL_SWSURFACE );

}


Game::~Game()
{
}


void Game::eventHandler(SDL_Event event)
{
    if( event.type == SDL_QUIT )
    {
        bIsGameRunning = false;
    }

    if( event.type == SDL_KEYDOWN )
    {
        switch( event.key.keysym.sym )
        {
        case SDLK_UP:
            dy=-1;
            break;
        case SDLK_DOWN:
            dy=1;
            break;
        case SDLK_LEFT:
            dx=-1;
            break;
        case SDLK_RIGHT:
            dx=1;
            break;
        default:; // to avoid warnings
        }
    }
    if( event.type == SDL_KEYUP )
    {
        switch( event.key.keysym.sym )
        {
        case SDLK_UP:
            dy=0;
            break;
        case SDLK_DOWN:
            dy=0;
            break;
        case SDLK_LEFT:
            dx=0;
            break;
        case SDLK_RIGHT:
            dx=0;
            break;
        default:;  // to avoid warnings
        }
    }


}


void Game::update()
{


}

void Game::render()
{
    SDL_FillRect(screen, 0, 0);
}




void Game::run()
{

    int x=400,y=240; //starting center
    int dx=0,dy=0;
    SDL_Surface* pic = NULL;
    pic =load_image("untitled.JPG");

    DWORD lastTime= GetTickCount();
    MSG msg;
    srand ( time(NULL) );

    while( isGameRunning == true )
    {
        DWORD currentTime = GetTickCount();
        while( currentTime - lastTime >= TIME_PER_TICK)
        {

            while( SDL_PollEvent( &event ) )
            {
                eventHandler(event);
            }
            x+=dx*20;
            y+=dy*20;
            //making the picture to not exit the screen
            if(x<-130) x=-130;
            else if(x>screenWidth-570) x=screenWidth-570;

            if (y<-38) y=-38;
            else if(y>screenHeight-480) y=screenHeight-480;

            render();
            SDL_Rect offset;
            offset.x = x;
            offset.y = y;
            SDL_BlitSurface( pic, NULL, screen, &offset );
            SDL_Flip( screen );

            lastTime += TIME_PER_TICK;
        }
    }

    SDL_FreeSurface(pic);
    SDL_Quit();
}
