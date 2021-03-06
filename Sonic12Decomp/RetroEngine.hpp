#ifndef RETROENGINE_H
#define RETROENGINE_H

// Disables POSIX use c++ name blah blah stuff
#pragma warning(disable : 4996)

// ================
// STANDARD LIBS
// ================
#include <stdio.h>
#include <string.h>

// ================
// STANDARD TYPES
// ================
typedef unsigned char byte;
typedef signed char sbyte;
typedef unsigned short ushort;
typedef unsigned int uint;
// typedef unsigned long long ulong;

#define RETRO_USE_NETWORKING (0)
#if !RETRO_USE_NETWORKING
#define NETWORK_H // easy way to fuck over network header LOL
#endif

// Platforms (RSDKv4 only defines these 7 (I assume), but feel free to add your own custom platform define for easier platform code changes)
#define RETRO_WIN      (0)
#define RETRO_OSX      (1)
#define RETRO_XBOX_360 (2)
#define RETRO_PS3      (3)
#define RETRO_iOS      (4)
#define RETRO_ANDROID  (5)
#define RETRO_WP7      (6)
// Custom Platforms start here
#define RETRO_VITA     (7)
#define RETRO_NX       (8)

// Platform types (Game manages platform-specific code such as HUD position using this rather than the above)
#define RETRO_STANDARD (0)
#define RETRO_MOBILE   (1)

#if defined _WIN32
#define RETRO_PLATFORM (RETRO_WIN)
#define RETRO_PLATTYPE (RETRO_STANDARD)
#elif defined __APPLE__
#if __IPHONEOS__
#define RETRO_PLATTYPE (RETRO_iOS)
#define RETRO_PLATTYPE (RETRO_MOBILE)
#else
#define RETRO_PLATFORM (RETRO_OSX)
#define RETRO_PLATTYPE (RETRO_STANDARD)
#endif
#elif defined __vita__
#define RETRO_PLATFORM (RETRO_VITA)
#define RETRO_PLATTYPE (RETRO_STANDARD)
#elif defined __SWITCH__
#define RETRO_PLATFORM (RETRO_NX)
#define RETRO_PLATTYPE (RETRO_STANDARD)
#else
#define RETRO_PLATFORM (RETRO_WIN)
#define RETRO_PLATTYPE (RETRO_STANDARD)
#endif

#if RETRO_PLATFORM == RETRO_VITA
#if RETRO_GAME_SONIC == 1
#define BASE_PATH            "ux0:data/Sonic1/"
#define BASE_RO_PATH         "ux0:data/Sonic1/"
#elif RETRO_GAME_SONIC == 2
#define BASE_PATH            "ux0:data/Sonic2/"
#define BASE_RO_PATH         "ux0:data/Sonic2/"
#else
#error "RETRO_GAME_SONIC not defined"
#endif
#define DEFAULT_SCREEN_XSIZE 480
#define DEFAULT_FULLSCREEN   false
#define SCREEN_YSIZE (272)
#elif RETRO_PLATFORM == RETRO_NX

#define BASE_PATH ""
#define BASE_RO_PATH "romfs:/"
#define DEFAULT_SCREEN_XSIZE 480
#define DEFAULT_FULLSCREEN   false
#define SCREEN_YSIZE         (272)
#define DEFAULT_WINDOW_SCALE 4
#define RETRO_DISABLE_CONTROLLER_HOTSWAP

#else

#define BASE_PATH            ""
#define BASE_RO_PATH         ""
#define DEFAULT_SCREEN_XSIZE 424 
#define DEFAULT_FULLSCREEN   false
#define SCREEN_YSIZE         (240)
#define RETRO_USING_MOUSE
#define RETRO_USING_TOUCH
#define RETRO_USING_KEYBOARD

#endif

#ifndef DEFAULT_WINDOW_SCALE
#define DEFAULT_WINDOW_SCALE 2
#endif

#if RETRO_PLATFORM == RETRO_WINDOWS || RETRO_PLATFORM == RETRO_OSX || RETRO_PLATFORM == RETRO_VITA || RETRO_PLATFORM == RETRO_NX
#define RETRO_USING_SDL (1)
#else // Since its an else & not an elif these platforms probably aren't supported yet
#define RETRO_USING_SDL (0)
#endif

#define RETRO_GAME_STANDARD (0)
#define RETRO_GAME_MOBILE   (1)

#if RETRO_PLATFORM == RETRO_iOS || RETRO_PLATFORM == RETRO_ANDROID || RETRO_PLATFORM == RETRO_WP7
#define RETRO_GAMEPLATFORM (RETRO_GAME_MOBILE)
#else
#define RETRO_GAMEPLATFORM (RETRO_GAME_STANDARD)
#endif

#define RETRO_SW_RENDER  (0)
#define RETRO_HW_RENDER  (1)
#define RETRO_RENDERTYPE (RETRO_SW_RENDER)

#define RETRO_USE_HAPTICS (1)

enum RetroLanguages {
    RETRO_EN = 0,
    RETRO_FR = 1,
    RETRO_IT = 2,
    RETRO_DE = 3,
    RETRO_ES = 4,
    RETRO_JP = 5,
    RETRO_PT = 6,
    RETRO_RU = 7,
    RETRO_KO = 8,
    RETRO_ZH = 9,
    RETRO_ZS = 10,
};

enum RetroStates {
    ENGINE_DEVMENU     = 0,
    ENGINE_MAINGAME    = 1,
    ENGINE_INITDEVMENU = 2,
    ENGINE_WAIT        = 3,
    ENGINE_SCRIPTERROR = 4,
    ENGINE_INITPAUSE   = 5,
    ENGINE_EXITPAUSE   = 6,
    ENGINE_ENDGAME     = 7,
    ENGINE_RESETGAME   = 8,

    // Custom GameModes (required to make some features work
    ENGINE_CONNECT2PVS = 0x80,
};

enum RetroGameType {
    GAME_UNKNOWN = 0,
    GAME_SONIC1  = 1,
    GAME_SONIC2  = 2,
};

// General Defines
#define SCREEN_CENTERY (SCREEN_YSIZE / 2)

#if RETRO_PLATFORM == RETRO_WIN
#include <SDL.h>
#include <vorbis/vorbisfile.h>
#elif RETRO_PLATFORM == RETRO_OSX
#include <SDL2/SDL.h>
#include <Vorbis/vorbisfile.h>

#include "cocoaHelpers.hpp"

#elif RETRO_USING_SDL
#include <SDL2/SDL.h>
#include <vorbis/vorbisfile.h>

#else

#endif

extern bool usingCWD;
extern bool engineDebugMode;

// Utils
#include "Ini.hpp"
#include "Network.hpp"

#include "Math.hpp"
#include "Reader.hpp"
#include "String.hpp"
#include "Animation.hpp"
#include "Audio.hpp"
#include "Input.hpp"
#include "Object.hpp"
#include "Palette.hpp"
#include "Drawing.hpp"
#include "Scene3D.hpp"
#include "Collision.hpp"
#include "Scene.hpp"
#include "Script.hpp"
#include "Sprite.hpp"
#include "Text.hpp"
#include "Userdata.hpp"
#include "Debug.hpp"

// Native Entities
#include "PauseMenu.hpp"
#include "RetroGameLoop.hpp"

class RetroEngine
{
public:
    bool usingDataFile = false;
    bool usingBytecode = false;

    char *dataFile = new char[0x80];

    bool initialised = false;
    bool running     = false;

    int gameMode = 1;
    int language = RETRO_EN;
    int message  = 0;

    bool trialMode      = false;
    bool onlineActive   = true;
    bool hapticsEnabled = true;

    int frameSkipSetting = 0;
    int frameSkipTimer   = 0;

    // Ported from RSDKv5
    bool devMenu         = false;
    int startList        = 0;
    int startStage       = 0;
    int gameSpeed        = 1;
    int fastForwardSpeed = 8;
    bool masterPaused    = false;
    bool frameStep       = false;

    bool showPaletteOverlay = false;
    bool useHQModes         = true;

    void Init();
    void Run();

    bool LoadGameConfig(const char *Filepath);

    int callbackMessage = 0;
    int prevMessage     = 0;
    int waitValue       = 0;
    void Callback(int callbackID);

    bool finishedStartMenu = false;

    char gameWindowText[0x40];
    char gameDescriptionText[0x100];
    const char *gameVersion = "1.0.0";
#if RETRO_GAMEPLATFORM == RETRO_GAME_STANDARD
    const char *gamePlatform = "Standard"; // "STANDARD"
#elif RETRO_GAMEPLATFORM == RETRO_GAME_MOBILE
    const char *gamePlatform = "Mobile"; // "MOBILE"
#endif

#if RETRO_RENDERTYPE == RETRO_SW_RENDER
    const char *gameRenderType = "SW_Rendering"; //"SW_RENDERING"
#elif RETRO_RENDERTYPE == RETRO_HW_RENDER
    const char *gameRenderType = "HW_Rendering"; // "HW_RENDERING"
#endif

#if RETRO_USE_HAPTICS
    const char *gameHapticSetting = "Use_Haptics"; //"USE_F_FEEDBACK"; // None is default, but people with controllers exist
#else
    const char *gameHapticSetting = "No_Haptics"; //"NO_F_FEEDBACK";
#endif

    byte gameType = GAME_UNKNOWN;

    ushort *frameBuffer   = nullptr;
    ushort *frameBuffer2x = nullptr;

    bool isFullScreen = false;

    bool startFullScreen  = false; // if should start as fullscreen
    bool borderless       = false;
    bool vsync            = false;
    int windowScale       = 2;
    int refreshRate       = 60; // user-picked screen update rate
    int screenRefreshRate = 60; // hardware screen update rate
    int targetRefreshRate = 60; // game logic update rate

    uint frameCount      = 0; // frames since scene load
    int renderFrameIndex = 0;
    int skipFrameIndex   = 0;

#if RETRO_USING_SDL
    SDL_Window *window          = nullptr;
    SDL_Renderer *renderer      = nullptr;
    SDL_Texture *screenBuffer   = nullptr;
    SDL_Texture *screenBuffer2x = nullptr;

    SDL_Event sdlEvents;
#endif
};

extern RetroEngine Engine;
#endif // !RETROENGINE_H
