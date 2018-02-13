#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

// #include<iostream>


template<class T>
struct element {
	T data;
	element *prev, *next;
};

template<class T = int>
class LinkedList {
public:
	// The big four
	LinkedList();
	LinkedList(const LinkedList<T>&);
	LinkedList<T>& operator=(const LinkedList<T>&);
	~LinkedList();
	// get functions
	element<T> getFirstElement() const;
	element<T> getLastElement() const;
	// insert element at some index
	// void insertElement(const T&, int);
	// add element at the last index
	void addLast(const T&);
	void addFirst(const T&);
	// void addMiddle(const T&, int);
	// deleting element at some index
	void deleteElement(int);
	void delFirst();
	void delLast();
	// print list
	void print() const;
	// [] operator for accessing an element
	T& operator[](int);
	// Bool function to checks if a list is empty
	bool isEmpty() const;
	int getSize() const { return size; }
private:
	element<T> *start, *end;
	int size;
	void deleteElements();
};

template<class T>
void LinkedList<T>::deleteElements() {
	while (start) {
		element<T>* temp = start;
		start = start->next;
		delete temp;
	}
	size = 0;
}

template<class T>
LinkedList<T>::LinkedList() {
	start = NULL;
	end = NULL;
	size = 0;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T>& other) {
	*this = other;
}

template<class T>
LinkedList<T>::~LinkedList() {
	deleteElements();
}

template<class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other) {
	if (this != &other) {
		deleteElements();
		start = new element<T>;
		end = start;
		start->prev = NULL;
		start->data = other.start->data;
		element<T>* pointer = other.start->next;
		while (pointer) {
			element<T>* beforeEnd = end;
			end = new element<T>;
			end->data = pointer->data;
			beforeEnd->next = end;
			end->next = NULL;
			pointer = pointer->next;
		}
	}
	return *this;
}

template<class T>
element<T> LinkedList<T>::getFirstElement() const {
	return start->data;
}

template<class T>
element<T> LinkedList<T>::getLastElement() const {
	return end->data;
}

template<class T>
T& LinkedList<T>::operator[](int index) {
	int counter = 0;
	element<T> *pointer = start;
	if (index >= size) {
		// std::cout << "Incorrect index" << std::endl;
		T a = -1;
		return a;
	}
	else {
		while (counter != index) {
			pointer = pointer->next;
			counter++;
		}
		return pointer->data;
	}
}

template<class T>
void LinkedList<T>::addLast(const T& elem) {
	// Create space for the new element by end->next pointer
	element<T> *pointer = new element<T>;
	// Matching the last element with the new element created with end->next
	pointer->prev = end;
	pointer->next = NULL;
	pointer->data = elem;
	end->next = pointer;
	// Matching end with end->next so that now end is a pointer to the last element in the list
	end = pointer;
	++size;
}

template<class T>
void LinkedList<T>::addFirst(const T& elem) {
	if (size == 0) {
		start = new element<T>;
		start->data = elem;
		start->next = NULL;
		start->prev = NULL;
		end = start;
	}
	else {
		element<T>* pointer = new element<T>;
		pointer->prev = NULL;
		pointer->next = start;
		pointer->data = elem;
		start = pointer;
	}
	++size;
}

/*
template<class T>
void LinkedList<T>::addMiddle(const T& elem, int index) {
	if (index < 0 || index > size - 1) {
		std::cout << "Incorrect index" << std::endl;
		return;
	}
	else if (index == 0) {
		addFirst(elem);
	}
	else if (index == size - 1) {
		addLast(elem);
	}
	else {  // Нещо не работи както трябва
		element<T> *ptr = start;
		int counter = 0;
		while (counter < index) {
			ptr = ptr->next;
			counter++;
		}
		element<T> *ptr1 = new element<T>;
		element<T> *prevv = ptr->prev;
		ptr1->data = elem;
		prevv->next = ptr1;
		ptr1->prev = prevv->next;
		ptr->prev = ptr1;
		ptr1->next = ptr;
		++size;
	}
}
*/

template<class T>
void LinkedList<T>::print() const {
	element<T> *pointer = start;
	for (int i = 0; i < size; i++) {
		std::cout << pointer->data << " ";
		pointer = pointer->next;
	}
	std::cout << std::endl;
}

template<class T>
bool LinkedList<T>::isEmpty() const {
	return size == 0;
}

template<class T>
void LinkedList<T>::delFirst() {
	element<T> *pointer = start;
	start = start->next;
	start->prev = NULL;
	delete pointer;
}

template<class T>
void LinkedList<T>::delLast() {
	element<T> *pointer = end;
	end = end->prev;
	end->next = NULL:
	delete pointer;
}

template<class T>
void LinkedList<T>::deleteElement(int index) {
	if (index < 0 || index >= size) {
		std::cout << "Can't delete an illegal element" << std::endl;
	}
	else if (start == end) {
		element<T> *ptr = start;
		start = end = NULL;
		delete ptr;
		--size;
	}
	else if (index == 0) {
		element<T> *ptr = start;
		start = start->next;
		start->prev = NULL;
		--size;
		delete ptr;
	}
	else if (index == size - 1) {
		element<T> *ptr = end;
		end = end->prev;
		end->next = NULL;
		--size;
		delete ptr;
	}
	else {
		element<T> *pointer = NULL, *pointer2 = NULL, *pointer1 = start->next;
		int counter = 1;
		while (counter < index) {
			pointer1 = pointer1->next;
			counter++;
		}
		pointer = pointer1->prev;
		pointer2 = pointer1->next;
		// Here I do something
		pointer->next = pointer2;
		pointer2->prev = pointer;
		// Some help pointers
		pointer1->prev = NULL;
		pointer1->next = NULL;
		--size;
		delete pointer1;
	}
}

#endif // LINKEDLIST_H_INCLUDED
