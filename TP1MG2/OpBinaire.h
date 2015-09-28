#pragma once
#include "node.h"
class OpBinaire :
	public Node
{
protected:
	Node *n1;
	Node *n2;

public:
	OpBinaire(void) : Node() {}
	OpBinaire(Node *n1_, Node *n2_) : Node(), n1(n1_), n2(n2_) {}
	~OpBinaire(void);

	
};

