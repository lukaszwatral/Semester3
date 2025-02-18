#include <iostream>
#include <time.h>
#include <string>

template<typename T, typename Y>
class list_object {
public:
    T field1;
    Y field2;
    list_object<T, Y>* prev;
    list_object<T, Y>* next;
    list_object(T value1, Y value2) {
        this->field1 = value1;
        this->field2 = value2;
        this->prev = nullptr;
        this->next = nullptr;
    }
};

template<typename T, typename Y>
class linked_list {
public:
    size_t size;
    list_object<T, Y>* head;
    list_object<T, Y>* tail;
    linked_list() {
        this->size = 0;
        this->head = nullptr;
        this->tail = nullptr;
    }

    ~linked_list() {
        clear_list();
    }

    void insert_tail(T value1, Y value2); //a
    void insert_head(T value1, Y value2); //b
    void remove_tail(); //c
    void remove_head(); //d
    void show(size_t i); //e
    void update(size_t i, T value1, Y value2); //f
    list_object<T, Y>* find(T value); //g
    void find_and_remove(T value); //h
    void insert(size_t i, T value1, Y value2); //i
    void clear_list(); //j
    void string_display(); //k
    list_object<T, Y>* operator [](size_t i) {
        if (size == 0) {
            std::cout << "The list is empty!";
        }
        else if (i < 0 || i >(size - 1)) {
            std::cout << "Index out of range!";
        }
        else {
            list_object<T, Y>* tmp = head;
            int j = 0;
            while (j != i) {
                j++;
                tmp = tmp->next;
            }
            return tmp;
        }
    }
};


int main()
{
    srand(time(NULL));
    const int MAX_ORDER = 6;
    linked_list<int, char>* ll = new linked_list<int, char>();
    double adding_time = 0.0;
    double find_and_remove_time = 0.0;
    for (int o = 1; o <= MAX_ORDER; o++)
    {
        const int n = pow(10, o);
        clock_t t1 = clock();
        for (int i = 0; i < n; i++) {
            ll->insert_tail(std::rand(), (char)std::rand());
        }
        clock_t t2 = clock();
        adding_time = (double)(t2 - t1) / CLOCKS_PER_SEC;
        ll->string_display();
        std::cout << "Adding time: " << adding_time << std::endl;
        const int m = pow(10, 4);
        t1 = clock();
        for (int i = 0; i < m; i++) {
            ll->find_and_remove(std::rand());
        }
        t2 = clock();
        find_and_remove_time = (double)(t2 - t1) / CLOCKS_PER_SEC;
        ll->string_display();
        std::cout << "Find and remove time: " << find_and_remove_time << std::endl;
        ll->clear_list();
    }
    delete ll;
    return 0;
}

template<typename T, typename Y>
void linked_list<T, Y>::insert_tail(T value1, Y value2) {
    if (head == nullptr) {
        linked_list<T, Y>::insert_head(value1, value2);
    }
    else {
        list_object<T, Y>* tmp = new list_object<T, Y>(value1, value2);
        tmp->prev = tail;
        tail->next = tmp;
        tail = tmp;
        size++;
    }
}


template<typename T, typename Y>
void linked_list<T, Y>::insert_head(T value1, Y value2) {
    list_object<T, Y>* tmp = new list_object<T, Y>(value1, value2);
    if (head == nullptr) {
        head = tmp;
        tail = tmp;
    }
    else {
        tmp->next = head;
        head->prev = tmp;
        head = tmp;
    }
    size++;
}

template<typename T, typename Y>
void linked_list<T, Y>::remove_tail() {
    if (head == nullptr) {
        return;
    }
    else {
        if (size > 1) {
            list_object<T, Y>* tmp = tail->prev;
            tmp->next = nullptr;
            delete tail;
            tail = tmp;
        }
        else {
            delete tail;
            head = nullptr;
            tail = nullptr;
        }
    }
    size--;
}

template<typename T, typename Y>
void linked_list<T, Y>::remove_head() {
    if (head == nullptr) {
        return;
    }
    else {
        if (size > 1) {
            list_object<T, Y>* tmp = head->next;
            tmp->prev = nullptr;
            delete head;
            head = tmp;
        }
        else {
            delete head;
            head = nullptr;
            tail = nullptr;
        }
    }
    size--;
}

template<typename T, typename Y>
void linked_list<T, Y>::show(size_t i) {
    if (size == 0) {
        std::cout << "The list is empty!";
    }
    else if (i < 0 || i >(size - 1)) {
        std::cout << "Index out of range!";
    }
    else {
        list_object<T, Y>* tmp = head;
        int j = 0;
        while (j != i) {
            j++;
            tmp = tmp->next;
        }
        std::cout << tmp->field1 << ", " << tmp->field2;
    }
}

template<typename T, typename Y>
void linked_list<T, Y>::update(size_t i, T value1, Y value2) {
    if (size == 0) {
        std::cout << "The list is empty!";
    }
    else if (i < 0 || i >(size - 1)) {
        std::cout << "Index out of range!";
    }
    else {
        list_object<T, Y>* tmp = head;
        int j = 0;
        while (j != i) {
            j++;
            tmp = tmp->next;
        }
        tmp->field1 = value1;
        tmp->field2 = value2;
    }
}

template<typename T, typename Y>
list_object<T, Y>* linked_list<T, Y>::find(T value) {
    list_object<T, Y>* tmp = head;
    while (tmp != nullptr) {
        if (tmp->field1 == value || tmp->field2 == value) {
            return tmp;
        }
        tmp = tmp->next;
    }
    return NULL;
}

template<typename T, typename Y>
void linked_list<T, Y>::find_and_remove(T value) {
    list_object<T, Y>* tmp = head;
    while (tmp != nullptr) {
        if (tmp->field1 == value || tmp->field2 == value) {
            if (tmp->prev) {
                tmp->prev->next = tmp->next;
            }
            else {
                head = tmp->next;
            }
            if (tmp->next) {
                tmp->next->prev = tmp->prev;
            }
            size--;
            delete tmp;
            return;
        }
        tmp = tmp->next;
    }
}

template<typename T, typename Y>
void linked_list<T, Y>::insert(size_t i, T value1, Y value2) {
    list_object<T, Y>* new_obj = new list_object<T, Y>(value1, value2);
    list_object<T, Y>* tmp = head;
    if (i == 0) {
        insert_head(value1, value2);
    }
    else if (i < 0 || i > size) {
        std::cout << "Index out of range!";
    }
    else if (i == size) {
        insert_tail(value1, value2);
    }
    else {
        int j = 0;
        while (j != (i - 1)) {
            j++;
            tmp = tmp->next;
        }
        new_obj->next = tmp->next;
        tmp->next->prev = new_obj;
        tmp->next = new_obj;
        new_obj->prev = tmp;
        size++;
    }
}

template<typename T, typename Y>
void linked_list<T, Y>::clear_list() {
    while (size > 0) {
        remove_head();
    }
}

template<typename T, typename Y>
void linked_list<T, Y>::string_display() {
    std::cout << "----------------Linked list----------------" << std::endl;
    if (size == 0) {
        std::cout << "The list is empty!";
    }
    else {
        std::cout << "Number of objects: " << size << ", list address: " << this << std::endl;
        std::cout << "Objects: " << std::endl;
        list_object<T, Y>* tmp = head;
        if (size <= 10) {
            for (int i = 0; i < size; i++) {
                std::cout << tmp->field1 << ", " << tmp->field2 << std::endl;
                tmp = tmp->next;
            }
        }
        else {
            for (int i = 0; i < 5; i++) {
                std::cout << tmp->field1 << ", " << tmp->field2 << std::endl;
                tmp = tmp->next;
            }
            std::cout << "..." << std::endl;
            std::cout << tail->field1 << ", " << tail->field2 << std::endl;
        }
    }
}