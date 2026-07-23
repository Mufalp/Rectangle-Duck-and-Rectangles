#include <raylib.h>
#include "uiMechanics.h"
#include "Mechanics.h"
#include "Levels.h"
#include "External.h"

int main(){
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_UNDECORATED | FLAG_VSYNC_HINT);
    InitWindow(wwidth,wheight,"Rectangle Duck and Rectangles");
    SetTargetFPS(60);

    //pre-calculations
    Duck duck;
    Camera2D camera = {0};
    State GameState = StartState, LastState = StartState;
    int level=0;

    std::vector<std::unique_ptr<Enemy> > enemy;
    std::vector<std::vector<std::unique_ptr<Block>>> rBlocks;
    std::map<std::string,std::unique_ptr<Buton>> buttons;
    std::map<std::string,std::unique_ptr<Slider>> sliders;
    
    LoadGame(duck);
    preLevelDesign(rBlocks,&GameState);
    PreCam(camera,duck);
    
    SetAudioStreamBufferSizeDefault(16384);
    InitAudioDevice();
    
    anySound sounds;
    loadMyAudio(sounds);
    MusicManager musicMngr(&sounds.mainMenuM);
    
    
    RaceMenu racemenu(100.0f,40.0f,wwidth-200.0f,300.0f,&GameState,&level,&duck,sounds);
    preButtonMap(buttons,&GameState,sounds);
    preSliderMap(sliders,duck,&musicMngr.volume);

    BackGround background;
    loadMyTexture(background);

    while(!WindowShouldClose()){
        //repeated calculations
        musicMngr.Update();
        isStateChanged(GameState, musicMngr, sounds, duck, camera, enemy);

        switch(GameState){
            case RUN:
                duck.Jump();
                enemyCycle(enemy, duck);
                isStop(&GameState);
                LastState=RUN;
                break;
            case GAMEOVER:
                buttons["runRetry"]->isClicked();
                buttons["goMenu"]->isClicked();
                deathChecker(duck);
                break;
            case MAINMENU:
                buttons["mainTrain"]->isClicked();
                buttons["raceSelect"]->isClicked();
                buttons["options"]->isClicked();
                buttons["howTo"]->isClicked();
                break;
            case RACE:
                RCamFollow(camera,duck);
                raceCycle(duck,rBlocks,level);
                deathChecker(duck);
                isStop(&GameState);
                LastState=RACE;
                break;
            case RACEMENU:
                rMenuCheck(racemenu);
                break;
            case RACEWIN:
                buttons["winToMenu"]->isClicked();
                break;
            case PAUSE:
                Stopped(&GameState,LastState);
                buttons["pauseToMenu"]->isClicked();
                break;
            case OPTION:
                sliders["sound"]->isSliding();
                sliders["run"]->isSliding();
                buttons["optionToMenu"]->isClicked();
                break;
            case HOWTO:
                buttons["howToMenu"]->isClicked();
                break;
        }
        
        //Drawing-Block
        BeginDrawing();

        ClearBackground(BLACK);

        switch(GameState){
            case RUN:
                slideBackground(background,duck);
                Run(enemy,duck,GameState);
                break;
            case GAMEOVER:
                GameOver(duck,*buttons["runRetry"],enemy);
                buttons["goMenu"]->Draw();
                deathDraw(duck);
                break;
            case MAINMENU:
                MainMenu(*buttons["mainTrain"]);
                buttons["raceSelect"]->Draw();
                buttons["options"]->Draw();
                buttons["howTo"]->Draw();
                break;
            case RACE:
                slideBackground2D(background, duck);
                Race(duck,rBlocks,camera,level);
                deathDraw(duck);
                break;
            case RACEMENU:
                racemenu.Draw();
                break;
            case RACEWIN:
                winMenu(duck,*buttons["winToMenu"],level);
                break;
            case PAUSE:
                pauseMenu();
                buttons["pauseToMenu"]->Draw();
                break;
            case OPTION:
                optionMenu();
                sliders["sound"]->Draw();
                sliders["run"]->Draw();
                buttons["optionToMenu"]->Draw();
                break;
            case HOWTO:
                howtoMenu();
                buttons["howToMenu"]->Draw();
        }

        EndDrawing();
    }
    unloadMyAudio(sounds);
    CloseAudioDevice();
    unloadMyTexture(background);
    return 0;
}