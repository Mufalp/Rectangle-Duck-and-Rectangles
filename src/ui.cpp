#include"raylib.h"
#include"ui.h"

Start::Start(float x, float y, float w, float h, const char t[25],State *st,State need, anySound& s):  effect(s){
    rect = {x, y, w, h};
    strcpy(txt,t);
    color = { 45, 45, 45, 255 }, hover = { 80, 80, 80, 255 };
    change = need;
    curr = st;
}
int Start::turn = 0;

void Start::isClicked(){
    Vector2 mousepos = GetMousePosition();
    bool over = CheckCollisionPointRec(mousepos,rect);

    if(over && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        *curr = change;
        if(turn%2) PlaySound(effect.xsound);
        else PlaySound(effect.ysound);
        turn++;
    }
}

void Start::Draw(){
    bool isHovered = CheckCollisionPointRec(GetMousePosition(), rect);
    Color baseColor = isHovered ? hover : color;

    DrawRectangleRec(rect,baseColor);

    int fSize = isHovered ? 25 : 20;
    float tX = rect.x + (rect.width / 2.0f) - (MeasureText(txt, fSize) / 2.0f);
    float tY = rect.y + (rect.height / 2.0f) - (fSize / 2.0f);

    DrawText(txt, tX + 2, tY + 2, fSize, Fade(BLACK, 0.5f));
    DrawText(txt, tX, tY, fSize, WHITE);
}

RaceMenu::RaceMenu(float x, float y, float w, float h,State* st, int* lvl,Duck* duck, anySound& s):curr(st),level(lvl) {
    rect = {x, y, w, h};
    color = {20,20,20,255};
    this->duck = duck;

    for(int i = 0; i < levelnum; i++){
        butons.push_back(std::make_unique<RaceButon>(rect.x+i*(20.0f+bwidth)+10.0f,80.0f,bwidth,bheight,level,i,curr));
    }
    
    butons.push_back(std::make_unique<Start>(wwidth/2.0f - bwidth/2.0f,wheight-80.0f,bwidth,bheight,"return",curr,MAINMENU,s));
}

void RaceMenu::Draw(){
    DrawRectangle(0, 0, wwidth, wheight, { 15, 15, 30, 255 });

    for(int i = 0; i < levelnum; i++) i <= duck->stats.unlockedLevel ? activates[i] = true : activates[i] = false;
    for(int i = 0; i < levelnum; i++) butons[i]->isActive = activates[i];

    DrawRectangleRec(rect,color);

    for(int i = 0; i < (int)butons.size(); i++) butons[i]->Draw();
    
}

RaceButon::RaceButon(float x, float y, float w, float h, int *lvl,int need,State *st) : level(lvl),thislvl(need), curr(st){
    rect = {x, y, w, h};
    color = { 45, 45, 45, 255 }, hover = { 80, 80, 80, 255 };
    strcpy(txt,TextFormat("%d",thislvl+1));
}

void RaceButon::isClicked(){
    Vector2 mousepos = GetMousePosition();
    bool over = CheckCollisionPointRec(mousepos,rect);
    if(isActive){
        if(over && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){//level progress
            *level = thislvl;
            *curr = RACE;
        }
    }
    
}

void RaceButon::Draw(){
    bool isHovered = CheckCollisionPointRec(GetMousePosition(), rect);
    
    Color baseColor = (isActive && isHovered) ? hover : color;

    DrawRectangleRec(rect, baseColor);

    if (isActive) {
        int fSize = isHovered ? 25 : 20;
        float tX = rect.x + (rect.width / 2.0f) - (MeasureText(txt, fSize) / 2.0f);
        float tY = rect.y + (rect.height / 2.0f) - (fSize / 2.0f);

        DrawText(txt, tX + 2, tY + 2, fSize, Fade(BLACK, 0.5f));
        DrawText(txt, tX, tY, fSize, WHITE);

        if (isHovered) {
            const char* goalTxt = TextFormat("GOAL: %.0f second", targetTimes[thislvl]);
            DrawText(goalTxt,wwidth / 2 - MeasureText(goalTxt, 20) / 2, 20, 20, WHITE);
        }
    } 
    else {
        int fSize = 20;
        float tX = rect.x + (rect.width / 2.0f) - (MeasureText("LOCKED", fSize) / 2.0f);
        float tY = rect.y + (rect.height / 2.0f) - (fSize / 2.0f);

        DrawText("LOCKED", tX, tY, fSize, Fade(WHITE, 0.6f)); 
    }
    
}

Slider::Slider(float x, float y, float w, float r, float* val, const std::string& c) : radius(r){
    rect = {x, y, w, 10.0f};
    center = {x+w,y-5.0f+r};//start max
    done = SKYBLUE,undone = { 80, 80, 80, 255 }, ball = WHITE;
    curr = w, max = w, value = val,oldvalue = *val;
    str = c;
}

void Slider::isSliding(){
    Vector2 mousepos = GetMousePosition();
    bool over = CheckCollisionPointCircle(mousepos, center, radius);

    if (over && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) isDragging = true;
    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) isDragging = false;

    if (isDragging) {
        if (mousepos.x < rect.x) center.x = rect.x;
        else if (mousepos.x > rect.x + rect.width) center.x = rect.x + rect.width;
        else center.x = mousepos.x;

        float percent = (center.x - rect.x) / rect.width;
        
        *value = percent * oldvalue; 
    }
}

void Slider::Draw(){
    float fillWidth = center.x - rect.x;
    DrawRectangle(rect.x, rect.y, fillWidth, rect.height, done);
    DrawRectangle(center.x, rect.y, rect.width - fillWidth, rect.height, undone);
    DrawCircleV({center.x,center.y+radius/2}, radius, ball);
    DrawText(TextFormat("%.2f",*value),rect.x+rect.width+10.0f,rect.y,15,WHITE);
    DrawText(TextFormat("%s",str.c_str()),rect.x-MeasureText(str.c_str(),15)-10.0f,rect.y,15,WHITE);
}

