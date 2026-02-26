#include <math.h>
#include <raylib.h>

// gcc shadow-cast.c -o shadow-cast $(pkg-config --cflags --libs raylib) -lm

bool SegmentCircleIntersect(Vector2 A, Vector2 B, Vector2 C, float radius, Vector2 *hitPoint){
    Vector2 d = { B.x - A.x, B.y - A.y };
    Vector2 f = { C.x - A.x, C.y - A.y };

    float dotDD = d.x*d.x + d.y*d.y;
    float dotFD = f.x*d.x + f.y*d.y;

    float t = dotFD / dotDD;

    if (t < 0) t = 0;
    if (t > 1) t = 1;

    Vector2 closest = {
        A.x + d.x * t,
        A.y + d.y * t
    };

    float dx = closest.x - C.x;
    float dy = closest.y - C.y;

    float distSquared = dx*dx + dy*dy;

    if (distSquared <= radius*radius)
    {
        *hitPoint = closest;
        return true;
    }

    return false;
}

int main(void)
{
    const int factor = 50;
    const int screenWidth = 16*factor;
    const int screenHeight = 9*factor;

    InitWindow(screenWidth, screenHeight, "shadow-cast");
    SetTargetFPS(60);

    Vector2 obstacles[] = {
        {200, 200},
        {500, 300},
        {350, 500}
    };

    float radii[] = {70, 50, 90};

    int obstacleCount = 3;

    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);

        float centerX = GetMouseX();
        float centerY = GetMouseY();

        Vector2 origin = { centerX, centerY };

        DrawText(TextFormat("X: %f, Y: %f", centerX, centerY), 0, 0, 12, WHITE);

        DrawCircle(centerX, centerY, 30, WHITE);

        int rayCount = 360;
        float rayLength = 2000.0f;

        for (int i = 0; i < rayCount; i++)
        {
            float angle = (2 * PI / rayCount) * i;

            float dirX = cosf(angle);
            float dirY = sinf(angle);

            Vector2 endPoint = {
                centerX + dirX * rayLength,
                centerY + dirY * rayLength
            };

            Vector2 closestHit;
            float closestDistSq = rayLength * rayLength;
            bool hitSomething = false;

            for (int j = 0; j < obstacleCount; j++)
            {
                Vector2 hit;

                if (SegmentCircleIntersect(origin, endPoint,
                                           obstacles[j], radii[j],
                                           &hit))
                {
                    float dx = hit.x - origin.x;
                    float dy = hit.y - origin.y;
                    float distSq = dx*dx + dy*dy;

                    if (distSq < closestDistSq)
                    {
                        closestDistSq = distSq;
                        closestHit = hit;
                        hitSomething = true;
                    }
                }
            }

            if (hitSomething)
                DrawLineV(origin, closestHit, WHITE);
            else
                DrawLineV(origin, endPoint, WHITE);
        }

        for (int i = 0; i < obstacleCount; i++)
        {
            DrawCircleV(obstacles[i], radii[i], YELLOW);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
