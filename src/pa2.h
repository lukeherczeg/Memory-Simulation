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
	Page * current();
	void next();
};

class OS {
private:
	std::string algorithmChosen;
	Page * startPage;
	Page * endPage;
	int size;
	void addPageBestAlgorithm(std::string programName, int pageSize);
	void addPageWorstAlgorithm(std::string programName, int pageSize);
	int getFreeSpaceSize(Page * startPage);
public:
	OS(std::string algorithmChosen, int osSize);
	void addToFront(std::string programName);
	void addAfter(std::string program, Page * loc);
	void useSelectedAlgorithm(std::string programName, int pageSize);
	void removePage(std::string programName);
	int amountOfFragments();
	void print();
	Iterator * makeIterator();
};

#endif /* PA2_H_ */
