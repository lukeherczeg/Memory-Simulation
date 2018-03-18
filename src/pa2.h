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
public:
	OS(std::string algorithmChosen, int osSize);
	void addToFront(std::string programName);
	void insert(std::string program, Page * loc);
	int getFreeSpaceSize(Page * loc);
	void deleteFreeSpace(Page * loc);
	void useSelectedAlgorithm(std::string programName, int pageSize);
	void removePage(std::string programName);
	int sizeOfPage(std::string programName);
	bool pageExists(std::string programName, Iterator * it);
	void print();
	Iterator * makeIterator();
};

#endif /* PA2_H_ */
