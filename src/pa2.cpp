#include <iostream>
#include <string>
#include <cmath>
#include "pa2.h"

////////////////// Simple definitions for iterator //////////////////

Iterator::Iterator(Page * startNode){ // Initializes iterator
	this->startNode = startNode;
	this->currentNode = startNode;
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

//////////////////////////////////////////////////////////////////

template <class T> int findAmountOfFragments(T valueSearchingFor, Iterator * it){ // Takes in an iterator and then iterates through, and once it finds a value
	int count = 0;																  // it uses getToEndOfProgram() to only increase the count 1 for each section of
	it->begin();																  // contiguous free space. Returns the number of fragments in the OS.
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

template <class T> int findContiguousSize(T valueSearchingFor, Iterator * it){ // Takes in an iterator and then iterates through, increasing count each time contiguous
	int count = 0;															   // values are found, and breaks the loop of iteration once they aren't contiguous.
	while(!(it->end())){													   // then returns the size (in pages)
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

template <class T> Page * findStartOfLongestCSS(T valueSearchingFor, Iterator * it){ // This algorithm is identical to the findStartOfBestFitCSS() one below,
	int max = 0;																	 // except it is much simpler, since we just iterate through and find the largest
	Page * maxPointer = NULL;														 // amount of free space, and set the pointer to the location where it starts.
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

template <class T> Page * findStartOfBestFitCSS(T valueSearchingFor, int minSize, Iterator * it){ // Using a bool to track if we've found a maximum value already,
	bool foundALocation = false;															      // a max value to track the greatest number of space,
	int max = 0; 																				  // and a min to track the pages allowed, and a pointer to
	int min = ceil((double)minSize/4);															  // track the location in the OS, we initialize the iterator
	Page * maxPointer = NULL;																	  // and loop until the end of the OS pages, checking the location
	it->begin();																				  // and determine the size to fit the pages of the program into.
	while(!it->end()){																			  // we use findContiguousSize() to get the number of pages of free
		if(it->current()->data == valueSearchingFor){											  // space starting at that location in the iterator.
			Page * possibleMax = it->current();													  // If it is the first time we've found free space, we set the max to
			int count = findContiguousSize(valueSearchingFor, it);								  // that number of free spaces, and the pointer to the start of the free
			if(count == min){																	  // spaces, then we set foundALocation to true.
				maxPointer = possibleMax;														  // If the space is equal to the size, it is perfect, so we return.
				return maxPointer;
			}
			if(count > max && count >= min && !foundALocation){
				max = count;
				maxPointer = possibleMax;
				foundALocation = true;
			}
			if(count < max && count >= min){													  // This time, we check all the contiguous subsequences of free space
				max = count;																	  // after the first to determine if they are smaller than the last.
				maxPointer = possibleMax;														  // making it fit best into that space.
			}
		}
		else {
			it->next();
		}
	}
	return maxPointer;
}

template <class T> void getToEndOfProgram(T valueSearchingFor, Iterator * it){ // Jumps the iterator location to the end of a program
	while(!(it->end()) && it->current()->data == valueSearchingFor){
		it->next();
	}
}

OS::OS(std::string algorithmChosen,int osSize){ // Initializes all private member variables and fills the OS with "Free" spaces
	this->algorithmChosen = algorithmChosen;	// for the size divided by 4, ie. fills with pages.
	this->size = osSize;
	startPage = NULL;
	endPage = NULL;
	for(int i = 0; i < osSize/4; i++)
		this->fillWithFree();
}

void OS::insert(std::string programName, Page * loc){ // Changes the data at a page location to the desired name
	loc->data = programName;
}

void OS::fillWithFree(){ // Fills a position of the linked list with "Free"
	if(startPage==NULL){
		startPage = new Page();
		startPage->data = "Free";
		endPage = startPage;
		return;
	}
	Page * temp = new Page();
	temp->data = "Free";
	temp->next = startPage;
	startPage = temp;
}

void OS::addPageBestAlgorithm(std::string programName, int pageSize){ // First finds a pointer to the optimal insertion location,
	Page * location = findStartOfBestFitCSS("Free", pageSize, this->makeIterator()); // then goes through the exact operation
	int numPages = ceil((double)pageSize/4);										 // of addPageWorstAlgorithm(). See below
	int freeSpaceSize = this->getFreeSpaceSize(location);							 // for details.
	if((pageSize <= freeSpaceSize) && (this->size >= freeSpaceSize)){
		for(int i = 0; i < numPages; i++){
			this->insert(programName, location);
			location = location->next;
		}
		std::cout << "Program " << programName << " added successfully: " << numPages << " page(s) used.\n" << std::endl;
	}
	else{
		std::cout << "Error, not enough memory for Program " << programName << "." << std::endl;
		std::cout << std::endl;
	}
}

void OS::addPageWorstAlgorithm(std::string programName,int pageSize){ // First finds a pointer to the optimal insertion location,
	Page * location = findStartOfLongestCSS("Free", this->makeIterator()); // then calculates the size of the free space (in KB)
	int numPages = ceil((double)pageSize/4);							   // and the size of number of pages from the pageSize
	int freeSpaceSize = this->getFreeSpaceSize(location);				   // then checks if there is enough space to insert.
	if((pageSize <= freeSpaceSize) && (this->size >= freeSpaceSize)){	   // If there is, insert for the numPages that it can,
		for(int i = 0; i < numPages; i++){								   // iterating to each next location.
			this->insert(programName, location);
			location = location->next;
		}
		std::cout << "Program " << programName << " added successfully: " << numPages << " page(s) used.\n" << std::endl;
	}
	else{
		std::cout << "Error, not enough memory for Program " << programName << "." << std::endl;
		std::cout << std::endl;
	}
}

void OS::useSelectedAlgorithm(std::string programName, int pageSize){ // Based on the arguments, just chooses the algorithm
	if(this->algorithmChosen == "best"){
		addPageBestAlgorithm(programName,pageSize);
	}
	else {
		addPageWorstAlgorithm(programName,pageSize);
	}
}

void OS::removeProgram(std::string programName){ // Changes every occurrence of a program to "Free"
	Page * current = startPage;
	while(current != endPage){
		if(programName == current->data){
			current->data = "Free";
		}
		current = current->next;
		if(current == endPage && programName == current->data){   // If after going to the next, before checking the while,
			current->data = "Free";								  // if current is the last page, set it to free before exiting
		}
	}
}

void OS::print(){ // Prints with formatting for 1, 2, 3, or 4 character long names
	int count = 0;
	std::string dataName = "";
	Page * temp = startPage;
	while(temp != NULL){
		std::cout << temp->data;
		switch((temp->data).length()){
			case 1:
				std::cout << "    ";
				break;
			case 2:
				std::cout << "   ";
				break;
			case 3:
				std::cout << "  ";
				break;
			default:
				std::cout << " ";
				break;
		}
		count++;
		temp = temp->next;
		if(count % 8 == 0){
			std::cout << std::endl;
		}
	}
}

int OS::getFreeSpaceSize(Page * loc){ // Given a location, determines the pages of free space from that location on (in KB)
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

int OS::sizeOfProgram(std::string programName){  // Accurately calculates the size of a given program (in pages)
	int count = 0;
	Page * current = this->startPage;
	while(current != endPage){
		if(programName == current->data){
			count++;
		}
		current = current->next;
		if(current == endPage && programName == current->data){
			count++;
		}
	}
	return count;
}

bool OS::pageExists(std::string programName, Iterator * it){ // Finds whether or not a program already exists
	it->begin();
	while(!it->end()){
		if(it->current()->data == programName){
			return true;
		}
		it->next();
	}
	return false;
}


int main(int argc, char *argv[]) {         // Takes in arguments for worst or best
	std::string algorithmChosen = argv[1]; // Sets the algorithm to the first (second) argument given
	int oSystemSize = 128;                 // Makes a system size of 128 as requested.

	OS * oSystem = new OS(algorithmChosen, oSystemSize); // Initializes OS

	std::cout << "Using " << algorithmChosen << " fit algorithm:\n" << std::endl;

	// Initializes all variables needed

	int tempSize = 0;
	int fragments;
	int userInput = 0;
	int programSize = 0;
	bool running = true;
	std::string programName = "";

	// Menu is outside loop since it is printed once

	std::cout << "\t1. Add program\n\t2. Kill program\n\t3. Fragmentation\n\t4. Print memory\n\t5. Exit\n" << std::endl;

	while(running){

		std::cout << "Choice - "; // Takes in the choice with cin
		std::cin >> userInput;

		switch(userInput){
			case 1:                             // This is the add program function, takes in name and size
				std::cout << "Program name - ";
				std::cin >> programName;
				std::cout << "Program size (KB) - ";
				std::cin >> programSize;
				std::cout << std::endl;
				if(!(oSystem->pageExists(programName,oSystem->makeIterator()))){ // Checks if the page exists,
						oSystem->useSelectedAlgorithm(programName, programSize); // if it does, uses the adding algorithm chosen,
				}																 // if it doesn't, gives an error that it's running
				else{
					std::cout << "Error, Program " << programName << " already running." << std::endl;
					std::cout << std::endl;
				}
				break;
			case 2:                             // This is the kill function, takes in name, doesn't need size
				std::cout << "Program name - ";
				std::cin >> programName;
				if(oSystem->pageExists(programName, oSystem->makeIterator())){ // Checks if the page exists, if it does,
					tempSize = oSystem->sizeOfProgram(programName);			   // calculates the size (in pages) given the name with sizeOfProgram()
					oSystem->removeProgram(programName);					   // and removes the page using removeProgram()
					std::cout << "\nProgram " << programName << " successfully killed, " << tempSize << " page(s) reclaimed.\n" << std::endl;
				}
				else{														   // If it doesn't exist, gives error message
					std::cout << "\nProgram " << programName << " doesn't exist. Please try something else.\n" << std::endl;
				}
				break;
			case 3:								// This is the fragments function
				fragments = findAmountOfFragments("Free", oSystem->makeIterator()); // Finds fragments using findAmountOfFragments(), and prints them
				std::cout << "\nThere are " << fragments << " fragment(s).\n" << std::endl;
				break;
			case 4:								// This is the print function
				std::cout << std::endl; // Prints the OS using print()
				oSystem->print();
				std::cout << std::endl;
				break;
			case 5:								// This is the exit function
				running = false;
				break;
			default:							// This is the error function, if an out of bounds integer is selected.
				std::cout << "\nError, choice out of bounds!\n" << std::endl;
				break;
		}
	}
	return 0;
}
