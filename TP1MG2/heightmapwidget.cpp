/*
    Copyright 2010-2011  Guillaume Belz
    This software is free: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.
    This software is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    in <http://www.gnu.org/licenses/>.
*/

#include "heightmapwidget.h"
#include <QtGui/QMouseEvent>

const float MAP_SIZE = 5.0;
QString MODE_NAME[4] = { "MODE_GL_VERTEX",
                         "MODE_VERTEXARRAY",
                         "MODE_VERTEXARRAY_INDICES",
                         "MODE_VERTEBUFFEROBJECT_INDICES" };

HeightmapWidget::HeightmapWidget(Terrain *t, QWidget *parent) :
        QGLWidget(parent),
        m_vertexbuffer(QGLBuffer::VertexBuffer),
        m_indicebuffer(QGLBuffer::IndexBuffer),
        m_texturebuffer(QGLBuffer::VertexBuffer),
		terrain(t)
{
    // Render mode set up
	mode_rendu = MODE_VERTEBUFFEROBJECT_INDICES;
    mode_texture = true;
    mode_fill = true;

    // Timer settings
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    delay = 20;
    timer.start(delay);
    frame_count = 0;
    last_count = 0;
    last_time = QTime::currentTime();
}

HeightmapWidget::~HeightmapWidget()
{
    deleteTexture(m_textureid);
	delete mesh;
}

QSize HeightmapWidget::minimumSizeHint() const
{
    return QSize(200,200);
}

QSize HeightmapWidget::sizeHint() const
{
    return QSize(1280, 720); // 800x600
}

void HeightmapWidget::initializeGL()
{
    // View & rotation settings
    distance = -10.0;
    x_rot = 0;
    y_rot = 0;
    z_rot = 0;

    // Load heightmap
    //QImage img = QImage("x64/Debug/testhm.png");

	mesh = terrain->GetMesh();

    // Load texture
    m_textureid = bindTexture(QPixmap("Resources/Heightmap.png"), GL_TEXTURE_2D);

    // Vertex buffer init
    m_vertexbuffer.create();
    m_vertexbuffer.bind();
    m_vertexbuffer.allocate(mesh->getVertices().constData(), mesh->getVertices().size() * sizeof(QVector3D));
    m_vertexbuffer.release();

    // Texture coordonnees vbo
    m_texturebuffer.create();
    m_texturebuffer.bind();
    m_texturebuffer.allocate(mesh->getTextures().constData(), sizeof(QVector2D) * mesh->getTextures().size());
    m_texturebuffer.release();

    // Indices buffer init
    m_indicebuffer.create();
    m_indicebuffer.bind();
    m_indicebuffer.allocate(mesh->getIndices().constData(), mesh->getIndices().size() * sizeof(GLuint));
    m_indicebuffer.release();

    // GL options
    qglClearColor(Qt::darkGray);
    glEnable(GL_DEPTH_TEST);
}

void HeightmapWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT, mode_fill ? GL_FILL : GL_LINE);
    glPolygonMode(GL_BACK, GL_LINE);

    if (mode_texture)
        glEnable(GL_TEXTURE_2D);
    else
        glDisable(GL_TEXTURE_2D);

    // Model view matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	gluLookAt(0.0, 0.0, -distance,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    glRotatef(x_rot / 16.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(y_rot / 16.0f, 0.0f, 1.0f, 0.0f);
    glRotatef(z_rot / 16.0f, 0.0f, 0.0f, 1.0f);


	//glTranslatef(x_dis, 0, z_dis);

    // Projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.0f, 1.0*width()/height(), 0.1f, 100.0f);

    // Draw map
    qglColor(Qt::white);
	glLineWidth(1);


	QVector<QVector3D> m_vertices = mesh->getVertices();
    QVector<QVector3D> m_vertexarray = mesh->getVertexArray();
    QVector<QVector2D> m_textures = mesh->getTextures();
    QVector<QVector2D> m_texturearray = mesh->getTextureArray();
	QVector<GLuint>    m_indices = mesh->getIndices();

    switch(mode_rendu)
    {
    case MODE_GL_VERTEX:        
        glBegin(GL_TRIANGLES);
        for(int i = 0; i < m_vertexarray.size(); i += 3)
        {
            glBindTexture(GL_TEXTURE_2D, m_textureid);

            glTexCoord2f(m_texturearray[i].x(), m_texturearray[i].y());
            glVertex3f(m_vertexarray[i].x(), m_vertexarray[i].y(), m_vertexarray[i].z());

            glTexCoord2f(m_texturearray[i+1].x(), m_texturearray[i+1].y());
            glVertex3f(m_vertexarray[i+1].x(), m_vertexarray[i+1].y(), m_vertexarray[i+1].z());

            glTexCoord2f(m_texturearray[i+2].x(), m_texturearray[i+2].y());
            glVertex3f(m_vertexarray[i+2].x(), m_vertexarray[i+2].y(), m_vertexarray[i+2].z());
        }   
		
        glEnd();
        break;

    case MODE_VERTEXARRAY:
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);

        glVertexPointer(3, GL_FLOAT, 0, m_vertexarray.constData());
        glTexCoordPointer(2, GL_FLOAT, 0, m_texturearray.constData());

        glDrawArrays(GL_TRIANGLES, 0, m_vertexarray.size());

        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);

        break;

    case MODE_VERTEXARRAY_INDICES:
        glEnableClientState(GL_VERTEX_ARRAY);        
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);

        glVertexPointer(3, GL_FLOAT, 0, m_vertices.constData());
        glTexCoordPointer(2, GL_FLOAT, 0, m_textures.constData());

        glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, m_indices.constData());

        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);

        break;

    case MODE_VERTEBUFFEROBJECT_INDICES:
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);

        m_vertexbuffer.bind();
        glVertexPointer(3, GL_FLOAT, 0, NULL);
        m_vertexbuffer.release();

        m_texturebuffer.bind();
        glTexCoordPointer(2, GL_FLOAT, 0, NULL);
        m_texturebuffer.release();

        m_indicebuffer.bind();
        glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, NULL);
        m_indicebuffer.release();

        glDisableClientState(GL_VERTEX_ARRAY);
        break;
    }

	std::list<Ray>::iterator
		ray(listRays.begin()),
		lend(listRays.end());

	for (; ray != lend; ++ray)
	{
		double t;
		bool touche = (Node *)terrain->intersect(*ray, t);
		glLineWidth(2);
		glBegin(GL_LINE_STRIP);
		glColor3f(0.0f, 0.0f, 1.0f); // le point de départ du lancé est en bleu

		// Origine
		glVertex3f((MAP_SIZE * ray->getOrigin().x / mesh->getHeight()) - MAP_SIZE / 2,
			ray->getOrigin().z / 255,
			(MAP_SIZE * ray->getOrigin().y / mesh->getWidth()) - MAP_SIZE / 2);

		if (touche)
			glColor3f(0.0f, 1.0f, 0.0f); // point vert si le Ray a touché le terrain
		else
			glColor3f(1.0f, 0.0f, 0.0f); // point rouge sinon

		Vector3 tmp(ray->getDirection() * t);

		// Point d'arrivée du lancé de rayon
		glVertex3f((MAP_SIZE * (ray->getOrigin() + tmp).x / mesh->getHeight()) - MAP_SIZE / 2,
			(ray->getOrigin() + tmp).z / 255,
			(MAP_SIZE * (ray->getOrigin() + tmp).y / mesh->getWidth()) - MAP_SIZE / 2);

		glEnd();
	}

    // FPS count
    ++frame_count;
    QTime new_time = QTime::currentTime();
    // if 1 sec (1000 msec) ellapsed
    if (last_time.msecsTo(new_time) >= 1000)
    {
        last_count = frame_count;
        frame_count = 0;
        last_time = QTime::currentTime();
    }

    // Debug display
    qglColor(Qt::white);
    renderText(10, 15, "Press spacebar to change transfert mode");
    renderText(10, 30, "Press T to draw on/off texture");
    renderText(10, 45, "Press F to fill on/off");
    renderText(10, 60, "Press Up/Down to increase/decrease delay");
    renderText(10, height()-55, "Delay : " + QString::number(delay));
    renderText(10, height()-40, "Size points : " + QString::number(m_indices.size()));
    renderText(10, height()-25, QString("%1 : %2").arg(MODE_NAME[mode_rendu]).arg(last_count));
    renderText(10, height()-10, QString("Rotation x:%1 y:%2 z:%3").arg(x_rot/16).arg(y_rot/16).arg(z_rot/16));
}

void HeightmapWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
}

void HeightmapWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space)
        mode_rendu  = static_cast<MODE_RENDU>((mode_rendu + 1) % 4);

    if (event->key() == Qt::Key_T)
        mode_texture = !mode_texture;

    if (event->key() == Qt::Key_F)
        mode_fill = !mode_fill;

    if (event->key() == Qt::Key_Up)
    {
        if (delay < 50) ++delay;
        timer.start(delay);
    }

    if (event->key() == Qt::Key_Down)
    {
        if (delay > 0) --delay;
        timer.start(delay);
    }
}

void HeightmapWidget::mousePressEvent(QMouseEvent *event)
{
    last_pos = event->pos();
}

void HeightmapWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - last_pos.x();
    int dy = event->y() - last_pos.y();

    if (event->buttons() & Qt::RightButton)
    {
        rotateBy(dy*8, 0, 0);
        rotateBy(0, dx*8, 0);
    }
    last_pos = event->pos();
}

void HeightmapWidget::wheelEvent(QWheelEvent *event)
{
    distance *= 1.0 + (1.0 * event->delta() / 1200.0);
}

void HeightmapWidget::rotateBy(int x, int y, int z)
{
    x_rot += x;
    y_rot += y;
    z_rot += z;
}

void HeightmapWidget::AddRay(Ray r)
{
	listRays.push_back(r);
}
