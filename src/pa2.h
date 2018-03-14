#ifndef PA2_H_
#define PA2_H_


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

template<class T>
class Node {
public:
	T data;
	Node<T> * next;
};

template <class T>
class LinkedList{
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



#endif /* PA2_H_ */
