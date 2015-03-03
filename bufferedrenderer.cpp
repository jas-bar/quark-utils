#include "bufferedrenderer.h"
#include <cstring>
#define QUARK_GL_NULL 0

GLuint loadShader(GLenum shaderType, const char* shaderCSTR)
{
    const GLint strLen = strlen(shaderCSTR);

    GLuint shaderObject = glCreateShader(shaderType);
    glShaderSource(shaderObject, 1, &shaderCSTR, &strLen);
    glCompileShader(shaderObject);

    return shaderObject;
}

BufferedRenderer::BufferedRenderer(GLint mode, unsigned int maxVertices, unsigned int dimensions, GLuint shader) :
    vertices(Buffer<GLfloat>(maxVertices * dimensions)),
    normals(Buffer<GLfloat>(maxVertices * dimensions)),
    texCoords(Buffer<GLfloat>(maxVertices * TEXCOORD_SIZE)),
    colors(Buffer<GLfloat>(maxVertices * COLOR_SIZE))
{
    this->mode = mode;
    dimensionCount = dimensions;
    this->shader = shader;
    if(shader == 0){
        GLuint vertexShader = loadShader(GL_VERTEX_SHADER, "attribute vec4 vPosition; void main() { gl_Position = vPosition; }");
        GLuint fragmentShader = loadShader(GL_VERTEX_SHADER, "precision mediump float; uniform vec4 vColor; void main(){ gl_FragCoolor = vColor;}");

        shader = glCreateProgram();

        glAttachShader(shader, vertexShader);
        glAttachShader(shader, fragmentShader);
        glLinkProgram(shader);
    }
}

BufferedRenderer::~BufferedRenderer()
{
}

#ifndef GLES
void BufferedRenderer::endEdit()
{

    glBindBuffer(GL_ARRAY_BUFFER, vertices.getBufferID());
    glBufferData(GL_ARRAY_BUFFER, vertices.getDataCount()*sizeof(GLfloat), vertices.getPointer(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, normals.getBufferID());
    glBufferData(GL_ARRAY_BUFFER, normals.getDataCount()*sizeof(GLfloat), normals.getPointer(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, texCoords.getBufferID());
    glBufferData(GL_ARRAY_BUFFER, texCoords.getDataCount()*sizeof(GLfloat), vertices.getPointer(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, colors.getBufferID());
    glBufferData(GL_ARRAY_BUFFER, colors.getDataCount()*sizeof(GLfloat), colors.getPointer(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, QUARK_GL_NULL);
}
#else
void BufferedRenderer::endEdit()
{

}
#endif

void BufferedRenderer::reset()
{
    vertices.reset();
    texCoords.reset();
    normals.reset();
    colors.reset();
}

#ifndef GLES
void BufferedRenderer::draw()
{

    glBindBuffer(GL_ARRAY_BUFFER, vertices.getBufferID());
    glVertexPointer(dimensionCount, GL_FLOAT, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, normals.getBufferID());
    glNormalPointer(GL_FLOAT, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, texCoords.getBufferID());
    glTexCoordPointer(TEXCOORD_SIZE, GL_FLOAT, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, colors.getBufferID());
    glColorPointer(COLOR_SIZE, GL_FLOAT, 0, 0);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glDrawArrays(mode, 0, vertices.getDataCount() / dimensionCount);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, QUARK_GL_NULL);
}
#else
void BufferedRenderer::draw()
{
    glUseProgram(shader);

    GLint mPositionHandle = glGetAttribLocation(shader, "vPosition");
    glEnableVertexAttribArray(mPositionHandle);
    glVertexAttribPointer(mPositionHandle, dimensionCount, GL_FLOAT, false, dimensionCount*sizeof(GLfloat), vertices.getPointer());

    GLint mColorHandle = glGetUniformLocation(shader, "vColor");
    glEnableVertexAttribArray(mColorHandle);
    glVertexAttribPointer(mColorHandle, COLOR_SIZE, GL_FLOAT, false, COLOR_SIZE * sizeof(GLfloat), colors.getPointer());

    glDrawArrays(mode, 0, vertices.getDataCount() / dimensionCount);

    glDisableVertexAttribArray(mPositionHandle);
    glDisableVertexAttribArray(mColorHandle);
}
#endif

void BufferedRenderer::addVertex3D(float x, float y, float z)
{
    vertices.add(x);
    vertices.add(y);
    vertices.add(z);
    ++vertexCount;
}

void BufferedRenderer::addTextureCoord(float x, float y)
{
    texCoords.add(x);
    texCoords.add(y);
}

void BufferedRenderer::addNormal3D(float x, float y, float z)
{
    normals.add(x);
    normals.add(y);
    normals.add(z);
}

void BufferedRenderer::addColor(float r, float g, float b, float a)
{
    colors.add(r);
    colors.add(g);
    colors.add(b);
    colors.add(a);
}


template <class T>
Buffer<T>::Buffer(unsigned int maxSize)
{
    data = new T[maxSize];
    glGenBuffers(1, &bufferId);
    dataCount = 0;
}

template <class T>
void Buffer<T>::add(T newData)
{
    data[dataCount] = newData;
    ++dataCount;
}

template <class T>
GLuint Buffer<T>::getBufferID()
{
    return bufferId;
}

template <class T>
GLuint Buffer<T>::getDataCount()
{
    return dataCount;
}

template <class T>
T* Buffer<T>::getPointer()
{
    return data;
}

/*template <class T>
void Buffer<T>::sendData()
{
    glBindBuffer(GL_ARRAY_BUFFER, bufferId);
    glBufferData(GL_ARRAY_BUFFER, dataCount*sizeof(T), data, GL_STATIC_DRAW);
}*/

template <class T>
void Buffer<T>::reset()
{
    dataCount = 0;
}

template <class T>
Buffer<T>::~Buffer()
{
    glDeleteBuffers(1, &bufferId);
    delete[] data;
}
