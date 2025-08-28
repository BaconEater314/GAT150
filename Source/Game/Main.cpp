#include "Game/SpaceGame.h"
#include "Game/Player.h"
#include "Platformer/PlatformerGame.h"

using namespace bacon;

int main(int argc, char* argv[]) {

    file::SetCurrentDirectory("Assets/Platformer");

    //initialize Engine
    Logger::Info("Initialize Engine");
    GetEngine().Initialize();
    
    //initialize game
    std::unique_ptr<PlatformerGame> game = std::make_unique<PlatformerGame>();
    game->Initialize();

    SDL_Event e;
    bool quit = false;

    // Main loop
    // This is where all the code that runs the code goes.
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        //update
        GetEngine().Update();
        game->Update(GetEngine().GetTime().GetDeltaTime());
        //scene.Update(GetEngine().GetTime().GetTime());


        vec3 color{ 0,0,0 };
        GetEngine().GetRenderer().SetColor(color.r, color.g, color.b);
        GetEngine().GetRenderer().Clear();

        game->Draw(GetEngine().GetRenderer());
        //GetEngine().GetRenderer().DrawTexture(texture.get(), 30, 30, 90, 4);


        //quits the program when pressing escape.
        if (GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_ESCAPE)) quit = true;

        //soundboard
        if (GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_P) && !GetEngine().GetInput().GetPrevKeyDown(SDL_SCANCODE_P)) { GetEngine().GetAudio().PlaySound("pipe"); }
        if (GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_F) && !GetEngine().GetInput().GetPrevKeyDown(SDL_SCANCODE_F)) { GetEngine().GetAudio().PlaySound("fart"); }
        if (GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_Y) && !GetEngine().GetInput().GetPrevKeyDown(SDL_SCANCODE_Y)) { GetEngine().GetAudio().PlaySound("yippee"); }


        // all control code before this spot

        GetEngine().GetRenderer().Present();
    }
    Logger::Info("Shutdown Engine");

    GetEngine().GetRenderer().Clear();
    
    game->Kill();
    game.release();
    GetEngine().Kill();

    return 0;
}