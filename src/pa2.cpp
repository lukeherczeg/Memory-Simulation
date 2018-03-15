#include <iostream>
#include <string>
using namespace std;
#include "pa2.h"

template <class T> void LinkedList<T>::quickAppend(T value){
	if(head==NULL){
		head = new Node<T>();
		head->data = value;
		tail = head;
		return;
	}
	tail->next = new Node<T>();
	tail->next->data = value;
	tail = tail->next;
}

template <class T> void LinkedList<T>::add(int index,T value){
	if(index == 0){
		Node <T> * newNode = new Node<T>();
		newNode->data = value;
		newNode->next = head;
		head = newNode;
		return;
	}
	Node <T> * current = head;
	for(int i = 0; i < index - 1; ++i)
		current = current->next;
	Node <T> * newNode = new Node<T>();
	newNode->data = value;
	newNode->next = current->next;
	current->next = newNode;
	if(current == tail){
		tail = newNode;
	}
}

template <class T> void LinkedList<T>::remove(int index){
	if(index == 0){
		Node <T> * temp = head;
		head = head->next;
		delete temp;
		temp = NULL;
		return;
	}
	Node <T> * current = head;
	for(int i = 0; i < index - 1; ++i)
		current = current->next;
	Node <T> * temp = current->next;
	current->next = temp->next;
	if(temp == tail){
		tail = current;
	}
	current->next = current->next->next;
	delete temp;
	temp = NULL;
}

template <class T> void LinkedList<T>::print(){
	int count = 0;
	Node <T> * temp = head;
	while(temp != NULL){
		cout << temp->data << " ";
		temp = temp->next;
		count++;
		if(count % 8 == 0){
			cout << endl;
		}
	}
	//cout << "NULL\n";
}

void OS::addPageBestAlgorithm(string programName, int pageSize){
	LinkedList <string> * list = new LinkedList<string>();
	for(int i = 0; i < pageSize; i += 4){
		list->quickAppend(programName);
	}

}

void OS::addPageWorstAlgorithm(string programName,int pageSize){
	;
}

int OS::getFreeSpaceSize(Page * startPage){
	return 0;
}

OS::OS(string algorithmChosen,int osSize){ // @suppress("Class members should be properly initialized")
	this->algorithmChosen = algorithmChosen;
	this->size = osSize;
}

void OS::addPage(string programName, int pageSize){
	if(algorithmChosen == "best"){
		addPageBestAlgorithm(programName,pageSize);
	}
	else {
		addPageWorstAlgorithm(programName,pageSize);
	}
}

void OS::removePage(string programName){
	;
}

int OS::amountOfFragments(){
	return 0;
}

void OS::print(){
	;
}



int main() {
	LinkedList <string> * list = new LinkedList<string>();
	for(int i = 0; i < 32; i++){
		list->quickAppend("Free");
	}
	list->print();
	return 0;
}
