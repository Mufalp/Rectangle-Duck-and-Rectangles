#include "Mechanics.h"


void enemyCycle(std::vector<std::unique_ptr<Enemy> >& enemy, Duck& duck){
    duck.isScore=true;
    static float timeRun = 0, RunInterval = 3.0f;
    duck.cFaster += GetFrameTime();
    timeRun += GetFrameTime();
    duck.score += GetFrameTime();

    while(timeRun >= RunInterval){
        timeRun=0;

        switch(GetRandomValue(1,4)){
            case 1:
                enemy.push_back(std::make_unique<ClassicE>(4.0f+duck.cFaster/30));
                break;
            case 2:
                enemy.push_back(std::make_unique<Accelerator>(0.075f+duck.cFaster/400));
                break;
            case 3:
                enemy.push_back(std::make_unique<Jumper>(3.0f+duck.cFaster/30,GetRandomValue(30,50)/10));
                break;
            case 4:
                enemy.push_back(std::make_unique<Dasher>((float)GetRandomValue(100, 150),2.5f+duck.cFaster/30,&duck));
                break;
        }

        
        float progress = duck.cFaster / 75.0f;
        if (progress > 1.0f) progress = 1.0f;
        float baseInterval = 3.0f - (progress * (2.5));

        float jitter = (float)GetRandomValue(-20, 20) / 100.0f;
        RunInterval = baseInterval + jitter;

        if (RunInterval < 0.4f) RunInterval = 0.4f;
    }

    if(!enemy.empty() && !(enemy[0]->isActive)) enemy.erase(enemy.begin()); //upgradeble
}

void Run(std::vector<std::unique_ptr<Enemy> >& enemy, Duck& duck,State &game){
    DrawRectangle(0,floorY,wwidth,wheight/5,GRAY);//floor

    for(int i = 0; i < (int)enemy.size(); i++){
        if (enemy[i]->isActive){
            Rectangle rec1 = {duck.coor.x,duck.coor.y,duck.shape.x,duck.shape.y}, 
            rec2={enemy[i]->coor.x,enemy[i]->coor.y,enemy[i]->shape.x,enemy[i]->shape.y};
            if(CheckCollisionRecs(rec1,rec2)){
                duck.hp--;
                enemy[i]->isActive = false;
                if(duck.hp <= 0)  game=GAMEOVER;
            }

            enemy[i]->Come();
            DrawRectangleV(enemy[i]->coor,enemy[i]->shape,enemy[i]->color);
        }
    }
    
    duck.rDuckDraw(true);

    DrawText(TextFormat("HP: %d\nScore: %.0f",duck.hp,duck.score),30,30,20,RED);
    
}

bool CheckGrounded(const Duck& duck, const std::vector<std::unique_ptr<Block>>& blocks) {//iceri yaz

    for (const auto& b : blocks) {
        if (duck.coor.x + duck.shape.x > b->rect.x && duck.coor.x < b->rect.x + b->rect.width) {
            if (std::abs(duck.coor.y + duck.shape.y + 0.15f - b->rect.y) < 0.3f && b->haveGround) { 
                return true; 
            }
        }
    }
    return false;
}

void raceCycle(Duck& duck,std::vector<std::vector<std::unique_ptr<Block>>>& rBlocks,int level){
    duck.rRun();
    duck.rJump();

    for(int i = 0; i < (int)rBlocks[level].size(); i++){
        rBlocks[level][i]->Some(duck);   
    }
    duck.isGround = CheckGrounded(duck,rBlocks[level]);
}


void Race(Duck& duck,std::vector<std::vector<std::unique_ptr<Block>>>& rBlocks,Camera2D& camera,int level){
    duck.score+=GetFrameTime();
    BeginMode2D(camera);
    for(int i = 0; i < (int)rBlocks[level].size(); i++){
        DrawRectangleRec(rBlocks[level][i]->rect,rBlocks[level][i]->color);
    }
    
    switch (level){
        case 0:
            DrawText("Arrow keys to move",30,wheight/3,20,WHITE);
            DrawText("Did you train?",5*wwidth/3+10.0f,wheight/3+20.0f,20,WHITE);
            DrawText("You should be hurry here, this is long path.",5*wwidth/2-250.0f,2*wheight/3+250.0f,20,WHITE);
            DrawText("Green block is finish line.",7.0f*wwidth/6,wheight/3-350.0f,20,WHITE);
            break;
        case 1:
            DrawText("Down arrow key to fall",2*wwidth/3,2*wheight/3-50.0f,20,WHITE);
            DrawText("If you can't reach not my problem.",5*wwidth/3-275.0f,2*wheight/3+120.0f,20,WHITE);
            DrawText("Go down. You can try right way as well.",11*wwidth/3+100.0f,2*wheight/3+50.0f,20,WHITE);
    }
    
    duck.rDuckDraw(false);
    EndMode2D();

    DrawText(TextFormat("Time: %.2f",duck.score),30,30,20,RED);
}

void PreCam(Camera2D& camera, Duck& duck){
    camera.target = duck.coor;
    camera.offset = (Vector2){ wwidth/2.0f, wheight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
}

void RCamFollow(Camera2D& camera, Duck& duck){
    camera.target.x += (duck.coor.x - camera.target.x) * CameraSpeed;
    camera.target.y += (duck.coor.y - camera.target.y) * CameraSpeed;
}

void deathChecker(Duck &duck){
    if(duck.isDeath){
        duck.deathTimer -= GetFrameTime();

        if (duck.deathTimer <= 0) {
            duck.isDeath = false;
            duck.deathTimer = 0;

            duck.score=0;
            duck.coor = SpawnPoint;
            duck.rSpeed=0;
            duck.lastlook=true;
        }
    }
}

void deathDraw(Duck &duck){
    if(duck.isDeath){
        DrawRectangle(0, 0, wwidth, wheight, BLACK);
        //Fade(BLACK, 0.6f)
        
        
        int fontSize = 50;

        int textWidth = MeasureText(duck.deathText.c_str(), fontSize);
        int centerX = wwidth / 2 - textWidth / 2;
        int centerY = wheight / 2 - fontSize / 2;

        int shakeX = GetRandomValue(-15, 15);
        int shakeY = GetRandomValue(-15, 15);

        Color flashColor = WHITE;
        if (((int)(GetTime() * 20) % 2) == 0) flashColor = BLACK;
        DrawText(duck.deathText.c_str(), centerX + shakeX, centerY + shakeY, fontSize, flashColor);
    }
}

void slideBackground(BackGround background, Duck& duck){
    static float start = 0.0f;
    static float start2 = 0.0f;

    ClearBackground(BLACK);
    DrawTexture(background.back,0 , 0, WHITE);

    duck.scrSpeed += GetFrameTime()/30.0f;
    start-=duck.scrSpeed;

    if(start <= -wwidth*2) start = 0.0f;

    duck.scrSpeed += GetFrameTime()/30.0f;
    start2-=duck.scrSpeed*0.75f;

    if(start2 <= -wwidth*2) start2 = 0.0f;

    DrawTexture(background.backbackground,(int)start2, 0, WHITE);
    DrawTexture(background.backbackground,(int)start2+wwidth*2, 0, WHITE);
    DrawTexture(background.frontbackground,(int)start, 0, WHITE);
    DrawTexture(background.frontbackground,(int)start+wwidth*2, 0, WHITE);

    
}
void slideBackground2D(BackGround background, Duck& duck) {
    static Vector2 offset = {0.0f, 0.0f};
    
    ClearBackground(BLACK);

    
    DrawTexture(background.backraceground, 0, 0, WHITE);

    float dt = GetFrameTime();

    offset.x -= duck.rSpeed * dt * 6.0f;
    offset.y -= duck.rFall * dt * 3.0f;

    
    offset.x = fmodf(offset.x, (float)wwidth);
    offset.y = fmodf(offset.y, (float)wheight);

    
    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            DrawTexture(background.frontraceground, 
                        (int)offset.x + x * wwidth, 
                        (int)offset.y + y * wheight, WHITE);
        }
    }
}


