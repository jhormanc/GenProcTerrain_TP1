#pragma once

#include <QtGui/QVector2D>
#include <QtGui/QVector3D>
#include <QtOpenGL/QGLBuffer>

class Mesh
{
public:
	Mesh(int height_, int width_);
	~Mesh(void);

	void pushVertice(QVector3D vert);
	void pushTexture(QVector2D text);
	void generateArray();

	int getHeight();
	int getWidth();

	QVector<QVector3D> getVertices();
	QVector<QVector3D> getVertexArray();
	QVector<QVector2D> getTextures();
	QVector<QVector2D> getTextureArray();
	QVector<GLuint>    getIndices();


private:
	// Heightmap infos
    int vertices_by_x;
    int vertices_by_z;
    int quads_by_x;
    int quads_by_z;

	QVector<QVector3D> m_vertices;
    QVector<QVector3D> m_vertexarray;
    QVector<QVector2D> m_textures;
    QVector<QVector2D> m_texturearray;
    QVector<GLuint>    m_indices;
};

