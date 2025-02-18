#include <iostream>
#include <time.h>
#include <random>

template<typename T>
class dynamic_array {
private:
	int size, max_size;
	T* array;
public:
	dynamic_array() {
		this->size = 0;
		this->max_size = 1;
		array = new T[max_size];
	}
	~dynamic_array() {
		delete[] array;
	}

	int get_size() {
		return size;
	}

	int get_max_size() {
		return max_size;
	}

	void add_back(T value); //a
	T show(int i); //b
	void update(int i, T value); //c
	void clear_array(); //d
	void string_display(); //e
	void bubble_sort(); //f

	void decrement_size() {
		size--;
	}

	void swap(int a, int b) {
		T tmp = array[a];
		array[a] = array[b];
		array[b] = tmp;
	}

};

template<typename T>
class BinaryHeap {
public:
	BinaryHeap() {
		arr = new dynamic_array<T>;
	}
	
	~BinaryHeap() {
		clear_heap();
	}

	dynamic_array<T>* arr;
	void add(T val); //a
	T remove_max(); //b
	void clear_heap(); //c
	void string_display(); //d
	void heapify_up(int index); //e
	void heapify_down(int index); //f
};

int main() {//////////////////////////////////////////////////////////////////////////////////////
	BinaryHeap<int>* bh = new BinaryHeap<int>();
	int choice;
	clock_t t1, t2;
	srand(std::time(NULL));
	while (1) {
		system("cls");
		std::cout << "1. Add element" << std::endl;
		std::cout << "2. Remove max value" << std::endl;
		std::cout << "3. Clear heap" << std::endl;
		std::cout << "4. String display" << std::endl;
		std::cout << "5. Add many elements" << std::endl;
		std::cout << "0. Exit" << std::endl;
		std::cout << "Choice: ";
		std::cin >> choice;
		switch (choice) {
		case 1:
			int val;
			std::cout << "Value: ";
			std::cin >> val;
			t1 = clock();
			bh->add(val);
			t2 = clock();
			std::cout << "Adding time: " << (double)(t2 - t1) / CLOCKS_PER_SEC << std::endl;
			system("pause");
			break;
		case 2:
			t1 = clock();
			std::cout << "Removed element: " << bh->remove_max() << std::endl;
			t2 = clock();
			std::cout << "Finding and removing time: " << (double)(t2 - t1) / CLOCKS_PER_SEC << std::endl;
			system("pause");
			break;
		case 3:
			t1 = clock();
			bh->clear_heap();
			t2 = clock();
			std::cout << "Clearing time: " << (double)(t2 - t1) / CLOCKS_PER_SEC << std::endl;
			system("pause");
			break;
		case 4:
			bh->string_display();
			system("pause");
			break;
		case 5:
			int n;

			std::cout << "How many elements? ";
			std::cin >> n;
			t1 = clock();
			for (int i = 0; i < n; i++) {
				bh->add(std::rand()*std::rand());
			}
			t2 = clock();
			std::cout << "Adding time: " << (double)(t2 - t1) / CLOCKS_PER_SEC << std::endl;
			system("pause");
			break;
		case 0:
			return 0;
			break;
		default:
			break;
		}
	}
	delete bh;
	return 0;
}

template<typename T>
void BinaryHeap<T>::add(T val) { //a
	arr->add_back(val);
	heapify_up(arr->get_size() - 1);
}

template<typename T>
T BinaryHeap<T>::remove_max(){ //b
	if (arr->get_size() <= 0) {
		std::cout << "Heap is empty!" << std::endl;
		return NULL;
	}
	else if(arr->get_size() == 1) {
		T tmp = arr->show(0);
		arr->update(0, NULL);
		arr->decrement_size();
		return tmp;
	}
	else {
		T tmp = arr->show(0);
		arr->update(0, arr->show(arr->get_size() - 1));
		arr->update(arr->get_size() - 1, NULL);
		arr->decrement_size();
		heapify_down(0);
		return tmp;
	}

}

template<typename T>
void BinaryHeap<T>::clear_heap() { //c
	arr->clear_array();
}

template<typename T>
void BinaryHeap<T>::string_display() { //d
	arr->string_display();
}

template<typename T>
void BinaryHeap<T>::heapify_up(int index) { //e
	if (index < 0 || index >= arr->get_size()) {
		return;
	}
	else {
		int parentIndex = (index - 1) / 2;
		if ((arr->show(index)) > (arr->show(parentIndex))) {
			arr->swap(index, parentIndex);
			heapify_up(parentIndex);
		}
		else {
			return;
		}
	}
}

template<typename T>
void BinaryHeap<T>::heapify_down(int index) { //f
	if (index < 0 || index >= arr->get_size()) {
		return;
	}
	else {
		int leftIndex = 2 * index + 1;
		int rightIndex = 2 * index + 2;
		int tmp = index;
		if (leftIndex < arr->get_size() && arr->show(leftIndex) > arr->show(tmp)) {
			tmp = leftIndex;
		}
		if (rightIndex < arr->get_size() && arr->show(rightIndex) > arr->show(tmp)) {
			tmp = rightIndex;
		}

		if (arr->show(tmp) != arr->show(index)) {
			arr->swap(tmp, index);
			heapify_down(tmp);
		}
	}
}


template<typename T>
void dynamic_array<T>::add_back(T value) { //a
	if (size >= max_size) {
		max_size *= 2;
		T* tmp = new T[max_size];
		for (int i = 0; i < size; i++) {
			tmp[i] = array[i];
		}
		delete[] array;
		array = tmp;
	}
	array[size] = value;
	size++;
}

template<typename T>
T dynamic_array<T>::show(int i) { //b
	if (i < 0 || i >= size) {
		return NULL;
	}
	else {
		return array[i];
	}
}

template<typename T>
void dynamic_array<T>::update(int i, T value) { //c
	if (size == 0) {
		std::cout << "Array is empty!";
	}
	else if (i < 0 || i >= size) {
		//std::cout << "Index out of range!" << std::endl;
	}
	else {
		array[i] = value;
	}
}

template<typename T>
void dynamic_array<T>::clear_array() { //d
	delete[] array;
	size = 0;
	max_size = 1;
	array = new T[max_size];
}

template<typename T>
void dynamic_array<T>::string_display() { //e
	std::cout << "--------------------Array--------------------" << std::endl;
	if (size == 0) {
		std::cout << "Array is empty!" << std::endl;
	}
	else {
		std::cout << "Size: " << size << ", max size: " << max_size << ", address: " << this << std::endl;
		std::cout << "Elements: " << std::endl;
		if (size <= 10) {
			for (int i = 0; i < size; i++) {
				std::cout << i << ". " << array[i] << std::endl;
			}
		}
		else {
			for (int i = 0; i < 5; i++) {
				std::cout << i << ". " << array[i] << std::endl;
			}
			std::cout << "..." << std::endl;
			for (int i = (size - 5); i < size; i++) {
				std::cout << i << ". " << array[i] << std::endl;
			}
		}
	}
}

template<typename T>
void dynamic_array<T>::bubble_sort() { //f
	T tmp;
	for (int i = 0; i < size; i++) {
		bool flag = false;
		for (int j = 0; j < size - 1; j++) {
			if (array[j] > array[j + 1]) {
				tmp = array[j + 1];
				array[j + 1] = array[j];
				array[j] = tmp;
				flag = true;
			}
		}
		if (flag == 0) {
			break;
		}
	}

}