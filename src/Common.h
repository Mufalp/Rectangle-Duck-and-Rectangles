#ifndef COMMON_H_
#define COMMON_H_

inline constexpr float gravity = 0.2f;
inline constexpr int wwidth = 800;
inline constexpr int wheight = 450;

inline constexpr float bwidth = 80.0f;
inline constexpr int bheight = 40.0f;

inline constexpr float MaxRaceSpeed = 4.0f;//default 4
inline constexpr float RaceAcc = 0.35f;
inline constexpr float CameraSpeed = 0.08f;

inline constexpr Vector2 SpawnPoint = {20.0f,250.0f};
inline constexpr float floorY = 400.0f;
inline constexpr Vector2 RunPoint = {20.0f,floorY+50.0f};

inline constexpr int levelnum = 2;
inline constexpr float targetTimes[] = { 30.0f, 35.0f, 15.0f };

inline constexpr float BackGroundSpeed = 2.0f;



//Main game state
enum State{
    RUN,MAINMENU,RACE,GAMEOVER,RACEMENU,RACEWIN,PAUSE,OPTION,HOWTO
};

inline constexpr State StartState = MAINMENU;

/* TO DO:
try:
background?
add 2 more enemies to run (lagging, fly&shoot)
look around (again) animate maybe
moving platforms
moving enemy race
design fly n swim
r key
*/

#endif
//x86_64-w64-mingw32-g++ src/*.cpp -o MyGame.exe -O2 -I./../raylib/src -L./lib_win -lraylib -lopengl32 -lgdi32 -lwinmm -mwindows -static -lpthread -lws2_32

