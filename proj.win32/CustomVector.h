#ifndef _CUSTOM_VECTOR_H_
#define _CUSTOM_VECTOR_H_
#include "Planaria.h"
#include "cocos2d.h"
//#include <memory>
using namespace std; //just in case that we may have to use some new ptr for deleting the node clean & safe
class Element{
public:
	Planaria *planaria;
	Element* next;
	Element();
	Element(Planaria* planaria) :planaria(planaria){};
	~Element();
};
class PlanariaList{
public:
	PlanariaList();
	~PlanariaList();
	Element* front;
	void initList();
	int listSize();
	int begin();
	int end();
	void push(Planaria* newPlanaria);
	void remove(float pollutionRate);//removal algorithm can be reused, 
									//only need to overload & override the part where removal condition is different
private:
	int size=0;
};
#endif