#ifndef MESH_H
#define MESH_H

#include <vertex.h>
#include <QVector3D>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <math.h>
#include <qmath.h>
#include "vector2.h"

class Mesh {

public:
	Mesh ( );
	Mesh ( QString name );
	Mesh ( QString name, QString color );

	inline QString getName ( ) { return _name; }
	inline void setName ( QString name ) { _name = name; }
	inline QString getColor ( ) { return _color; }
	inline void setColor ( QString color ) { _color = color; }
	inline QVector<Vertex> getVertices ( ) { return _vertices; }
	inline void setVertices ( QVector<Vertex> vertices ) { _vertices = vertices; }
	inline QVector<double> getFaces ( ) { return _faces; }
	inline void setFaces ( QVector<double> faces ) { _faces = faces; }
	inline QVector<QVector2D> getTex ( ) { return _tex; }
	inline void setTex ( QVector<QVector2D> tex ) { _tex = tex; }

	void append ( Mesh & );
	void reset ( );

	void drawCube ( );
	void drawCube ( const double & size );
	void drawCube ( const QVector3D & origin, const double & );
	void drawParalellepiped ( );
	void drawParalellepiped ( const double &, const double &, const double & );
	void drawParalellepiped ( const QVector3D & origin, const double &, const double &, const double & );
	void drawCircle ( );
	void drawCircle ( const double & );
	void drawCircle ( const QVector3D & origin, const double & radius );
	void drawCircle ( const QVector3D & origin, const double & radius, const int & );
	void drawCylinder ( );
	void drawCylinder ( const double &, const double & );
	void drawCylinder ( const QVector3D & origin, const double & radius, const double & length );
	void drawCylinder ( const QVector3D & origin, const double & radius, const double & length, const int & precision );
	void drawCone ( );
	void drawCone ( const double & radius, const double & );
	void drawCone ( const QVector3D & origin, const double & radius, const double & );
	void drawCone ( const QVector3D & origin, const double & radius, const double &, const int & precision );
	void drawSphere ( const QVector3D & origin, const double & radius );

	void translate ( const QVector3D & );

	void save ( const QString & name, const int & nbVertices );
	void load ( const QString & file );

protected:
	QVector<Vertex> _vertices;
	QVector<double> _faces;
	QVector<QVector3D> _normals;
	QVector<QVector2D> _tex;
	QString _name;
	QString _color;
};

#endif // MESH_H
