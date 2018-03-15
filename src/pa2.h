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
	int size;
	void addPageBestAlgorithm(std::string programName, int pageSize);
	void addPageWorstAlgorithm(std::string programName, int pageSize);
	int getFreeSpaceSize(Page * startPage);
public:
	OS(std::string algorithmChosen, int osSize);
	void quickAppend(std::string programName);
	void addPage(std::string programName, int pageSize);
	void removePage(std::string programName);
	int amountOfFragments();
	void print();
};

#endif /* PA2_H_ */
