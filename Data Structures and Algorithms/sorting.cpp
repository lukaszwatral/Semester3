#include <iostream>
#include <time.h>
#include <random>
#include <cstdlib>

template<typename T>
bool cmp(T a, T b) {
	return a > b;
}

struct some_object {
	double field1;
	char field2;
};


bool so_cmp(some_object* a, some_object* b) {
	if (a->field1 > b->field1) return true;
	else if (a->field1 < b->field1) return false;
	else {
		if ((int)a->field2 > (int)b->field2) return true;
		else return false;
	}
}


template<typename T>
class dynamic_array {
public:
	T* array;
	int size, max_size;
	dynamic_array(T* arr = nullptr, int s = 0, int ms = 1) : array(arr), max_size(ms), size(s) {

		if (!array) {
			array = new T[max_size];
		}
	}
	~dynamic_array() {
		if (array != nullptr)
			delete[] array;
	}

	T& operator[](int index) {
		return array[index];
	}

	void add_back(T value); //a
	T show(int i); //b
	void update(int i, T value); //c
	void clear_array(); //d
	void string_display(); //e
	template<typename C>
	void bubble_sort(C cmp); //f

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
		arr = new dynamic_array<T>();
	}
	template<typename C>
	BinaryHeap(T* array, int s, C cmp, bool fix = true) {
		arr = new dynamic_array<T>(array, s, s);
		if (fix) {
			bottom_up(cmp);
		}
		else {
			top_down(cmp);
		}
	}

	~BinaryHeap() {};

	dynamic_array<T>* arr;
	template<typename C>
	void add(T val, C cmp) { //a
		arr->add_back(val);
		heapify_up(arr->size - 1, cmp);
	}
	template<typename C>
	T remove_max(C cmp) { //b
		if (arr->size <= 0) {
			std::cout << "Heap is empty!" << std::endl;
			return NULL;
		}
		else if (arr->size == 1) {
			T tmp = arr->show(0);
			arr->update(0, NULL);
			arr->decrement_size();
			return tmp;
		}
		else {
			T tmp = arr->show(0);
			arr->update(0, arr->show(arr->size - 1));
			arr->update(arr->size - 1, NULL);
			arr->decrement_size();
			heapify_down(0, cmp);
			return tmp;
		}

	}
	void clear_heap() { //c
		arr->clear_array();
	}
	void string_display() { //d
		arr->string_display();
	}
	template<typename C>
	void heapify_up(int index, C cmp) { //e
		if (index < 0 || index >= arr->size) {
			return;
		}
		else {
			int parentIndex = (index - 1) / 2;
			if (cmp(arr->show(index),arr->show(parentIndex))) {
				arr->swap(index, parentIndex);
				heapify_up(parentIndex, cmp);
			}
			else {
				return;
			}
		}
	}
	template<typename C>
	void heapify_down(int index, C cmp) { //f
		if (index < 0 || index >= arr->size) {
			return;
		}
		else {
			int leftIndex = 2 * index + 1;
			int rightIndex = 2 * index + 2;
			int tmp = index;
			if (leftIndex < arr->size && cmp(arr->show(leftIndex),arr->show(tmp))) {
				tmp = leftIndex;
			}
			if (rightIndex < arr->size && cmp(arr->show(rightIndex),arr->show(tmp))) {
				tmp = rightIndex;
			}

			if (arr->show(tmp) != arr->show(index)) {
				arr->swap(tmp, index);
				heapify_down(tmp, cmp);
			}
		}
	}
	template<typename C>
	void bottom_up(C cmp) {
		for (int i = (arr->size - 1); i >= 0; i--) {
			heapify_down(i, cmp);
		}
	}
	template<typename C>
	void top_down(C cmp) {
		for (int i = 0; i < arr->size; i++) {
			heapify_up(i, cmp);
		}
	}
	template<typename C>
	void sort(C cmp) {
		int size = arr->size;
		if (size <= 1) {
			return;
		}

		for (int i = 1; i <= size; i++) {
			arr->swap(0, size - i);
			arr->size--;
			heapify_down(0, cmp);
		}
		arr->size = size;
	}
};



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
template<typename C>
void dynamic_array<T>::bubble_sort(C cmp) { //f
	T tmp;
	for (int i = 0; i < size; i++) {
		bool flag = false;
		for (int j = 0; j < size - 1; j++) {
			if (cmp(array[j], array[j + 1])) {
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

template<typename T>
void to_string(T* tab, int size) {
	if (size > 10) {
		for (int i = 0; i < 5; i++) {
			std::cout << tab[i] << " ";
		}
		std::cout << " ... ";
		for (int i = (size - 5); i < size; i++) {
			std::cout << tab[i] << " ";
		}
	}
	else {
		for (int i = 0;i < size; i++) {
			std::cout << tab[i] << " ";
		}
	}
}

void to_string_obj(some_object** tab, int size) {
	if (size > 10) {
		for (int i = 0; i < 5; i++) {
			std::cout << "{" << tab[i]->field1 << ":" << tab[i]->field2 << "}" << " ";
		}
		std::cout << " ... ";
		for (int i = (size - 5); i < size; i++) {
			std::cout << "{" << tab[i]->field1 << ":" << tab[i]->field2 << "}" << " ";
		}
	}
	else {
		for (int i = 0;i < size; i++) {
			std::cout << "{" << tab[i]->field1 << ":" << tab[i]->field2 << "}" << " ";
		}
	}
}

void counting_sort(int* tab, int n, int m) {
	int* cnt = new int[m];
	for (int i = 0; i < m; i++) {
		cnt[i] = 0;
	}
	for (int i = 0; i < n; i++) {
		cnt[tab[i]]++;
	}
	int a = 0;
	for (int i = 0; i < m; i++) {
		while (cnt[i] > 0) {
			tab[a] = i;
			a++;
			cnt[i]--;
		}
	}
	delete[] cnt;
}

void bucket_sort(int* tab, int n, int m) {
	dynamic_array<int>* buckets = new dynamic_array<int>[n];
	double w = (double)m / (double)n;
	for (int i = 0; i < n; i++) {
		int bucketIdx = tab[i] / w;
		buckets[bucketIdx].add_back(tab[i]);
	}

	int k = 0;
	for (int i = 0; i < n; i++) {
		buckets[i].bubble_sort(cmp<int>);
		for (int j = 0; j < buckets[i].size; j++) {
			tab[k] = buckets[i][j];
			k++;
		}
	}
}

template<typename C>
void bucket_sort_obj(some_object** tab, int n, float m, C cmp) {
	dynamic_array<some_object*>* buckets = new dynamic_array<some_object*>[n];
	double w = (double)m / (double)n;
	for (int i = 0; i < n; ++i) {
		int bucketIdx = tab[i]->field1 / w;
		buckets[bucketIdx].add_back(tab[i]);
	}

	int k = 0;
	for (int i = 0; i < n; i++) {
		buckets[i].bubble_sort(cmp);
		for (int j = 0; j < buckets[i].size; j++) {
			tab[k] = buckets[i][j];
			k++;
		}
	}
}


void judge_int(int* arr1, int* arr2, int* arr3, int n) {
	bool flag = false;
	for (int i = 0; i < n; i++) {
		if (arr1[i] != arr2[i] || arr1[i] != arr3[i] || arr2[i] != arr3[i]) {
			flag = true;
		}
			if (flag) {
				std::cout << "\n" << "ARRAYS ARE NOT EQUAL!" << "\n";
				return;
			}
	}
	std::cout << "\n" << "ARRAYS ARE EQUAL!" << "\n";
}


void judge_obj(some_object** arr1, some_object** arr2, int n) {
	bool flag = false;
	for (int i = 0; i < n; i++) {
		if (arr1[i]->field1 != arr2[i]->field1 || arr1[i]->field2 != arr2[i]->field2 ) {
			flag = true;
		}
		if (flag) {
			std::cout << "\n" << "ARRAYS ARE NOT EQUAL!" << "\n";
			return;
		}
	}
	std::cout << "\n" << "ARRAYS ARE EQUAL!" << "\n";
}

//int main()
//{
//	srand(0);
//	const int MAX_ORDER = 7;
//	const int m = (int)pow(10, 7);
//	for (int o = 1; o <= MAX_ORDER; o++)
//	{
//		const int n = (int)pow(10, o);
//		std::cout << "\n" << "------------------------------------------";
//		std::cout << "\n" << "Size: 10^" << o << "\n";
//		int* array1 = new int[n];
//		for (int i = 0; i < n; i++)
//		{
//			int rand_val = ((rand() << 15) + rand()) % m;
//				array1[i] = rand_val;
//		}
//		std::cout << "\n" << "ARRAY: " << "\n";
//		to_string(array1, n);
//		int* array2 = new int[n];
//		int* array3 = new int[n];
//		memcpy(array2, array1, n * sizeof(int));
//		memcpy(array3, array1, n * sizeof(int));
//		std::cout << "\n\n" << "COUNTING SORT" << "\n";
//		clock_t t1 = clock();
//		counting_sort(array1, n, m);
//		clock_t t2 = clock();
//		to_string(array1, n);
//		std::cout << "\n" << "TIME: " << (double)((double)(t2 - t1) / CLOCKS_PER_SEC) << "\n";
//		std::cout << "\n" << "HEAP SORT" << "\n";
//			t1 = clock();
//		BinaryHeap<int>* bh = new BinaryHeap < int >(array2, n, cmp<int>, true);
//		bh->sort(cmp<int>);
//		t2 = clock();
//		to_string(array2, n);
//		std::cout << "\n" << "TIME: " << (double)((double)(t2 - t1) / CLOCKS_PER_SEC) << "\n";
//		std::cout << "\n" << "BUCKET SORT" << "\n";
//			t1 = clock();
//		bucket_sort(array3, n, m);
//		t2 = clock();
//		to_string(array3, n);
//		std::cout << "\n" << "TIME: " << (double)((double)(t2 - t1) / CLOCKS_PER_SEC) << "\n";
//		judge_int(array1, array2, array3, n);
//		delete bh;
//		delete[] array1;
//		delete[] array2;
//		delete[] array3;
//	}
//}

int main() {
	srand(0);
	const int MAX_ORDER = 7;
	const double m_double = (double)pow(2, 30);
		for (int o = 1; o <= MAX_ORDER; o++)
		{
			const int n = (int)pow(10, o);
			std::cout << "\n" << "------------------------------------------";
			std::cout << "\n" << "Size: 10^" << o << "\n";
			some_object** array1 = new some_object * [n];
			for (int i = 0; i < n; i++)
			{
				some_object* so = new some_object();
				so->field1 = ((rand() << 15) + rand()) / m_double;
				so->field2 = 'a' + rand() % 26;
				array1[i] = so;
			}
			std::cout << "\n" << "ARRAY: " << "\n";
			to_string_obj(array1, n);
			some_object** array2 = new some_object*[n];
			memcpy(array2, array1, n * sizeof(some_object*));
			std::cout << "\n\n" << "HEAP SORT" << "\n";
			clock_t t1 = clock();
			BinaryHeap<some_object*>* bh = new BinaryHeap<some_object*>(array1, n, so_cmp, true);
			bh->sort(so_cmp);
			clock_t t2 = clock();
			to_string_obj(array1, n);
			std::cout << "\n" << "TIME: " << (double)((double)(t2 - t1) / CLOCKS_PER_SEC) << "\n";
			std::cout << "\n\n" << "BUCKET SORT" << "\n";
			t1 = clock();
			bucket_sort_obj(array2, n, 1.0, so_cmp);
			t2 = clock();
			to_string_obj(array2, n);
			std::cout << "\n" << "TIME: " << (double)((double)(t2 - t1) / CLOCKS_PER_SEC) << "\n";
			judge_obj(array1, array2, n);
			delete bh;
			delete[] array1;
			delete[] array2;
		}
}