#include "Game/SpaceGame.h"
#include "Game/Player.h"

using namespace bacon;

int main(int argc, char* argv[]) {

    file::SetCurrentDirectory("Assets");

    /*// load the json data from a file
    std::string buffer;
    file::ReadTextFile("Ajson.txt", buffer);
    // show the contents of the json file (debug)
    std::cout << buffer << std::endl;

    // create json document from the json file contents
    rapidjson::Document document;
    json::Load("json.txt", document);

    // read the age data from the json
    int age;
    json::Read(document, "age", age);
    // show the age data
    std::cout << age << std::endl;

    // read/show the data from the json file
    std::string name;
    float speed;
    bool isAwake;
    vec2 position;
    vec3 color;

    // read the json data
    JSON_READ(document, name);
    JSON_READ(document, age);
    JSON_READ(document, speed);
    JSON_READ(document, isAwake);
    JSON_READ(document, position);
    JSON_READ(document, color);

    // show the data
    std::cout << name << " " << age << " " << speed << " " << isAwake << std::endl;
    std::cout << position.x << " " << position.y << std::endl;
    std::cout << color.r << " " << color.g << " " << color.b << " " << std::endl;

    return 0;*/

    //initialize Engine
    Logger::Info("Initialize Engine");
    GetEngine().Initialize();
    
    //initialize game
    std::unique_ptr<SpaceGame> game = std::make_unique<SpaceGame>();
    game->Initialize();

    SDL_Event e;
    bool quit = false;

    //create stars
    std::vector<vec2> stars;
    for (int i = 0; i < 100; i++) {
        stars.push_back(vec2{random::GetRandomFloat() * 1280 ,random::GetRandomFloat() * 1024 });
    }

    vec2(30, 40);

    // sound work
    GetEngine().GetAudio().AddSound("Drums/bass.wav", "bass");
    GetEngine().GetAudio().AddSound("Drums/snare.wav", "snare");
    GetEngine().GetAudio().AddSound("Drums/clap.wav", "clap");
    GetEngine().GetAudio().AddSound("Drums/cowbell.wav", "cowbell");
    GetEngine().GetAudio().AddSound("Sounds/pipe.wav", "pipe");
    GetEngine().GetAudio().AddSound("Sounds/fart.wav", "fart");
    GetEngine().GetAudio().AddSound("Sounds/yippee.wav", "yippee");
    GetEngine().GetAudio().AddSound("Sounds/impact2.wav", "impact");
    GetEngine().GetAudio().AddSound("Sounds/pew.wav", "pew");
    GetEngine().GetAudio().AddSound("Sounds/impact.wav", "other_impact");
    GetEngine().GetAudio().AddSound("Sounds/game_over.wav", "game_over");
    GetEngine().GetAudio().AddSound("Sounds/laser.wav", "laser");
    GetEngine().GetAudio().AddSound("Sounds/game_music.wav", "music");
    
    auto texture = ResourceManager::Instance().Get<Texture>("Images/krill.png", GetEngine().GetRenderer());

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
        //GetEngine().GetRenderer().DrawTexture(texture.get(), 30, 30, 90, 4);


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
    Logger::Info("Shutdown Engine");

    GetEngine().GetRenderer().Clear();
    
    game->Kill();
    game.release();
    GetEngine().Kill();

    return 0;
}