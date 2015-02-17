#include "frustum.h"

#include <stdlib.h>
#include <SDL.h>

#define POW2(A) A * A

void Frustum::normalize(int plane)
{
    float t = SDL_sqrt(POW2(frustum[plane][0]) + POW2(frustum[plane][1]) + POW2(frustum[plane][2]) );

    for(int i = 0; i < 4; ++i){
        frustum[plane][i] /= t;
    }
}

Frustum::Frustum()
{

}

#define INSERT_CLIP(MODL, PROJ, A, B, C, D, E, F, G, H) (*(MODL + A) * *(PROJ + B) + *(MODL + C) * *(PROJ + D) + *(MODL + E) * *(PROJ + F) + *(MODL + G) * *(PROJ + H))

void Frustum::init()
{
    proj = (float*)malloc(16 << 2);
    glGetFloatv(GL_PROJECTION_MATRIX, proj);

    modl = (float*)malloc(16 << 2);
    glGetFloatv(GL_PROJECTION_MATRIX, modl);

    // fuj.
    clip[0] = INSERT_CLIP(modl, proj, 0, 0, 1, 4, 2, 8, 3, 12);
    clip[1] = INSERT_CLIP(modl, proj, 0, 1, 1, 5, 2, 9, 3, 13);
    clip[2] = INSERT_CLIP(modl, proj, 0, 2, 1, 6, 2, 10, 3, 14);
    clip[3] = INSERT_CLIP(modl, proj, 0, 3, 1, 7, 2, 11, 3, 15);
    // example after macro substitution:
    // clip[4] = *(modl + 4) * *(proj + 0) + *(modl + 5) * *(proj + 4) + *(modl + 6) * *(proj + 8) + *(modl + 7) * *(proj + 12);
    clip[4] = INSERT_CLIP(modl, proj, 4, 0, 5, 4, 6, 8, 7, 12);
    clip[5] = INSERT_CLIP(modl, proj, 4, 1, 5, 5, 6, 9, 7, 13);
    clip[6] = INSERT_CLIP(modl, proj, 4, 2, 5, 6, 6, 10, 7, 14);
    clip[7] = INSERT_CLIP(modl, proj, 4, 3, 5, 7, 6, 11, 7, 15);
    clip[8] = INSERT_CLIP(modl, proj, 8, 0, 9, 4, 10, 8, 11, 12);
    clip[9] = INSERT_CLIP(modl, proj, 8, 1, 9, 5, 10, 9, 11, 13);
    clip[10] = INSERT_CLIP(modl, proj, 8, 2, 9, 6, 10, 10, 11, 14);
    clip[11] = INSERT_CLIP(modl, proj, 8, 3, 9, 7, 10, 11, 11, 15);
    clip[12] = INSERT_CLIP(modl, proj, 12, 0, 13, 4, 14, 8, 15, 12);
    clip[13] = INSERT_CLIP(modl, proj, 12, 1, 13, 5, 14, 9, 15, 13);
    clip[14] = INSERT_CLIP(modl, proj, 12, 2, 13, 6, 14, 10, 15, 14);
    clip[15] = INSERT_CLIP(modl, proj, 12, 3, 13, 7, 14, 11, 15, 15);

    /* Extract the numbers for the RIGHT plane */
    frustum[0][0] = clip[3] - clip[0];
    frustum[0][1] = clip[7] - clip[4];
    frustum[0][2] = clip[11] - clip[8];
    frustum[0][3] = clip[15] - clip[12];
    normalize(0);

    /* Extract the numbers for the LEFT plane */
    frustum[1][0] = clip[3] + clip[0];
    frustum[1][1] = clip[7] + clip[4];
    frustum[1][2] = clip[11] + clip[8];
    frustum[1][3] = clip[15] + clip[12];
    normalize(1);

    /* Extract the BOTTOM plane */
    frustum[2][0] = clip[3] + clip[1];
    frustum[2][1] = clip[7] + clip[5];
    frustum[2][2] = clip[11] + clip[9];
    frustum[2][3] = clip[15] + clip[13];
    normalize(2);

    /* Extract the TOP plane */
    frustum[3][0] = clip[3] - clip[1];
    frustum[3][1] = clip[7] - clip[5];
    frustum[3][2] = clip[11] - clip[9];
    frustum[3][3] = clip[15] - clip[13];
    normalize(3);

    /* Extract the FAR plane */
    frustum[4][0] = clip[3] - clip[2];
    frustum[4][1] = clip[7] - clip[6];
    frustum[4][2] = clip[11] - clip[10];
    frustum[4][3] = clip[15] - clip[14];
    normalize(4);

    /* Extract the NEAR plane */
    frustum[5][0] = clip[3] - clip[2];
    frustum[5][1] = clip[7] - clip[6];
    frustum[5][2] = clip[11] - clip[10];
    frustum[5][3] = clip[15] - clip[14];
    normalize(5);
}

bool Frustum::isBoxInFrustum(float x, float y, float z, float w, float h, float d)
{
    bool boxInFrustum = false;
    for(int i = 0; i < 6; ++i){
        boxInFrustum |= (frustum[i][0] * (x - w) + frustum[i][1] * (y - h) + frustum[i][2] * (z - d) + frustum[i][3] > 0);
        boxInFrustum |= (frustum[i][0] * (x + w) + frustum[i][1] * (y - h) + frustum[i][2] * (z - d) + frustum[i][3] > 0);
        boxInFrustum |= (frustum[i][0] * (x - w) + frustum[i][1] * (y + h) + frustum[i][2] * (z - d) + frustum[i][3] > 0);
        boxInFrustum |= (frustum[i][0] * (x + w) + frustum[i][1] * (y + h) + frustum[i][2] * (z - d) + frustum[i][3] > 0);
        boxInFrustum |= (frustum[i][0] * (x - w) + frustum[i][1] * (y - h) + frustum[i][2] * (z + d) + frustum[i][3] > 0);
        boxInFrustum |= (frustum[i][0] * (x + w) + frustum[i][1] * (y - h) + frustum[i][2] * (z + d) + frustum[i][3] > 0);
        boxInFrustum |= (frustum[i][0] * (x - w) + frustum[i][1] * (y + h) + frustum[i][2] * (z + d) + frustum[i][3] > 0);
        boxInFrustum |= (frustum[i][0] * (x + w) + frustum[i][1] * (y + h) + frustum[i][2] * (z + d) + frustum[i][3] > 0);
        if(!boxInFrustum)
            return false;
    }
    return boxInFrustum;
}

Frustum::~Frustum()
{

}

