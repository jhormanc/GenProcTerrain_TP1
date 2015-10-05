#include "Triangle.h"

using namespace std;

Vector3 Triangle::getO() const
{
	return a;
}

bool Triangle::inside(const Vector3 &p) const
{

	return true;
}

Vector3 Triangle::normal(Vector3 p) const
{
	return Vector3::normalize((a-p)^(c-p));
}

//Return -1 if negatif / +1 if positif / 0 if =0
double Triangle::sign(double a) const{
	return (a==0) ? 0 : (a<0 ? -1 : 1 ) ;
}

//Function clamp.
double Triangle::clamping(double v , double max_v , double min_v) const{
	return  std::min(std::max ( v , min_v), max_v);
}

double Triangle::distance(const Vector3 & p) const
{

	/*Vector3 ba = b-a ; Vector3 pa = p-a ;
	Vector3 cb = c-b; Vector3 pb = p-b;
	Vector3 ac = a -c ; Vector3 pc = p-c;
	Vector3 nor = ba ^ ac;
	
	if(sqrt(sign((ba^nor)*pa)+sign((cb^nor)*pb)+sign((ac^nor)*pc))<2.0){
	
		return std::min(std::min((ba*clamping((ba*pa)/(ba*ba),0.0,1.0)-pa)*(ba*clamping((ba*pa)/(ba*ba),0.0,1.0)-pa),
					(cb*clamping((cb*pb)/(cb*cb),0.0,1.0)-pb)*(cb*clamping((cb*pb)/(cb*cb),0.0,1.0)-pb)),
					(ac*clamping((ac*pc)/(ac*ac),0.0,1.0)-pc)*(ac*clamping((ac*pc)/(ac*ac),0.0,1.0)-pc));
	}else{

		return (nor*pa)*(nor*pa)/(nor*nor);

	}*/

	Vector3 n = Vector3::normalize((b-a)^(c-a)); //normal
	
	double t = n*a-n*p;

	Vector3 p0 = p+ (n*t); //Point sur le plan du triangle.
	
	return (p-p0).normal();
		
}

Vector3 Triangle::getColor(const Vector3 & p) const
{
	return Vector3(255.);
}