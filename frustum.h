#ifndef FRUSTUM_H
#define FRUSTUM_H

#include <SDL2/SDL_opengl.h>

class Frustum
{
private:
    GLfloat* proj;
    GLfloat* modl;
    GLfloat clip[16];
    GLfloat frustum[6][4];

    void normalize(int plane);
public:
    Frustum();

    void init();
    bool isBoxInFrustum(float x, float y, float z, float w, float h, float d);

    ~Frustum();
};

#endif // FRUSTUM_H
