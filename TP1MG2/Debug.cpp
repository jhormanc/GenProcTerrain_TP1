#include "Debug.h"

// Renvoi une QString du Vector3 v pour l'afficher dans le log (ici QTextEdit).
QString Debug::printVector3(Vector3 v) const
{
	QString res('[');
	res.append(QString::number(v.x)).append("," ).append(QString::number(v.y)).append(", ").append(QString::number(v.z)).append(']');
	return res;
}

// Renvoi une QString du Terrain t pour l'afficher dans le log (ici QTextEdit).
QString Debug::printTerrain(Terrain t) const
{
	QString res("width : ");
	res.append(QString::number(t.getWidth())).append(", height : ").append(QString::number(t.getHeight())).append('\n').append("[");
	Vector3 ** tmp = t.getPointList();

	for (int j = 0; j < t.getHeight(); j++)
	{
		for (int i = 0; i < t.getWidth(); i++)
		{
			res.append(printVector3(tmp[i][j]));
			res.append(" ");
		}
		res.append('\n');
	}
	return res;
}

// Renvoi une QString du resultat de la "collision" entre le point p et le terrain t pour l'afficher dans le log (ici QTextEdit).
QString Debug::testInOut(Vector3 p, Terrain t) const
{
	QString res("Point ");
	res.append(printVector3(p));
	t.inOut(p) ? res.append(" est dehors") : res.append(" est dedans") ;
	res.append('\n');
	return res;
}

// Renvoi une QString du resultat de la "collision" entre le rayon r et le terrain t pour l'afficher dans le log (ici QTextEdit).
QString Debug::testIntersection(Ray r, Terrain t) const
{
	QString res("Ray ");
	res.append(printVector3(r.getOrigin()));
	res.append(printVector3(r.getDirection()));
	double n;
	bool touche = t.instersection(r, n);
	if (!touche)
		res.append(" ne touche pas");
	else
		res.append(" touche");
	//t.instersection(r) ? res.append(" touche") : res.append(" ne touche pas");
	return res;
}