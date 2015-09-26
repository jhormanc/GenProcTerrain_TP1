#include "Debug.h"

// Renvoi une QString du Vector3 v pour l'afficher dans le log (ici QTextEdit).
QString Debug::printVector3(Vector3 v) const
{
	QString res('[');
	res.append(QString::number(v.x)).append("," ).append(QString::number(v.y)).append(", ").append(QString::number(v.z)).append(']');
	return res;
}

// Renvoi une QString du Terrain t pour l'afficher dans le log (ici QTextEdit).
QString Debug::printTerrain(Terrain * t) const
{
	QString res("width : ");
	res.append(QString::number(t->getWidth())).append(", height : ").append(QString::number(t->getHeight())).append('\n').append("[");
	//Vector3 ** tmp = t.getPointList();

	for (int j = 0; j < t->getHeight(); j++)
	{
		for (int i = 0; i < t->getWidth(); i++)
		{
			res.append(printVector3(t->getPoint(i,j)));
			res.append(" ");
		}
		res.append('\n');
	}
	return res;
}

// Renvoi une QString du resultat de la "collision" entre le point p et le terrain t pour l'afficher dans le log (ici QTextEdit).
QString Debug::testInOut(Vector3 p, Terrain * t) const
{
	QString res("Point ");
	res.append(printVector3(p));
	t->inOut(p) ? res.append(" est dehors") : res.append(" est dedans") ;
	res.append('\n');
	return res;
}

// Renvoi une QString du resultat de la "collision" entre le rayon r et le terrain t pour l'afficher dans le log (ici QTextEdit).
QString Debug::testIntersection(Ray r, Terrain * t) const
{
	QString res("Ray ");
	res.append(printVector3(r.getOrigin()));
	res.append(printVector3(r.getDirection()));
	double n;
	bool touche = t->intersection(r, n);
	if (!touche)
		res.append(" ne touche pas");
	else
		res.append(" touche");
	//t.instersection(r) ? res.append(" touche") : res.append(" ne touche pas");
	return res;
}

void Debug::execTest(QTextEdit * logTxt)
{
	QImage hm("Resources/testhm");
	Terrain * t = new TerrainHeightmap(hm); /*Terrain crée grace à une image*/
	logTxt->setReadOnly(true);
	//Afficher en écrie le Terrain "t"
	logTxt->insertPlainText(printTerrain(t).toHtmlEscaped());
	for (int i = 0; i < 10; i++)
	{
		Vector3 tmp(((int)(rand()) % 1800) / 10.0, ((int)(rand()) % 1800) / 10.0, ((int)(rand()) % 2000) / 10.0);
		logTxt->append(testInOut(tmp, t).toHtmlEscaped());
	}

	logTxt->append(printVector3(t->getPoint(90.0, 10.0)).toHtmlEscaped());
	logTxt->append(testIntersection(Ray(Vector3(0.0, 0.0, 10.0), Vector3(1.0, 1.0, -5.0)), t).toHtmlEscaped());
	logTxt->append(testIntersection(Ray(Vector3(0.0, 0.0, 10.0), Vector3(1.0, 1.0, 5.0)), t).toHtmlEscaped());
	//hmw->AddRay(Ray(Vector3(0.0, 0.0, 255), Vector3(1.0, 1.0, -100.0)));
	//hmw->AddRay(Ray(Vector3(0.0, 0.0, 100.0), Vector3(1.0, 1.0, 5.0)));
	//hmw->AddRay(Ray(Vector3(0.0, 0.0, 100.0), Vector3(2.0, 1.0, -20)));
	//hmw->AddRay(Ray(Vector3(0.0, 0.0, 100.0), Vector3(0.5, 1.5, -20)));
	//hmw->AddRay(Ray(Vector3(0.0, 0.0, 100.0), Vector3(0.0, 0.5, 5)));
	//hmw->AddRay(Ray(Vector3(0.0, 0.0, 100.0), Vector3(1.0, 1.0, 50)));

	for (int i = 0; i < 10; i++)
	{
		Vector3 tmp1((int)(rand() % 180) / 10.0, (int)(rand() % 180) / 10.0, (int)(rand() % 200) / 10.0 + 5);
		Vector3 tmp2((int)(rand() % 180) / 10.0, (int)(rand() % 180) / 10.0, (int)(rand() % 200) / 10.0 + 5);
		logTxt->append(testIntersection(Ray(tmp1, tmp2), t).toHtmlEscaped());
	}
	//logTxt.append(d.printVector3(t.getPoint(90.0, 10.0)));
	logTxt->append(QString('\n').toHtmlEscaped());

	//Afficher en écrie le Terrain "t2"
	/*logTxt.append(d.printTerrain(t2).toHtmlEscaped());*/

	logTxt->insertPlainText(printTerrain(t).toHtmlEscaped());
	delete t;
}