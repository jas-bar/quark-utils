#ifndef BUFFEREDRENDERER_H
#define BUFFEREDRENDERER_H

#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_opengles.h>
#include <SDL2/SDL_opengles2.h>

#define TEXCOORD_SIZE 2
#define COLOR_SIZE 4

#ifndef GL_VERSION_2_0
    #ifdef GL_ES_VERSION_2_0
        #define GLES
    #else
        #error "OpenGL2 or GLES2 are needed for bufferedrenderer"
    #endif
#endif

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
    void sendData();
    T* getPointer();
    void reset();
    ~Buffer();
};

class BufferedRenderer
{
private:
    Buffer<GLfloat> vertices, normals, texCoords, colors;
    GLint mode;
    GLuint dimensionCount;
    GLuint shader;
public:
    BufferedRenderer(GLint mode, unsigned int maxVertices, unsigned int dimensions, GLuint shader);
    ~BufferedRenderer();
    void endEdit();
    void reset();
    void draw();
    void addVertex3D(float x, float y, float z);
    void addVertex2D(float x, float y);
    void vertexCoord(float x);
    void addTextureCoord(float x, float y);
    void addNormal3D(float x, float y, float z);
    void addColor(float r, float g, float b, float a);
};



#endif // BUFFEREDRENDERER_H
