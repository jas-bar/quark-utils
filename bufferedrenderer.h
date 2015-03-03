#ifndef BUFFEREDRENDERER_H
#define BUFFEREDRENDERER_H

#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_opengles.h>
#include <SDL2/SDL_opengles2.h>

#define TEXCOORD_SIZE 2


template <class T>
class Buffer {
private:
    GLuint bufferId;
    T* data;
    GLuint dataCount;
public:
    Buffer(unsigned int maxSize);
    void add(T newData);
    GLuint getBufferID();
    GLuint getDataCount();
    T* getPointer();
    void reset();
    ~Buffer();
};

class BufferedRenderer
{
private:
    Buffer<GLfloat> vertices, normals, texCoords;
    GLint mode;
    GLsizei vertexCount;
    GLuint dimensionCount;
public:
    BufferedRenderer(GLint mode, unsigned int maxVertices, unsigned int dimensions);
    ~BufferedRenderer();
    void endEdit();
    void reset();
    void draw();
    void addVertex3D(float x, float y, float z);
    void addTextureCoord(float x, float y);
    void addNormal3D(float x, float y, float z);
};



#endif // BUFFEREDRENDERER_H
