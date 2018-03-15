#include <iostream>
#include <string>
#include <algorithm>
#include "pa2.h"

OS::OS(std::string algorithmChosen,int osSize){ // @suppress("Class members should be properly initialized")
	this->algorithmChosen = algorithmChosen;
	this->size = osSize;
	startPage = NULL;
	for(int i = 0; i < osSize/4; i++)
		this->quickAppend("Free");
}

void OS::quickAppend(std::string programName){
	if(startPage==NULL){
		startPage = new Page();
		startPage->data = programName;
		endPage = startPage;
		return;
	}
	endPage->next = new Page();
	endPage->next->data = programName;
	endPage = endPage->next;
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
	Page * temp = new Page();
	int amtFragments = this->amountOfFragments();
	int * amtOfFragment = new int[amtFragments];
	int amtFreeSpace = 0;
	for(int i = 0; i < amtFragments; i++){
		amtFreeSpace = this->getFreeSpaceSize(temp);
		amtOfFragment[i] = amtFreeSpace;
		if(temp->next != NULL)
			for(int i = 0; i < amtFreeSpace/4; i++)
				temp = temp->next;
	}
	std::sort(amtOfFragment[0],amtOfFragment[amtFragments-1]);
	if(amtOfFragment[amtFragments-1] >= pageSize){
		//
		//addPage(programName,
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
			if(temp->data == "Free"){
				count += 4;
				temp = temp->next;
			}
			else{
				temp = temp->next;
			}
		}
	}
	else if(startPage->next == NULL && startPage->data == "Free")
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
	Page * temp = current->next;
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
	std::cout << "Number of fragments:: " << oSystem->amountOfFragments() << std::endl;
	oSystem->quickAppend(algorithmChosen);
	oSystem->print();
	return 0;
}
