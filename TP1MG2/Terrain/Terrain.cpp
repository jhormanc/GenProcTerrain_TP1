#include "Terrain.h"
#include "Noise.h"

// Fonction pour trouver la hauteur max et min
void Terrain::MaxMin(double x)
{
	high = std::max(high,x);
	low = std::min(low, x);
}

// Renvoie vrai si le point p est en dehors du terrain, faux sinon.
bool Terrain::inside(const Vector3 &  p) const
{
	return (p.z > getPoint(p.x, p.y).z);
}

// calcul la distance en hauteur entre le point p et le terrain
double Terrain::distance(const Vector3 &  p) const
{
	Vector3 pointTerrain = getPoint(p.x, p.y);
	if (pointTerrain != Constante::noIntersectVec) // Car distance en z en attendant box.
		return (p.z - pointTerrain.z) * k; // 0.5 = pente maximale
	return Constante::noIntersect;
}

// Calcul la pente maximale du terrain
void Terrain::calcK()
{
	k = std::abs(getPoint(0., 0.).z - getPoint(0., 1.).z);
	for (uint j = 0; j < terrain_height - 1; j++)
	{
		for (uint i = 0; i < terrain_width - 1; i++)
		{
			k = std::max(
				std::max(
				std::max(k, std::abs(getPoint(i, j).z - getPoint(i, j + 1).z)),
				std::abs(getPoint(i, j).z - getPoint(i + 1, j).z)),

				std::abs(getPoint(i, j).z - getPoint(i + 1, j + 1).z));
		}
	}
	k /= high;
}


Mesh* Terrain::GetMesh()
{
	Mesh terrain ( "terrain" );
	QVector<Vertex> vertices = QVector<Vertex> ( );
	QVector<qreal> faces = QVector<qreal> ( );
	QVector<QVector2D> tex = QVector<QVector2D> ( );


	tex << QVector2D ( 0, 0 )
		<< QVector2D ( 1, 0 )
		<< QVector2D ( 0, 1 );

	for ( int jj = 0; jj <= terrain_height; ++jj ) {
		for ( int ii = 0; ii <= terrain_width; ++ii ) {
			vertices << QVector3D ( ii, jj, getPoint( ii, jj ).z );
		}
	}

	for ( int jj = 0; jj <= terrain_height; ++jj ) {
		for ( int ii = 1; ii <= terrain_width; ++ii ) {
			faces << ii + jj * ( terrain_width + 1 ) << ii + 1 + jj * ( terrain_width + 1 ) << ii + terrain_width + 1 + jj * ( terrain_width + 1 );
			faces << ii + 1 + jj * ( terrain_width+ 1 ) << ii + terrain_width + 2 + jj * (terrain_width + 1 ) << ii + terrain_width + 1 + jj * (terrain_width + 1 );
		}
	}

	terrain.setVertices ( vertices );
	terrain.setFaces ( faces );
	terrain.setTex ( tex );

	return &terrain;

	/*const float MAP_SIZE = 5.0;

	Mesh mesh();

	QVector3D vertice;
    QVector2D texture;

    for(uint z = 0; z < terrain_width; ++z)
    {
        for(uint x = 0; x < terrain_height; ++x)
        {
			float y = getPoint(x, z).z;

			vertice.setX((MAP_SIZE * x / terrain_height) - MAP_SIZE / 2);
			vertice.setY(y / 255);
			vertice.setZ((MAP_SIZE * z / terrain_width) - MAP_SIZE / 2);
			mesh->pushVertice(vertice);

            texture.setX(static_cast<float>(x) / static_cast<float>(terrain_height));
            texture.setY(1.0 - static_cast<float>(z) / static_cast<float>(terrain_width));
			mesh->pushTexture(texture);
        }
    }

   mesh->generateArray();

   return mesh;*/
}

// Renvoi la normal du terrain au point p
Vector3 Terrain::normal(const Vector3 &p) const
{
	//Technique Derivé
	//Vector3 eps(1.,0.0,0.0);
	//Vector3 tmp = p;
	//Vector3 tmp2 = eps;
	//double x = getPoint(tmp.x-tmp2.x,tmp.z-tmp2.y).z-getPoint(tmp.x+tmp2.x,tmp.z+tmp2.y).z;
	//double y = 2*eps.x;
	//double z = getPoint(tmp.x-tmp2.y,tmp.z-tmp2.x).z-getPoint(tmp.x+tmp2.y,tmp.z+tmp2.x).z;

	//return Vector3::normalize(Vector3(x,y,z));
	
	Vector3 a = getPoint(p.x, p.y);

	if (p.x == 0 && p.y == 0){
		//Need 2 normals
		Vector3 b = getPoint(p.x + 1.,p.y);
		Vector3 c = getPoint(p.x,p.y + 1.);
		//normal point b
		Vector3 nb = ((c - b) ^ (a - b));
		//normal point c
		Vector3 nc = ((b - c) ^ (a - c));
		return Vector3::normalize((nb + nc) / 2.0);
	}

	if (p.x == terrain_width - 1. && p.y == 0){
		//Need 3 normals
		Vector3 b = getPoint(p.x - 1.,p.y);
		Vector3 c = getPoint(p.x,p.y + 1.);
		Vector3 d = getPoint(p.x - 1.,p.y + 1.);

		//normal point b
		Vector3 nb1 = ((a - b) ^ (d - b));
		Vector3 nb2 = (a - b) ^ (c - b);
		Vector3 nb = nb1 + nb2;
		//normal point c
		Vector3 nc = ((a - c) ^ (d - c));
		//normal point d
		Vector3 nd = ((a - d) ^ (b - d));
		return Vector3::normalize((nb + nc + nd) / 3.0);
	}

	if (p.x == terrain_width - 1. && p.y == terrain_height - 1.){
		//Need 3 normals
		Vector3 b = getPoint(p.x + 1.,p.y);
		Vector3 c = getPoint(p.x,p.y - 1.);
		Vector3 d = getPoint(p.x + 1.,p.y - 1.);
		//normal point b
		Vector3 nb1 = ((a - b) ^ (d - b));
		Vector3 nb2 = (a - b) ^ (c - b);
		Vector3 nb = nb1 + nb2;
		//normal point c
		Vector3 nc = ((a - c) ^ (d - c));
		//normal point d
		Vector3 nd = ((a - d) ^ (b - d));
		return Vector3::normalize((nb + nc + nd) / 3.0);
	}

	if (p.x == 0 && p.y == terrain_height - 1.){
		//Need 2 normals
		Vector3 b = getPoint(p.x - 1.,p.y);
		Vector3 c = getPoint(p.x,p.y - 1.);
		//normal point b
		Vector3 nb = ((c - b) ^ (a - b));
		//normal point c
		Vector3 nc = ((a - c) ^ (b - c));
		return Vector3::normalize((nb + nc) / 2.0);
	}

	//cotés:
	//Coté gauche
	if (p.x == 0 && p.y != 0 && p.y != terrain_height - 1.){
		//Need 4 normals
		//point du haut
		Vector3 b = getPoint(p.x,p.y - 1.);
		//point diagonal
		Vector3 c = getPoint(p.x + 1.,p.y - 1.);
		//point gauche
		Vector3 d = getPoint(p.x + 1.,p.y);
		//point bas
		Vector3 e = getPoint(p.x,p.y + 1.);

		Vector3 nb = ((a - b) ^ (c - b));
		Vector3 nc = ((b - c) ^ (a - c));
		Vector3 nd1 = (a - d) ^ (c - d);
		Vector3 nd2 = ((a - d) ^ (e - d));
		Vector3 nd = nd1 + nd2;
		Vector3 ne = ((a - e) ^ (d - e));
		return Vector3::normalize((nb + nc + nd + ne) / 4.0);
	}

	//Coté haut
	if (p.y == 0 && p.x != 0 && p.x != terrain_width - 1.){
		//Need 4 normals
		//point du haut
		Vector3 b = getPoint(p.x - 1.,p.y);
		//point diagonal
		Vector3 c = getPoint(p.x - 1.,p.y + 1.);
		//point gauche
		Vector3 d = getPoint(p.x,p.y + 1.);
		//point bas
		Vector3 e = getPoint(p.x + 1.,p.y);

		Vector3 nb = ((a - b) ^ (c - b));
		Vector3 nc = ((b - c) ^ (a - c));
		Vector3 nd1 = (a - d) ^ (c - d);
		Vector3 nd2 = ((a - d) ^ (e - d));
		Vector3 nd = nd1 + nd2;
		Vector3 ne = ((a - e) ^ (d - e));
		return Vector3::normalize((nb + nc + nd + ne) / 4.0);
	}

	//Coté droit
	if (p.x == terrain_width - 1. && p.y != 0 && p.y != terrain_height - 1.){
		//Need 4 normals
		//point du haut
		Vector3 b = getPoint(p.x,p.y - 1.);
		//point diagonal
		Vector3 c = getPoint(p.x - 1.,p.y);
		//point gauche
		Vector3 d = getPoint(p.x - 1.,p.y + 1.);
		//point bas
		Vector3 e = getPoint(p.x,p.y + 1.);

		Vector3 nb = ((a - b) ^ (c - b));
		Vector3 nc = ((b - c) ^ (a - c));
		Vector3 nd1 = ((a - d) ^ (e - d));
		Vector3 nd2 = (a - d) ^ (c - d);
		Vector3 nd = nd1 + nd2;
		Vector3 ne = ((a - e) ^ (d - e));
		return Vector3::normalize((nb + nc + nd + ne) / 4.0);
	}

	//Coté Bas
	if (p.y == terrain_height && p.x != 0 && p.x != terrain_width - 1.){
		//Need 4 normals
		//point du haut
		Vector3 b = getPoint(p.x - 1.,p.y);
		//point diagonal
		Vector3 c = getPoint(p.x,p.y - 1.);
		//point gauche
		Vector3 d = getPoint(p.x + 1.,p.y - 1.);
		//point bas
		Vector3 e = getPoint(p.x + 1.,p.y);

		Vector3 nb = ((a - b) ^ (c - b));
		Vector3 nc = ((b - c) ^ (a - c));
		Vector3 nd1 = ((a - d) ^ (e - d));
		Vector3 nd2 = (a - d) ^ (c - d);
		Vector3 nd = nd1 + nd2;
		Vector3 ne = ((a - e) ^ (d - e));
		return Vector3::normalize((nb + nc + nd + ne) / 4.0);
	}

	//Le reste des points :

	//Need 6 normals
	Vector3 b = getPoint(p.x - 1.,p.y);
	Vector3 c = getPoint(p.x,p.y - 1.);
	Vector3 d = getPoint(p.x + 1.,p.y - 1.);
	Vector3 e = getPoint(p.x + 1.,p.y - 1.);
	Vector3 f = getPoint(p.x,p.y + 1.);
	Vector3 g = getPoint(p.x - 1.,p.y + 1.);

	Vector3 nb1 = (a - b) ^ (g - b);
	Vector3 nb2 = ((a - b) ^ (c - b));
	Vector3 nb = nb1 + nb2;

	Vector3 nc1 = ((b - c) ^ (a - c));
	Vector3 nc2 = (b - c) ^ (d - c);
	Vector3 nc = nc1 + nc2;

	Vector3 nd1 = ((a - d) ^ (e - d));
	Vector3 nd2 = (a - d) ^ (c - d);
	Vector3 nd = nd1 + nd2;

	Vector3 ne1 = ((a - e) ^ (f - e));
	Vector3 ne2 = (a - e) ^ (d - e);
	Vector3 ne = ne1 + ne2;

	Vector3 nf1 = ((a - f) ^ (e - f));
	Vector3 nf2 = (a - f) ^ (g - f);
	Vector3 nf = nf1 + nf2;

	Vector3 ng1 = ((a - g) ^ (f - g));
	Vector3 ng2 = (a - g) ^ (b - g);
	Vector3 ng = ng1 + ng2;

	return Vector3::normalize((nb + nc + nd + ne + nf + ng) / 6.0);
}

Vector3 Terrain::getColor(const Vector3 & p) const
{
	double z = getPoint(p.x, p.y).z;
	Vector3 color;

	Vector3 white = Vector3(255, 255, 255);
	Vector3 brown = Vector3(51, 25, 0);
	Vector3 green = Vector3(0, 102, 0);
	Vector3 blue = Vector3(0, 128, 255);
	Vector3 grey = Vector3(64, 64, 64);

	double max = high - low;

	// Noise
	//if (z <= low + (max * (5. / 100.)))
	//	color = green;
	//else if (z >= low + (max * (90. / 100.)))
	//	color = white;
	//else if (z >= low + (max * (50. / 100.)))
	//	color = grey;
	//else if (z >= low + (max * (5. / 100.)) && (z <= low + (max * (50. / 100.))))
	//	color = brown;
	//else
	//	color = blue;

	// World
	if (z <= low + (max * (0.1 / 100.)))
		color = blue;
	else if (z >= low + (max * (80. / 100.)))
		color = white;
	else if (z >= low + (max * (40. / 100.)))
		color = grey;
	else if (z >= low + (max * (20. / 100.)))
		color = brown;
	else if (z >= low + (max * (0.1 / 100.)))
		color = green;
	else
		color = blue;

	return color;
}