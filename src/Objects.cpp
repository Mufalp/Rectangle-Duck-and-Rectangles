#include"Objects.h"


float Duck::cFaster=0;

ClassicE::ClassicE(float sped) {
    coor = {wwidth+10.0f,275.0f};
    shape = {25.0f,25.0f};
    color = GRAY;
    speed = sped;
}

Accelerator::Accelerator(float sped) {
    coor = {wwidth+10.0f,275.0f};
    shape = {25.0f,25.0f};
    color = LIME;
    speed = 1.0f;
    acc = sped;
}

Jumper::Jumper(float sped,float sped2) {
    coor = {wwidth+10.0f,275.0f};
    shape = {25.0f,25.0f};
    color = MAGENTA;
    speed = sped;
    jumpf = sped2;
}

Dasher::Dasher(float sped,float sped2,Duck* player) : target(player) {
    coor = {wwidth+10.0f,275.0f};
    shape = {25.0f,25.0f};
    color = ORANGE;
    speed = sped2;
    jumpRange = sped;
}

//Jump Mechanic
void Duck::Jump(){
    this->coor.y += this->speedf;
    if(this->coor.y >= 2*wheight/3-this->shape.y){
        this->coor.y = 2*wheight/3-this->shape.y;
        this->speedf = 0;
    }
    else this->speedf += gravity;

    if(IsKeyPressed(KEY_UP) && this->speedf == 0){
        this->speedf = -this->jumpf;
        this->isJump = true;
    }
    else if(!(IsKeyDown(KEY_UP) && this->isJump)){
        this->isJump = false;
        if(this->speedf < 0) this->speedf/=2;
    }
}

//Race Run mechanic
void Duck::rRun(){
    float UpdatedSpeed = MaxRaceSpeed + stats.run * rMult;
    if(IsKeyDown(KEY_RIGHT)){
        rSpeed+=rAcc;
        lastlook=true;
    }
    else if(IsKeyDown(KEY_LEFT)){
        rSpeed-=rAcc;
        lastlook=false;
    }
    else if((rSpeed < 0.2 && rSpeed > -0.2)) rSpeed=0;
    else rSpeed > 0 ? rSpeed-=rAcc : rSpeed+=rAcc;
    
    if(rSpeed >= UpdatedSpeed) rSpeed = UpdatedSpeed;
    else if(rSpeed <= -UpdatedSpeed) rSpeed = -UpdatedSpeed;
    coor.x += rSpeed;
}

void Duck::rJump(){

    if (isGround) coyoteCounter = COYOTE_BUFFER;
    else{
        if (coyoteCounter > 0) coyoteCounter--;
    }

    if(IsKeyPressed(KEY_UP) && coyoteCounter > 0){
        coor.y-=0.5f;//cut collision
        rFall = -jumpf;
        isJump = true;
        isGround=false;
        coyoteCounter=0;
    }
    if(!(IsKeyDown(KEY_UP) && isJump)){
        isJump = false;
        if(rFall < 0) rFall/=2;
    }
    
    if(!isGround) rFall += gravity;
    else rFall=0;

    coor.y += rFall;
}

void Duck::rDuckDraw(bool isConst){
    
    if(lastlook || isConst){
        DrawRectangleV(coor,shape,color);
        DrawRectangleGradientH(coor.x+shape.x/2,coor.y+10.0f,shape.x,10.0f,YELLOW,ORANGE);
        DrawCircle(coor.x+8.0f,coor.y+8.0f,4.0f,BLACK);
        DrawCircle(coor.x+8.0f,coor.y+8.0f,3.0f,WHITE);
        DrawCircle(coor.x+9.0f,coor.y+8.0f,1.0f,BLACK);
    }
    else {
        DrawRectangleV(coor,shape,color);
        DrawRectangleGradientH(coor.x-shape.x/2,coor.y+10.0f,shape.x,10.0f,ORANGE,YELLOW);
        DrawCircle(coor.x+shape.x-8.0f,coor.y+8.0f,4.0f,BLACK);
        DrawCircle(coor.x+shape.x-8.0f,coor.y+8.0f,3.0f,WHITE);
        DrawCircle(coor.x+shape.x-9.0f,coor.y+8.0f,1.0f,BLACK);
        
    }
}

void Duck::stringer(const std::vector<std::string>& texts){
    int x = GetRandomValue(0,texts.size()-1);
    deathText = texts[x];
}

void ClassicE::Come(){
    coor.x -= speed;
    timeAcc += GetFrameTime();
    if(timeAcc >= 6.0f) isActive = false;
}

void Accelerator::Come(){
    coor.x -= speed;
    timeAcc += GetFrameTime();
    if(timeAcc >= 6.0f) isActive = false;
    speed+=acc;
}

void Jumper::Come(){
    coor.x-=speed;
    coor.y+=jump;
    timeAcc += GetFrameTime();
    if(timeAcc >= 6.0f) isActive = false;
    if(coor.y >= 2*wheight/3-shape.y){
        coor.y = 2*wheight/3-shape.y;
        jump = 0;
        isJump=false;
    }
    else jump += gravity;

    if(!isJump){
        jump = -jumpf;
        isJump=true;
    }
}

void Dasher::Come(){
    coor.x-=speed;
    coor.y+=jump;
    timeAcc += GetFrameTime();
    if(timeAcc >= 6.0f) isActive = false;
    if(coor.y >= 2*wheight/3-shape.y){
        coor.y = 2*wheight/3-shape.y;
        jump = 0;
        isJump=false;
    }
    else jump += gravity;

    if(!target->isJump);//dont jump
    else if (!isJump && (coor.x - target->coor.x) <= jumpRange) {
        float dx = coor.x - target->coor.x;
        if (dx <= 0) dx = 1.0f; // division of 0
        float N = dx / speed;
        float dy = target->coor.y - coor.y;
        // formula: v0 = dy/N - (g * (N-1) / 2)
        jump = (dy / N) - (gravity * (N - 1) / 2.0f);
        
        isJump = true;
    }
}

RaceBlocks::RaceBlocks(float x,float y, float w, float h, Color c){
    rect.x=x,rect.y=y,rect.width=w,rect.height=h,color=c;
    haveGround = true;
}

void RaceBlocks::Some(Duck& duck){

    float dL = duck.coor.x;
    float dR = duck.coor.x + duck.shape.x;
    float dT = duck.coor.y;
    float dB = duck.coor.y + duck.shape.y;

    float bL = rect.x;
    float bR = rect.x + rect.width;
    float bT = rect.y;
    float bB = rect.y + rect.height;
    //Inside or not
    if (dR > bL && dL < bR && dB > bT && dT < bB) {

        float overlapL = dR - bL;
        float overlapR = bR - dL;
        float overlapT = dB - bT;
        float overlapB = bB - dT;
        // X or Y
        float minOverlapX = (overlapL < overlapR) ? overlapL : overlapR;
        float minOverlapY = (overlapT < overlapB) ? overlapT : overlapB;

        if (minOverlapX < minOverlapY) {
            // horizontal
            if (overlapL < overlapR) {
                // block left
                duck.coor.x = bL - duck.shape.x;
            }
            else {
                // block right
                duck.coor.x = bR;
            }
            duck.rSpeed = 0;
        } 
        else {
            // vertical
            if (overlapT < overlapB) {
                // floor
                duck.coor.y = bT - duck.shape.y;
                duck.rFall = 0;
                duck.isGround = true;
            }
            else {
                // Ahh! My head!
                duck.coor.y = bB;
                duck.rFall = 0;
            }
        }
    }
    
}

DeathBlock::DeathBlock(float x,float y, float w, float h, Color c){
    rect.x=x,rect.y=y,rect.width=w,rect.height=h,color=c;
    haveGround = false;
}

void DeathBlock::Some(Duck& duck){
    if(CheckCollisionRecs({duck.coor.x,duck.coor.y,duck.shape.x,duck.shape.y},rect)){
        
        duck.coor = SpawnPoint;
        
        duck.stringer({"Why did you die?","Skill issue!","You are hopeless!"});

        duck.deathTimer=1.0f;
        duck.isDeath = true;
    }
}

FloatBlock::FloatBlock(float x,float y, float w, float h, Color c){
    rect.x=x,rect.y=y,rect.width=w,rect.height=h,color=c;
    haveGround = true;
}

void FloatBlock::Some(Duck& duck){
    
    bool xOverlap = (duck.coor.x + duck.shape.x > rect.x) && (duck.coor.x < rect.x + rect.width);

    bool isFallingOnto = (duck.coor.y + duck.shape.y >= rect.y-0.5f) && 
    (duck.coor.y + duck.shape.y <= rect.y + 10.0f);//that would be problem
    
    if(press) if(timer > 0) timer--;

    // when falling
    if (xOverlap && isFallingOnto && duck.rFall >= 0) {
        if (IsKeyDown(KEY_DOWN)) {
            
            duck.coor.y += 0.5f;
            duck.isGround = false;
            press = true;
            timer = 10;
            
        } 
        else if (timer <= 0) {
            duck.coor.y = rect.y - duck.shape.y; 
            duck.rFall = 0;
            duck.isGround = true;
            press=false;
        }
    }
    
}

WinBlock::WinBlock(float x,float y, float w, float h, Color c,State *GameState){
    rect.x=x,rect.y=y,rect.width=w,rect.height=h,color=c;
    Game = GameState, haveGround = false;
}

void WinBlock::Some(Duck& duck){
    if(CheckCollisionRecs({duck.coor.x,duck.coor.y,duck.shape.x,duck.shape.y},rect)){
        *Game = RACEWIN;
        duck.rSpeed=0;
        duck.lastlook=true;
        duck.coor = SpawnPoint;
        duck.rscore = duck.score;
        duck.score=0;
    }
}
