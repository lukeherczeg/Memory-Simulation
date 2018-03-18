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

Page * Iterator::getNext(){
	return this->currentNode->next;
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

template <class T> int findContiguousSizeProgram(T valueSearchingFor, Iterator * it){
	int count = 0;
	it->begin();
	while(!(it->end())){
		if(it->current()->data == valueSearchingFor){
			count++;
		}
		it->next();
	}
	return count;
}

template <class T> int findContiguousSize(T valueSearchingFor, Iterator * it){
	int count = 0;
	while(!(it->end())){
		if(it->current()->data == valueSearchingFor){
			count++;
		}
		else if(it->current()->data != valueSearchingFor && count > 0){
			break;
		}
		it->next();
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
	return maxPointer;
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
		this->addToFront("Free");
}

void OS::insert(std::string programName, Page * loc){
	/*Page * newPage = new Page();
	if(startPage == loc){
		newPage->next = startPage;
		startPage = newPage;
		return;
	}
	if(endPage == loc){
		newPage->next = loc;
		prev->next = newPage;
		return;
	}
	newPage->next = loc->next;
	prev->next = newPage;
	 */

	if(loc == NULL)
		return;
	Page * newPage = new Page();
	newPage->data = programName;
	newPage->next = loc->next;
	loc->next = newPage;
}

void OS::deleteFreeSpace(Page * loc){
	if(loc->next == NULL){
		Page * temp = loc->next;
		free(temp);
		return;
	}

   	if(loc->data == "Free"){
		Page * temp = loc->next;
		loc->next = temp->next;
		free(temp);
	}
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
	Page * location = findStartOfBestFitCSS("Free", pageSize, this->makeIterator());
	for(int i = 0; i < ceil(pageSize/4); i++){
		this->deleteFreeSpace(location);
	}
	for(int i = 0; i < ceil(pageSize/4); i++){
		this->insert(programName,location);
	}
}

void OS::addPageWorstAlgorithm(std::string programName,int pageSize){
	Page * location = findStartOfLongestCSS("Free", this->makeIterator());
	int target = ceil(pageSize/4);
	int freeSpaceSize = this->getFreeSpaceSize(location);
	std::cout << freeSpaceSize << std::endl;
	if((pageSize <= freeSpaceSize) && (this->size >= freeSpaceSize)){
		for(int i = 0; i < target; i++){
			this->deleteFreeSpace(location);
		}
		for(int i = 0; i < target; i++){
			this->insert(programName, location);
		}
		std::cout << "Program " << programName << " added successfully: " << target << " page(s) used.\n" << std::endl;
	}
	else{
		std::cout << "Error, not enough memory for Program " << programName << "." << std::endl;
		std::cout << std::endl;
	}
}

void OS::useSelectedAlgorithm(std::string programName, int pageSize){ //works
	if(this->algorithmChosen == "best"){
		addPageBestAlgorithm(programName,pageSize);
	}
	else {
		addPageWorstAlgorithm(programName,pageSize);
	}
}

void OS::removePage(std::string programName){ //works
	Page * current = startPage;
	while(programName != current->data && current != endPage)
		current = current->next;
	while(programName == current->data && current != endPage){
		if(programName == startPage->data){
			startPage->data == "Free";
			startPage = startPage->next;
			return;
		}
		current->data = "Free";
		if(current == endPage)
			endPage = current;
		else
			current = current->next;
	}
}

int OS::getFreeSpaceSize(Page * loc){
	int count = 0;
	while(loc != NULL){
		if(loc->data == "Free"){
			count++;
		}
		else if(loc->data != "Free" && count > 0){
			break;
		}
		if(loc->next == NULL)
			break;
		loc = loc->next;
	}
	return count * 4;
}

bool OS::pageExists(std::string programName, Iterator * it){ //works
	it->begin();
	while(!it->end()){
		if(it->current()->data == programName){
			return true;
		}
		it->next();
	}
	return false;
}

int OS::sizeOfPage(std::string programName){
	int count = 0;
	Page * current = this->startPage;
	while(programName != current->data && current != endPage)
		current = current->next;
	while(programName == current->data && current != endPage){
		count++;
		if(current != endPage)
			current = current->next;
	}
	return count;
}

void OS::print(){ // works
	int count = 0;
	Page * temp = startPage;
	while(temp != NULL){
		if(temp->data == "Free")
			std::cout << temp->data << " ";
		else
			std::cout << temp->data << "   ";
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
	int oSystemSize = 128;

	OS * oSystem = new OS(algorithmChosen, oSystemSize);

	std::cout << "Using " << algorithmChosen << " fit algorithm\n" << std::endl;

	int programSize = 0;
	std::string programName = "";
/*
	//TEST
	programSize = 50;
	programName = "P1";
	if(!(oSystem->pageExists(programName,oSystem->makeIterator()))){
		oSystem->useSelectedAlgorithm(programName, programSize);
	}
	else{
		std::cout << "Error, Program " << programName << " already running." << std::endl;
		std::cout << std::endl;
	}
	std::cout << std::endl;
	oSystem->print();
	std::cout << std::endl;

	programSize = 50;
	programName = "P2";
	if(!(oSystem->pageExists(programName,oSystem->makeIterator()))){
		oSystem->useSelectedAlgorithm(programName, programSize);
	}
	else{
		std::cout << "Error, Program " << programName << " already running." << std::endl;
		std::cout << std::endl;
	}
	std::cout << std::endl;
	oSystem->print();
	std::cout << std::endl;
*//*
	//Test
	programSize = 50;
	programName = "P1";
	if(!(oSystem->pageExists(programName,oSystem->makeIterator()))){
		oSystem->useSelectedAlgorithm(programName, programSize);
	}
	else{
		std::cout << "Error, Program " << programName << " already running." << std::endl;
		std::cout << std::endl;
	}
	std::cout << std::endl;
	oSystem->print();
	std::cout << std::endl;

	int tempSize = oSystem->sizeOfPage(programName);
	oSystem->removePage(programName);
	std::cout << "\nProgram " << programName << " successfully killed, " << tempSize << " page(s) reclaimed.\n" << std::endl;

	std::cout << std::endl;
	oSystem->print();
	std::cout << std::endl;
*/
	std::cout << "\t1. Add program\n\t2. Kill program\n\t3. Fragmentation\n\t4. Print memory\n\t5. Exit\n" << std::endl;

	int tempSize = 0;
	bool running = true;
	int userInput = 0;
	while(running){
		std::cout << "choice - ";
		std::cin >> userInput;
		switch(userInput){
			case 1:
				std::cout << "Program name - ";
				std::cin >> programName;
				std::cout << "Program size (KB) - ";
				std::cin >> programSize;
				std::cout << std::endl;


				if(!(oSystem->pageExists(programName,oSystem->makeIterator()))){
						oSystem->useSelectedAlgorithm(programName, programSize);
				}
				else{
					std::cout << "Error, Program " << programName << " already running." << std::endl;
					std::cout << std::endl;
				}

				break;
			case 2:
				std::cout << "Program name - ";
				std::cin >> programName;
				tempSize = oSystem->sizeOfPage(programName);
				oSystem->removePage(programName);
				std::cout << "\nProgram " << programName << " successfully killed, " << tempSize << " page(s) reclaimed.\n" << std::endl;
				break;
			case 3:
				std::cout << "\nThere are " << findAmountOfFragments("Free", oSystem->makeIterator()) << " fragment(s).\n" << std::endl;
				break;
			case 4:
				std::cout << std::endl;
				oSystem->print();
				std::cout << std::endl;
				break;
			case 5:
				running = false;
				break;
			default:
				std::cout << "\nError, choice out of bounds!\n" << std::endl;
				break;
		}
	}
	return 0;
}
