#include <iostream>
#include "array.h"

using namespace std;

template <typename T>
void manualInput(Array<T>&, const T);
template <typename T>
void demonstrateArray(Array<T>& arr, const string& typeName);
void demonstrateArray(Array<string>& arr, const string& typeName);
void demonstrateArray(Array<char>& arr, const string& typeName);
void demonstrateDifferentTypes();

int main() {
    demonstrateDifferentTypes();
    return 0;
}

template <typename T>
void manualInput(Array<T>& arr, const T g) {
    arr.push_back(g);
}

template <typename T>
void demonstrateArray(Array<T>& arr, const string& typeName) {
    cout << endl << "Array of " << typeName << "s" << endl;

    cout << "Adding elements" << endl;
    for (int i = 0; i < 8; i++) {
        arr.push_back(static_cast<T>(i * 1.5));
        cout << "Element added: " << arr[arr.getSize() - 1] << ", size: " << arr.getSize() << ", capacity: " << arr.getCapacity() << endl;
    }

    T g;
    cout << endl << "What element would you like to add?" << endl;
    cin >> g;
    manualInput(arr, g);

    cout << endl << "Indexes:" << endl;
    for (int i = 0; i < arr.getSize(); i++) {
        cout << "arr[" << i << "] = " << arr[i] << endl;
    }

    cout << "Total " << typeName << " arrays created: " << Array<T>::getTotalArraysCreated() << endl;
    cout << "Total " << typeName << " elements: " << Array<T>::getTotalElements() << endl;
}

void demonstrateDifferentTypes() {
    cout << "=== DEMONSTRATING STATIC VARIABLES FOR DIFFERENT TYPES ===" << endl;

    Array<int> intArray;
    demonstrateArray(intArray, "INT");

    Array<double> doubleArray;
    demonstrateArray(doubleArray, "DOUBLE");

    Array<string> stringArray;
    demonstrateArray(stringArray, "STRING");

    Array<char> charArray;
    demonstrateArray(charArray, "CHAR");

    Array<int> intArray2;
    Array<double> doubleArray2;

    cout << endl << "=== AFTER CREATING ADDITIONAL ARRAYS ===" << endl;
    cout << "Total INT arrays: " << Array<int>::getTotalArraysCreated() << endl;
    cout << "Total DOUBLE arrays: " << Array<double>::getTotalArraysCreated() << endl;
    cout << "Total STRING arrays: " << Array<string>::getTotalArraysCreated() << endl;
    cout << "Total CHAR arrays: " << Array<char>::getTotalArraysCreated() << endl;
}

void demonstrateArray(Array<string>& arr, const string& typeName) {
    cout << endl << "Array of " << typeName << "s" << endl;

    const string words[] = {"Bear", "Forest", "Car", "Fire", "Anekdot"};

    for (const auto& word : words) {
        arr.push_back(word);
        cout << "Added element: '" << arr[arr.getSize() - 1] << "'" << endl;
    }

    string g;
    cout << endl << "What element would you like to add?" << endl;
    cin >> g;
    manualInput(arr, g);

    cout << endl << "All elements:" << endl;
    for (int i = 0; i < arr.getSize(); i++) {
        cout << i << ": '" << arr[i] << "'" << endl;
    }

    cout << "Total " << typeName << " arrays created: " << Array<string>::getTotalArraysCreated() << endl;
    cout << "Total " << typeName << " elements: " << Array<string>::getTotalElements() << endl;
}

void demonstrateArray(Array<char>& arr, const string& typeName) {
    cout << endl << "Array of " << typeName << "s" << endl;
    for (char c = 'A'; c <= 'Z'; c++) {
        arr.push_back(c);
    }

    char g;
    cout << endl << "What element would you like to add?" << endl;
    cin >> g;
    manualInput(arr, g);

    cout << endl << "All elements:" << endl;
    for (int i = 0; i < arr.getSize(); i++) {
        cout << i << ": '" << arr[i] << "'" << endl;
    }
    cout << "Total " << typeName << " arrays created: " << Array<char>::getTotalArraysCreated() << endl;
    cout << "Total " << typeName << " elements: " << Array<char>::getTotalElements() << endl;
}
