#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

int main()
{
    // array of window dimensions
    int windowDimensions[2];
    windowDimensions[0] = 384;
    windowDimensions[1] = 384;

    // initialize window
    InitWindow(windowDimensions[0], windowDimensions[1], "TOP-DOWN");

    // load map texture
    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos{0.0, 0.0};
    const float mapScale{4.0f};

    Character knight{windowDimensions[0],windowDimensions[1]};

    // prop objects in array
    Prop props[2]{
        Prop{Vector2{600.f,300.f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{400.f,500.f}, LoadTexture("nature_tileset/Log.png")}
    };

    Enemy goblin{
        Vector2{},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png")
    };
    goblin.setTarget(&knight);

    SetTargetFPS(60);
    // game loop
    while (!WindowShouldClose())
    {
        // start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos=Vector2Scale(knight.getWorldPos(),-1.f);
        // draw the map
        DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);

        for(auto prop: props)
        {
            prop.Render(knight.getWorldPos());
        }

        if(!knight.getAlive()) // character is not alive
        {
            DrawText("Game Over!", 55.f,45.f,40,RED);
            EndDrawing();
            continue;
        }
        else
        {
            
        }

        knight.tick(GetFrameTime());
        
        // check map bounds
        if(knight.getWorldPos().x<0.f ||
        knight.getWorldPos().y<0.f ||
        knight.getWorldPos().x+windowDimensions[0]>map.width*mapScale ||
        knight.getWorldPos().y+windowDimensions[1]>map.height*mapScale)
        {
            knight.undoMovement();
        }

        // check prop collisions
        for(auto prop:props)
        {
            if(CheckCollisionRecs(prop.GetCollisionRec(knight.getWorldPos()),knight.GetCollisionRec()))
            {
                knight.undoMovement();
            }
        }

        goblin.tick(GetFrameTime());

        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if(CheckCollisionRecs(goblin.GetCollisionRec(), knight.getWeaponCollissionRec()))
            {
                goblin.setAlive(false);
            }
        }

        EndDrawing();
    }

    UnloadTexture(map);
    CloseWindow();

    return 0;
}