#include <iostream>
#include <string>
#include "pa2.h"

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
	if(startPage->data == programName){
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
		endPage = newPage;
}

void OS::addPageWorstAlgorithm(std::string programName,int pageSize){
	;
}

int OS::getFreeSpaceSize(Page * startPage){
	return 0;
}

OS::OS(std::string algorithmChosen,int osSize){ // @suppress("Class members should be properly initialized")
	this->algorithmChosen = algorithmChosen;
	this->size = osSize;
	/*for(int i = 0; i < osSize/4; i++)
		this->quickAppend("Free");*/
}

void OS::addPage(std::string programName, int pageSize){
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
	if(temp == endPage){
		endPage = current;
	}
	current->next = current->next->next;
	delete temp;
	temp = NULL;
}

int OS::amountOfFragments(){
	//int size = this->getFreeSpaceSize();

	return 0;
}

void OS::print(){
	int count = 0;
	Page * temp = startPage;
	while(temp != NULL){
		std::cout << temp->data;
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
	return 0;
}
