#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include <windows.h>
#include <tchar.h>

typedef unsigned int IUINT32;

typedef struct { float m[4][4]; } mat4x4_t;
typedef struct { float x, y, z, w; } vec4_t;
typedef vec4_t point_t;

int clamp(int x, int min, int max) { return (x < min)?min:(x>max)?max:x ;}

float interp(float x1, float x2, float t) { return x1 + t * (x2 - x1);}

float vlen(const vec4_t *v)
{
    float sq = v->x * v->x + v->y * v->y + v->z * v->z;
    return (float)sqrt(sq);
}

// Render Device
typedef struct {} device_t;

#define RENDER_STATE_WIREFRAME
#define RENDER_STATE_TEXTURE
#define RENDER_STATE_COLOR


int main(void)
{
    device_t device;
    TCHAR *title = _T("Mini3d render totorial");

    // device init
    // set camera
    // init texture

}