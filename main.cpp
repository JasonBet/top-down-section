#include "raylib.h"
#include "raymath.h"

int main()
{
    // array of window dimensions
    int windowDimensions[2];
    windowDimensions[0]=384;
    windowDimensions[1]=384;

    // initialize window
    InitWindow(windowDimensions[0],windowDimensions[1],"TOP-DOWN");

    // load map texture
    Texture2D map=LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos{0.0,0.0};

    float speed=4.0;

    Texture2D knight=LoadTexture("characters/knight_idle_spritesheet.png");
    Vector2 knightPos{
        static_cast<float>(windowDimensions[0])/2.0f-4.0f*(0.5f*static_cast<float>(knight.width)/6.0f),
        static_cast<float>(windowDimensions[1])/2.0f-4.0f*(0.5f*static_cast<float>(knight.height))
    };

    // 1 : facing right, -1 : facing left
    float rightLeft{1.f};

    SetTargetFPS(60);
    // game loop
    while(!WindowShouldClose())
    {
        // start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        Vector2 direction{};
        if(IsKeyDown(KEY_A)) direction.x-=1.0;
        if(IsKeyDown(KEY_D)) direction.x+=1.0;
        if(IsKeyDown(KEY_W)) direction.y-=1.0;
        if(IsKeyDown(KEY_S)) direction.y+=1.0;
        
        if(Vector2Length(direction)!=0.0)
        {
            mapPos=Vector2Subtract(mapPos,Vector2Scale(Vector2Normalize(direction),speed));
            direction.x<0.f ? rightLeft=-1.f : rightLeft=1.f;

        }

        // draw the map
        DrawTextureEx(map,mapPos,0.0,4,WHITE);

        // draw the character
        Rectangle source{0.f,0.f,rightLeft*static_cast<float>(knight.width)/6.f,static_cast<float>(knight.height)};
        Rectangle dest{knightPos.x,knightPos.y,4.0f*static_cast<float>(knight.width)/6.0f,4.0f*static_cast<float>(knight.height)};
        DrawTexturePro(knight,source,dest,Vector2{},0.f,WHITE);

        EndDrawing();
    }

    UnloadTexture(map);
    UnloadTexture(knight);

    CloseWindow();

    return 0;
}