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




/*class Matrix{
	private:
		int size;
		int ** matrix;  //array that contains references to other arrays
	public:
		Matrix(int size);
		~Matrix();
		void print();
		int get(int row, int column);
	};
*/

#endif /* PA2_H_ */
