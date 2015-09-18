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
	
}


//*Fonction pour trouver la hauteur max et min*//
void Terrain::MaxMin(float x){
	if(x>hight)
		hight=x;
		
	if(x<low)
		low=x;
		
}


// Renvoi une valeur aleatoire entre 0 et 1 a partir de x.
double Terrain::hash(double x)
{
	return (1.0 + (sin(sin(x) * rand()))) / 2.0;
}

// Perlin noise
double Terrain::noise(double x, double y, const double res_x, const double res_y)
{
	double tempX, tempY;
	int x0, y0, ii, jj, gi0, gi1, gi2, gi3;
	double unit = 1.0f / sqrt(2);
	double tmp, s, t, u, v, Cx, Cy, Li1, Li2;
	double gradient2[][2] = { { unit, unit }, { -unit, unit }, { unit, -unit }, { -unit, -unit }, 
	{ 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };

	unsigned int perm[] =
	{ 151, 160, 137, 91, 90, 15, 131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 140, 36, 103, 30, 69,
	142, 8, 99, 37, 240, 21, 10, 23, 190, 6, 148, 247, 120, 234, 75, 0, 26, 197, 62, 94, 252, 219,
	203, 117, 35, 11, 32, 57, 177, 33, 88, 237, 149, 56, 87, 174, 20, 125, 136, 171, 168, 68, 175,
	74, 165, 71, 134, 139, 48, 27, 166, 77, 146, 158, 231, 83, 111, 229, 122, 60, 211, 133, 230, 220,
	105, 92, 41, 55, 46, 245, 40, 244, 102, 143, 54, 65, 25, 63, 161, 1, 216, 80, 73, 209, 76, 132,
	187, 208, 89, 18, 169, 200, 196, 135, 130, 116, 188, 159, 86, 164, 100, 109, 198, 173, 186, 3,
	64, 52, 217, 226, 250, 124, 123, 5, 202, 38, 147, 118, 126, 255, 82, 85, 212, 207, 206, 59, 227,
	47, 16, 58, 17, 182, 189, 28, 42, 223, 183, 170, 213, 119, 248, 152, 2, 44, 154, 163, 70, 221,
	153, 101, 155, 167, 43, 172, 9, 129, 22, 39, 253, 19, 98, 108, 110, 79, 113, 224, 232, 178, 185,
	112, 104, 218, 246, 97, 228, 251, 34, 242, 193, 238, 210, 144, 12, 191, 179, 162, 241, 81, 51, 145,
	235, 249, 14, 239, 107, 49, 192, 214, 31, 181, 199, 106, 157, 184, 84, 204, 176, 115, 121, 50, 45,
	127, 4, 150, 254, 138, 236, 205, 93, 222, 114, 67, 29, 24, 72, 243, 141, 128, 195, 78, 66, 215, 61,
	156, 180 };

	//Adapter pour la résolution
	x /= res_x;
	y /= res_y;

	//On récupère les positions de la grille associée à (x,y)
	x0 = (int)(x);
	y0 = (int)(y);

	//Masquage
	ii = x0 & 255;
	jj = y0 & 255;

	//Pour récupérer les vecteurs
	gi0 = perm[ii + perm[jj]] % 8;
	gi1 = perm[ii + 1 + perm[jj]] % 8;
	gi2 = perm[ii + perm[jj + 1]] % 8;
	gi3 = perm[ii + 1 + perm[jj + 1]] % 8;

	//on récupère les vecteurs et on pondère
	tempX = x - x0;
	tempY = y - y0;
	s = gradient2[gi0][0] * tempX + gradient2[gi0][1] * tempY;

	tempX = x - (x0 + 1);
	tempY = y - y0;
	t = gradient2[gi1][0] * tempX + gradient2[gi1][1] * tempY;

	tempX = x - x0;
	tempY = y - (y0 + 1);
	u = gradient2[gi2][0] * tempX + gradient2[gi2][1] * tempY;

	tempX = x - (x0 + 1);
	tempY = y - (y0 + 1);
	v = gradient2[gi3][0] * tempX + gradient2[gi3][1] * tempY;


	//Lissage
	tmp = x - x0;
	Cx = 3 * tmp * tmp - 2 * tmp * tmp * tmp;

	Li1 = s + Cx*(t - s);
	Li2 = u + Cx*(v - u);

	tmp = y - y0;
	Cy = 3 * tmp * tmp - 2 * tmp * tmp * tmp;

	return Li1 + Cy*(Li2 - Li1);
}


// Renvoi un terrain genere aléatoirement
Terrain Terrain::CreateRidgeFractal(uint terrain_width_, uint terrain_height_, double step_x_, double step_y_, double max_z)
{
//	Terrain res();
	double facteur = max_z; // On veut que les montagnes dépassent pour pouvoir faire le ridge.
	Vector3 ** pointList = new Vector3 *[terrain_width_];
	for (int i = 0; i < terrain_width_; i++)
		pointList[i] = new Vector3[terrain_height_];

	double z0, z1;

	for (int j = 0; j < terrain_height_; j++)
	{
		for (int i = 0; i < terrain_width_; i++)
		{

			pointList[i][j] = Vector3(step_x_ * i, step_y_ * j, (noise(i, j, step_x_, step_y_) + 1) * 0.5 * facteur);
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
bool Terrain::intersection(Ray r, double &t) const
{
	double zMin = 0;
	double zMax = 0;
	double k = 0;

	// Calcul du point z le plus haut du terrain
	for (int j = 0; j < terrain_height; j++)
		for (int i = 0; i < terrain_width; i++)
				zMax = std::max(zMax, pointList[i][j].z);

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

	t = zMin;
	double epsilon = 1;
	double deltaz;
	Vector3 p = r.getOrigin(); // Point de départ du lancé de rayon
	Vector3 tmp, pas;

	while (t < zMax)
	{
		pas = (r.getDirection() * (double)t);
		tmp = r.getOrigin() + pas;
		deltaz = p.z - getPoint(tmp.x * step_x, tmp.y * step_y).z;

		if (deltaz < epsilon) 
		{ 
			return true; 
		}

		if (deltaz > k) 
		{ 
			return false;
		}

		t += (deltaz) / (k - r.getDirection().z);
		p = tmp;
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