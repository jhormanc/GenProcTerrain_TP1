#include "Terrain.h"
#include "Noise.h"

// Fonction pour trouver la hauteur max et min
void Terrain::MaxMin(double x)
{
	high = std::max(high,x);
	low = std::min(low, x);
}

// Renvoie vrai si le point p est en dehors du terrain, faux sinon.
bool Terrain::inOut(Vector3 p) const
{
	return (p.z > getPoint(p.x, p.y).z);
}

// Renvoie True si le Ray r touche le terrain
bool Terrain::intersection(Ray r, double &t) const
{
	t = 0.;
	Vector3 res;
	for (int i = 0; i < 256; i++)
	{
		res = r.getOrigin() + (r.getDirection() * t);
		Vector3 tmp = getPoint(res.x, res.y);
		if (tmp != Constante::noIntersectVec)
		{
			double h = res.z - tmp.z;
			if (h < (0.001*t)) 
				return true;
			t += k*h;
		}
		else
			t += 10.;
		
	}
	t = Constante::noIntersect;
	return false;
}

// Calcul la pente maximale du terrain
void Terrain::calcK()
{
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


// Renvoi la normal du terrain au point p
Vector3 Terrain::normal(Vector3 p)
{
	// Technique derivee

	//double eps = 0.5;
	//double x = (getPoint(p.x + eps, p.y).z - getPoint(p.x - eps, p.y).z) / (2 * eps);
	//double y = (getPoint(p.x, p.y + eps).z - getPoint(p.x, p.y - eps).z) / (2 * eps);
	//double z = 1.;
	//return Vector3::normalize(Vector3(-x, -y, z));

	//Technique triangle

	Vector3 a = getPoint(p.x, p.y);

	if (p.x == 0 && p.y == 0){
		//Need 2 normals
		Vector3 b = getPoint(p.x + 1., p.y);
		Vector3 c = getPoint(p.x, p.y + 1.);
		return Vector3::normalize((((c - b) ^ (a - b)) + ((b - c) ^ (a - c))) / 2.0); // (nb + nc) / 2
	}

	if (p.x == terrain_width - 1. && p.y == 0){
		//Need 3 normals
		Vector3 b = getPoint(p.x - 1., p.y);
		Vector3 c = getPoint(p.x, p.y + 1.);
		Vector3 d = getPoint(p.x - 1., p.y + 1.);

		//normal point b
		Vector3 nb = ((a - b) ^ (d - b)) + ((a - b) ^ (c - b));

		return Vector3::normalize((nb + ((a - c) ^ (d - c)) + ((a - d) ^ (b - d))) / 3.0); // (nb + nc + nd ) / 3
	}

	if (p.x == terrain_width - 1. && p.y == terrain_height - 1.){
		//Need 3 normals
		Vector3 b = getPoint(p.x + 1., p.y);
		Vector3 c = getPoint(p.x, p.y - 1.);
		Vector3 d = getPoint(p.x + 1., p.y - 1.);

		//normal point b
		Vector3 nb = ((a - b) ^ (d - b)) + ((a - b) ^ (c - b));

		return Vector3::normalize((nb + ((a - c) ^ (d - c)) + ((a - d) ^ (b - d))) / 3.0); // (nb + nc + nd ) / 3
	}

	if (p.x == 0 && p.y == terrain_height - 1.){
		//Need 2 normals
		Vector3 b = getPoint(p.x - 1., p.y);
		Vector3 c = getPoint(p.x, p.y - 1.);

		return Vector3::normalize((((c - b) ^ (a - b)) + ((a - c) ^ (b - c))) / 2.0); //(nb + nc )/2
	}

	//cotés:
	//Coté gauche
	if (p.x == 0 && p.y != 0 && p.y != terrain_height - 1.){
		//Need 4 normals
		//point du haut
		Vector3 b = getPoint(p.x, p.y - 1.);
		//point diagonal
		Vector3 c = getPoint(p.x + 1., p.y - 1.);
		//point gauche
		Vector3 d = getPoint(p.x + 1., p.y);
		//point bas
		Vector3 e = getPoint(p.x, p.y + 1.);

		Vector3 nb = ((a - b) ^ (c - b));
		Vector3 nc = ((b - c) ^ (a - c));
		Vector3 nd = ((a - d) ^ (c - d)) + ((a - d) ^ (e - d));
		Vector3 ne = ((a - e) ^ (d - e));
		return Vector3::normalize((nb + nc + nd + ne) / 4.0);
	}

	//Coté haut
	if (p.y == 0 && p.x != 0 && p.x != terrain_width - 1.){
		//Need 4 normals
		//point du haut
		Vector3 b = getPoint(p.x - 1., p.y);
		//point diagonal
		Vector3 c = getPoint(p.x - 1., p.y + 1.);
		//point gauche
		Vector3 d = getPoint(p.x, p.y + 1.);
		//point bas
		Vector3 e = getPoint(p.x + 1., p.y);

		Vector3 nb = ((a - b) ^ (c - b));
		Vector3 nc = ((b - c) ^ (a - c));
		Vector3 nd = ((a - d) ^ (e - d)) + ((a - d) ^ (c - d));
		Vector3 ne = ((a - e) ^ (d - e));
		return Vector3::normalize((nb + nc + nd + ne) / 4.0);
	}

	//Coté droit
	if (p.x == terrain_width - 1. && p.y != 0 && p.y != terrain_height - 1.){
		//Need 4 normals
		//point du haut
		Vector3 b = getPoint(p.x, p.y - 1.);
		//point diagonal
		Vector3 c = getPoint(p.x - 1., p.y);
		//point gauche
		Vector3 d = getPoint(p.x - 1., p.y + 1.);
		//point bas
		Vector3 e = getPoint(p.x, p.y + 1.);

		Vector3 nb = ((a - b) ^ (c - b));
		Vector3 nc = ((b - c) ^ (a - c));
		Vector3 nd = ((a - d) ^ (c - d)) + ((a - d) ^ (e - d));
		Vector3 ne = ((a - e) ^ (d - e));
		return Vector3::normalize((nb + nc + nd + ne) / 4.0);
	}

	//Coté Bas
	if (p.y == terrain_height && p.x != 0 && p.x != terrain_width - 1.){
		//Need 4 normals
		//point du haut
		Vector3 b = getPoint(p.x - 1., p.y);
		//point diagonal
		Vector3 c = getPoint(p.x, p.y - 1.);
		//point gauche
		Vector3 d = getPoint(p.x + 1., p.y - 1.);
		//point bas
		Vector3 e = getPoint(p.x + 1., p.y);

		Vector3 nb = ((a - b) ^ (c - b));
		Vector3 nc = ((b - c) ^ (a - c));
		Vector3 nd = ((a - d) ^ (e - d)) + ((a - d) ^ (c - d));
		Vector3 ne = ((a - e) ^ (d - e));
		return Vector3::normalize((nb + nc + nd + ne) / 4.0);
	}

	//Le reste des points :

	//Need 6 normals
	Vector3 b = getPoint(p.x - 1., p.y);
	Vector3 c = getPoint(p.x, p.y - 1.);
	Vector3 d = getPoint(p.x + 1., p.y - 1.);
	Vector3 e = getPoint(p.x + 1., p.y - 1.);
	Vector3 f = getPoint(p.x, p.y + 1.);
	Vector3 g = getPoint(p.x - 1., p.y + 1.);


	Vector3 nb = ((a - b) ^ (g - b)) + ((a - b) ^ (c - b));
	Vector3 nc = ((b - c) ^ (a - c)) + ((b - c) ^ (d - c));
	Vector3 nd = ((a - d) ^ (e - d)) + ((a - d) ^ (c - d));
	Vector3 ne = ((a - e) ^ (d - e)) + ((a - e) ^ (f - e));
	Vector3 nf = ((a - f) ^ (g - f)) + ((a - f) ^ (e - f));
	Vector3 ng = ((a - g) ^ (b - g)) + ((a - g) ^ (f - g));

	return Vector3::normalize((nb + nc + nd + ne + nf + ng) / 6.0);
}


Mesh* Terrain::GetMesh()
{
	const float MAP_SIZE = 5.0;

	Mesh *mesh = new Mesh(terrain_height, terrain_width);;

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

   return mesh;
}



Vector3 Terrain::getColor(double x, double y)
{
	double z = getPoint(x, y).z;
	Vector3 color;

	Vector3 white = Vector3(255, 255, 255);
	Vector3 brown = Vector3(51, 25, 0);
	Vector3 green = Vector3(0, 102, 0);
	Vector3 blue = Vector3(0, 128, 255);
	Vector3 grey = Vector3(64, 64, 64);

	double max = high - low;

	// Noise
	if (z <= low + (max * (5. / 100.)))
		color = green;
	else if (z >= low + (max * (90. / 100.)))
		color = white;
	else if (z >= low + (max * (50. / 100.)))
		color = grey;
	else if (z >= low + (max * (5. / 100.)) && (z <= low + (max * (50. / 100.))))
		color = brown;
	else
		color = blue;

	// World
	//if (z <= low + (max * (0.1 / 100.)))
	//	color = blue;
	//else if (z >= low + (max * (50. / 100.)))
	//	color = white;
	//else if (z >= low + (max * (30. / 100.)))
	//	color = grey;
	//else if (z >= low + (max * (10. / 100.)))
	//	color = brown;
	//else if (z >= low + (max * (0.1 / 100.)))
	//	color = green;
	//else
	//	color = blue;

	// Heightmap2
	//if (z <= low + (max * (0.1 / 100.)))
	//	color = blue;
	//else if (z >= low + (max * (50. / 100.)))
	//	color = green;
	//else if (z >= low + (max * (30. / 100.)))
	//	color = green;
	//else if (z >= low + (max * (10. / 100.)))
	//	color = brown;
	//else if (z >= low + (max * (0.1 / 100.)))
	//	color = blue;
	//else
	//	color = blue;

	return color;
}