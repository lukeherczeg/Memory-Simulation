#include <iostream>
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
	Node <T> * temp = head;
	while(temp != NULL){
		cout << temp->data << " -> ";
		temp = temp->next;
	}
	cout << "NULL\n";
}

int main() {
	LinkedList <int> * linkedList = new LinkedList<int>();
	for(int i = 0; i < 5; i++){
		linkedList->quickAppend(i);
	}
	linkedList->print();
	linkedList->remove(0);
	linkedList->print();
	linkedList->remove(2);
	linkedList->print();
	linkedList->quickAppend(26);
	linkedList->print();
	return 0;
}
