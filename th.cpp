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

// Шаблонний клас однозв'язного списку
template <typename T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;

public:
    // Конструктор
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}

    // Деструктор
    ~LinkedList() {
        clear();
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

    // Видалення елемента з кінця списку
    void pop_back() {
        if (tail == nullptr) {
            throw out_of_range("Список порожній");
        }

        if (head == tail) {
            delete tail;
            head = tail = nullptr;
        } else {
            Node<T>* current = head;
            while (current->next != tail) {
                current = current->next;
            }
            delete tail;
            tail = current;
            tail->next = nullptr;
        }
        size--;
    }

    // Видалення елемента з початку списку
    void pop_front() {
        if (head == nullptr) {
            throw out_of_range("Список порожній");
        }

        Node<T>* temp = head;
        head = head->next;
        delete temp;

        if (head == nullptr) {
            tail = nullptr;
        }
        size--;
    }

    // Отримання елемента за індексом
    T& at(int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Невірний індекс");
        }

        Node<T>* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }

    // Отримання розміру списку
    int getSize() const {
        return size;
    }

    // Перевірка на порожність
    bool isEmpty() const {
        return size == 0;
    }

    // Очищення списку
    void clear() {
        while (!isEmpty()) {
            pop_front();
        }
    }

    // Виведення списку
    void print() const {
        Node<T>* current = head;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    // Ітератор для списку
    class Iterator {
    private:
        Node<T>* current;

    public:
        Iterator(Node<T>* node) : current(node) {}

        Iterator& operator++() {
            if (current) {
                current = current->next;
            }
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }

        T& operator*() {
            return current->data;
        }
    };

    Iterator begin() {
        return Iterator(head);
    }

    Iterator end() {
        return Iterator(nullptr);
    }
};

// Приклад використання
int main() {
    system("chcp 65001");
    // Тестування списку з цілими числами
    LinkedList<int> intList;

    cout << "Додаємо елементи в кінець списку:" << endl;
    intList.push_back(10);
    intList.push_back(20);
    intList.push_back(30);
    intList.print(); // 10 20 30

    cout << "Додаємо елементи на початок списку:" << endl;
    intList.push_front(5);
    intList.push_front(1);
    intList.print(); // 1 5 10 20 30

    cout << "Розмір списку: " << intList.getSize() << endl; // 5

    cout << "Видаляємо перший елемент:" << endl;
    intList.pop_front();
    intList.print(); // 5 10 20 30

    cout << "Видаляємо останній елемент:" << endl;
    intList.pop_back();
    intList.print(); // 5 10 20

    cout << "Елемент за індексом 1: " << intList.at(1) << endl; // 10

    // Тестування списку з рядками
    LinkedList<string> strList;
    strList.push_back("Hello");
    strList.push_back("World");
    strList.push_front("C++");

    cout << "\nСписок рядків:" << endl;
    strList.print(); // C++ Hello World

    // Використання ітератора
    cout << "Елементи списку (через ітератор):" << endl;
    for (auto it = strList.begin(); it != strList.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    return 0;
}