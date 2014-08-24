#include "CustomVector.h"
Element::~Element(){
	delete planaria;
}
PlanariaList::PlanariaList(){
	front = NULL;
}
void PlanariaList::push(Planaria* newPlanaria){
	Element* newNode = new Element(newPlanaria);
	if (newNode == NULL){
		return;
	}
	newNode->next = NULL;
	if (front == NULL){
		front = newNode;
	}
	else{
		newNode->next = front;
		front = newNode;
	}
	size++;
}
void PlanariaList::remove(float pollutionRate){
	Element* currentNode;
	Element* removeThis;
	Element* previousNode;
	currentNode = front;
	while (currentNode != NULL){
		removeThis = NULL;
		if(currentNode->planaria->getPollutionThreshold() <= pollutionRate){
			if (currentNode == front){
				front = currentNode->next;
				removeThis = currentNode;
				delete removeThis;//is this appropriate way to delete planaria node? feedback & test required
				currentNode = NULL;
				currentNode = front;
			}
			else{
				removeThis = currentNode;
				currentNode = currentNode->next;
				previousNode->next = currentNode;
				delete removeThis;
			}
			size--;
		}
		else{
			if (front == currentNode)
				previousNode = currentNode;
			else
				previousNode = previousNode->next;
			currentNode = currentNode->next;
		}
	}
}

int PlanariaList::listSize(){ return size; }