#include "PackmanUI.h"

PackmanUI::PackmanUI(GameWindow *win): Object(win)
{
    Init();
}

PackmanUI::~PackmanUI()
{
    TTF_CloseFont( font );
    SDL_FreeSurface(scoreText);
    SDL_FreeSurface(scoreNumber);
    SDL_FreeSurface(livesText);
    SDL_FreeSurface(livesNumber);
    SDL_FreeSurface(levelText);
    SDL_FreeSurface(levelNumber);
    SDL_FreeSurface(gameOver);
}


void PackmanUI::Init()
{

    scoreNumber = NULL;
    livesNumber = NULL;
    levelNumber = NULL;

    string buffer ;

    textColor = { 255, 0, 0 };
    font = TTF_OpenFont( "Alexis.ttf", 70 );
    buffer = "GAME OVER";
    gameOver = TTF_RenderText_Solid(font,buffer.c_str(), textColor);
    TTF_CloseFont( font );


    textColor = { 255, 255, 0 };
    font = TTF_OpenFont( "Alexis.ttf", 40 );

    buffer = "SCORE";
    scoreText = TTF_RenderText_Solid(font,buffer.c_str(), textColor);

    buffer = "LIFE";
    livesText = TTF_RenderText_Solid(font,buffer.c_str(), textColor);

    buffer = "LEVEL";
    levelText = TTF_RenderText_Solid(font,buffer.c_str(), textColor);
}
void PackmanUI::Update()
{
    stringstream prebuffer;
    string buffer;

    prebuffer.str("");
    prebuffer << std::setw(5) << setfill('0') << packman->GetScore();
    buffer =  prebuffer.str();
    SDL_FreeSurface(scoreNumber);
    scoreNumber = TTF_RenderText_Solid(font,buffer.c_str(), textColor);

    prebuffer.str("");
    prebuffer << std::setw(3) << setfill('0') << packman->GetLives();
    buffer =  prebuffer.str();
    SDL_FreeSurface(livesNumber);
    livesNumber = TTF_RenderText_Solid(font,buffer.c_str(), textColor);

    prebuffer.str("");
    prebuffer << std::setw(3) << setfill('0') << packman->GetLevel();
    buffer =  prebuffer.str();
    SDL_FreeSurface(levelNumber);
    levelNumber = TTF_RenderText_Solid(font,buffer.c_str(), textColor);
}


void PackmanUI::Render()
{
    SDL_Rect destination;

    destination.x= xPix;
    destination.y = yPix;
    SDL_BlitSurface( scoreText,NULL, window->Screen(), &destination );

    destination.x= xPix;
    destination.y = yPix+20;
    SDL_BlitSurface( scoreNumber,NULL, window->Screen(), &destination );

    destination.x= xPix;
    destination.y = yPix+45;
    SDL_BlitSurface( livesText,NULL, window->Screen(), &destination );

    destination.x= xPix;
    destination.y = yPix+65;
    SDL_BlitSurface( livesNumber,NULL, window->Screen(), &destination );

    destination.x= xPix;
    destination.y = yPix+90;
    SDL_BlitSurface( levelText,NULL, window->Screen(), &destination );

    destination.x= xPix;
    destination.y = yPix+110;
    SDL_BlitSurface( levelNumber,NULL, window->Screen(), &destination );

    if(packman->GetLives()==0 && packman->IsDead())
    {
        destination.x= 50;
        destination.y = 150;
        SDL_BlitSurface( gameOver,NULL, window->Screen(), &destination );
    }
}


void PackmanUI::SetPackmanTarget(Packman* packmanTarget)
{
    packman = packmanTarget;
}
