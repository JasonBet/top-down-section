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
    Texture2D map=LoadTexture("nature_tileset/OpenWorldMap24x24.png");

    SetTargetFPS(60);
    // game loop
    while(!WindowShouldClose())
    {
        // start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        Vector2 mapPos{0.0,0.0};
        DrawTextureEx(map,mapPos,0.0,4,WHITE);



        EndDrawing();
    }

    UnloadTexture(map);

    CloseWindow();

    return 0;
}