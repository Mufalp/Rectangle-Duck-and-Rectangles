#include "uiMechanics.h"

void SaveGame(const Duck &duck){
    const char* filename = "assets/data/save.dat";
    const char* tempFile = "assets/data/save.dat.tmp";

    std::ofstream out(tempFile, std::ios::binary);
    if (!out) return;

    out.write(reinterpret_cast<const char*>(&duck.stats), sizeof(Stats));
    out.close();

    std::remove(filename);
    std::rename(tempFile, filename);
}

void LoadGame(Duck &duck){
    Stats stat = { 0x4455434C, 0, 0, 0.0f }; // Default
    std::ifstream in("assets/data/save.dat", std::ios::binary);
    
    if (in) {
        Stats temp;
        in.read(reinterpret_cast<char*>(&temp), sizeof(Stats));
        //check
        if (temp.magic == 0x4455434C) {
            stat = temp;
        }
        in.close();
    }
    duck.stats=stat;
}

void GameOver(Duck &duck,Buton &retry,std::vector<std::unique_ptr<Enemy> >& enemy){
    static float lastscore,Increase;
    if(duck.isScore){
        Increase = duck.score*sqrt(duck.score)/5000;
        duck.stats.run += Increase;
        SaveGame(duck);

        enemy.clear();
        duck.hp = duck.maxhp;
        lastscore = duck.score;
        duck.score=0;
        duck.coor = SpawnPoint;
        duck.cFaster=0;
        duck.isScore = false;

        duck.stringer({"More! More!","Must train!","No pain no gain!"});
        duck.deathTimer=1.0f;
        duck.isDeath = true;
    }
    DrawRectangle(0, 0, wwidth, wheight, { 30, 15, 15, 255 });

    const char* goTitle = "GAME OVER";
    int titleSize = 40;
    DrawText(goTitle, wwidth/2 - MeasureText(goTitle, titleSize)/2, wheight/2 - 140, titleSize, RED);

    const char* scoreTxt = TextFormat("Score: %.0f", lastscore);
    int scoreSize = 25;
    DrawText(scoreTxt, wwidth/2 - MeasureText(scoreTxt, scoreSize)/2, wheight/2 - 90, scoreSize, WHITE);

    const char* statTxt = TextFormat("Stat: %.3f + %.3f = %.3f",duck.stats.run - Increase + MaxRaceSpeed,Increase,duck.stats.run+MaxRaceSpeed);
    int statSize = 18;
    DrawText(statTxt, wwidth/2 - MeasureText(statTxt, statSize)/2, wheight/2 - 50, statSize, LIGHTGRAY);

    retry.Draw();
}

void MainMenu(Buton& start){

    DrawRectangle(wwidth/2 - 250 + 5, 100 + 5, 500, 100, Fade(SKYBLUE, 0.4f)); 
    DrawRectangle(wwidth/2 - 250, 100, 500, 100, WHITE);
    DrawText("Rectangle Duck and Rectangles", wwidth/2 - MeasureText("Rectangle Duck and Rectangles", 30)/2, 135, 30, BLACK);
    start.Draw();
}

void winMenu(Duck &duck,Buton& menu, int level){
    if(duck.rscore < duck.stats.bestTimes[level] || duck.stats.bestTimes[level] == 0) duck.stats.bestTimes[level] = duck.rscore;

    if(level == duck.stats.unlockedLevel && duck.rscore <= targetTimes[level]) duck.stats.unlockedLevel++;


    DrawRectangle(0, 0, wwidth, wheight, Color{ 15, 30, 15, 255 });
    if(duck.rscore <= targetTimes[level]){
        const char* winTitle = "VICTORY!";
        int titleSize = 50;
        DrawText(winTitle,wwidth/2 - MeasureText(winTitle, titleSize)/2, wheight/2 - 130, titleSize, GOLD);
    }
    else{
        const char* winTitle = TextFormat("Lose! You didn't reach in goal time");
        int titleSize = 25;
        DrawText(winTitle,wwidth/2 - MeasureText(winTitle, titleSize)/2, wheight/2 - 130, titleSize, DARKGRAY);
    }
    

    const char* finishMsg = "You finished the race!";
    int msgSize = 20;
    DrawText(finishMsg, wwidth/2 - MeasureText(finishMsg, msgSize)/2, wheight/2 - 75, msgSize, WHITE);
    const char* scoreTxt = TextFormat("FINAL SCORE: %.2f", duck.rscore);
    int scoreSize = 30;

    DrawText(scoreTxt, wwidth/2 - MeasureText(scoreTxt, scoreSize)/2 + 2, wheight/2 - 40 + 2, scoreSize, BLACK);
    DrawText(scoreTxt, wwidth/2 - MeasureText(scoreTxt, scoreSize)/2, wheight/2 - 40, scoreSize, SKYBLUE);
    menu.Draw();

    SaveGame(duck);
}

void optionMenu(){
    DrawRectangle(0, 0, wwidth, wheight, Color{ 33, 33, 33, 255 }); 
    DrawText("OPTIONS",wwidth/2 - MeasureText("OPTIONS", 30)/2,40,30, GOLD);
}

namespace texts{
    const char* tutorialTitle = "DUCK TRAINING 101";
    const char* line1 = "- Train your duck then race for better scores.";
    const char* line2 = "- Higher stats mean duck is better at race.";
    const char* line3 = "- Run speed slider in options to adjust your increased stats.";
    const char* line4 = "- Press [ESC] to leave. Sorry for just text tutorial.";
}

void howtoMenu(){
    DrawRectangle(0, 0, wwidth, wheight, { 20, 20, 20, 255 });
    int titleSize = 35;
    DrawText(texts::tutorialTitle, wwidth/2 - MeasureText(texts::tutorialTitle, titleSize)/2, 50, titleSize, GOLD);
    DrawRectangle(wwidth/2 - 100, 95, 200, 2, SKYBLUE);

    int bodySize = 20;
    int startY = 150;
    int lineSpacing = 40;

    DrawText(texts::line1, wwidth/2 - 250, startY, bodySize, LIGHTGRAY);
    DrawText(texts::line2, wwidth/2 - 250, startY + lineSpacing, bodySize, LIGHTGRAY);
    DrawText(texts::line3, wwidth/2 - 250, startY + (lineSpacing * 2), bodySize, SKYBLUE);
    DrawText(texts::line4, wwidth/2 - 250, startY + (lineSpacing * 3), bodySize, ORANGE);
}

void rMenuCheck(RaceMenu& racemenu){
    for(int i = 0; i < (int)racemenu.butons.size(); i++) racemenu.butons[i]->isClicked();
}

void preButtonMap(std::map<std::string,std::unique_ptr<Buton>>& buttons, State *GameState,anySound& s){
    buttons["runRetry"] = std::make_unique<Start>(wwidth/2.0f - bwidth - 10.0f, wheight/2.0f + 40.0f, bwidth, bheight, "Retry", GameState, RUN,s);
    buttons["goMenu"] = std::make_unique<Start>(wwidth/2.0f + 10.0f,wheight/2.0f + 40.0f,bwidth,bheight,"Menu", GameState,MAINMENU,s);
    buttons["mainTrain"] = std::make_unique<Start>(wwidth/2.0f - 190.0f, 2*wheight/3.0f,bwidth,bheight,"Train", GameState,RUN,s);
    buttons["raceSelect"] = std::make_unique<Start>(wwidth/2.0f - 90.0f, 2*wheight/3.0f,bwidth,bheight,"Race", GameState,RACEMENU,s);
    buttons["options"] = std::make_unique<Start>(wwidth/2.0f + 10.0f, 2*wheight/3.0f,bwidth,bheight,"Options", GameState,OPTION,s);
    buttons["howTo"] = std::make_unique<Start>(wwidth/2.0f + 110.0f, 2*wheight/3.0f,bwidth,bheight,"How to", GameState,HOWTO,s);
    buttons["winToMenu"] = std::make_unique<Start>(wwidth/2.0f-bwidth/2.0f,wheight/2.0f + 40.0f,bwidth,bheight,"Menu", GameState,MAINMENU,s);
    
    buttons["howToMenu"] = std::make_unique<Start>(wwidth/2.0f - bwidth/2.0f,wheight-80.0f,bwidth,bheight,"Return", GameState,MAINMENU,s);
    buttons["optionToMenu"] = std::make_unique<Start>(wwidth/2.0f - bwidth/2.0f,wheight-80.0f,bwidth,bheight,"Return", GameState,MAINMENU,s);
    buttons["pauseToMenu"] = std::make_unique<Start>(wwidth/2.0f - bwidth/2.0f,wheight/2.0f + 10.0f,bwidth,bheight,"Menu", GameState,MAINMENU,s);
}

void preSliderMap(std::map<std::string,std::unique_ptr<Slider>>& sliders, Duck& duck, float* global){
    sliders["sound"] = std::make_unique<Slider>(120.0f,140.0f, 100.0f, 8.0f, global, "Master Volume:");
    sliders["run"] = std::make_unique<Slider>(120.0f,180.0f, 100.0f, 8.0f, &duck.rMult, "Run Mult:");
}

void isStop(State *game){
    if(IsKeyPressed(KEY_SPACE)) *game = PAUSE;
}

void Stopped(State *game,State which){
    if(IsKeyPressed(KEY_SPACE)) *game = which;
}

void pauseMenu(){
    const char* text = "PAUSED";
    DrawText(text, wwidth/2 - MeasureText(text, 40)/2, wheight/2 - 100, 40, GOLD);

    const char* subtext = "Press space to return";
    DrawText(subtext, wwidth/2 - MeasureText(subtext, 20)/2, wheight/2 - 40, 20, LIGHTGRAY);
}

void isStateChanged(State& game, MusicManager& mngr, anySound& s, Duck &duck, Camera2D& cam,std::vector<std::unique_ptr<Enemy> >& enemy){
    static State last = StartState;
    if(game != last){
        if(game == MAINMENU){
            mngr.Play(&s.mainMenuM);
            last = game;
            duck.coor = SpawnPoint;
            duck.score = 0;
            duck.rSpeed=0;
            duck.lastlook=true;
            cam.target = SpawnPoint;

            duck.hp = duck.maxhp;
            duck.cFaster=0;
            enemy.clear();
            
            //Music ve değerleri sıfırla
        }
        if(game == RACE){
            mngr.Play(&s.raceM);
            last = game;
            //Music camera duck olduğu yere çekme
        }
        if(game == RUN){
            mngr.Play(&s.runM);
            last = game;
            //Music
        }
    
    }
}


