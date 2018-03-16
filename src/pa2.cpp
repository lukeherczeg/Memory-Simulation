#include <iostream>
#include <string>
#include <algorithm>
#include "pa2.h"

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

void OS::addAfter(std::string programName, int index){
	Page * temp, * left, * right;
	right = startPage;
	for(int i = 1; i < index; i++){
		left = right;
		right = right->next;
	}
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
			for(int i = 0; i < amtFreeSpace/4; i++)
				temp = temp->next;
	}
	int maxVal = 0;
	for(int i = 0; i < amtFragments; i++){
		maxVal = max(amtsOfFragment[i], maxVal);
	}
	if(maxVal >= pageSize){
		//for(pagesize)
		//addAfter(programName, index of the start of maxVal)
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
	bool doneChecking = false;
	while(!doneChecking){
		amtFreeSpace = this->getFreeSpaceSize(temp);
		if(amtFreeSpace > 0)
			countOfFragments++;

		if(temp->next != NULL)
			for(int i = 0; i < amtFreeSpace/4; i++)
				temp = temp->next;

		if(temp == NULL)
			doneChecking = true;
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



int main() {
	std::string algorithmChosen = "best";
	OS * oSystem = new OS(algorithmChosen, 128);
	oSystem->print();
	std::cout << std::endl;
	oSystem->removePage("FREE");
	oSystem->print();
	std::cout << "\nNumber of fragments:: " << oSystem->amountOfFragments() << "\n" <<std::endl;
	oSystem->addToFront(algorithmChosen);
	oSystem->print();
	std::cout << std::endl;
	oSystem->addAfter(algorithmChosen,5);
	oSystem->print();
	return 0;
}
