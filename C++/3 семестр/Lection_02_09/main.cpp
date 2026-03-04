#include "address.h"
#include "developer.h"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    char q = 'N';
    int f;

    do{
        Developer dev;

        ifstream input("input.txt", ios::in);
        if (!input) {
            cerr << "Error, couldn't read from the file";
            exit(1);
        }
        input >> dev;

        cout << "Addresses: " << endl << endl;
        cout << dev << endl;

        cout << "Choose a sorting method:" << endl;
        cout << "1 - Quick sort" << endl;
        cout << "2 - Shaker sort" << endl;
        cout << "0 - Without sorting" << endl << endl;

        cin >> f;
        if (f == 1) {
            dev.QuickSort(0, dev.getCount()-1);
            cout << "Sorted addresses: " << endl << endl;
            cout << dev << endl;
        } else if (f == 2) {
            dev.ShakerSort();
            cout << "Sorted addresses: " << endl << endl;
            cout << dev << endl;
        }

        ofstream output("output.txt", ios::out);
        if (!output) {
            cerr << "Error, couldn't open the file";
            exit(2);
        }
        output << dev;

        cout << "Want to continue? (Y/N): ";
        cin >> q;
        cin.ignore();
    }while (q == 'y' || q == 'Y');

    return 0;
}
