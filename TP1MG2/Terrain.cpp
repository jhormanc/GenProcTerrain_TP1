#include "Terrain.h"

Terrain::Terrain(const Terrain& t){
	pointList = new Vector3 *[t.terrain_width];
	for (int i = 0; i < t.terrain_width; i++)
		pointList[i] = new Vector3[t.terrain_height];
	
	for (int j = 0; j < t.terrain_height; j++)
		for (int i = 0; i < t.terrain_width; i++)
			pointList[i][j] = t.pointList[i][j];

	terrain_height = t.terrain_height;
	terrain_width = t.terrain_width;
	step_x = t.step_x;
	step_y = t.step_y;
}


Terrain::Terrain(QImage heightmap, uint terrain_width_, uint terrain_height_, double step_x_, double step_y_)
{
	pointList = new Vector3 *[terrain_width_];
	for (int i = 0; i < terrain_width_; i++)
		pointList[i] = new Vector3[terrain_height_];

	terrain_height = terrain_height_;
	terrain_width = terrain_width_;
	step_x = step_x_;
	step_y = step_y_;
	double fact = 1.0;
	int height = heightmap.height();
	int width = heightmap.width();
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
		
			QColor it = (heightmap.pixel(i, j));
			double gray = 255 - ((it.red() + it.blue() + it.green()) / 3);
			pointList[i][j] = Vector3(step_x_ * i, step_y_ * j, gray * fact);

		}
	}
}

// Renvoi une valeur aleatoire entre 0 et 1 a partir de x.
double Terrain::hash(double x)
{
	return (1.0 + (sin(sin(x) * rand()))) / 2.0;
}

// Renvoi un terrain genere aléatoirement
Terrain Terrain::CreateRidgeFractal(uint terrain_width_, uint terrain_height_, double step_x_, double step_y_, double max_z)
{
//	Terrain res();
	double facteur = max_z; // On veut que les montagnes dépassent pour pouvoir faire le ridge.
	Vector3 ** pointList = new Vector3 *[terrain_width_];
	for (int i = 0; i < terrain_width_; i++)
		pointList[i] = new Vector3[terrain_height_];

	for (int j = 0; j < terrain_height_; j++)
	{
		for (int i = 0; i < terrain_width_; i++)
		{
			pointList[i][j] = Vector3(step_x_ * i, step_y_ * j, (hash(i + j) + 1) * facteur);
			if (pointList[i][j].z > max_z) 
				pointList[i][j].z = 2 * max_z - pointList[i][j].z;
		}
	}
	return Terrain(pointList, terrain_width_, terrain_height_, step_x_, step_y_);
}



// Renvoi le point x, y, z appartenant a pointList a partir du x, y (recherche matrice + interpolation).
Vector3 Terrain::getPoint(double x, double y) const
{
	int tmpI = (int)(x / step_x);
	int tmpJ = (int)(y / step_y);

	if (!(tmpI < terrain_width && tmpJ < terrain_height))
	{
		return Vector3(x, y, -10000);
	}
	Vector3 a;
	Vector3 b;

	if (tmpI < terrain_width - 1)
		a = Vector3(pointList[tmpI + 1][tmpJ]);
	else
		a = Vector3(x, y, 0);

	if (tmpJ < terrain_height - 1)
		b = Vector3(pointList[tmpI][tmpJ + 1]);
	else
		b = Vector3(x, y, 0);


	double x2 = (x - b.x) / step_x;
	double y2 = (y - a.y) / step_y;
	int z = (1 - x2) * (1 - y2) * pointList[tmpI][tmpJ].z
		+ x2 * (1 - y2) * a.z
		+ (1 - x2) * y2 * b.z;

	if (tmpI < terrain_width - 1 && tmpJ < terrain_height - 1)
		z += x2 * y2 * pointList[tmpI + 1][tmpJ + 1].z;


	return Vector3(x, y, z);
}


// Renvoie vrai si le point p est en dehors du terrain, faux sinon.
bool Terrain::inOut(Vector3 p) const
{
	return (p.z > getPoint(p.x, p.y).z);
}

// Renvoie True si le Ray r touche le terrain
bool Terrain::instersection(Ray r, double &t) const
{
	double zMin = 0;
	double zMax = 0;
	double k = 0;

	// Calcul du point z le plus haut du terrain
	for (int j = 0; j < terrain_height; j++)
		for (int i = 0; i < terrain_width; i++)
				zMax = std::max(zMax, pointList[i][j].z);

	// Calcul de l'écart z maximum entre deux points (== zMax ?)
	for (int j = 0; j < terrain_height - 1; j++)
	{
		for (int i = 0; i < terrain_width - 1; i++)
		{
			k = std::max(
			    	std::max(
			     	  std::max(k, std::abs(pointList[i][j].z - pointList[i][j + 1].z)), 
				      std::abs(pointList[i][j].z - pointList[i + 1][j].z)),					  
			    	std::abs(pointList[i][j].z - pointList[i + 1][j + 1].z));
		}
	}

	t = zMin;
	double epsilon = 1.0;
	double deltaz;
	Vector3 p = r.getOrigin(); // Point de départ du lancé de rayon
	Vector3 tmp, pas;

	while (t < zMax)
	{
		pas = (r.getDirection() * (double)t);
		tmp = r.getOrigin() + pas;
		deltaz = p.z - getPoint(tmp.x, tmp.y).z; 

		if (deltaz < epsilon) 
		{ 
			return true; 
		}

		if (deltaz > k) 
		{ 
			//pas = r.getDirection() * zMax;
			return false;
		}

		t += (deltaz) / (k - r.getDirection().z);
		p = p + pas;
	}
	return false;

}

// Desctructeur. Desalloue pointList.
Terrain::~Terrain()
{
	for (int i = 0; i < terrain_width; ++i)
		delete[] pointList[i];
	delete[] pointList;
}