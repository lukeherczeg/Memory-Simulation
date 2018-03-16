#include <string>
#ifndef PA2_H_
#define PA2_H_

class Page {
public:
	std::string data;
	Page * next;
};

class OS {
private:
	std::string algorithmChosen;
	Page * startPage;
	Page * endPage;
	int index;
	int size;
	void addPageBestAlgorithm(std::string programName, int pageSize);
	void addPageWorstAlgorithm(std::string programName, int pageSize);
	int getFreeSpaceSize(Page * startPage);
public:
	OS(std::string algorithmChosen, int osSize);
	void addToFront(std::string programName);
	void addAfter(std::string program, int index);
	void chooseAlgorithm(std::string programName, int pageSize);
	void removePage(std::string programName);
	int amountOfFragments();
	void print();
};

#endif /* PA2_H_ */
