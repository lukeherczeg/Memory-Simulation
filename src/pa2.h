#ifndef PA2_H_
#define PA2_H_

template<class T> class Node {
public:
	T data;
	Node<T> * next;
};

template <class T> class LinkedList{
private:
	Node<T> * head;
	Node<T> * tail;
public:
	void quickAppend(T value);
	void add(int index, T value);
	void remove(int index);
	T get(int index);
	void print();
};

class Page {
	string programName;
};

class OS {
private:
	string algorithmChosen;
	Page * startPage;
	int size;
	void addPageBestAlgorithm(string programName, int pageSize);
	void addPageWorstAlgorithm(string programName, int pageSize);
	int getFreeSpaceSize(Page * startPage);
public:
	OS(string algorithmChosen, int osSize);
	void addPage(string programName, int pageSize);
	void removePage(string programName);
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
