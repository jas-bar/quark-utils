#include "bufferedrenderer.h"

#define QUARK_GL_NULL 0

BufferedRenderer::BufferedRenderer(GLint mode, unsigned int maxVertices, unsigned int dimensions) :
    vertices(Buffer<GLfloat>(maxVertices * dimensions)),
    normals(Buffer<GLfloat>(maxVertices * dimensions)),
    texCoords(Buffer<GLfloat>(maxVertices * TEXCOORD_SIZE)),
    colors(Buffer<GLfloat>(maxVertices * COLOR_SIZE))
{
    this->mode = mode;
    dimensionCount = dimensions;
}

BufferedRenderer::~BufferedRenderer()
{
}

void BufferedRenderer::endEdit()
{
    vertices.sendData();
    normals.sendData();
    texCoords.sendData();
    colors.sendData();

    glBindBuffer(GL_ARRAY_BUFFER, QUARK_GL_NULL);
}

void BufferedRenderer::reset()
{
    vertices.reset();
    texCoords.reset();
    normals.reset();
    colors.reset();
}

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
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, QUARK_GL_NULL);
}

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

template <class T>
void Buffer<T>::sendData()
{
    glBindBuffer(GL_ARRAY_BUFFER, bufferId);
    glBufferData(GL_ARRAY_BUFFER, dataCount*sizeof(T), data, GL_STATIC_DRAW);
}

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
