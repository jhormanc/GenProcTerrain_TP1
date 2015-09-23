#include "Terrain.h"
#include "Noise.h"

Terrain::Terrain(const Terrain& t){
	pointList = new Vector3 *[t.terrain_width];
	for (int i = 0; i < t.terrain_width; i++)
		pointList[i] = new Vector3[t.terrain_height];
	
	for (int j = 0; j < t.terrain_height; j++)
		for (int i = 0; i < t.terrain_width; i++){
			pointList[i][j] = t.pointList[i][j];
			if(i==0 && j==0){
				hight=t.pointList[i][j].z;
				low=t.pointList[i][j].z;
			}
			MaxMin(t.pointList[i][j].z);
		}
	terrain_height = t.terrain_height;
	terrain_width = t.terrain_width;
	step_x = t.step_x;
	step_y = t.step_y;
	calcK();
}


Terrain::Terrain(QImage heightmap, uint terrain_width_, uint terrain_height_, double step_x_, double step_y_)
{
	int height = heightmap.height();
	int width = heightmap.width();
	pointList = new Vector3 *[width];
	for (int i = 0; i < width; i++)
		pointList[i] = new Vector3[height];

	terrain_height = height;
	terrain_width = width;
	step_x = 1. / width;
	step_y = 1. / height;
	double fact = 1.5 / 255.;
	
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
		
			QColor it = (heightmap.pixel(i, j));
			double gray = 255 - ((it.red() + it.blue() + it.green()) / 3);
			pointList[i][j] = Vector3((2 * (i - width * 0.5) / width), (2 * (j - height * 0.5) / height), gray * fact);
			if(i==0 && j==0){
				hight=gray*fact;
				low=gray*fact;
			}
			MaxMin(gray*fact);
		}
	}
	calcK();
}

Terrain::Terrain(QImage heightmap,Vector3 v1,Vector3 v2/*, const double* low_, const double* hight_*/){
	
	
	pointList = new Vector3 *[heightmap.height()];
	for (int i = 0; i < heightmap.width(); i++)
		pointList[i] = new Vector3[heightmap.width()];

	terrain_height = heightmap.height();
	terrain_width = heightmap.width();
	/*step_x = step_x_;
	step_y = step_y_;*/
	double fact = 1.0;
	for (int j = 0; j < heightmap.height(); j++)
	{
		for (int i = 0; i < heightmap.width(); i++)
		{
		
			QColor it = (heightmap.pixel(i, j));
			double gray = 255 - ((it.red() + it.blue() + it.green()) / 3);
			MaxMin(gray);
			pointList[i][j] = Vector3(step_x * i, step_y * j, gray * fact);

		}
	}
	
	//v1 etant le point bas gauche on va lui donner comme z la valeur de "low"
	v1.z=low;
	
	//v2 etant le point haut droite on va lui donner comme z la valeur de "hight"
	v2.z=hight;
	
	//*On passe en parametre les deux vecteur3 definissant les limites du carrée : le coté bas gauche et le coté haut droit*//
	boxlimit = new Box(v1 , v2);
	calcK();
}


//*Fonction pour trouver la hauteur max et min*//
void Terrain::MaxMin(float x){
	if(x>hight)
		hight=x;
		
	if(x<low)
		low=x;
		
}





// Renvoi un terrain genere aléatoirement
Terrain Terrain::CreateRidgeFractal(uint terrain_width_, uint terrain_height_, double step_x_, double step_y_, double max_z)
{
//	Terrain res();
	double facteur = max_z; // On veut que les montagnes dépassent pour pouvoir faire le ridge.
	Vector3 ** pointList = new Vector3 *[terrain_width_];
	for (int i = 0; i < terrain_width_; i++)
		pointList[i] = new Vector3[terrain_height_];

	double z;
	float h,l;

	for (int j = 0; j < terrain_height_; j++)
	{
		for (int i = 0; i < terrain_width_; i++)
		{
			z = Noise::noise(i, j);
			pointList[i][j] = Vector3(step_x_ * i, step_y_ * j, z);
		
		/**Pour recuperer le Low and Hight**/
			if(j==0 && i==0){
				h=pointList[i][j].z;
				l=pointList[i][j].z;
			}
			if(pointList[i][j].z>h)
				h=pointList[i][j].z;

			if(pointList[i][j].z<l)
				l=pointList[i][j].z;
		

		}
	}
	return Terrain(pointList, terrain_width_, terrain_height_, step_x_, step_y_,h,l);
}



// Renvoi le point x, y, z appartenant a pointList a partir du x, y (recherche matrice + interpolation).
Vector3 Terrain::getPoint(double x, double y) const
{
		int tmpI = (int)(( (( x + 1. ) * 0.5) * terrain_width ));
		int tmpJ = (int)(( ((y +1) * 0.5) * terrain_height ));
		//int tmpJ = (int)(((( terrain_height * 2 - y) * 0.5) / step_y));
	if (!(tmpI < terrain_width && tmpJ < terrain_height))
	{
		return noneVec;
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
	double z = (1 - x2) * (1 - y2) * pointList[tmpI][tmpJ].z
		+ x2 * (1 - y2) * a.z
		+ (1 - x2) * y2 * b.z;

	if (tmpI < terrain_width - 1 && tmpJ < terrain_height - 1)
	{
		z += x2 * y2 * pointList[tmpI + 1][tmpJ + 1].z;
	}


	return Vector3(x, y, z);
}


// Renvoie vrai si le point p est en dehors du terrain, faux sinon.
bool Terrain::inOut(Vector3 p) const
{
	return (p.z > getPoint(p.x, p.y).z);
}

// Renvoie True si le Ray r touche le terrain
bool Terrain::intersection(Ray r, double &t) const
{
	double zMin = -1.;
	double zMax = 1.;
	/*
	// Calcul du point z le plus haut du terrain
	for (int j = 0; j < terrain_height; j++)
		for (int i = 0; i < terrain_width; i++)
				zMax = std::max(zMax, pointList[i][j].z);
				*/
	
	/*
	t = 0;

	double epsilon = 0.1;
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
			t = -10.;
			return false;
		}

		t += (deltaz) * 0.5;
		p = tmp;
	}
	t = -10.;
	return false;
	*/
	t = 0.;
	Vector3 res;
	for (int i = 0; i<256; i++)
	{
		res = r.getOrigin() + (r.getDirection() * t);
		Vector3 tmp = getPoint(res.x, res.y);
		if (tmp != noneVec)
		{
			double h = res.z - tmp.z;
			if (h < (0.01*t)) return true;
			t += 0.5*h;
		}
		else
			t += 0.1;
		
	}
	t = -10.;
	return false;
}

// calcul la pente maximale du terrain
void Terrain::calcK()
{
	// Calcul de l'écart z maximum entre deux points
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
}


// renvoi la normal du terrain au point p
Vector3 Terrain::normal(Vector3 p)
{
	int tmpI = (int)((((p.x + 1.) * 0.5) * terrain_width));
	int tmpJ = (int)((((p.y + 1) * 0.5) * terrain_height));
	//int tmpI = (int)(p.x / step_x);
	//int tmpJ = (int)(p.y / step_y);
	Vector3 a = getPoint(p.x, p.y);
	Vector3 b = pointList[tmpI < terrain_width - 1 ? tmpI + 1 : tmpI][tmpJ];
	Vector3 c = pointList[tmpI][tmpI < terrain_height - 1 ? tmpJ + 1 : tmpJ];
	return Vector3::normalize((b - a) ^ (c - a));
}
// Desctructeur. Desalloue pointList.
Terrain::~Terrain()
{
	for (int i = 0; i < terrain_width; ++i)
		delete[] pointList[i];
	delete[] pointList;
}

Mesh* Terrain::GetMesh()
{
	const float MAP_SIZE = 5.0;

	Mesh *mesh = new Mesh(terrain_height, terrain_width);;

	QVector3D vertice;
    QVector2D texture;

    for(int z = 0; z < terrain_width; ++z)
    {
        for(int x = 0; x < terrain_height; ++x)
        {
			float y = getPoint(x * step_x, z * step_y).z;

			vertice.setX((MAP_SIZE * x / terrain_height) - MAP_SIZE / 2); // x
			vertice.setY(y / 255); //(2.0 * qGray(color) / 255);
			vertice.setZ((MAP_SIZE * z / terrain_width) - MAP_SIZE / 2); // y
			mesh->pushVertice(vertice);

            texture.setX(static_cast<float>(x) / static_cast<float>(terrain_height));
            texture.setY(1.0 - static_cast<float>(z) / static_cast<float>(terrain_width));
			mesh->pushTexture(texture);
        }
    }

   mesh->generateArray();

   return mesh;
}