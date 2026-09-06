#include "Levels.h"



void loadLevel(const std::string& filename, std::vector<std::unique_ptr<Block>>& level, State* GameState) {
    level.clear();
    std::ifstream file(filename);
    if (!file.is_open()) return;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        char type;
        float x, y, w, h;
        
        if (ss >> type >> x >> y >> w >> h) {
            switch (type) {
                case 'R':
                    level.push_back(std::make_unique<RaceBlocks>(x, y, w, h, GRAY));
                    break;
                case 'F':
                    level.push_back(std::make_unique<FloatBlock>(x, y, w, h, ORANGE));
                    break;
                case 'D':
                    level.push_back(std::make_unique<DeathBlock>(x, y, w, h, RED)); // Veya siyah olanlar için ayarlanabilir
                    break;
                case 'W':
                    level.push_back(std::make_unique<WinBlock>(x, y, w, h, GREEN, GameState));
                    break;
            }
        }
    }
}

void preLevelDesign(std::vector<std::vector<std::unique_ptr<Block>>>& rBlocks,State *GameState){
    std::vector<std::unique_ptr<Block>> level0;
    loadLevel("assets/levels/level0.txt", level0, GameState);
    rBlocks.push_back(std::move(level0));

    std::vector<std::unique_ptr<Block>> level1;
    loadLevel("assets/levels/level1.txt", level1, GameState);
    rBlocks.push_back(std::move(level1));

    // //Level-0
    // std::vector<std::unique_ptr<Block>> level0;
    // //First part
    // level0.push_back(std::make_unique<RaceBlocks>(0,2*wheight/3,wwidth,wheight/50,GRAY));
    // level0.push_back(std::make_unique<RaceBlocks>(wwidth/2,wheight/3,wwidth/30,wheight/3,GRAY));
    // level0.push_back(std::make_unique<RaceBlocks>(0,2*wheight/3-100.0f,wwidth/3,wheight/50,GRAY));
    // //long jumps
    // level0.push_back(std::make_unique<RaceBlocks>(wwidth,2*wheight/3-80.0f,wwidth/3,wheight/50,GRAY));
    // level0.push_back(std::make_unique<RaceBlocks>(5*wwidth/3-20.0f,2*wheight/3-80.0f,wwidth/3+20.0f,wheight/50,GRAY));
    // level0.push_back(std::make_unique<RaceBlocks>(5*wwidth/2-70.0f,2*wheight/3-80.0f,wwidth/3,wheight/50,GRAY));
    // //Higher part
    // level0.push_back(std::make_unique<RaceBlocks>(18*wwidth/6-10.0f,2*wheight/3-120.0f,wwidth/3,wheight/50,GRAY));
    // level0.push_back(std::make_unique<RaceBlocks>(20*wwidth/6,2*wheight/3-200.0f,wwidth/6,wheight/50,GRAY));
    // level0.push_back(std::make_unique<RaceBlocks>(18.5*wwidth/6,2*wheight/3-260.0f,wwidth/6,wheight/50,GRAY));
    // level0.push_back(std::make_unique<RaceBlocks>(21*wwidth/6,2*wheight/3-320.0f,4*wwidth/6,wheight/50,GRAY));
    // level0.push_back(std::make_unique<RaceBlocks>(22.5f*wwidth/6,wheight/3-320.0f,wwidth/30,wheight/3,GRAY));
    // level0.push_back(std::make_unique<RaceBlocks>(23.5f*wwidth/6,wheight/3-255.0f,wwidth/6,wheight/50,GRAY));
    // //Failed jump / Alternative way
    // level0.push_back(std::make_unique<RaceBlocks>(5*wwidth/2-240.0f,2*wheight/3+225.0f,wwidth/3+180.0f,wheight/50,GRAY));
    // level0.push_back(std::make_unique<RaceBlocks>(18*wwidth/6,2*wheight/3+225.0f,wwidth/24,wheight/50,GRAY));
    // level0.push_back(std::make_unique<RaceBlocks>(20*wwidth/6.0f,2*wheight/3+225.0f,wwidth/24,wheight/50,GRAY));
    // level0.push_back(std::make_unique<RaceBlocks>(22*wwidth/6.0f,2*wheight/3+225.0f,wwidth/24,wheight/50,GRAY));
    // level0.push_back(std::make_unique<RaceBlocks>(24*wwidth/6.0f,2*wheight/3+225.0f,wwidth/24,wheight/50,GRAY));
    // level0.push_back(std::make_unique<RaceBlocks>(25*wwidth/6+40.0f,2*wheight/3+200.0f,wwidth/4,wheight/50,GRAY));
    // level0.push_back(std::make_unique<RaceBlocks>(27*wwidth/6+40.0f,2*wheight/3+120.0f,wwidth/8,wheight/50,GRAY));
    // level0.push_back(std::make_unique<RaceBlocks>(28*wwidth/6+40.0f,2*wheight/3+30.0f,wwidth/36,wheight/6,GRAY));
    // level0.push_back(std::make_unique<RaceBlocks>(29*wwidth/6+40.0f,2*wheight/3-60.0f,wwidth/36,wheight/6,GRAY));
    // level0.push_back(std::make_unique<RaceBlocks>(28*wwidth/6,2*wheight/3-150.0f,wwidth/36,wheight/6,GRAY));
    // level0.push_back(std::make_unique<RaceBlocks>(29*wwidth/6,2*wheight/3-250.0f,wwidth/6,wheight/50,GRAY));
    // level0.push_back(std::make_unique<RaceBlocks>(27*wwidth/6,2*wheight/3-310.0f,wwidth/6,wheight/50,GRAY));
    // level0.push_back(std::make_unique<RaceBlocks>(25*wwidth/6+60.0f,2*wheight/3-370.0f,wwidth/6-20.0f,wheight/50,GRAY));
    // //Final part
    // level0.push_back(std::make_unique<RaceBlocks>(17.0f*wwidth/6,wheight/3-260.0f,wwidth/2,wheight/50,GRAY));
    // level0.push_back(std::make_unique<RaceBlocks>(16.0f*wwidth/6,wheight/3-320.0f,wwidth/36,wheight/5,GRAY));
    // level0.push_back(std::make_unique<RaceBlocks>(14.0f*wwidth/6,wheight/3-220.0f,wwidth/36,wheight/5,GRAY));
    // level0.push_back(std::make_unique<RaceBlocks>(13.0f*wwidth/6-50.0f,wheight/3-260.0f,wwidth/36,wheight/5,GRAY));
    // level0.push_back(std::make_unique<RaceBlocks>(7.0f*wwidth/6,wheight/3-300.0f,2*wwidth/3,wheight/50,GRAY));
    // level0.push_back(std::make_unique<RaceBlocks>(7.0f*wwidth/6,wheight/3-380.0f,wwidth/3,wheight/50,GRAY));

    // level0.push_back(std::make_unique<WinBlock>(7.0f*wwidth/6+25.0f,wheight/3-380.0f-wheight/5,wwidth/36,wheight/5,GREEN,GameState));

    // level0.push_back(std::make_unique<DeathBlock>(-wwidth,2.5f*wheight,8*wwidth,wheight,BLACK));

    // rBlocks.push_back(std::move(level0));
    
    // std::vector<std::unique_ptr<Block>> level1;
    // //Start
    // level1.push_back(std::make_unique<RaceBlocks>(0,2*wheight/3,2*wwidth/3,wheight/50,GRAY));
    // level1.push_back(std::make_unique<FloatBlock>(2*wwidth/3,2*wheight/3,wwidth/3,wheight/50,ORANGE));
    // level1.push_back(std::make_unique<RaceBlocks>(2*wwidth/3,2*wheight/3+170.0f,2*wwidth/3,wheight/50,GRAY));
    // level1.push_back(std::make_unique<RaceBlocks>(wwidth-wwidth/29,wheight/3,wwidth/30,wheight/3,GRAY));
    // //long jumps
    // level1.push_back(std::make_unique<RaceBlocks>(5*wwidth/3+45.0f,2*wheight/3+170.0f,wwidth/3,wheight/50,GRAY));
    // level1.push_back(std::make_unique<RaceBlocks>(7*wwidth/3+90.0f,2*wheight/3+170.0f,wwidth/3,wheight/50,GRAY));
    // level1.push_back(std::make_unique<DeathBlock>(5*wwidth/3,2*wheight/3+250.0f,4*wwidth/3+540.0f,wheight/20,BLACK));
    // //Spikes
    // level1.push_back(std::make_unique<RaceBlocks>(9*wwidth/3+90.0f,2*wheight/3+150.0f,wwidth/36,wheight/8,GRAY));
    // level1.push_back(std::make_unique<RaceBlocks>(9*wwidth/3+90.0f,2*wheight/3-wheight/4,wwidth/36,wheight/4,GRAY));
    // level1.push_back(std::make_unique<RaceBlocks>(9*wwidth/3+240.0f,2*wheight/3+150.0f,wwidth/36,wheight/8,GRAY));
    // level1.push_back(std::make_unique<RaceBlocks>(9*wwidth/3+240.0f,2*wheight/3-wheight/4,wwidth/36,wheight/4,GRAY));
    // level1.push_back(std::make_unique<RaceBlocks>(9*wwidth/3+390.0f,2*wheight/3+150.0f,wwidth/36,wheight/8,GRAY));
    // level1.push_back(std::make_unique<RaceBlocks>(9*wwidth/3+390.0f,2*wheight/3-wheight/4,wwidth/36,wheight/4,GRAY));
    // level1.push_back(std::make_unique<RaceBlocks>(9*wwidth/3+540.0f,2*wheight/3+150.0f,wwidth/36,wheight/8,GRAY));
    // level1.push_back(std::make_unique<RaceBlocks>(9*wwidth/3+540.0f,2*wheight/3-wheight/4,wwidth/36,wheight/4,GRAY));
    // level1.push_back(std::make_unique<DeathBlock>(9*wwidth/3+240.0f,2*wheight/3,wwidth/36,wheight/24,RED));
    // level1.push_back(std::make_unique<DeathBlock>(9*wwidth/3+390.0f,2*wheight/3+150.0f-wheight/24,wwidth/36,wheight/24,RED));
    // level1.push_back(std::make_unique<DeathBlock>(9*wwidth/3+540.0f,2*wheight/3,wwidth/36,wheight/24,RED));
    // //Speed way
    // level1.push_back(std::make_unique<FloatBlock>(11*wwidth/3+100.0f,2*wheight/3+150.0f,wwidth/3,wheight/50,ORANGE));
    // level1.push_back(std::make_unique<FloatBlock>(13*wwidth/3+230.0f,2*wheight/3+150.0f,wwidth/3,wheight/50,ORANGE));
    // level1.push_back(std::make_unique<RaceBlocks>(15*wwidth/3+250.0f,2*wheight/3+75.0f,wwidth/3,wheight/50,GRAY));
    // level1.push_back(std::make_unique<RaceBlocks>(17*wwidth/3+210.0f,2*wheight/3,wwidth/3,wheight/50,GRAY));
    // level1.push_back(std::make_unique<DeathBlock>(17*wwidth/3+210.0f,2*wheight/3-wheight/50,wwidth/16,wheight/50,RED));
    // level1.push_back(std::make_unique<RaceBlocks>(19*wwidth/3+250.0f,2*wheight/3+75.0f,wwidth/3,wheight/50,GRAY));
    // //Death part
    // level1.push_back(std::make_unique<DeathBlock>(12*wwidth/3+100.0f,500.0f,wwidth/36,2*wheight/3,RED));
    // level1.push_back(std::make_unique<DeathBlock>(12*wwidth/3+100.0f,2*wheight/3+200.0f,wwidth/2,wheight/50,BLACK));
    // //Low part
    // level1.push_back(std::make_unique<RaceBlocks>(11*wwidth/3+100.0f,2*wheight/3+500.0f,wwidth/3,wheight/50,GRAY));
    // level1.push_back(std::make_unique<FloatBlock>(10*wwidth/3+60.0f,2*wheight/3+460.0f,wwidth/36,wheight/50,ORANGE));
    // level1.push_back(std::make_unique<DeathBlock>(8*wwidth/3+220.0f,2*wheight/3+500.0f,wwidth/2+260.0f,wheight/50,RED));
    // level1.push_back(std::make_unique<FloatBlock>(8*wwidth/3+260.0f,2*wheight/3+460.0f,wwidth/36,wheight/50,ORANGE));
    // level1.push_back(std::make_unique<RaceBlocks>(6*wwidth/3+300.0f,2*wheight/3+600.0f,wwidth/3,wheight/50,GRAY));
    // level1.push_back(std::make_unique<RaceBlocks>(6*wwidth/3+260.0f,2*wheight/3+750.0f,3*wwidth/2,wheight/50,GRAY));
    // level1.push_back(std::make_unique<DeathBlock>(8*wwidth/3+230.0f,2*wheight/3+750.0f-wheight/8,wwidth/50,wheight/8,RED));
    // level1.push_back(std::make_unique<DeathBlock>(9*wwidth/3+130.0f,2*wheight/3+750.0f-wheight/8,wwidth/50,wheight/8,RED));
    // level1.push_back(std::make_unique<DeathBlock>(10*wwidth/3+30.0f,2*wheight/3+750.0f-wheight/8,wwidth/50,wheight/8,RED));
    // level1.push_back(std::make_unique<DeathBlock>(11*wwidth/3-70.0f,2*wheight/3+750.0f-wheight/8,wwidth/50,wheight/8,RED));
    // level1.push_back(std::make_unique<RaceBlocks>(10.5f*wwidth/3+260.0f-wwidth/30,2*wheight/3+675.0f,wwidth/30,wheight/6,GRAY));
    // level1.push_back(std::make_unique<RaceBlocks>(10.5f*wwidth/3+260.0f,2*wheight/3+675.0f,wwidth/3,wheight/50,GRAY));
    // level1.push_back(std::make_unique<RaceBlocks>(12.5f*wwidth/3+305.0f,2*wheight/3+675.0f,wwidth/3,wheight/50,GRAY));
    // level1.push_back(std::make_unique<RaceBlocks>(11.5f*wwidth/3+260.0f-wwidth/30,2*wheight/3+675.0f,wwidth/30,wheight/6,GRAY));
    // level1.push_back(std::make_unique<RaceBlocks>(12.5f*wwidth/3+305.0f,2*wheight/3+675.0f,wwidth/30,wheight/6,GRAY));
    // level1.push_back(std::make_unique<DeathBlock>(11.5f*wwidth/3+260.0f,2*wheight/3+750.0f,wwidth/3+45.0f,wheight/20,RED));
    // level1.push_back(std::make_unique<DeathBlock>(13.5*wwidth/3+305.0f,2*wheight/3+600.0f,wwidth/50,wheight/6,RED));
    // level1.push_back(std::make_unique<RaceBlocks>(13.5*wwidth/3+305.0f+wwidth/50,2*wheight/3+600.0f,wwidth/25,wheight/6,GRAY));
    // //Other part
    // level1.push_back(std::make_unique<RaceBlocks>(14.0*wwidth/3+305.0f+wwidth/50,2*wheight/3+500.0f,wwidth/25,wheight/6,GRAY));
    // level1.push_back(std::make_unique<RaceBlocks>(15.0*wwidth/3+250.0f+wwidth/50,2*wheight/3+400.0f,wwidth/25,wheight/6,GRAY));
    // level1.push_back(std::make_unique<RaceBlocks>(16.0*wwidth/3+200.0f+wwidth/50,2*wheight/3+300.0f,wwidth/25,wheight/6,GRAY));
    // level1.push_back(std::make_unique<RaceBlocks>(17.0*wwidth/3+150.0f+wwidth/50,2*wheight/3+250.0f,wwidth/2,wheight/50,GRAY));
    // level1.push_back(std::make_unique<RaceBlocks>(19.0*wwidth/3+150.0f+wwidth/50,2*wheight/3+170.0f,wwidth/25,wheight/50,GRAY));
    // //Utility
    // level1.push_back(std::make_unique<WinBlock>(19*wwidth/3+450.0f,2*wheight/3+75.0f-wheight/5,wwidth/36,wheight/5,GREEN,GameState));
    // level1.push_back(std::make_unique<DeathBlock>(-wwidth,3.0f*wheight,9*wwidth,wheight,BLACK));
    

    // rBlocks.push_back(std::move(level1));

}