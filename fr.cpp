#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <memory>

using namespace std;

// Шаблони функцій для знаходження мінімуму та максимуму
template <typename T>
T findMin(T a, T b) {
    return (a < b) ? a : b;
}

template <typename T>
T findMax(T a, T b) {
    return (a > b) ? a : b;
}

// Спеціалізація для C-рядків
template <>
const char* findMin<const char*>(const char* a, const char* b) {
    return (strcmp(a, b) < 0) ? a : b;
}

template <>
const char* findMax<const char*>(const char* a, const char* b) {
    return (strcmp(a, b) > 0) ? a : b;
}

// Функції для роботи з введенням
template <typename T>
void inputFromKeyboard(T& a, T& b) {
    cout << "Введіть перше значення: ";
    cin >> a;
    cout << "Введіть друге значення: ";
    cin >> b;
    cin.ignore(); // Очистка буфера
}

// Спеціалізація для string
template <>
void inputFromKeyboard<string>(string& a, string& b) {
    cout << "Введіть перший рядок: ";
    getline(cin, a);
    cout << "Введіть другий рядок: ";
    getline(cin, b);
}

// Спеціалізація для const char*
void inputFromKeyboardCharPtr(const char*& a, const char*& b) {
    string s1, s2;
    cout << "Введіть перший рядок: ";
    getline(cin, s1);
    cout << "Введіть другий рядок: ";
    getline(cin, s2);

    a = strdup(s1.c_str());
    b = strdup(s2.c_str());
}

template <typename T>
void inputFromFile(T& a, T& b, const string& filename) {
    ifstream file(filename);
    if (file) {
        file >> a >> b;
        file.close();
    } else {
        cerr << "Помилка відкриття файлу " << filename << endl;
    }
}

// Спеціалізація для string
template <>
void inputFromFile<string>(string& a, string& b, const string& filename) {
    ifstream file(filename);
    if (file) {
        getline(file, a);
        getline(file, b);
        file.close();
    } else {
        cerr << "Помилка відкриття файлу " << filename << endl;
    }
}

// Спеціалізація для const char*
void inputFromFileCharPtr(const char*& a, const char*& b, const string& filename) {
    ifstream file(filename);
    if (file) {
        string s1, s2;
        getline(file, s1);
        getline(file, s2);
        a = strdup(s1.c_str());
        b = strdup(s2.c_str());
        file.close();
    } else {
        cerr << "Помилка відкриття файлу " << filename << endl;
    }
}

template <typename T>
void generateRandom(T& a, T& b) {
    srand(time(0));
    a = static_cast<T>(rand() % 100);
    b = static_cast<T>(rand() % 100);
}

// Спеціалізація для string
template <>
void generateRandom<string>(string& a, string& b) {
    const string words[] = {"яблуко", "апельсин", "банан", "груша", "слива"};
    srand(time(0));
    a = words[rand() % 5];
    b = words[rand() % 5];
}

// Спеціалізація для const char*
void generateRandomCharPtr(const char*& a, const char*& b) {
    const char* words[] = {"яблуко", "апельсин", "банан", "груша", "слива"};
    srand(time(0));
    a = strdup(words[rand() % 5]);
    b = strdup(words[rand() % 5]);
}

// Тестова функція
template <typename T>
void testMinMax(const string& typeName) {
    T a{}, b{};
    int choice;

    cout << "\n--- Тест для " << typeName << " ---" << endl;
    cout << "Виберіть спосіб введення:\n";
    cout << "1. З клавіатури\n";
    cout << "2. З файлу\n";
    cout << "3. Випадкові значення\n";
    cout << "Ваш вибір: ";
    cin >> choice;
    cin.ignore(); // Очистка буфера

    switch (choice) {
        case 1:
            if constexpr (is_same_v<T, const char*>) {
                inputFromKeyboardCharPtr(a, b);
            } else {
                inputFromKeyboard(a, b);
            }
            break;
        case 2:
            if constexpr (is_same_v<T, const char*>) {
                inputFromFileCharPtr(a, b, "string_data.txt");
            } else if constexpr (is_same_v<T, string>) {
                inputFromFile(a, b, "string_data.txt");
            } else {
                inputFromFile(a, b, "numeric_data.txt");
            }
            break;
        case 3:
            if constexpr (is_same_v<T, const char*>) {
                generateRandomCharPtr(a, b);
            } else {
                generateRandom(a, b);
            }
            break;
        default:
            cout << "Невірний вибір!" << endl;
            return;
    }

    cout << "Значення: " << a << ", " << b << endl;
    cout << "Мінімальне: " << findMin(a, b) << endl;
    cout << "Максимальне: " << findMax(a, b) << endl;

    // Очищення пам'яті для const char*
    if constexpr (is_same_v<T, const char*>) {
        free(const_cast<char*>(a));
        free(const_cast<char*>(b));
    }
}

int main() {
    system("chcp 65001");

    cout << "*** Тестування шаблонів findMin та findMax ***" << endl << endl;

    // Тестування для різних типів
    testMinMax<int>("int");
    testMinMax<double>("double");
    testMinMax<char>("char");
    testMinMax<const char*>("const char*");
    testMinMax<string>("string");

    return 0;
}