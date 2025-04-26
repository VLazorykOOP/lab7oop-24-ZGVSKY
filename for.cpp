#include <iostream>
#include <stdexcept>

using namespace std;

// Шаблонний клас вузла списку
template <typename T>
class Node {
public:
    T data;
    Node<T>* next;
    
    Node(const T& value) : data(value), next(nullptr) {}
};

// Попереднє оголошення класу списку для дружнього доступу ітератора
template <typename T>
class LinkedList;

// Шаблонний клас ітератора
template <typename T>
class LinkedListIterator {
private:
    Node<T>* current;
    
public:
    // Конструктор
    LinkedListIterator(Node<T>* node) : current(node) {}
    
    // Перевантаження операторів
    LinkedListIterator& operator++() { // Префіксний інкремент
        if (current) {
            current = current->next;
        }
        return *this;
    }
    
    LinkedListIterator operator++(int) { // Постфіксний інкремент
        LinkedListIterator temp = *this;
        ++(*this);
        return temp;
    }
    
    bool operator==(const LinkedListIterator& other) const {
        return current == other.current;
    }
    
    bool operator!=(const LinkedListIterator& other) const {
        return !(*this == other);
    }
    
    T& operator*() {
        if (!current) {
            throw out_of_range("Ітератор вийшов за межі списку");
        }
        return current->data;
    }
    
    T* operator->() {
        if (!current) {
            throw out_of_range("Ітератор вийшов за межі списку");
        }
        return &(current->data);
    }
    
    // Дозволяємо класу списку доступ до приватних полів
    friend class LinkedList<T>;
};

// Шаблонний клас однозв'язного списку
template <typename T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;
    
public:
    // Оголошення типів для зручності
    using Iterator = LinkedListIterator<T>;
    using ConstIterator = LinkedListIterator<const T>;
    
    // Конструктор
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}
    
    // Деструктор
    ~LinkedList() {
    }
    
    // Додавання елемента в кінець списку
    void push_back(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (tail == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }
    
    // Додавання елемента на початок списку
    void push_front(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head = newNode;
        }
        size++;
    }
    
    // Отримання першого елемента
    T& front() {
        if (head == nullptr) {
            throw out_of_range("Список порожній");
        }
        return head->data;
    }

    // Отримання останнього елемента
    T& back() {
        if (tail == nullptr) {
            throw out_of_range("Список порожній");
        }
        return tail->data;
    }

    // Методи для роботи з ітераторами
    Iterator begin() {
        return Iterator(head);
    }

    Iterator end() {
        return Iterator(nullptr);
    }

    // ... (інші методи залишаються без змін)
};

// Функція для тестування ітератора
template <typename T>
void testIterator(LinkedList<T>& list) {
    cout << "\nТестування ітератора для списку:\n";

    // Виведення списку за допомогою ітератора
    cout << "Елементи списку (using iterator): ";
    for (auto it = list.begin(); it != list.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // Модифікація елементів через ітератор
    cout << "Модифікація елементів (подвоєння значень): ";
    for (auto it = list.begin(); it != list.end(); ++it) {
        *it = *it * 2; // Подвоюємо значення
        cout << *it << " ";
    }
    cout << endl;

    // Використання front() замість operator->
    cout << "Перший елемент (using front()): " << list.front() << endl;

    // ... (решта тестів залишається без змін)
}

int main() {
    // Створення та тестування списку з цілими числами
    LinkedList<int> intList;
    system("chcp 65001");

    cout << "Створення списку цілих чисел:\n";
    intList.push_back(10);
    intList.push_back(20);
    intList.push_back(30);
    intList.push_front(5);
    intList.push_front(1);

    // Тестування ітератора
    testIterator(intList);
    
    return 0;
}