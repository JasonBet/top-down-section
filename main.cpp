#include "raylib.h"
#include "raymath.h"

class Character
{
private:
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
    Vector2 screenPos{};
    Vector2 worldPos{};
    // 1 : facing right, -1 : facing left
    float rightLeft{1.f};
    // animation variables
    float runningTime{};
    int frame{};
    const int maxFrames{6};
    const float updateTime{1.f / 12.f};
    const float speed{4.f};

public:
    Vector2 getWorldPos() { return worldPos; }
    void setScreenPos(int winWidth, int winHeight);
    void tick(float deltaTime);
};

void Character::setScreenPos(int winWidth, int winHeight)
{
    screenPos = {static_cast<float>(winWidth) / 2.0f - 4.0f * (0.5f * static_cast<float>(texture.width) / 6.0f),
                 static_cast<float>(winHeight) / 2.0f - 4.0f * (0.5f * static_cast<float>(texture.height))};
}

void Character::tick(float deltaTime)
{
    Vector2 direction{};
    if (IsKeyDown(KEY_A))
        direction.x -= 1.0;
    if (IsKeyDown(KEY_D))
        direction.x += 1.0;
    if (IsKeyDown(KEY_W))
        direction.y -= 1.0;
    if (IsKeyDown(KEY_S))
        direction.y += 1.0;

    if (Vector2Length(direction) != 0.0)
    {
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed));
        direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
        texture = run;
    }
    else
    {
        texture = idle;
    }
    // update animation frame
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        if (frame > maxFrames)
            frame = 0;
    }
    // draw the character
    Rectangle source{frame * static_cast<float>(texture.width) / 6.f, 0.f, rightLeft * static_cast<float>(texture.width) / 6.f, static_cast<float>(texture.height)};
    Rectangle dest{screenPos.x, screenPos.y, 4.0f * static_cast<float>(texture.width) / 6.0f, 4.0f * static_cast<float>(texture.height)};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}
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

    SetTargetFPS(60);
    // game loop
    while (!WindowShouldClose())
    {
        // start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        // draw the map
        DrawTextureEx(map, mapPos, 0.0, 4, WHITE);

        EndDrawing();
    }

    UnloadTexture(map);
    CloseWindow();

    return 0;
}