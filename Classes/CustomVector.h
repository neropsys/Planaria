#ifndef _CUSTOM_VECTOR_H_
#define _CUSTOM_VECTOR_H_
#include "Planaria.h"
#include "cocos2d.h"
/*#include <memory>
using namespace std;*/ //just in case that we may have to use some new ptr for deleting the node clean & safe
class Node{
public:
	Planaria *planaria;
	Node* next;
	Node();
	Node(Planaria* planaria) :planaria(planaria){};
	~Node();
};
class PlanariaList{
public:
	PlanariaList();
	~PlanariaList();
	Node* front;
	void initList(PlanariaList* list);
	void push(PlanariaList* list, Planaria newPlanaria);
	void remove(PlanariaList* list, float pollutionRate);//removal algorithm can be reused, 
														 //only need to overload & override the part where removal condition is different
};
#endif