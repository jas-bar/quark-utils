#ifndef BUFFEREDRENDERER_H
#define BUFFEREDRENDERER_H

#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_opengles.h>
#include <SDL2/SDL_opengles2.h>

#define TEXCOORD_SIZE 2

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
    GLuint shader;
public:
    BufferedRenderer(GLint mode, unsigned int maxVertices, unsigned int dimensions, GLuint shader);
    ~BufferedRenderer();
    void endEdit();
    void reset();
    void draw();
    void addVertex3D(float x, float y, float z);
    void addTextureCoord(float x, float y);
    void addNormal3D(float x, float y, float z);
};



#endif // BUFFEREDRENDERER_H
