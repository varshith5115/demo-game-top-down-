#include "raylib.h"
#include "raymath.h"
#include "character.h"
#include "prop.h"
#include "Enemy.h"
#include "Enemy1.h"
#include <string>

int main()
{
    const int windowWidth{384};
    const int windowHeight{384};
    InitWindow(windowWidth, windowHeight, "TopDown");

    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos{0.0, 0.0};
    const float mapScale{4.0f};

    character knight{windowWidth, windowHeight};

    prop props[2]{
        prop{Vector2{600.f,300.f},LoadTexture("nature_tileset/Rock.png")},
        prop{Vector2{400.f,500.f},LoadTexture("nature_tileset/Log.png")}
    };

    Enemy goblin{
        Vector2{800.f,300.f},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png")
    };

    Enemy1 slime{
        Vector2{500.f,700.f},
        LoadTexture("characters/slime_idle_spritesheet.png"),
        LoadTexture("characters/slime_run_spritesheet.png")
    };
    
    
    goblin.setTarget(&knight);
    slime.setTarget(&knight);

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getworldPos(),-1.f);

        // draw the map
        DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);

        //draw the props
        for (auto prop:props)
        {
            prop.Render(knight.getworldPos());
        }

        if(!knight.getAlive()) //char is not alive
        {
            DrawText("Game Over!",55.f,45.f,40,RED);
            EndDrawing();
            continue;
        }
        else //char is alive
        {
            std::string knightsHealth = "Health: ";
            knightsHealth.append(std::to_string(knight.getHealth()), 0, 5);
            DrawText(knightsHealth.c_str(), 55.f, 45.f, 40, RED);

        }
        
        knight.tick(GetFrameTime());
        //check map bounds
        if(knight.getworldPos().x < 0.f ||
           knight.getworldPos().y < 0.f ||
           knight.getworldPos().x + windowWidth > map.width * mapScale ||
           knight.getworldPos().y + windowHeight > map.height * mapScale)
        {
            knight.undoMovement();
        }

        for (auto prop : props)
        {
            if(CheckCollisionRecs(prop.GetCollisionRec(knight.getworldPos()),knight.GetCollisionRec()))
            {
                knight.undoMovement();
            }
        }
        
        goblin.tick(GetFrameTime());

        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if(CheckCollisionRecs(goblin.GetCollisionRec(), knight.getWeaponCollisionRec()))
            {
                goblin.setAlive(false);
            }
        }

        slime.tick(GetFrameTime());

        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if(CheckCollisionRecs(slime.GetCollisionRec(), knight.getWeaponCollisionRec()))
            {
                slime.setAlive(false);
            }
        }

        EndDrawing();
    }
    CloseWindow();
}