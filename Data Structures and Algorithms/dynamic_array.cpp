#include <iostream>
#include <time.h>

template<typename T>
class dynamic_array {
private:
	size_t size, max_size;
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

	size_t get_size() {
		return size;
	}

	size_t get_max_size() {
		return max_size;
	}

	void add_back(T value); //a
	void show(int i); //b
	void update(int i, T value); //c
	void clear_array(); //d
	void string_display(); //e
	void bubble_sort(); //f
};


int main()
{

	srand(time(NULL));
	dynamic_array <int>* da = new dynamic_array <int>();
	const int order = 7;
	double update_all = 0.0;
	double show_all = 0.0;
	const int n = pow(10, order);
	clock_t t1, t2, t3, t4, t5, t6;
	clock_t time_adding_begin, time_adding_end, time_all_end;
	double worst_adding_time = 0.0, time_all, time_adding_element;
	clock_t time_all_begin = clock();
	for (int i = 0; i < n; i++) {
		time_adding_begin = clock();
		da->add_back(std::rand() % 10001);
		time_adding_end = clock();
		time_adding_element = (double)(time_adding_end - time_adding_begin) / CLOCKS_PER_SEC;
		if (time_adding_element > worst_adding_time) {
			worst_adding_time = time_adding_element;
			std::cout << "New worst adding time: " << worst_adding_time << ", index: " << da->get_size() << std::endl;
		}
		t1 = clock();
		da->show(std::rand());
		t2 = clock();
		show_all += (double)(t2 - t1) / CLOCKS_PER_SEC;
		t3 = clock();
		da->update(std::rand(), std::rand());
		t4 = clock();
		update_all += (double)(t4 - t3) / CLOCKS_PER_SEC;
	}
	time_all_end = clock();
	time_all = (double)(time_all_end - time_all_begin) / CLOCKS_PER_SEC;
 	std::cout << "Total adding time: " << time_all << std::endl;
	std::cout << "Worst adding time: " << worst_adding_time << std::endl;
	da->string_display();
	t5 = clock();
	da->clear_array();
	t6 = clock();
	std::cout << "Show time: " << show_all << std::endl;
	std::cout << "Update time: " << update_all << std::endl;
	std::cout << "Clear time: " << (double)(t6 - t5) / CLOCKS_PER_SEC << std::endl;
	delete da;
	return 0;
}

/*
int main() {
	dynamic_array<int>* da = new dynamic_array<int>();
	srand(time(NULL));
	for (int i = 0; i < 10; i++) {
		da->add_back(std::rand());
	}
	da->string_display();
	da->add_back(99);
	da->string_display();
	std::cout << std::endl;
	da->show(14);
	std::cout << std::endl;
	da->update(4, 77);
	da->string_display();
	da->clear_array();
	da->string_display();
}
*/

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
void dynamic_array<T>::show(int i) { //b
	if (size == 0) {
		std::cout << "Array is empty!" << std::endl;
	}
	else if (i < 0 || i >= size) {
		//std::cout << "Index out of range!" << std::endl;
	}
	else {
		//std::cout << array[i] << std::endl;
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
				std::cout << array[i] << std::endl;
			}
		}
		else {
			for (int i = 0; i < 5; i++) {
				std::cout << array[i] << std::endl;
			}
			std::cout << "..." << std::endl;
			for (int i = (size - 5); i < size; i++) {
				std::cout << array[i] << std::endl;
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