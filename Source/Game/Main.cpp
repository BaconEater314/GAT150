#include "Core/Random.h"
#include "Math/Vector2.h"
#include "Math/Transform.h"
#include "Renderer/Renderer.h"
#include "Core/Time.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Math/Vector3.h"
#include "Renderer/Model.h"
#include "GameEngine/Scene.h"
#include "GameEngine/Actor.h"
#include "Engine.h"
#include "Game/SpaceGame.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"
#include "Core/File.h"

#include "Game/Player.h"

#include <vector>
#include <memory>
#include <iostream>

using namespace bacon;

int main(int argc, char* argv[]) {

    //initialize Engine
    GetEngine().Initialize();

    //initialize scene
    
    //initialize game
    std::unique_ptr<SpaceGame> game = std::make_unique<SpaceGame>();
    game->Initialize();

    Font* font = new Font();
    font->Load("Surprise Valentine.ttf", 30);

    SDL_Event e;
    bool quit = false;

    //create stars
    std::vector<vec2> stars;
    for (int i = 0; i < 100; i++) {
        stars.push_back(vec2{random::GetRandomFloat() * 1280 ,random::GetRandomFloat() * 1024 });
    }

    vec2(30, 40);

    // Define a rectangle
    SDL_FRect greenSquare{ 270, 190, 200, 200 };

    // sound work
    GetEngine().GetAudio().AddSound("Assets/drums/bass.wav", "bass");
    GetEngine().GetAudio().AddSound("Assets/drums/snare.wav", "snare");
    GetEngine().GetAudio().AddSound("Assets/drums/clap.wav", "clap");
    GetEngine().GetAudio().AddSound("Assets/drums/cowbell.wav", "cowbell");
    GetEngine().GetAudio().AddSound("Assets/Sounds/pipe.wav", "pipe");
    GetEngine().GetAudio().AddSound("Assets/Sounds/fart.wav", "fart");
    GetEngine().GetAudio().AddSound("Assets/Sounds/yippee.wav", "yippee");
    GetEngine().GetAudio().AddSound("Assets/Sounds/impact2.wav", "impact");
    GetEngine().GetAudio().AddSound("Assets/Sounds/pew.wav", "pew");
    GetEngine().GetAudio().AddSound("Assets/Sounds/impact.wav", "other_impact");
    GetEngine().GetAudio().AddSound("Assets/Sounds/game_over.wav", "game_over");
    GetEngine().GetAudio().AddSound("Assets/Sounds/laser.wav", "laser");
    GetEngine().GetAudio().AddSound("Assets/Sounds/game_music.wav", "music");
    

    // Main loop
    // This is where all the code that runs the code goes.
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
            
        }

        GetEngine().Update();
        game->Update(GetEngine().GetTime().GetDeltaTime());
        //scene.Update(GetEngine().GetTime().GetTime());

        vec3 color{ 0,0,0 };
        GetEngine().GetRenderer().SetColor(color.r, color.g, color.b);
        GetEngine().GetRenderer().Clear();

        game->Draw(GetEngine().GetRenderer());

        // movement and rotation code
        //float playerSpeed = 200;

        //vec2 direction{ 0,0 };
        

        //drawing shapes
        
        //text->Draw(GetEngine().GetRenderer(), 40.0f, 40.0f);


        //quits the program when pressing escape.
        if (GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_ESCAPE)) quit = true;

        //soundboard
        //if (GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_Q) && !GetEngine().GetInput().GetPrevKeyDown(SDL_SCANCODE_Q)) { GetEngine().GetAudio().PlaySound("bass");}
        //if (GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_W) && !GetEngine().GetInput().GetPrevKeyDown(SDL_SCANCODE_W)) { GetEngine().GetAudio().playSound("snare"); }
        //if (GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_E) && !GetEngine().GetInput().GetPrevKeyDown(SDL_SCANCODE_E)) { GetEngine().GetAudio().PlaySound("clap"); }
        //if (GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_SPACE) && !GetEngine().GetInput().GetPrevKeyDown(SDL_SCANCODE_SPACE)) { GetEngine().GetAudio().PlaySound("pew"); }
        if (GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_P) && !GetEngine().GetInput().GetPrevKeyDown(SDL_SCANCODE_P)) { GetEngine().GetAudio().PlaySound("pipe"); }
        if (GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_F) && !GetEngine().GetInput().GetPrevKeyDown(SDL_SCANCODE_F)) { GetEngine().GetAudio().PlaySound("fart"); }
        if (GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_Y) && !GetEngine().GetInput().GetPrevKeyDown(SDL_SCANCODE_Y)) { GetEngine().GetAudio().PlaySound("yippee"); }


        // all control code before this spot

        GetEngine().GetRenderer().Present();
    }

    GetEngine().GetRenderer().Clear();
    
    game.release();
    game->Kill();
    GetEngine().Kill();

    return 0;
}