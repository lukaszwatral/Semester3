#include <iostream>
#include <time.h>
#include <vector>
#include <ctime>
#include <cstdlib>

template<typename T>
class Node {
public:
	T data;
	int ID;
	Node<T>* parent;
	Node<T>* left;
	Node<T>* right;
	bool color; //red - true; black - false
	Node(T data, int id) {
		this->ID = id;
		this->data = data;
		this->parent = nullptr;
		this->left = nullptr;
		this->right = nullptr;
		this->color = true;
	}

	friend std::ostream& operator<<(std::ostream& os, const Node& obj) {
		os << obj.ID << ": [color: " << obj.color << ", p: " << (obj.parent == nullptr ? -1 : obj.parent->ID) << ", l: " << (obj.left == nullptr ? -1 : obj.left->ID) << ", r: " << (obj.right == nullptr ? -1 : obj.right->ID) << "], data: " << obj.data << std::endl;
		//os << obj.ID << ": [color:" << obj.color << ", p : " << (obj.parent == nullptr ? -1 : obj.parent->data) << ", l : " << (obj.left == nullptr ? -1 : obj.left->data) << ", r : " << (obj.right == nullptr ? -1 : obj.right->data) << "], data: " << obj.data << std::endl;
		return os;
	}
};

template<typename T>
class RBT {
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
	std::vector<Node<T>> vec;
	Node<T>* root;
	int size;
	RBT() {
		this->root = nullptr;
		this->size = 0;
	}
	~RBT() {
		clear_tree(this->root);
	}
	Node<T>* find(T val); //a
	void pre_order(Node<T>* root); //b
	void in_order(Node<T>* root); //c
	void clear_tree(Node<T>* root); //d
	int tree_height(Node<T>* root); //e
	void insert(T val); //f
	void string_display(); //g
	void rotate_left(Node<T>* child, Node<T>* parent); //h
	void rotate_right(Node<T>* child, Node<T>* parent); //i
	void string_pre_order(Node<T>* root);
	void remove(Node<T>* node);
};

int main() {
	clock_t t1, t2;

	srand(time(NULL));
	RBT<int>* rbt = new RBT<int>();
	rbt->insert(10);
	rbt->insert(18);
	rbt->insert(7);
	rbt->insert(15);
	rbt->insert(16);
	rbt->insert(30);
	rbt->insert(25);
	rbt->insert(40);
	rbt->insert(60);
	rbt->insert(2);
	rbt->insert(1);
	rbt->insert(70);
	int choice;
	int val;
	while (true) {
		system("cls");
		std::cout << "1. Find" << std::endl;
		std::cout << "2. Pre-order" << std::endl;
		std::cout << "3. In-order" << std::endl;
		std::cout << "4. Clear tree" << std::endl;
		std::cout << "5. Tree height" << std::endl;
		std::cout << "6. Insert" << std::endl;
		std::cout << "7. String display" << std::endl;
		std::cout << "8. Add many elements" << std::endl;
		std::cout << "0. Exit" << std::endl;
		std::cout << "Choice: ";
		std::cin >> choice;
		switch (choice) {
		case 1:
			std::cout << "Value: ";
			std::cin >> val;
			t1 = clock();
			rbt->find(val);
			t2 = clock();
			std::cout << "Finding time: " << (double)(t2 - t1) / CLOCKS_PER_SEC << std::endl;
			system("pause");
			break;
		case 2:
			t1 = clock();
			rbt->pre_order(rbt->root);
			t2 = clock();
			std::cout << "Pre-order time: " << (double)(t2 - t1) / CLOCKS_PER_SEC << std::endl;
			system("pause");
			break;
		case 3:
			t1 = clock();
			rbt->in_order(rbt->root);
			t2 = clock();
			std::cout << "In-order time: " << (double)(t2 - t1) / CLOCKS_PER_SEC << std::endl;
			system("pause");
			break;
		case 4:
			t1 = clock();
			rbt->clear_tree(rbt->root);
			t2 = clock();
			std::cout << "Clearing time: " << (double)(t2 - t1) / CLOCKS_PER_SEC << std::endl;
			system("pause");
			break;
		case 5:
			t1 = clock();
			std::cout << rbt->tree_height(rbt->root);
			t2 = clock();
			std::cout << "Operation time: " << (double)(t2 - t1) / CLOCKS_PER_SEC << std::endl;
			system("pause");
			break;
		case 6:
			std::cout << "Value: ";
			std::cin >> val;
			t1 = clock();
			rbt->insert(val);
			t2 = clock();
			std::cout << "Adding time: " << (double)(t2 - t1) / CLOCKS_PER_SEC << std::endl;
			system("pause");
			break;
			break;
		case 7:
			t1 = clock();
			rbt->string_display();
			t2 = clock();
			std::cout << "Operation time: " << (double)(t2 - t1) / CLOCKS_PER_SEC << std::endl;
			system("pause");
			break;
		case 8:
			std::cout << "How many elements?: ";
			std::cin >> val;
			t1 = clock();
			for (int i = 0; i < val; i++) {
				rbt->insert(std::rand()); //rand ma zakres 0-32767
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
	delete rbt;
}


template<typename T>
Node<T>* RBT<T>::find(T val) { //a
	bool found = false;
	Node<T>* tmp = root;
	while (tmp != nullptr && found != true) {
		if (tmp->data == val) {
			found = true;
		}
		else if (tmp->data < val) {
			tmp = tmp->right;
		}
		else {
			tmp = tmp->left;
		}
	}
	if (found) {
		std::cout << tmp->ID << ": [color: " << tmp->color << ", p: " << (tmp->parent == nullptr ? -1 : tmp->parent->ID) << ", l: " << (tmp->left == nullptr ? -1 : tmp->left->ID) << ", r: " << (tmp->right == nullptr ? -1 : tmp->right->ID) << "], data: " << tmp->data << std::endl;
		return tmp;
	}
	else {
		std::cout << "Nie znaleziono!" << std::endl;
		return NULL;
	}
}

template<typename T>
void RBT<T>::pre_order(Node<T>* root) { //b
	if (size == 0) {
		std::cout << "Tree is empty!";
	}
	else {
		if (root == nullptr) {
			return;
		}
		std::cout << root->data << "\n";
		pre_order(root->left);
		pre_order(root->right);
	}
}

template<typename T>
void RBT<T>::in_order(Node<T>* root) { //c
	if (root == nullptr) {
		return;
	}
	in_order(root->left);
	//std::cout << root->data << " ";
	in_order(root->right);
}

template<typename T>
void RBT<T>::clear_tree(Node<T>* root) { //d
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
int RBT<T>::tree_height(Node<T>* root) { //e
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
void RBT<T>::insert(T val) { //f
	Node<T>* newNode = new Node<T>(val, size);
	if (root == nullptr) {
		root = newNode;
		root->color = false;
		size++;
		return;
	}
	Node<T>* tmp = root;
	Node<T>* prev = nullptr;
	while (tmp != nullptr) {
		if (tmp->data == val) {
			//std::cout << "Value " << value << " already exists!" << std::endl;
			return;
		}
		prev = tmp;
		if (tmp->data < val) {
			tmp = tmp->right;
		}
		else {
			tmp = tmp->left;
		}
	}
	if (prev->data < val) {
		prev->right = newNode;
	}
	else {
		prev->left = newNode;
	}
	newNode->parent = prev;
	size++;
	
	//warunki
	
	if (newNode->parent->color == false) {
		return;
	}
	else {
		while (newNode != nullptr && newNode != root && newNode->parent != nullptr &&newNode->parent->color == true) {
			Node<T>* uncle = nullptr;
			Node<T>* father = newNode->parent;
			Node<T>* grandpa = father->parent;
			if (grandpa != nullptr && father == father->parent->right) {
				uncle = grandpa->left;
			}
			else if (grandpa != nullptr && father == father->parent->left) {
				uncle = grandpa->right;
			}
			if (uncle == nullptr || uncle->color == false) {
				if (grandpa != nullptr && grandpa->left == father && newNode == father->left) {
					rotate_right(father, grandpa);
					father->color = !father->color;
					grandpa->color = !grandpa->color;
				}
				else if (grandpa != nullptr && grandpa->right == father && newNode == father->right) {
					rotate_left(father, grandpa);
					father->color = !father->color;
					grandpa->color = !grandpa->color;
				}
				else if (grandpa != nullptr && grandpa->left == father && newNode == father->right) {
					rotate_left(newNode, father);
					rotate_right(newNode, grandpa);
					newNode->color = !newNode->color;
					grandpa->color = !grandpa->color;
				}
				else if (grandpa != nullptr && grandpa->right == father && newNode == father->left) {
					rotate_right(newNode, father);
					rotate_left(newNode, grandpa);
					newNode->color = !newNode->color;
					grandpa->color = !grandpa->color;
				}
				newNode->parent != nullptr ? newNode = newNode->parent->parent : newNode = nullptr;
			}
			else {
				father->color = !(father->color);
				uncle->color = !(uncle->color);
				if (grandpa != root) {
					grandpa->color = !grandpa->color;
				}
				newNode->parent != nullptr ? newNode = newNode->parent->parent : newNode = nullptr;
			}
		}
	}
}

template<typename T>
void RBT<T>::string_pre_order(Node<T>* root) {
	if (root == nullptr) {
		return;
	}
	vec.push_back(*root);
	string_pre_order(root->left);
	string_pre_order(root->right);
}
template<typename T>
void RBT<T>::string_display() {
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

template<typename T>
void RBT<T>::rotate_left(Node<T>* child, Node<T>* par) { //h
	if (size <= 1 || par == nullptr) {
		return;
	}
	child->parent = par->parent;
	par->right = child->left;
	child->left != nullptr ? child->left->parent = par : child->left = nullptr;
	if (par->parent != nullptr && par->parent->right == par) {
		par->parent->right = child;
	}
	else if(par->parent != nullptr && par->parent->left == par) {
		par->parent->left = child;
	}
	par->parent = child;
	child->left = par;
	if (child->parent == nullptr) {
		this->root = child;
	}
}

template<typename T>
void RBT<T>::rotate_right(Node<T>* child, Node<T>* par) { //i
	if (size <= 1 || par == nullptr) {
		return;
	}
		child->parent = par->parent;
		par->left = child->right;
		child->right != nullptr ? child->right->parent = par : child->right = nullptr;
		if (par->parent != nullptr && par->parent->right == par) {
			par->parent->right = child;
		}
		else if(par->parent != nullptr && par->parent->left == par) {
			par->parent->left = child;
		}
		par->parent = child;
		child->right = par;
		if (child->parent == nullptr) {
			this->root = child;
	}
}

template<typename T>
void RBT<T>::remove(Node<T>* node) {
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
		if (flag) {
			root = suc;
		}
		size--;
	}
}