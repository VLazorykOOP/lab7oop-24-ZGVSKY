#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include <vector>
#include <string>

using namespace std;

// Функція-шаблон сортування методом Шелла
template <typename T>
void shellSort(T arr[], int n) {
    // Починаємо з великого проміжку, потім зменшуємо його
    for (int gap = n/2; gap > 0; gap /= 2) {
        // Виконуємо сортування вставками для цього проміжку
        for (int i = gap; i < n; i++) {
            T temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

// Специфікація функції-шаблону для типу char* (лексикографічне порівняння)
template <>
void shellSort<char*>(char* arr[], int n) {
    for (int gap = n/2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            char* temp = arr[i];
            int j;
            for (j = i; j >= gap && strcmp(arr[j - gap], temp) > 0; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

// Функція для введення даних з клавіатури
template <typename T>
void inputFromKeyboard(T arr[], int n) {
    cout << "Введіть " << n << " елементів:\n";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
}

// Специфікація для char*
template <>
void inputFromKeyboard<char*>(char* arr[], int n) {
    cout << "Введіть " << n << " рядків (макс. 100 символів кожен):\n";
    char buffer[101];
    for (int i = 0; i < n; i++) {
        cin >> buffer;
        arr[i] = new char[strlen(buffer) + 1];
        strcpy(arr[i], buffer);
    }
}

// Функція для введення даних з файлу
template <typename T>
void inputFromFile(T arr[], int n, const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Не вдалося відкрити файл " << filename << endl;
        return;
    }
    
    for (int i = 0; i < n; i++) {
        file >> arr[i];
    }
    file.close();
}

// Специфікація для char*
template <>
void inputFromFile<char*>(char* arr[], int n, const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Не вдалося відкрити файл " << filename << endl;
        return;
    }
    
    char buffer[101];
    for (int i = 0; i < n; i++) {
        file >> buffer;
        arr[i] = new char[strlen(buffer) + 1];
        strcpy(arr[i], buffer);
    }
    file.close();
}

// Функція для генерації випадкових даних
template <typename T>
void generateRandomData(T arr[], int n) {
    srand(time(0));
    for (int i = 0; i < n; i++) {
        arr[i] = static_cast<T>(rand() % 100);
    }
}

// Специфікація для char*
template <>
void generateRandomData<char*>(char* arr[], int n) {
    srand(time(0));
    const int max_len = 10;
    for (int i = 0; i < n; i++) {
        int len = rand() % max_len + 1;
        arr[i] = new char[len + 1];
        for (int j = 0; j < len; j++) {
            arr[i][j] = 'a' + rand() % 26;
        }
        arr[i][len] = '\0';
    }
}

// Функція для виведення масиву
template <typename T>
void printArray(T arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Специфікація для char*
template <>
void printArray<char*>(char* arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Функція для звільнення пам'яті (специфічна для char*)
void freeMemory(char* arr[], int n) {
    for (int i = 0; i < n; i++) {
        delete[] arr[i];
    }
}

// Тест для цілих чисел
void testInt() {
    const int n = 10;
    int arr[n];
    
    cout << "\nТестування для int:\n";
    cout << "1. Введення з клавіатури\n";
    inputFromKeyboard(arr, n);
    shellSort(arr, n);
    cout << "Відсортований масив: ";
    printArray(arr, n);
    
    cout << "2. Генерація випадкових даних\n";
    generateRandomData(arr, n);
    cout << "Початковий масив: ";
    printArray(arr, n);
    shellSort(arr, n);
    cout << "Відсортований масив: ";
    printArray(arr, n);
    
    cout << "3. Введення з файлу (int_data.txt)\n";
    inputFromFile(arr, n, "int_data.txt");
    cout << "Початковий масив: ";
    printArray(arr, n);
    shellSort(arr, n);
    cout << "Відсортований масив: ";
    printArray(arr, n);
}

// Тест для double
void testDouble() {
    const int n = 5;
    double arr[n];
    
    cout << "\nТестування для double:\n";
    cout << "1. Введення з клавіатури\n";
    inputFromKeyboard(arr, n);
    shellSort(arr, n);
    cout << "Відсортований масив: ";
    printArray(arr, n);
    
    cout << "2. Генерація випадкових даних\n";
    generateRandomData(arr, n);
    cout << "Початковий масив: ";
    printArray(arr, n);
    shellSort(arr, n);
    cout << "Відсортований масив: ";
    printArray(arr, n);
}

// Тест для char*
void testCharPtr() {
    const int n = 5;
    char* arr[n];
    
    cout << "\nТестування для char*:\n";
    cout << "1. Введення з клавіатури\n";
    inputFromKeyboard(arr, n);
    cout << "Початковий масив: ";
    printArray(arr, n);
    shellSort(arr, n);
    cout << "Відсортований масив: ";
    printArray(arr, n);
    freeMemory(arr, n);
    
    cout << "2. Генерація випадкових даних\n";
    generateRandomData(arr, n);
    cout << "Початковий масив: ";
    printArray(arr, n);
    shellSort(arr, n);
    cout << "Відсортований масив: ";
    printArray(arr, n);
    freeMemory(arr, n);
    
    cout << "3. Введення з файлу (string_data.txt)\n";
    inputFromFile(arr, n, "string_data.txt");
    cout << "Початковий масив: ";
    printArray(arr, n);
    shellSort(arr, n);
    cout << "Відсортований масив: ";
    printArray(arr, n);
    freeMemory(arr, n);
}

int main() {
    system("chcp 65001");
    testInt();
    testDouble();
    testCharPtr();
    
    return 0;
}