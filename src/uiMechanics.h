#ifndef UIMECHANICS_H_
#define UIMECHANICS_H_

#include "ui.h"

void GameOver(Duck &duck,Buton& retry,std::vector<std::unique_ptr<Enemy> >& enemy);
void MainMenu(Buton& start);
void rMenuCheck(RaceMenu& racemenu);
void preButtonMap(std::map<std::string,std::unique_ptr<Buton>>& buttons, State *GameState,anySound& s);
void preSliderMap(std::map<std::string,std::unique_ptr<Slider>>& sliders, Duck& duck, float* global);
void winMenu(Duck &duck, Buton& menu, int level);
void optionMenu();
void howtoMenu();

void isStop(State *game);
void Stopped(State *game,State which);
void pauseMenu();

void SaveGame(const Duck &duck);
void LoadGame(Duck &duck);

void isStateChanged(State& game, MusicManager& mngr, anySound& s, Duck &duck, Camera2D& cam,std::vector<std::unique_ptr<Enemy> >& enemy);

#endif