#include <string>
#ifndef PA2_H_
#define PA2_H_

class Page {
public:
	std::string data;
	Page * next;
};

class Iterator{
private:
	Page * startNode;
	Page * currentNode;
public:
	Iterator(Page * startNode);
	bool end();
	void begin();
	void next();
	Page * getNext();
	Page * current();
};

class OS {
private:
	std::string algorithmChosen;
	Page * startPage;
	Page * endPage;
	int size;
	void addPageBestAlgorithm(std::string programName, int pageSize);
	void addPageWorstAlgorithm(std::string programName, int pageSize);
	void insert(std::string program, Page * loc);
	int getFreeSpaceSize(Page * loc);
	void fillWithFree();
public:
	OS(std::string algorithmChosen, int osSize);
	Iterator * makeIterator();
	void useSelectedAlgorithm(std::string programName, int pageSize);
	void removeProgram(std::string programName);
	void print();
	int sizeOfProgram(std::string programName);
	bool pageExists(std::string programName, Iterator * it);
};

#endif /* PA2_H_ */
