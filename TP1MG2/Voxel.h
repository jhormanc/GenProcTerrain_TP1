#pragma once
#include "Node.h"
#include "Mesh.h"

class Voxel
{
	int n;
	QVector<int> v;

public:
	Voxel(Node &n, int n_);
	~Voxel(void);

	Mesh getMesh() const;

	// Surcharge de l'opérateur () pour l'accès au tableau
	int operator()(int i, int j, int k) const
	{
		return v.at(i * n * n + j * n + k);
	}
};

