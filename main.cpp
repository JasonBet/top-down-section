#include "raylib.h"

int main()
{
    // array of window dimensions
    int windowDimensions[2];
    windowDimensions[0]=384;
    windowDimensions[1]=384;

    // initialize window
    InitWindow(windowDimensions[0],windowDimensions[1],"TOP-DOWN");

    // load map texture
    Texture2D WorldMap=LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos{0.0,0.0};

    // game loop
    while(!WindowShouldClose())
    {
        // start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        DrawTextureEx(WorldMap,mapPos,0.0,4,WHITE);



        EndDrawing();
    }

    UnloadTexture(WorldMap);

    CloseWindow();
}