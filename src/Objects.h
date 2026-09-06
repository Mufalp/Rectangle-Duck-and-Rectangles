#ifndef OBJECTS_H_
#define OBJECTS_H_

#include "raylib.h"
#include "Common.h"
#include "External.h"
#include <sstream>
#include <iostream>
#include <memory>
#include <vector>
#include <cmath>
#include <map>
#include <fstream>
#include <cstdio>

struct Stats{
    int magic = 0x4455434C;
    float run=0,fly=0,swim=0;
    int unlockedLevel = 0;
    float bestTimes[10];
};

//The duck. He work hard, take care of him.
class Duck{
    public:
        //General
        Color color = YELLOW,eyeColor = GREEN;
        int maxhp=3,hp=3;
        State lastState=MAINMENU;
        Stats stats;
        float rMult=1.0f,fMult=1.0f,sMult=1.0f;
        //Race
        std::string deathText;
        void stringer(const std::vector<std::string>& texts);//If need apply any string
        const int COYOTE_BUFFER = 6;
        int coyoteCounter = 0;
        float rSpeed=0,rAcc=RaceAcc,rFall=0;
        bool lastlook=true;
        void rRun();
        void rJump();
        //Run
        float jumpf=6.5f,speedf,score=0,rscore=0,deathTimer=0;
        bool isJump = false,isGround=true,isScore=true,isDeath=false;
        static float cFaster, scrSpeed;
        Vector2 coor = {20.0f,250.0f}, shape = {20.0f,50.0f};
        void Jump();
        void rDuckDraw(bool isConst);
        //Fly

        //Swim

};
//Base class of enemies
class Enemy{
    public:
        virtual void Come() = 0;
        bool isActive = true;
        Vector2 coor,shape;
        float speed, timeAcc=0;
        Color color;
        virtual ~Enemy(){}
};
//Classic enemy, constant speed
class ClassicE : public Enemy{
    public:
        ClassicE(float sped);
        
        void Come() override;
};
//Accelerate enemy
class Accelerator : public Enemy{
    public:
        float acc;
        Accelerator(float sped);
        void Come() override;
};
//Jumping enemy
class Jumper : public Enemy{
    public:
        float jump=0,jumpf;
        bool isJump=false;
        Jumper(float sped,float sped2);
        void Come() override;
};
//Jump right into your head
class Dasher : public Enemy{
    private:
        Duck* target;
    public:
        float jump=0,jumpf=0,jumpRange;
        bool isJump=false;
        Dasher(float sped,float sped2,Duck* player);
        void Come() override;
};
//Base class of blocks
class Block{
    public:
    Rectangle rect;
    Color color;
    bool haveGround;

    virtual void Some(Duck& duck)=0;
    virtual ~Block(){}
};
//Normal block
class RaceBlocks : public Block{
    public:
    
    RaceBlocks(float x,float y, float w, float h, Color c);
    void Some(Duck& duck) override;
};
//Dont touch it
class DeathBlock : public Block{
    public:
    DeathBlock(float x,float y, float w, float h, Color c);
    void Some(Duck& duck) override;
};
//Floating block
class FloatBlock : public Block{
    public:
    int timer = 0;
    bool press = false;
    
    FloatBlock(float x,float y, float w, float h, Color c);
    void Some(Duck& duck) override;
};
//Finish block, You win!
class WinBlock : public Block{
    public:
    State *Game;
    WinBlock(float x,float y, float w, float h, Color c,State *GameState);
    void Some(Duck& duck) override;
};


#endif