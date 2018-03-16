#include <iostream>
#include <string>
#include <algorithm>
#include "pa2.h"

Iterator::Iterator(Page * startNode){ // @suppress("Class members should be properly initialized")
	this->startNode = startNode;
}

bool Iterator::end(){
	return this->currentNode == NULL;
}

void Iterator::begin(){
	this->currentNode = startNode;
}

void Iterator::next(){
	this->currentNode = this->currentNode->next;
}

Page * Iterator::current(){
	return this->currentNode;
}

Iterator * OS::makeIterator(){
	return new Iterator(startPage);
}



template <class T> int findAmountOfFragments(T valueSearchingFor, Iterator * it){
	int count = 0;
	it->begin();
	while(!it->end()){
		if(it->current()->data == valueSearchingFor){
			count++;
			getToEndOfProgram(valueSearchingFor, it);
		}
		else {
			it->next();
		}
	}
	return count;
}


template <class T> Page * findStartofLongestCSS(T valueSearchingFor, Iterator * it){
	int max = 0;
	Page * maxPointer = NULL;
	it->begin();
	while(!it->end()){
		if(it->current()->data == valueSearchingFor){
			Page * possibleMax = it->current();
			int count = findContiguousSize(valueSearchingFor, it);
			if(count > max){
				max = count;
				maxPointer = possibleMax;
			}
		}
		else {
		it->next();
		}
	}
	std::cout << max << std::endl;
	return maxPointer;
}

template <class T> Page * findStartOfLongestCSS(T valueSearchingFor, int minSize, Iterator * it){
	int max = 0;
	Page * maxPointer = NULL;
	it->begin();
	while(!it->end()){
		if(it->current()->data == valueSearchingFor){
			Page * possibleMax = it->current();
			int count = findContiguousSize(valueSearchingFor, it);
			if(count > max && count >= minSize){
				max = count;
				maxPointer = possibleMax;
			}
		}
		else {
			it->next();
		}
	}
	std::cout << max << std::endl;
	return maxPointer;
}

template <class T> int findContiguousSize(T valueSearchingFor, Iterator * it){
	int count = 0;
	while(!(it->end()) && it->current()->data == valueSearchingFor){
		count++;
		it->next();
	}
	return count;
}

template <class T> void getToEndOfProgram(T valueSearchingFor, Iterator * it){
	while(!(it->end()) && it->current()->data == valueSearchingFor){
		it->next();
	}
}

int max(int a,int b){
	return((a>b) ? (a) : (b));
}

OS::OS(std::string algorithmChosen,int osSize){ // @suppress("Class members should be properly initialized")
	this->algorithmChosen = algorithmChosen;
	this->size = osSize;
	startPage = NULL;
	for(int i = 0; i < osSize/4; i++)
		this->addToFront("FREE");
}

void OS::addAfter(std::string programName, Page * loc){
	Page * temp, * left, * right;
	right = startPage;
	left = right;
	temp = new Page();
	temp->data = programName;
	left->next = temp;
	left = temp;
	left->next = right;
	temp = right;
	right->next = temp->next;
	if(temp == endPage)
		endPage = right;
	right->next = right->next->next;
	delete temp;
	temp = NULL;
}

void OS::addToFront(std::string programName){
	if(startPage==NULL){
		startPage = new Page();
		startPage->data = programName;
		endPage = startPage;
		return;
	}
	Page * temp = new Page();
	temp->data = programName;
	temp->next = startPage;
	startPage = temp;
}

void OS::addPageBestAlgorithm(std::string programName, int pageSize){
	int numFragments = this->amountOfFragments();
	for(int i = 0; i < numFragments; i++){

	}






	/*if(startPage->data == programName){
		Page * newPage = new Page();
		newPage->data = programName;
		newPage->next = startPage;
		startPage = newPage;
		return;
	}
	Page * current = startPage;
	while(programName != current->data)
		current = current->next;
	Page * newPage = new Page();
	newPage->data = programName;
	newPage->next = current->next;
	current->next = newPage;
	if(current == endPage)
		endPage = newPage;*/
}

void OS::addPageWorstAlgorithm(std::string programName,int pageSize){
	Page * temp = startPage;
	int amtFragments = this->amountOfFragments();
	int * amtsOfFragment = new int[amtFragments];
	int amtFreeSpace = 0;
	for(int i = 0; i < amtFragments; i++){
		amtFreeSpace = this->getFreeSpaceSize(temp);
		amtsOfFragment[i] = amtFreeSpace;
		if(temp->next != NULL)
			for(int i = 0; i < amtFreeSpace/4 - 4; i++)
				temp = temp->next;
	}
	int maxVal = 0;
	for(int i = 0; i < amtFragments; i++){
		maxVal = max(amtsOfFragment[i], maxVal);
	}
	if(maxVal >= pageSize){
		for(int i = 0; i < maxVal; i++){
		//addAfter(programName, findstartof)
			//this->addAfter(programName,);
		}
	}
	else{
		std::cout << "Cannot add, not enough space." << std::endl;
	}
}

int OS::getFreeSpaceSize(Page * startPage){
	int count = 0;
	Page * temp = startPage;
	if(temp->next != NULL){
		while(temp != NULL){
			if(temp->data == "FREE"){
				count += 4;
				if(temp->next == NULL && temp->data == "FREE")
					count += 4;
				temp = temp->next;
			}
			else{
				temp = temp->next;
			}
		}
	}
	else if(startPage->next == NULL && startPage->data == "FREE")
		count = 4;
	return count;
}

void OS::chooseAlgorithm(std::string programName, int pageSize){
	if(algorithmChosen == "best"){
		addPageBestAlgorithm(programName,pageSize);
	}
	else {
		addPageWorstAlgorithm(programName,pageSize);
	}
}

void OS::removePage(std::string programName){
	if(programName == startPage->data){
		Page * temp = startPage;
		startPage = startPage->next;
		delete temp;
		temp = NULL;
		return;
	}
	Page * current = startPage;
	while(programName != current->data)
		current = current->next;
	Page * temp = current;
	current->next = temp->next;
	if(temp == endPage)
		endPage = current;
	current->next = current->next->next;
	delete temp;
	temp = NULL;
}

int OS::amountOfFragments(){
	int countOfFragments = 0;
	int amtFreeSpace = 0;
	Page * temp = startPage;
	while(temp->next != NULL){
		amtFreeSpace = this->getFreeSpaceSize(temp);
		if(amtFreeSpace > 0)
			countOfFragments++;
		for(int i = 1; i < (amtFreeSpace/4); i++){
			if(temp->next != NULL)
				temp = temp->next;
		}
	}
	return countOfFragments;
}

void OS::print(){
	int count = 0;
	Page * temp = startPage;
	while(temp != NULL){
		std::cout << temp->data << " ";
		count++;
		temp = temp->next;
		if(count % 8 == 0){
			std::cout << std::endl;
		}
	}
}




int main(/*int argc, char *argv[]*/) {
	/*std::string algorithmChosen = "";
	algorithmChosen = argv[1];
	search eclipse command line arguments stuff.
	*/
	std::string algorithmChosen = "worst";
	OS * oSystem = new OS(algorithmChosen, 128);
	oSystem->print();
	std::cout << std::endl;
	//oSystem->removePage("FREE");
	oSystem->print();
	oSystem->addToFront("P1");
	oSystem->removePage("FREE");
	std::cout << "\nNumber of fragments:: " << findAmountOfFragments("FREE", oSystem->makeIterator()) << "\n" << std::endl;
	std::cout << "\nNumber of fragments:: " << findAmountOfFragments("P1", oSystem->makeIterator()) << "\n" << std::endl;
	//std::cout << "\nSize of P1:: " << findContiguousSize("P1", oSystem->makeIterator()) << "\n" << std::endl;
	oSystem->print();
	return 0;
}
