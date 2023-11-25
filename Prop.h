#include "raylib.h"

class Prop
{
public:
    Prop();
private:
    Texture2D textre{};
    Vector2 worldPos{};
    float scale{4.f};
};