#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Node {
	int id;
	double x;
	double y;
};

struct Edge {
	int id;
	Node* n1;
	Node* n2;
	double cost;
};

bool ecmp(Edge* e1, Edge* e2) {
	return e1->cost < e2->cost;
}


template<typename T>
class dynamic_array {
public:
	T* arr;
	int size, max_size;
	dynamic_array() {
		this->size = 0;
		this->max_size = 1;
		arr = new T[max_size];
	}
	~dynamic_array() {
		if (arr != nullptr)
			delete[] arr;
	}

	T operator[](int index) {
		if (index < 0 || index >= size) {
			return NULL;
		}
		else {
			return arr[index];
		}
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
	template<typename C>
	void bubble_sort(C cmp); //f

	void decrement_size() {
		size--;
	}

	void swap(int a, int b) {
		T tmp = arr[a];
		arr[a] = arr[b];
		arr[b] = tmp;
	}

	template<typename C>
	void merge_sort(C cmp) {
		if (size <= 1) {
			return;
		}
			int mid = size / 2;

			dynamic_array<T> leftarr;
			dynamic_array<T> rightarr;

			for (int i = 0; i < mid; i++) {
				leftarr.add_back(arr[i]);
			}

			for (int i = mid; i < size; i++) {
				rightarr.add_back(arr[i]);
			}

			leftarr.merge_sort(cmp);
			rightarr.merge_sort(cmp);

			int i = 0;
			int l = 0;
			int r = 0;

			while (l < leftarr.size && r < rightarr.size) {
				if (cmp(leftarr[l], rightarr[r])) {
					arr[i] = leftarr[l];
					i++;
					l++;
				}
				else {
					arr[i] = rightarr[r];
					i++;
					r++;
				}
			}

			while (l < leftarr.size) {
				arr[i] = leftarr[l];
				i++;
				l++;
			}

			while (r < rightarr.size) {
				arr[i] = rightarr[r];
				i++;
				r++;
			}
		}
};





class UnionFind {
public:
    dynamic_array<int>* index = new dynamic_array<int>();
    dynamic_array<int>* rank = new dynamic_array<int>();
	UnionFind(int n) {
		for (int i = 0;i < n;i++) {
			index->add_back(i);
			rank->add_back(0);
		}
	}
	~UnionFind() {
		delete index;
		delete rank;
	}

	void unionclassic(int i, int j) {
			index->update(findpc(i), findpc(j));
	}

	void unionbyrank(int i, int j) {
		int I = findpc(i);
		int J = findpc(j);
		if (I != J) {
			if (rank->show(I) < rank->show(J)) {
				index->update(I, J);
			}
			else if (rank->show(I) > rank->show(J)) {
				index->update(J, I);
			}
			else {
				index->update(I, J);
				rank->update(J, rank->show(J) + 1);
			}
		}
	}

	int findpc(int i) {
		if (index->show(i) != i) {
			index->update(i, findpc(index->show(i)));
		}
		return (index->show(i));
	}

	int findnopc(int i) {
		if (index->show(i) != i) {
			return findnopc(index->show(i));
		}
		return i;
	}
	
	void string_display() {
		int size = rank->size;
		for (int i = 0; i < size; i++) {
			std::cout << i << "->" << index->show(i) << ", r:" << rank->show(i) << "\n";
		}
	}
};



dynamic_array<Edge*>* Kruskal(dynamic_array<Edge*>* edges, int n) {
	clock_t t1 = clock();
	edges->merge_sort(ecmp);
	clock_t t2 = clock();
	double sort_time = 0.0;
	sort_time = (double)((t2 - t1) / CLOCKS_PER_SEC);
	dynamic_array<Edge*>* result = new dynamic_array<Edge*>();
	UnionFind* UF = new UnionFind(n);
	int cnt = 0;
	t1 = clock();
	for (int i = 0; i < edges->size; i++) {
		if (UF->findpc(edges->show(i)->n1->id) != UF->findpc(edges->show(i)->n2->id)) {
			result->add_back(edges->show(i));
			UF->unionbyrank(edges->show(i)->n1->id, edges->show(i)->n2->id);
		}
		cnt += 2;
	}
	t2 = clock();
	double loop_time = 0.0;
	loop_time = (double)((t2 - t1) / CLOCKS_PER_SEC);
	double cost_sum = 0.0;
	for (int i = 0; i < result->size; i++) {
		cost_sum += result->show(i)->cost;
	}
	std::cout << "Number of edges: " << result->size << ", sum of costs: " << cost_sum << "\n";
	std::cout << "Sorting time: " << sort_time << ", main loop time: " << loop_time << "\n";
	std::cout << "Number of find operation: " << cnt << "\n";
	delete UF;
	return result;
} 


int main()
{
	

	std::ifstream file("g3.txt");
	int nnodes, nedges;
	file >> nnodes;
	dynamic_array<Node*>* nodes = new dynamic_array<Node*>();
	double xx, yy;
	for (int i = 0; i < nnodes; i++) {
		file >> xx >> yy;
		Node* nn = new Node();
		nn->id = i;
		nn->x = xx;
		nn->y = yy;
		nodes->add_back(nn);
	}
	file >> nedges;
	int e1, e2;
	dynamic_array<Edge*>* edges = new dynamic_array<Edge*>();
	for (int i = 0; i < nedges; i++) {
		file >> e1 >> e2 >> xx;
		Edge* ee = new Edge();
		ee->id = i;
		ee->n1 = nodes->show(e1);
		ee->n2 = nodes->show(e2);
		ee->cost = xx;
		edges->add_back(ee);
	}

	file.close();

	std::cout << "MST\n";
	double time = 0.0;
	clock_t t1 = clock();
	dynamic_array<Edge*>* MST = Kruskal(edges, nnodes);
	edges->merge_sort(ecmp);
	clock_t t2 = clock();
	//for (int i = 0; i < (nnodes - 1); i++) {
	//	std::cout << MST->show(i)->n1->id << " " << MST->show(i)->n2->id << " " << MST->show(i)->cost << "\n";
	//	//std::cout << edges->show(i)->n1->id << " " << edges->show(i)->n2->id << " " << edges->show(i)->cost << "\n";
	//}

	time = (double)(t2 - t1) / CLOCKS_PER_SEC;
	std::cout << "Time: " << (double)time;
	delete nodes;
	delete edges;
	

}

template<typename T>
void dynamic_array<T>::add_back(T value) { //a
	if (size >= max_size) {
		max_size *= 2;
		T* tmp = new T[max_size];
		for (int i = 0; i < size; i++) {
			tmp[i] = arr[i];
		}
		delete[] arr;
		arr = tmp;
	}
	arr[size] = value;
	size++;
}

template<typename T>
T dynamic_array<T>::show(int i) { //b
	if (i < 0 || i >= size) {
		return NULL;
	}
	else {
		return arr[i];
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
		arr[i] = value;
	}
}

