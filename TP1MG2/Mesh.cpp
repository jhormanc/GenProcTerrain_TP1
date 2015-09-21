#include "Mesh.h"


Mesh::Mesh(int height_, int width_)
{
	vertices_by_x = height_;
	vertices_by_z = width_;
    quads_by_x = vertices_by_x - 1;
    quads_by_z = vertices_by_z - 1;

	m_vertices.reserve(vertices_by_x * vertices_by_z);
    m_textures.reserve(vertices_by_x * vertices_by_z);
}


Mesh::~Mesh(void)
{
}

int Mesh::getHeight()
{
	return vertices_by_x;
}

int Mesh::getWidth()
{
	return vertices_by_z;
}

QVector<QVector3D> Mesh::getVertices()
{
	return m_vertices;
}

QVector<QVector3D> Mesh::getVertexArray()
{
	return m_vertexarray;
}

QVector<QVector2D> Mesh::getTextures()
{
	return m_textures;
}

QVector<QVector2D> Mesh::getTextureArray()
{
	return m_texturearray;
}

QVector<GLuint> Mesh::getIndices()
{
	return m_indices;
}

void Mesh::pushVertice(QVector3D vert)
{
	m_vertices.push_back(vert);
}

void Mesh::pushTexture(QVector2D text)
{
	m_textures.push_back(text);
}

void Mesh::generateArray()
{
	 // Vertex array & indices
    m_vertexarray.reserve(quads_by_x * quads_by_z * 6);
    m_texturearray.reserve(quads_by_x * quads_by_z * 6);
    m_indices.reserve(quads_by_x * quads_by_z * 6);
    for (int z = 0; z < quads_by_z; ++z)
    {
        for (int x = 0; x < quads_by_x; ++x)
        {
            int i = z * vertices_by_x + x;

            // VertexArray
            m_vertexarray.push_back(m_vertices[i]);
            m_vertexarray.push_back(m_vertices[i+vertices_by_x]);
            m_vertexarray.push_back(m_vertices[i+1]);

            m_vertexarray.push_back(m_vertices[i+1]);
            m_vertexarray.push_back(m_vertices[i+vertices_by_x]);
            m_vertexarray.push_back(m_vertices[i+1+vertices_by_x]);

            // Texture array
            m_texturearray.push_back(m_textures[i]);
            m_texturearray.push_back(m_textures[i+vertices_by_x]);
            m_texturearray.push_back(m_textures[i+1]);

            m_texturearray.push_back(m_textures[i+1]);
            m_texturearray.push_back(m_textures[i+vertices_by_x]);
            m_texturearray.push_back(m_textures[i+1+vertices_by_x]);

            // Indices
            m_indices.push_back(i);
            m_indices.push_back(i + vertices_by_x);
            m_indices.push_back(i + 1);

            m_indices.push_back(i + 1);
            m_indices.push_back(i + vertices_by_x);
            m_indices.push_back(i + 1 + vertices_by_x);
        }
    }
}


