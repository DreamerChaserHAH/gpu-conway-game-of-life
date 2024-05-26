#include <raylib.h>
#include <iostream>
#include <chrono>

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#include <emscripten/bind.h>
#include <emscripten/val.h>

using namespace emscripten;

    EM_JS(int, canvas_get_width, (), {
        return window.innerWidth;
    });

    EM_JS(int, canvas_get_height, (), {
        return window.innerHeight;
    });

#endif

#define GLSL_VERSION 100

Vector2 previousMousePosition = Vector2{};
const std::chrono::milliseconds interval(50);
auto lastExecutionTime = std::chrono::steady_clock::now();
Vector2 ScreenResolution = Vector2{static_cast<float>(1920), static_cast<float>(1080)};

void DrawLineFromPreviousPosition()
{
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
    {
        Vector2 currentMousePosition = GetMousePosition();
        DrawLine(currentMousePosition.x, currentMousePosition.y, previousMousePosition.x, previousMousePosition.y, WHITE);
    }
    previousMousePosition = GetMousePosition();
}

int main()
{

    #ifdef __EMSCRIPTEN__
    //SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    ScreenResolution.x = static_cast<float>(canvas_get_width());
    ScreenResolution.y = static_cast<float>(canvas_get_height());
    
    #endif

    InitWindow(ScreenResolution.x, ScreenResolution.y, "Conway's Game of Life");

    RenderTexture2D buffer = LoadRenderTexture(ScreenResolution.x, ScreenResolution.y);
    RenderTexture2D target = LoadRenderTexture(ScreenResolution.x, ScreenResolution.y);

    Shader golShader = LoadShader("resources/gol.vs", "resources/gol.fs");
    int textureLoc = GetShaderLocation(golShader, "previous_texture");
    int resolutionLoc = GetShaderLocation(golShader, "screen_resolution");

    SetShaderValue(golShader, resolutionLoc,&ScreenResolution,SHADER_UNIFORM_VEC2);

    SetTargetFPS(60);
    bool InitFrame = true;

    BeginDrawing();
    BeginTextureMode(buffer);
    DrawRectangle(0, 0, ScreenResolution.x, ScreenResolution.y,BLACK);
    EndTextureMode();
    EndDrawing();

    BeginDrawing();
    BeginTextureMode(target);
    DrawTextureEx(buffer.texture, (Vector2){0.0f, 0.0f}, 0.0f, 1.0f, Color{255, 255, 255, 255});
    EndTextureMode();
    EndDrawing();

    while (!WindowShouldClose())
    {
        BeginDrawing();

        // Current time
        auto currentTime = std::chrono::steady_clock::now();

        // Calculate time elapsed since the last execution
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastExecutionTime);

        // Check if the elapsed time is greater than or equal to the desired interval
        if (elapsedTime >= interval)
        {
            BeginShaderMode(golShader);
            BeginTextureMode(buffer);
            SetShaderValueTexture(golShader, textureLoc, target.texture);

            DrawTextureEx(target.texture, (Vector2){0.0f, 0.0f}, 0.0f, 1.0f, WHITE);
            // DrawTextureEx(target.texture, (Vector2){0.0f, 0.0f}, 0.0f, 1.0f, WHITE);
            // DrawRectangle(0, 0, 500, 500, WHITE);
            EndTextureMode();
            EndShaderMode();

            lastExecutionTime = currentTime;
        }

        BeginTextureMode(buffer);
        DrawLineFromPreviousPosition();
        EndTextureMode();

        BeginTextureMode(target);
        DrawTextureEx(buffer.texture, (Vector2){0.0f, 0.0f}, 0.0f, 1.0f, Color{255, 255, 255, 255});
        EndTextureMode();

        DrawTexturePro(target.texture, (Rectangle){0.0f, 0.0f, ScreenResolution.x, ScreenResolution.y}, Rectangle{0, 0, ScreenResolution.x, ScreenResolution.y}, Vector2{}, 0, Color{255, 255, 255, 255});
        EndDrawing();
    }
    UnloadRenderTexture(buffer);
    UnloadRenderTexture(target);
    UnloadShader(golShader);
    CloseWindow();
    return 0;
}