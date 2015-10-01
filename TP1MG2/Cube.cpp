#include "Cube.h"


bool Cube::inside(const Vector3 &p) const{

		if(p.x > o.x-Largeur/2 && p.x < o.x+Largeur/2){
			if(p.y > o.y-Largeur/2 && p.y < o.y+Largeur/2){
				if(p.z < o.z+Largeur/2 && p.z > o.z-Largeur/2){
					return true;
				}
			}
		}

		return false;
}


double Cube::distance(const Vector3 & p) const{
	float d=0;
	Vector3 a(o.x-Largeur/2,o.y-Largeur/2,o.z+Largeur/2);
	Vector3 b(o.x+Largeur/2,o.y+Largeur/2,o.z-Largeur/2);
	//axe x
	if(p.x < a.x){
		d+=(p.x-a.x)*(p.x-a.x);
	}else if(p.x > b.x){
		d+=(p.x-b.x)*(p.x-b.x);
	}else{
		d+=0;
	}

	//axe y
	if(p.y < a.y){
		d+=(p.y-a.y)*(p.y-a.y);
	}else if(p.y > b.y){
		d+=(p.y-b.y)*(p.y-b.y);
	}else{
		d+=0;
	}

	//axe z
	if(p.z > a.z){
		d+=(p.z-a.z)*(p.z-a.z);
	}else if(p.z < b.z){
		d+=(p.z-b.z)*(p.z-b.z);
	}else{
		d+=0;
	}

	return d;
}