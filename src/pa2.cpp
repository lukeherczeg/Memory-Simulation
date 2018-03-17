#include <iostream>
#include <string>
#include <cmath>
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

template <class T> Page * findStartOfLongestCSS(T valueSearchingFor, Iterator * it){
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

template <class T> Page * findStartOfBestFitCSS(T valueSearchingFor, int minSize, Iterator * it){
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
	return count-1;
}

template <class T> void getToEndOfProgram(T valueSearchingFor, Iterator * it){
	while(!(it->end()) && it->current()->data == valueSearchingFor){
		it->next();
	}
}

OS::OS(std::string algorithmChosen,int osSize){ // @suppress("Class members should be properly initialized")
	this->algorithmChosen = algorithmChosen;
	this->size = osSize;
	startPage = NULL;
	for(int i = 0; i < osSize/4; i++)
		this->addToFront("FREE");
}

void OS::addAfter(std::string programName, Page * loc){
	removePage("FREE");
	if(loc == NULL)
		return;
	Page * newPage = new Page();
	newPage->data = programName;
	newPage->next = loc->next;
	loc->next = newPage;
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
	Page * location = findStartOfBestFitCSS("FREE", pageSize, this->makeIterator());
	this->addAfter(programName, location);
}

void OS::addPageWorstAlgorithm(std::string programName,int pageSize){
	Page * location = findStartOfLongestCSS("FREE", this->makeIterator());
	for(int i = 0; i < ceil(pageSize/4); i++)
		this->addAfter(programName,location);
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

void OS::useSelectedAlgorithm(std::string programName, int pageSize){
	if(this->algorithmChosen == "best"){
		addPageBestAlgorithm(programName,pageSize);
	}
	else {
		addPageWorstAlgorithm(programName,pageSize);
	}
}

void OS::removePage(std::string programName){
	if(programName == startPage->data){
		startPage->data == "FREE";
		startPage = startPage->next;
		return;
	}
	Page * current = startPage;
	while(programName != current->data && current!= endPage)
		current = current->next;
	current->data = "FREE";
	if(current == endPage)
		endPage = current;
	else
		current = current->next;
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
	oSystem->addToFront("P1");
	oSystem->print();
	std::cout << "\n" << std::endl;

	oSystem->useSelectedAlgorithm("FLEE", 20);
	std::cout << "\n\n" << std::endl;
	oSystem->print();



	return 0;
}
