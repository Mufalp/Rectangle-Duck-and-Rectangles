#ifndef UI_H_
#define UI_H_

#include<raylib.h>
#include<cstring>
#include"Objects.h"

//I wouldnt wish any living person code button.
class Buton{
    public:
    Rectangle rect;
    Color color,hover;
    char txt[25];
    bool isActive = true;

    virtual void isClicked()=0;
    virtual void Draw()=0;
    virtual ~Buton(){}
};
//State changer button
class Start : public Buton{
    public:
    State change, *curr;
    anySound& effect;
    static int turn;

    Start(float x, float y, float w, float h, const char t[25],State *st,State need, anySound& effect);
    void isClicked() override;
    void Draw() override;
};

//Race level buton
class RaceButon : public Buton{
    public:
    int *level;
    int thislvl;
    State *curr;

    RaceButon(float x, float y, float w, float h, int *lvl,int need ,State *st);
    void isClicked() override;
    void Draw() override;
};
//Base class of menu
class Menu{
    
    public:
    Rectangle rect;
    Color color;
    
    virtual void Draw()=0;
    virtual ~Menu(){}
};
//That race menu
class RaceMenu : public Menu{
    private:
    Duck *duck;
    public:
    State *curr;
    int *level;

    std::vector<std::unique_ptr<Buton>> butons;
    bool activates[levelnum];

    RaceMenu(float x, float y, float w, float h,State* st, int* lvl,Duck* duck, anySound& effect);
    void Draw() override;
};
// No base class OMG!
class Slider {
    public:
    Rectangle rect;
    float curr,max, *value,oldvalue, radius;
    Color done,undone,ball;
    Vector2 center;
    bool isDragging=false;
    std::string str;
    Slider(float x, float y, float w, float r, float* val, const std::string& c);

    void isSliding();
    void Draw();
};



#endif