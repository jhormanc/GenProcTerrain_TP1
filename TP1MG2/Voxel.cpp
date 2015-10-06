#include "Voxel.h"


Voxel::Voxel(Node& node, int n_) : n(n_)
{
	v = QVector<int>(n * n * n);

	for(int i = 0; i < n - 1; i++)
	{
		for(int j = 0; j < n - 1; j++)
		{
			for(int k = 0; k < n - 1; k++)
			{
				if(node.inside(Vector3(i, j, k)))
					v[i * n * n + j * n + k] = 1;
				else
					v[i * n * n + j * n + k] = 0;
			}
		}
	}
}


Voxel::~Voxel(void)
{
}

Mesh* Voxel::getMesh() const
{
	Mesh mesh ( "voxels" );
	QVector<Vertex> vertices = QVector<Vertex> ( );
	QVector<qreal> faces = QVector<qreal> ( );
	QVector<QVector2D> tex = QVector<QVector2D> ( );


	tex << QVector2D ( 0, 0 )
		<< QVector2D ( 1, 0 )
		<< QVector2D ( 0, 1 );

	/*for ( int jj = 0; jj <= n; ++jj ) {
		for ( int ii = 0; ii <= n; ++ii ) {
			vertices << QVector3D ( ii, jj, getPoint( ii, jj ).z );
		}
	}*/

	for ( int jj = 0; jj <= n; ++jj ) {
		for ( int ii = 1; ii <= n; ++ii ) {
			faces << ii + jj * ( n + 1 ) << ii + 1 + jj * ( n + 1 ) << ii + n + 1 + jj * ( n + 1 );
			faces << ii + 1 + jj * ( n+ 1 ) << ii + n + 2 + jj * (n + 1 ) << ii + n + 1 + jj * (n + 1 );
		}
	}

	mesh.setVertices ( vertices );
	mesh.setFaces ( faces );
	mesh.setTex ( tex );

	return &mesh;
}
