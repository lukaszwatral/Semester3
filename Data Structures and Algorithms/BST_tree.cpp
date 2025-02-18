#include <iostream>
#include <time.h>
#include <windows.h>
#include <vector>

template<typename T>
class Node {
public:
	T data;
	int ID;
	Node<T>* parent;
	Node<T>* left;
	Node<T>* right;
	Node(T value, size_t id) {
		this->data = value;
		this->ID = id;
		this->parent = nullptr;
		this->left = nullptr;
		this->right = nullptr;
	}

	friend std::ostream& operator<<(std::ostream& os, const Node& obj) {
		os << obj.ID << ": [p: " << (obj.parent == nullptr ? -1 : obj.parent->ID) << ", l: " << (obj.left == nullptr ? -1 : obj.left->ID) << ", r: " << (obj.right == nullptr ? -1 : obj.right->ID) << "], data: " << obj.data << std::endl;
		//os << obj.ID << ": [p: " << (obj.parent == nullptr ? -1 : obj.parent->data) << ", l: " << (obj.left == nullptr ? -1 : obj.left->data) << ", r: " << (obj.right == nullptr ? -1 : obj.right->data) << "], data: " << obj.data << std::endl;
		return os;
	}
};

template<typename T>
class binary_search_tree {
private:
	
	Node<T>* find_min(Node<T>* node) {
		Node<T>* tmp = node;
		Node<T>* prev = nullptr;
		while (tmp->left != nullptr) {
			prev = tmp;
			tmp = tmp->left;
		}
		return tmp;
	}

	Node<T>* find_max(Node<T>* node) {
		Node<T>* tmp;
		while (tmp->right != nullptr) {
			tmp = tmp->right;
		}
		return tmp;
	}

	Node<T>* predecessor(Node<T>* node) {
		if (node->left == nullptr) {
			return node->right;
		}
		else {
			Node<T>* tmp = node->left;
			Node<T>* prev = nullptr;
			while (tmp != nullptr) {
				prev = tmp;
				tmp = tmp->right;
			}
			return prev;
		}
	}
	
	Node<T>* successor(Node<T>* node) {
		if (node->right->left == nullptr) {
			return node->right;
		}
		else {
			Node<T>* tmp = node->right;
			Node<T>* prev = nullptr;
			while (tmp != nullptr) {
				prev = tmp;
				tmp = tmp->left;
			}
			return prev;
		}
	}
public:
	Node<T>* root;
	int size;
	binary_search_tree() {
		this->root = nullptr;
		this->size = 0;
	}

	~binary_search_tree() {
		clear_tree();
	}

	Node<T>* get_successor(Node<T>* node) {
		return successor(node);
	}

	std::vector<Node<T>> vec;
	void insert(T value); //a
	Node<T>* find(T value); //b
	void remove(Node<T>* node); //c
	void pre_order(Node<T>* root); //d
	void in_order(Node<T>* root); //e
	void clear_tree(); //f
	int tree_height(Node<T>* root); //g
	void string_pre_order(Node<T>* root);
	void string_display(); //h
};

//int main() {
//	int choice;
//	int val;
//	binary_search_tree<int>* bst = new binary_search_tree<int>();
//		bst->insert(10);
//		bst->insert(15);
//		bst->insert(12);
//		bst->insert(5);
//		bst->insert(30);
//		bst->insert(25);
//		bst->insert(35);
//		bst->insert(7);
//		bst->insert(-2);
//		bst->insert(33);
//
//		while (true) {
//			system("cls");
//			std::cout << "1. insert element" << std::endl;
//			std::cout << "2. find element" << std::endl;
//			std::cout << "3. remove element" << std::endl;
//			std::cout << "4. pre-order" << std::endl;
//			std::cout << "5. in-order" << std::endl;
//			std::cout << "6. clear tree" << std::endl;
//			std::cout << "7. tree height" << std::endl;
//			std::cout << "8. string display" << std::endl;
//			std::cout << "9. insert many elements"<< std::endl;
//			std::cout << "0. exit"<< std::endl;
//			std::cout << "choice: ";
//			std::cin >> choice;
//			std::cout << std::endl;
//			switch (choice) {
//			case 1:
//				std::cout << "value: ";
//				std::cin >> val;
//				bst->insert(val);
//				break;
//
//			case 2:
//				std::cout << "value: ";
//				std::cin >> val;
//				std::cout << bst->find(val)->ID << std::endl;
//				system("pause");
//				break;
//
//			case 3:
//				std::cout << "value: ";
//				std::cin >> val;
//				bst->remove(bst->find(val));
//				break;
//
//			case 4:
//				bst->pre_order(bst->root);
//				system("pause");
//				break;
//
//			case 5:
//				bst->in_order(bst->root);
//				system("pause");
//				break;
//
//			case 6:
//				bst->clear_tree();
//				break;
//
//			case 7:
//				std:: cout << "height: " << bst->tree_height(bst->root) << std::endl;
//				system("pause");
//				break;
//
//			case 8:
//				bst->string_display();
//				system("pause");
//				break;
//
//			case 9:
//				std::cout << "how many elements: ";
//				std::cin >> val;
//				for (int i = 0; i < val; i++) {
//					bst->insert(std::rand());
//				}
//				break;
//
//			case 0:
//				delete bst;
//				return 0;
//				break;
//
//			default:
//				std::cout << "wrong choice!";
//				Sleep(2000);
//				break;
//			}
//		}
//		
//}


int main()
{
	std::srand(std::time(NULL));
	const int MAX_ORDER = 7;
	clock_t t1, t2, t3, t4, t5, t6, t7, t8, t9, t10;
	binary_search_tree<int>* bst = new binary_search_tree <int>();
		for (int o = 1; o <= MAX_ORDER; o++)
		{
			const int n = pow(10, o);
			t1 = clock();
			for (int i = 0; i < n; i++)
			{
				bst->insert(std::rand()%1000);
			}
			t2 = clock();
			bst->string_display();
			std::cout << "Adding time: " << (double)(t2 - t1) / CLOCKS_PER_SEC;
			const int m = pow(10, 4);
			int hits = 0;
			t1 = clock();
			for (int i = 0; i < m; i++)
			{
				Node<int>* result = bst->find(std::rand()%1000001);
				if (result != NULL)
				hits++;
			}
			t2 = clock();
			t3 = clock();
			for (int i = 0; i < m; i++)
			{
				bst->in_order(bst->root);
			}
			t4 = clock();
			t5 = clock();
			for (int i = 0; i < m; i++)
			{
				bst->pre_order(bst->root);
			}
			t6 = clock();
			t9 = clock();
			for (int i = 0; i < m; i++)
			{
				bst->remove(bst->find(1));
			}
			t10 = clock();
			std::cout << std::endl << "Finding time: " << (double)(t2 - t1) / CLOCKS_PER_SEC << std::endl;
			std::cout << "Hits: " << hits << std::endl;
			std::cout << "Removing time: " << (double)(t10 - t9) / CLOCKS_PER_SEC << std::endl;
			std::cout << "In-order time: " << (double)(t4 - t3) / CLOCKS_PER_SEC << std::endl;
			std::cout << "Pre-order time: " << (double)(t6 - t5) / CLOCKS_PER_SEC << std::endl;
			t7 = clock();
			bst->clear_tree();
			t8 = clock();
			std::cout << "Clear time : " << (double)(t8 - t7) / CLOCKS_PER_SEC << std::endl;
		}

	delete bst;
	return 0;
}


template<typename T>
void binary_search_tree<T>::insert(T value) {
	Node<T>* newNode = new Node<T>(value, size);
	if (root == nullptr) {
		root = newNode;
		size++;
		return;
	}
	Node<T>* tmp = root;
	Node<T>* prev = nullptr;
	while (tmp != nullptr) {
		if (tmp->data == value) {
			//std::cout << "Value " << value << " already exists!" << std::endl;
			return;
		}
		prev = tmp;
		if (tmp->data < value) {
			tmp = tmp->right;
		}
		else {
			tmp = tmp->left;
		}
	}
	if(prev->data < value){
		prev->right = newNode;
	}
	else {
		prev->left = newNode;
	}
	newNode->parent = prev;
	size++;
}

template<typename T>
Node<T>* binary_search_tree<T>::find(T value) {
	bool found = false;
	Node<T>* tmp = root;
	while (tmp != nullptr && found != true) {
		if (tmp->data == value) {
			found = true;
		}
		else if (tmp->data < value) {
			tmp = tmp->right;
		}
		else {
			tmp = tmp->left;
		}
	}
	if (found) {
		return tmp;
	}
	else {
		return NULL;
	}
}

template<typename T>
void binary_search_tree<T>::remove(Node<T>* node) {
	bool flag = true;
	if (node == NULL) { //empty tree
		return;
	}
	if (node->right == nullptr && node->left == nullptr) { //no children
		if (node->parent != nullptr) {
			if (node->parent->right == node) {
				node->parent->right = nullptr;
			}
			else {
				node->parent->left = nullptr;
			}
			flag = false;
		}
		delete node;
		if (flag) {
			root = nullptr;

		}
		size--;
	}
	else if (node->right == nullptr && node->left != nullptr) { //1 child
		Node<T>* tmp = node->left;
		tmp->parent = node->parent;
		if (node != root) {
			if (node->parent->data < tmp->data) {
				node->parent->right = tmp;
			}
			else {
				node->parent->left = tmp;
			}
			flag = false;
		}
		delete node;
		if (flag) {
			root = tmp;
		}
		size--;
	}
	else if (node->right != nullptr && node->left == nullptr) { //1 child
		Node<T>* tmp = node->right;
		tmp->parent = node->parent;
		if (node != root) {
			if (node->parent->data < tmp->data) {
				node->parent->right = tmp;
			}
			else {
				node->parent->left = tmp;
			}
			flag = false;
		}
		delete node;
		if (flag) {
			root = tmp;
		}
		size--;
	}
	else { //2 children
		Node<T>* suc = successor(node);
		suc->left = node->left;
		node->left->parent = suc;
		if (suc != node->right) {
			if (suc->right != nullptr) {
				suc->right->parent = suc->parent;
			}
			suc->parent->left = suc->right;
			suc->right = node->right;
			node->right->parent = suc;
		}
		suc->parent = node->parent;
		if (suc->parent != nullptr) {
			node->parent->right = suc;
			flag = false;
		}
		delete node;
		if(flag){
			root = suc;
		}
		size--;
	}
}

template<typename T>
void binary_search_tree<T>::pre_order(Node<T>* root) {
	if (size == 0) {
		std::cout << "Tree is empty!";
	}
	else {
		if (root == nullptr) {
			return;
		}
		//std::cout << root->data << " ";
		pre_order(root->left);
		pre_order(root->right);
	}
}

template<typename T>
void binary_search_tree<T>::in_order(Node<T>* root) {
	if (root == nullptr) {
		return;
	}
	in_order(root->left);
	//std::cout << root->data << " ";
	in_order(root->right);
}

template<typename T>
void binary_search_tree<T>::clear_tree() {
	if (size == 0) {
		return;
	}
	else {
		while (size > 0) {
			remove(this->root);
		}
	}
}
template<typename T>
int binary_search_tree<T>::tree_height(Node<T>* root) {
	if (root == nullptr) {
		return -1;
	}
	int left_height = tree_height(root->left);
	int right_height = tree_height(root->right);
	if (left_height > right_height) {
		return left_height + 1;
	}
	else {
		return right_height + 1;
	}
}

template<typename T>
void binary_search_tree<T>::string_pre_order(Node<T>* root) {
		if (root == nullptr) {
			return;
		}
		vec.push_back(*root);
		string_pre_order(root->left);
		string_pre_order(root->right);
}
template<typename T>
void binary_search_tree<T>::string_display() {
	std::cout << std::endl << "-------------------BST-------------------" << std::endl;
	if (size == 0) {
		std::cout << "Tree is empty!" << std::endl;
	}
	else {
		std::cout << "Size: " << size << ", height: " << tree_height(this->root) << std::endl;
		string_pre_order(this->root);
		if (size <= 15) {
			for (int i = 0; i < 15; i++) {
				if (i >= size) {
					break;
				}
				std::cout << vec[i];
			}
		}
		else {
			for (int i = 0; i < 3; i++) {
				std::cout << vec[i];
			}
			std::cout << "..." << std::endl;
			for (int i = (size - 3); i < size; i++) {
				std::cout << vec[i];
			}
		}
		vec.clear();
	}
}