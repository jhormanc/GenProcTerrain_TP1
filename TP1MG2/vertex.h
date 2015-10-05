#ifndef VERTEX_H
#define VERTEX_H

#include <QVector3D>
#include <QVector2D>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <math.h>

class Vertex {

public:
	Vertex ( ) : m_Pos ( QVector3D ( 0.0, 0.0, 0.0 ) ), m_Tex ( QVector2D ( 0.0, 0.0 ) ) { }
	Vertex ( QVector3D pos ) : m_Pos ( pos ), m_Tex ( QVector2D ( 0.0, 0.0 ) ) { }
	Vertex ( QVector3D pos, QVector2D tex ) : m_Pos ( pos ), m_Tex ( tex ) { }

	inline QVector3D getPos ( ) { return m_Pos; }
	inline QVector2D getTex ( ) { return m_Tex; }
	inline qreal x ( ) { return m_Pos.x ( ); }
	inline qreal y ( ) { return m_Pos.y ( ); }
	inline qreal z ( ) { return m_Pos.z ( ); }
	inline qreal u ( ) { return m_Tex.x ( ); }
	inline qreal v ( ) { return m_Tex.y ( ); }
	inline void setPos ( QVector3D pos ) { m_Pos = pos; }
	inline void setTex ( QVector2D tex ) { m_Tex = tex; }
	inline void set ( QVector3D pos, QVector2D tex ) { m_Pos = pos; m_Tex = tex; }

protected:
	QVector3D m_Pos;
	QVector2D m_Tex;
};

#endif // VERTEX_H
