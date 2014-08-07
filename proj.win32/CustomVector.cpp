#include "CustomVector.h"
Node::~Node(){
	delete planaria;
}
void PlanariaList::initList(PlanariaList* list){
	list->front = NULL;
}
void PlanariaList::push(PlanariaList* list, Planaria newPlanaria){
	Node* newNode = new Node(&newPlanaria);
	if (newNode == NULL){
		return;
	}
	newNode->next = NULL;
	if (list->front == NULL){
		list->front = newNode;
	}
	else{
		newNode->next = list->front;
		list->front = newNode;
	}
}
void PlanariaList::remove(PlanariaList* list, float pollutionRate){
	Node* currentNode;
	Node* removeThis;
	Node* previousNode;
	currentNode = list->front;
	while (currentNode != NULL){
		removeThis = NULL;
		if(currentNode->planaria->getPollutionThreshold() <= pollutionRate){
			if (currentNode == list->front){
				list->front = currentNode->next;
				removeThis = currentNode;
				delete removeThis;//is this appropriate way to delete planaria node? feedback & test required
				currentNode = NULL;
				currentNode = list->front;
			}
			else{
				removeThis = currentNode;
				currentNode = currentNode->next;
				previousNode->next = currentNode;
				delete removeThis;
			}
		}
		else{
			if (list->front == currentNode)
				previousNode = currentNode;
			else
				previousNode = previousNode->next;
			currentNode = currentNode->next;
		}
	}
}
