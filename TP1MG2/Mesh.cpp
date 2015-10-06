#include "mesh.h"


Mesh::Mesh ( ) {
	_vertices	= QVector<Vertex> ( );
	_faces		= QVector<double> ( );
	_normals	= QVector<QVector3D> ( );
	_color		= QString ( "white" );
	_name		= "object";
}

Mesh::Mesh ( QString name ) {
	_vertices	= QVector<Vertex> ( );
	_faces		= QVector<double> ( );
	_normals	= QVector<QVector3D> ( );
	_color		= QString ( "white" );
	_name		= name;
}

Mesh::Mesh ( QString name, QString color ) {
	_vertices	= QVector<Vertex> ( );
	_faces		= QVector<double> ( );
	_normals	= QVector<QVector3D> ( );
	_color		= name;
	_name		= color;
}


void Mesh::drawCube ( ) {
	drawCube ( QVector3D ( 0, 0, 0 ), 1 );
}

void Mesh::drawCube ( const double & size ) {
	drawCube ( QVector3D ( 0, 0, 0 ), size );
}

void Mesh::drawCube ( const QVector3D & origin, const double & size ) {
	Mesh mesh ( _color );
	QVector<Vertex> vertices;
	QVector<double> faces;

	QVector3D v1 ( origin.x ( ), origin.y ( ), origin.z ( ) );
	QVector3D v2 ( origin.x ( ) + size, origin.y ( ), origin.z ( ) );
	QVector3D v3 ( origin.x ( ), origin.y ( ) + size, origin.z ( ) );
	QVector3D v4 ( origin.x ( ) + size, origin.y ( ) + size, origin.z ( ) );
	QVector3D v5 ( origin.x ( ), origin.y ( ), origin.z ( ) + size );
	QVector3D v6 ( origin.x ( ) + size, origin.y ( ), origin.z ( ) + size );
	QVector3D v7 ( origin.x ( ), origin.y ( ) + size, origin.z ( ) + size );
	QVector3D v8 ( origin.x ( ) + size, origin.y ( ) + size, origin.z ( ) + size );

	vertices << v1 << v2 << v3 << v4 << v5 << v6 << v7 << v8;

	faces << 1 << 2 << 5
		<< 6 << 5 << 2
		<< 2 << 4 << 6
		<< 8 << 6 << 4
		<< 3 << 8 << 4
		<< 3 << 7 << 8
		<< 3 << 5 << 7
		<< 1 << 5 << 3
		<< 6 << 7 << 5
		<< 6 << 8 << 7
		<< 1 << 4 << 2
		<< 3 << 4 << 1;

	mesh.setFaces ( faces );
	mesh.setVertices ( vertices );

	this->append ( mesh );
}

void Mesh::drawParalellepiped ( ) {
	drawParalellepiped ( QVector3D ( 0, 0, 0 ), 1, 2, 3 );
}

void Mesh::drawParalellepiped ( const double & width, const double & height, const double & depth ) {
	drawParalellepiped ( QVector3D ( 0, 0, 0 ), width, height, depth );
}

void Mesh::drawParalellepiped ( const QVector3D & origin, const double & width, const double & height, const double & depth ) {
	Mesh mesh ( _color );
	QVector<Vertex> vertices;
	QVector<double> faces;

	QVector3D v1 ( origin.x ( ), origin.y ( ), origin.z ( ) );
	QVector3D v2 ( origin.x ( ) + width, origin.y ( ), origin.z ( ) );
	QVector3D v3 ( origin.x ( ), origin.y ( ) + depth, origin.z ( ) );
	QVector3D v4 ( origin.x ( ) + width, origin.y ( ) + depth, origin.z ( ) );
	QVector3D v5 ( origin.x ( ), origin.y ( ), origin.z ( ) + height );
	QVector3D v6 ( origin.x ( ) + width, origin.y ( ), origin.z ( ) + height );
	QVector3D v7 ( origin.x ( ), origin.y ( ) + depth, origin.z ( ) + height );
	QVector3D v8 ( origin.x ( ) + width, origin.y ( ) + depth, origin.z ( ) + height );

	vertices << v1 << v2 << v3 << v4 << v5 << v6 << v7 << v8;

	faces << 1 << 2 << 5
		<< 6 << 5 << 2
		<< 2 << 4 << 6
		<< 8 << 6 << 4
		<< 3 << 8 << 4
		<< 3 << 7 << 8
		<< 3 << 5 << 7
		<< 1 << 5 << 3
		<< 6 << 7 << 5
		<< 6 << 8 << 7
		<< 1 << 4 << 2
		<< 3 << 4 << 1;

	mesh.setFaces ( faces );
	mesh.setVertices ( vertices );
	
	this->append ( mesh );
}

void Mesh::drawCircle ( ) {
	this->drawCircle ( QVector3D ( 0.0, 0.0, 0.0 ), 1, 50 );
}

void Mesh::drawCircle ( const double & radius ) {
	this->drawCircle ( QVector3D ( 0.0, 0.0, 0.0 ), radius, 50 );
}

void Mesh::drawCircle ( const QVector3D & origin, const double & radius ) {
	this->drawCircle ( origin, radius, 50 );
}

void Mesh::drawCircle ( const QVector3D & origin, const double & radius, const int & precision ) {
	_vertices.push_back ( origin );

	const qint8 N = precision;
	double a;
	for ( int ii = 0; ii < N; ++ii ) {
		a = 2.0 * ii * M_PI / N;

		_vertices << QVector3D ( cos ( a ) + origin.x ( ) + radius, sin ( a ) + origin.y ( ) + radius, origin.z ( ) );
		_faces << 1 << ii + 2; ii == N - 1 ? _faces << 2 : _faces << ii + 3;
	}
}

void Mesh::drawCylinder ( ) {
	this->drawCylinder ( QVector3D ( 0.0, 0.0, 0.0 ), 1, 2, 50 );
}

void Mesh::drawCylinder ( const double & radius, const double & length ) {
	this->drawCylinder ( QVector3D ( 0.0, 0.0, 0.0 ), radius, length, 50 );
}

void Mesh::drawCylinder ( const QVector3D & origin, const double & radius, const double & length ) {
	this->drawCylinder ( origin, radius, length, 50 );
}

void Mesh::drawCylinder ( const QVector3D & origin, const double & radius, const double & length, const int & precision ) {

	_tex << QVector2D ( 0, 0 )
		<< QVector2D ( 1, 0 )
		<< QVector2D ( 0, 1 );

	_vertices << QVector3D ( origin.x ( ), origin.y ( ), origin.z ( ) )
		<< QVector3D ( origin.x ( ), origin.y ( ), origin.z ( ) + length );

	const int N = precision;
	double a;
	for ( int ii = 0; ii < N; ++ii ) {
		a = 2.0 * ii * M_PI / N;
		if ( ii / N >= 0.2 && ii / N <= 0.4 ) {
			_vertices << QVector3D ( cos ( a ) * radius + origin.x ( ), sin ( a ) * radius + origin.y ( ), origin.z ( ) )
				<< QVector3D ( cos ( a ) * radius + origin.x ( ), sin ( a ) * radius + origin.y ( ), origin.z ( ) + length );
		}
		else {
			_vertices << QVector3D ( cos ( a ) * radius + origin.x ( ), sin ( a ) * radius + origin.y ( ), origin.z ( ) )
				<< QVector3D ( cos ( a ) * radius + origin.x ( ), sin ( a ) * radius + origin.y ( ), origin.z ( ) + length );
		}

		if ( ii % 2 == 0 ) {
			// faces des cercles
			_faces << 1 << ii + 5 << ii + 3
				<< 2 << ii + 4 << ii + 6

				// faces du cylindre
				<< ii + 5 << ii + 4 << ii + 3;
			ii == N - 2 ? _faces << 3 : _faces << ii + N + 5; _faces << ii + N + 4 << ii + N + 3;
		}
		else {
			// faces des cercles
			_faces << 1; ii == N - 1 ? _faces << 3 : _faces << ii + N + 4; _faces << ii + N + 2;
			_faces << 2 << ii + N + 3; ii == N - 1 ? _faces << 4 : _faces << ii + N + 5;

			// faces du cylindre
			_faces << ii + 3 << ii + 4 << ii + 5;
			_faces << ii + N + 3;  ii == N - 1 ? _faces << 3 : _faces << ii + N + 4;  ii == N - 1 ? _faces << 4 : _faces << ii + N + 5;
		}
	}
}

void Mesh::drawCone ( ) {
	drawCone ( QVector3D ( 0, 0, 0 ), 1, 2, 40 );
}

void Mesh::drawCone ( const double & radius, const double & length ) {
	drawCone ( QVector3D ( 0, 0, 0 ), radius, length, 40 );
}

void Mesh::drawCone ( const QVector3D & origin, const double & radius, const double & length ) {
	drawCone ( origin, radius, length, 50 );
}

void Mesh::drawCone ( const QVector3D & origin, const double & radius, const double & length, const int & precision ) {
	Mesh mesh ( _color );
	QVector<Vertex> vertices;
	QVector<double> faces;

	_tex << QVector2D ( 0, 0 )
		<< QVector2D ( 1, 0 )
		<< QVector2D ( 0, 1 );

	vertices << origin
		<< QVector3D ( origin.x ( ), origin.y ( ), origin.z ( ) + length );
	
	const int N = precision;
	double a;
	for ( int ii = 0; ii < N; ++ii ) {
		a = 2.0 * ii * M_PI / N;
		vertices << QVector3D ( cos ( a ) * radius + origin.x ( ), sin ( a ) * radius + origin.y ( ), origin.z ( ) );
		ii == N - 1 ? faces << 3 : faces << ii + 4; faces << ii + 3 << 1;
		faces << 2 << ii + 3;  ii == N - 1 ? faces << 3 : faces << ii + 4;
	}

	mesh.setFaces ( faces );
	mesh.setVertices ( vertices );

	this->append ( mesh );
}

void Mesh::drawSphere ( const QVector3D & origin, const double & radius ) {

	int circlePointNb = 50;
	int circleNb = circlePointNb / 2;

	double Beta, Alpha;

	for ( int i = 0; i <= circleNb; ++i ) {
		Alpha = -0.5 * M_PI + ( double ( i ) * M_PI / circleNb );
		for ( int j = 0; j < circlePointNb; ++j ) {
			Beta = double ( j ) * 2 * M_PI / circlePointNb;
			_vertices.push_back ( origin + radius * QVector3D ( cos ( Alpha ) * cos ( Beta ), sin ( Alpha ), cos ( Alpha ) * sin ( Beta ) ) );
			_normals.push_back ( QVector3D ( cos ( Alpha ) * cos ( Beta ), sin ( Alpha ), cos ( Alpha ) * sin ( Beta ) ) );
		}
	}

	for ( int i = 0; i < circleNb; ++i ) {
		for ( int j = 0; j < circlePointNb; ++j ) {
			_faces.push_back ( ( i * circlePointNb ) + j );
			_faces.push_back ( ( i * circlePointNb ) + j );
			_faces.push_back ( ( ( i + 1 ) * circlePointNb ) + j );
			_faces.push_back ( ( ( i + 1 ) * circlePointNb ) + j );
			_faces.push_back ( ( ( i + 1 ) * circlePointNb ) + ( j + 1 ) % circlePointNb );
			_faces.push_back ( ( ( i + 1 ) * circlePointNb ) + ( j + 1 ) % circlePointNb );

			_faces.push_back ( ( i * circlePointNb ) + j );
			_faces.push_back ( ( i * circlePointNb ) + j );
			_faces.push_back ( ( ( i + 1 ) * circlePointNb ) + ( j + 1 ) % circlePointNb );
			_faces.push_back ( ( ( i + 1 ) * circlePointNb ) + ( j + 1 ) % circlePointNb );
			_faces.push_back ( ( i * circlePointNb ) + ( j + 1 ) % circlePointNb );
			_faces.push_back ( ( i * circlePointNb ) + ( j + 1 ) % circlePointNb );
		}
	}
}

void Mesh::translate ( const QVector3D & vertices ) {
	for ( QVector<Vertex>::iterator it = this->_vertices.begin ( ); it != this->_vertices.end ( ); ++it ) {
		( *it ).setPos ( ( *it ).getPos ( ) + vertices );
	}
}

void Mesh::append ( Mesh & mesh ) {
	QVector<Vertex>::const_iterator it_verm_Tex;
	QVector<double>::const_iterator	it_int;

	int nb_vertices = _vertices.count ( );

	for ( it_verm_Tex = mesh._vertices.begin ( ); it_verm_Tex != mesh._vertices.end ( ); ++it_verm_Tex ) {
		_vertices << *it_verm_Tex;
	}

	for ( it_int = mesh._faces.begin ( ); it_int != mesh._faces.end ( ); ++it_int ) {
		_faces << ( *it_int + nb_vertices );
	}
}

void Mesh::reset ( ) {
	_vertices	= QVector<Vertex> ( );
	_faces		= QVector<double> ( );
	_normals	= QVector<QVector3D> ( );
	_tex		= QVector<QVector2D> ( );
}

void Mesh::save ( const QString & name, const int & nbVertices ) {
	QString filem_NameObj = name;
	filem_NameObj.append ( ".obj" );
	QFile fileObj ( filem_NameObj );
	QTextStream mesh ( &fileObj );

	if ( fileObj.open ( QIODevice::ReadWrite | QIODevice::Append ) ) {
		// VERTEX
		mesh << endl << "#" << _name << endl << endl;
		mesh << "o " << _name << endl << endl;
		for ( QVector<Vertex>::iterator it = this->_vertices.begin ( ); it != this->_vertices.end ( ); ++it ) {
			mesh << fixed << "v " << it->x ( ) << " " << it->y ( ) << " " << it->z ( ) << endl;
		}
		mesh << endl;

		// TEXTURES
		for ( QVector<QVector2D>::iterator it = this->_tex.begin ( ); it != this->_tex.end ( ); ++it ) {
			mesh << fixed << "vt " << it->x ( ) << " " << it->y ( ) << endl;
		}

		// FACES
		int cpt = 1;
		mesh << "usemtl " << _color << endl;
		for ( int ii = 0; ii < _faces.size ( ); ++ii ) {
			if ( ii % 3 == 0 ) mesh << "f ";

			mesh << ( int ) _faces[ii] + nbVertices << "/" << cpt++ << " ";
			if ( ( ii + 1 ) % 3 == 0 ) {
				cpt = 1;
				mesh << endl;
			}
		}
	}
	else {
		std::cerr << "Error opening file" << endl;
	}
	fileObj.close ( );
}

void Mesh::load ( const QString & p_file ) {
	this->reset ( );

	QFile file ( p_file );
	QVector3D vect;
	QString word, c1, c2, c3;

	if ( file.open ( QIODevice::ReadOnly | QIODevice::Text ) ) {
		QTextStream in ( &file );

		while ( !in.atEnd ( ) ) {
			in >> word;
			if ( word == "v" ) {
				in >> c1 >> c2 >> c3;
				_vertices << QVector3D ( c1.toFloat ( ), c2.toFloat ( ), c3.toFloat ( ) );
			}
			else if ( word == "f" ) {
				in >> c1 >> c2 >> c3;
				_faces << c1.toInt ( ) << c2.toInt ( ) << c3.toInt ( );
			}
		}
	}
	else {
		std::cerr << "Error opening file" << endl;
	}
}
