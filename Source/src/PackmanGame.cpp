#include "PackmanGame.h"

Packman* PackmanGame::packman = NULL;

PackmanGame::PackmanGame(GameWindow *win)
    : GameState(win),
      iMap(NULL)
{
}
PackmanGame::~PackmanGame() {}

GameState* PackmanGame::OnUpdate()
{
    if(packman->IsDead())
    {
        if(packman->GetLives()!=0)
        {
            packman->IncreaseLivesBy(-1);
            packman->SetAlive();
            ResetPackmanAndGhostsPositions();
        }
        //else do nothing - its Game Over
    }
    else
    {
        if(!isPaused || packman->IsDying())
        {
            packman->Update();
        }

        if(!isPaused)
        {
            for(unsigned i=0; i<ghosts.size(); i++)
            {
                ghosts[i]->Update();
                if( ghosts[i]->GetXPix() < packman->GetXPix()+cellSize &&
                        ghosts[i]->GetXPix() > packman->GetXPix()-cellSize &&
                        ghosts[i]->GetYPix() < packman->GetYPix()+cellSize &&
                        ghosts[i]->GetYPix() > packman->GetYPix()-cellSize)
                {
                    if(ghosts[i]->IsVulnerable())
                    {
                        ghosts[i]->SetDead();
                    }
                    else
                    {
                        packman->SetDying();
                        isPaused = true;
                    }
                }
            }
        }

        for(unsigned i=0; i<bonuses.size(); i++)
        {
            bonuses[i]->Update();
            if( bonuses[i]->GetXPix() < packman->GetXPix()+2 &&
                    bonuses[i]->GetXPix() > packman->GetXPix()-2 &&
                    bonuses[i]->GetYPix() < packman->GetYPix()+2 &&
                    bonuses[i]->GetYPix() > packman->GetYPix()-2)
            {
                if(bonuses[i]->GetType() == 1)
                {
                    packman->IncreaseScoreBy(100);
                }
                else
                {
                    for(unsigned g=0; g<ghosts.size(); g++)
                    {
                        ghosts[g]->SetVulnerable(10*25);
                    }
                }
                delete bonuses[i];
                bonuses.erase(bonuses.begin()+i);
                i--;
            }
        }
        packmanUI->Update();
    }

    if(bonuses.size()==0)
    {
        GameState* nextState = new PackmanGame(window);
        packman->IncreaseLevel();
        return nextState;
    }
    if(terminateState)
    {
        delete this;
        return NULL;
    }
    else return this;
}

void PackmanGame::Render()
{
    //SDL_FillRect(window->Screen(), 0, 0);

    SDL_Surface *pic = SDL_LoadBMP("Media/Level1Background.bmp");
    SDL_Rect offset;
    offset.x = 0;
    offset.y = 0;
    SDL_BlitSurface( pic, NULL, window->Screen(), &offset );

    for(unsigned i=0; i<bonuses.size(); i++)
    {
        bonuses[i]->Render();
    }
    for(unsigned i=0; i<ghosts.size(); i++)
    {
        ghosts[i]->Render();
    }
    packman->Render();

    packmanUI->Render();

    SDL_Flip( window->Screen());
    SDL_FreeSurface(pic);
}

void PackmanGame::HandleEvents()
{
    SDL_Event    event;
    while( SDL_PollEvent( &event ) )
    {
        if( event.type == SDL_QUIT)
        {
            terminateState = true;
        }
        if( event.type == SDL_KEYDOWN )
        {
            isPaused = false;
            switch( event.key.keysym.sym )
            {
            case SDLK_ESCAPE:
                isPaused = true;
                break;
            case SDLK_UP:
                packman->SetDirection(0,-1);
                break;
            case SDLK_DOWN:
                packman->SetDirection(0,1);
                break;
            case SDLK_LEFT:
                packman->SetDirection(-1,0);
                break;
            case SDLK_RIGHT:
                packman->SetDirection(1,0);
                break;
            default:; // to avoid warnings
            }
        }
    }
}



void PackmanGame::OnLeave()
{
    delete [] iMap;
    for(unsigned i=0; i<bonuses.size(); i++)
    {
        delete bonuses[i];
    }
    for(unsigned i=0; i<ghosts.size(); i++)
    {
        delete ghosts[i];
    }
    delete packmanUI;
    // delete packman;  // only to be deleted in last state - since the game is infinite - never delete
}

void PackmanGame::OnEnter()
{
    isPaused = true;

    if(packman == NULL)
    {
        packman = new Packman(window);
    }

    packmanUI = new PackmanUI(window);
    packmanUI->SetPackmanTarget(packman);
    packmanUI->SetXPix(400);
    packmanUI->SetYPix(100);

    mapWidth = 19;
    mapHeight = 19;
    cellSize = 20;
    int barrierLocationX=0,barrierLocationY=0;
    //0 - wall
    //1 - score point
    //2 - pill
    //3 - player(packman)
    //4 - ghost
    //5 - barrier
    //6 - empty
    delete [] iMap;
    iMap = new int[19*19]
    {
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,0,
        0,1,0,0,1,0,1,0,1,0,1,0,1,0,1,0,0,1,0,
        0,1,0,0,1,0,1,0,1,1,1,0,1,0,1,0,0,1,0,
        0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,
        0,1,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,1,0,
        0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
        0,1,0,1,0,0,1,0,0,5,0,0,1,0,0,1,0,1,0,
        0,1,0,1,0,0,1,0,6,6,6,0,1,0,0,1,0,1,0,
        0,1,1,1,1,1,1,0,6,4,6,0,1,1,1,1,1,1,0,
        0,1,0,1,0,0,1,0,6,6,6,0,1,0,0,1,0,1,0,
        0,1,0,1,0,0,1,0,0,0,0,0,1,0,0,1,0,1,0,
        0,1,0,1,0,0,1,1,1,3,1,1,1,0,0,1,0,1,0,
        0,1,0,1,1,1,1,0,0,0,0,0,1,1,1,1,0,1,0,
        0,1,1,1,0,0,1,0,0,0,0,0,1,0,0,1,1,1,0,
        0,1,0,1,1,0,1,1,1,1,1,1,1,0,1,1,0,1,0,
        0,1,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,1,0,
        0,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0

    };

    for(int k =0; k<mapHeight; k++)
    {
        for(int i=0; i<mapWidth; i++)
        {
            if(iMap[k*mapWidth + i] == 5)  // considering the barrier is above the ghosts, otherwise this will need to be rewritten
            {
                barrierLocationX = i;
                barrierLocationY = k;
                iMap[k*mapWidth + i] = 0;
            }
            if(iMap[k*mapWidth + i] == 4)
            {
                for(int g=0; g<4; g++)
                {
                    Ghost* ghost = new Ghost(window);
                    ghost->SetGhostType(g);
                    ghost->SetStartAndBarrier(i,k,barrierLocationX,barrierLocationY);
                    ghost->SetMap(iMap,mapWidth,mapHeight,cellSize,i,k);
                    ghost->SetTarget(packman);
                    ghosts.push_back(ghost);
                }
            }
            if(iMap[k*mapWidth + i] == 3)
            {
                packman->SetMap(iMap,mapWidth,mapHeight,cellSize,i,k);
            }
            if(iMap[k*mapWidth + i] == 1 || iMap[k*mapWidth + i] == 2)
            {
                Bonus* bonus = new Bonus(window);
                bonus->InitType(iMap[k*mapWidth + i]);
                bonus->SetXPix(i*cellSize);
                bonus->SetYPix(k*cellSize);
                bonuses.push_back(bonus);
            }

        }

    }
}


void PackmanGame::ResetPackmanAndGhostsPositions()
{
    isPaused = true;

    for(int k =0; k<mapHeight; k++)
    {
        for(int i=0; i<mapWidth; i++)
        {
            if(iMap[k*mapWidth + i] == 4)
            {
                for(unsigned g=0; g<ghosts.size(); g++)
                {
                    ghosts[g]->SetMap(iMap,mapWidth,mapHeight,cellSize,i,k);
                    ghosts[g]->SetInGraveyard();
                }
            }
            if(iMap[k*mapWidth + i] == 3)
            {
                packman->SetMap(iMap,mapWidth,mapHeight,cellSize,i,k);
            }
        }
    }
}
