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
			pointList[i][j] = Vector3(changeRepereX(i), changeRepereY(j), gray * fact);
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
	/*		double x = (2 * (i - terrain_width_ * 0.5) / terrain_width_);
			double y = (2 * (j - terrain_height_ * 0.5) / terrain_height_);*/
			double x = i; 
			double y = j;

			z = Noise::noise(i, j) / 255;
			pointList[i][j] = Vector3(x, y, z);
		
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
	
	//int tmpI = (int)(( (( x + 1. ) * 0.5) * terrain_width ));
	//int tmpJ = (int)(( ((y +1.) * 0.5) * terrain_height ));
	int tmpI = (int)x;
	int tmpJ = (int)y;

	if (!(tmpI < terrain_width && tmpJ < terrain_height))
	{
		return noneVec;
	}
	Vector3 a;
	Vector3 b;
	Vector3 c;
	if (tmpI < terrain_width - 1)
		a = Vector3(pointList[tmpI + 1][tmpJ]);
	else
		a = pointList[tmpI][tmpJ];

	if (tmpJ < terrain_height - 1)
		b = Vector3(pointList[tmpI][tmpJ + 1]);
	else
		b = pointList[tmpI][tmpJ];

	if (tmpI < terrain_width - 1 && tmpJ < terrain_height - 1)
	{
		c =  pointList[tmpI + 1][tmpJ + 1];
	}
	else
	{
		c = pointList[tmpI][tmpJ];
	}
	double x2 = ((x  - b.x) / (step_x)) * 0.5;
	double y2 = ((y  - a.y) / (step_y)) * 0.5;
	double z = (1 - x2) * (1 - y2) * pointList[tmpI][tmpJ].z
		+ x2 * (1 - y2) * a.z
		+ (1 - x2) * y2 * b.z
		+ x2 * y2 * c.z;



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

	//Technique Derivé
	//Vector3 eps(0.01,0.0,0.0);
	//Vector3 tmp = p;
	//Vector3 tmp2 = eps;
	//double x = getPoint(tmp.x-tmp2.x,tmp.z-tmp2.y).z-getPoint(tmp.x+tmp2.x,tmp.z+tmp2.y).z;
	//double y = 2*eps.x;
	//double z = getPoint(tmp.x-tmp2.y,tmp.z-tmp2.x).z-getPoint(tmp.x+tmp2.y,tmp.z+tmp2.x).z;

	//return Vector3::normalize(Vector3(x,y,z));
	
	//Technique triangle
	//int tmpI = (int)((((p.x + 1.) * 0.5) * terrain_width));
	//int tmpJ = (int)((((p.y + 1) * 0.5) * terrain_height));
	int tmpI = p.x;
	int tmpJ = p.y;

	if (tmpI == 0 && tmpJ == 0){
		//Need 2 normals
		Vector3 a = getPoint(p.x, p.y);
		Vector3 b = pointList[tmpI + 1][tmpJ];
		Vector3 c = pointList[tmpI][tmpJ + 1];
		//normal point b
		Vector3 nb = ((c - b) ^ (a - b));
		//normal point c
		Vector3 nc = ((b - c) ^ (a - c));
		return Vector3::normalize((nb + nc) / 2.0);
	}

	if (tmpI == terrain_width - 1 && tmpJ == 0){
		//Need 3 normals
		Vector3 a = getPoint(p.x, p.y);
		Vector3 b = pointList[tmpI - 1][tmpJ];
		Vector3 c = pointList[tmpI][tmpJ + 1];
		Vector3 d = pointList[tmpI - 1][tmpJ + 1];

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

	if (tmpI == terrain_width - 1 && tmpJ == terrain_height - 1){
		//Need 3 normals
		Vector3 a = getPoint(p.x, p.y);
		Vector3 b = pointList[tmpI + 1][tmpJ];
		Vector3 c = pointList[tmpI][tmpJ - 1];
		Vector3 d = pointList[tmpI + 1][tmpJ - 1];
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

	if (tmpI == 0 && tmpJ == terrain_height - 1){
		//Need 2 normals
		Vector3 a = getPoint(p.x, p.y);
		Vector3 b = pointList[tmpI - 1][tmpJ];
		Vector3 c = pointList[tmpI][tmpJ - 1];
		//normal point b
		Vector3 nb = ((c - b) ^ (a - b));
		//normal point c
		Vector3 nc = ((a - c) ^ (b - c));
		return Vector3::normalize((nb + nc) / 2.0);
	}

	//cotés:
	//Coté gauche
	if (tmpI == 0 && tmpJ != 0 && tmpJ != terrain_height - 1){
		//Need 4 normals
		Vector3 a = getPoint(p.x, p.y);
		//point du haut
		Vector3 b = pointList[tmpI][tmpJ - 1];
		//point diagonal
		Vector3 c = pointList[tmpI + 1][tmpJ - 1];
		//point gauche
		Vector3 d = pointList[tmpI + 1][tmpJ];
		//point bas
		Vector3 e = pointList[tmpI][tmpJ + 1];

		Vector3 nb = ((a - b) ^ (c - b));
		Vector3 nc = ((b - c) ^ (a - c));
		Vector3 nd1 = (a - d) ^ (c - d);
		Vector3 nd2 = ((a - d) ^ (e - d));
		Vector3 nd = nd1 + nd2;
		Vector3 ne = ((a - e) ^ (d - e));
		return Vector3::normalize((nb + nc + nd + ne) / 4.0);
	}

	//Coté haut
	if (tmpJ == 0 && tmpI != 0 && tmpI != terrain_width - 1){
		//Need 4 normals
		Vector3 a = getPoint(p.x, p.y);
		//point du haut
		Vector3 b = pointList[tmpI - 1][tmpJ];
		//point diagonal
		Vector3 c = pointList[tmpI - 1][tmpJ + 1];
		//point gauche
		Vector3 d = pointList[tmpI][tmpJ + 1];
		//point bas
		Vector3 e = pointList[tmpI + 1][tmpJ];

		Vector3 nb = ((a - b) ^ (c - b));
		Vector3 nc = ((b - c) ^ (a - c));
		Vector3 nd1 = (a - d) ^ (c - d);
		Vector3 nd2 = ((a - d) ^ (e - d));
		Vector3 nd = nd1 + nd2;
		Vector3 ne = ((a - e) ^ (d - e));
		return Vector3::normalize((nb + nc + nd + ne) / 4.0);
	}

	//Coté droit
	if (tmpI == terrain_width - 1 && tmpJ != 0 && tmpJ != terrain_height - 1){
		//Need 4 normals
		Vector3 a = getPoint(p.x, p.y);
		//point du haut
		Vector3 b = pointList[tmpI][tmpJ - 1];
		//point diagonal
		Vector3 c = pointList[tmpI - 1][tmpJ];
		//point gauche
		Vector3 d = pointList[tmpI - 1][tmpJ + 1];
		//point bas
		Vector3 e = pointList[tmpI][tmpJ + 1];

		Vector3 nb = ((a - b) ^ (c - b));
		Vector3 nc = ((b - c) ^ (a - c));
		Vector3 nd1 = ((a - d) ^ (e - d));
		Vector3 nd2 = (a - d) ^ (c - d);
		Vector3 nd = nd1 + nd2;
		Vector3 ne = ((a - e) ^ (d - e));
		return Vector3::normalize((nb + nc + nd + ne) / 4.0);
	}

	//Coté Bas
	if (tmpJ == terrain_height && tmpI != 0 && tmpI != terrain_width - 1){
		//Need 4 normals
		Vector3 a = getPoint(p.x, p.y);
		//point du haut
		Vector3 b = pointList[tmpI - 1][tmpJ];
		//point diagonal
		Vector3 c = pointList[tmpI][tmpJ - 1];
		//point gauche
		Vector3 d = pointList[tmpI + 1][tmpJ - 1];
		//point bas
		Vector3 e = pointList[tmpI + 1][tmpJ];

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
	Vector3 a = getPoint(p.x, p.y);
	Vector3 b = pointList[tmpI - 1][tmpJ];
	Vector3 c = pointList[tmpI][tmpJ - 1];
	Vector3 d = pointList[tmpI + 1][tmpJ - 1];
	Vector3 e = pointList[tmpI + 1][tmpJ - 1];
	Vector3 f = pointList[tmpI][tmpJ + 1];
	Vector3 g = pointList[tmpI - 1][tmpJ + 1];

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
			float y = getPoint(changeRepereX(x), changeRepereY(z)).z;

			vertice.setX((MAP_SIZE * x / terrain_height) - MAP_SIZE / 2); // x
			vertice.setY(y); //(2.0 * qGray(color) / 255);
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

Vector3 Terrain::getColor(double x, double y)
{
	double z = getPoint(x, y).z;
	Vector3 color;

	Vector3 white = Vector3(255, 255, 255);
	Vector3 brown = Vector3(51, 25, 0);
	Vector3 green = Vector3(0, 102, 0);
	Vector3 blue = Vector3(0, 128, 255);
	Vector3 grey = Vector3(64, 64, 64);

	double max = hight - low;

	if (z <= low + (max * (5. / 100.)))
		color = green;
	else if (z >= low + (max* (90. / 100.)))
		color = white;
	else if (z >= low + (max* (50. / 100.)))
		color = grey;
	else if (z >= low + (max * (5. / 100.)) && (z <= low + (max* (50. / 100.))))
		color = brown;
	else
		color = blue;

	return color;
}

double Terrain::changeRepereX(double _x)
{
	//return (2 * (_x - terrain_height * 0.5) / terrain_height);
	return _x; // *step_x;
}

double Terrain::changeRepereY(double _y)
{
	//return (2 * (_y - terrain_width * 0.5) / terrain_width);
	return _y; // *step_y;
}

double changeRepereZ(double _z)
{
	//return _z / 255.;
	return _z; // / 255;
}
