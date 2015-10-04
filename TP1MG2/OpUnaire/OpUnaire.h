#pragma once
#include "node.h"
class OpUnaire :
	public Node
{
protected:
	Node *n;

public:
	OpUnaire(void) : Node() {}
	OpUnaire(Node *n_) : Node(), n(n_) {}
	~OpUnaire(void){};


};