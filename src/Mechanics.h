#ifndef MECHANICS_H_
#define MECHANICS_H_

#include"raylib.h"
#include"Objects.h"

void enemyCycle(std::vector<std::unique_ptr<Enemy> >& enemy, Duck& duck);
void Run(std::vector<std::unique_ptr<Enemy> >& enemy, Duck& duck,State &game);

void raceCycle(Duck& duck,std::vector<std::vector<std::unique_ptr<Block>>>& rBlocks,int level);
void Race(Duck& duck,std::vector<std::vector<std::unique_ptr<Block>>>& rBlocks,Camera2D& camera,int level);

void PreCam(Camera2D& camera, Duck& duck);
void RCamFollow(Camera2D& camera, Duck& duck);

void deathChecker(Duck &duck);
void deathDraw(Duck &duck);

void slideBackground(BackGround background, Duck& duck);
void slideBackground2D(BackGround background, Duck& duck);

#endif