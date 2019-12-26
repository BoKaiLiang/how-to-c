#include <stdio.h>

typedef struct {
    union
    {
        struct { float x, y, z; };
        struct { float r, g, b; };
        struct { float s, t, p; };
        float vec[3];
    };
} vec3f;

int main() {

    vec3f vector = { .x = 3.0f, .y = 4.0f, .z = 5.0f };
    vec3f color = { .r = 1.0f, .g = 0.32f, .b = 0.24f };
    vec3f texcoords = { .s = 0.5f, .t = 0.5f, .p = 0.0f };
    vec3f data = { 1.0f, 1.0f, 1.0f };

    printf("vector = { %f, %f, %f }\n", vector.x, vector.y, vector.z);

    //// MAGIC! ////

    printf("color = { %f, %f, %f }\n", color.r, color.y, color.z);

    printf("tex coords = { %f, %f, %f }\n", texcoords.x, texcoords.y, texcoords.z);

    printf("data = { %f, %f, %f }\n", data.x, data.y, data.z);

    return 0;
}