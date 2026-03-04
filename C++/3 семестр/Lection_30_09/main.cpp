#include <iostream>
#include <iterator>
#include <random>
#include <vector>
#include <map>
#include <deque>
#include <list>
#include <algorithm>
#include <string>
#include <numeric>

using namespace std;

template <typename T>
void printVector(const vector<T>&);

template <typename Key, typename Value, typename Compare>
void printMapReverse(const map<Key, Value, Compare>&);

template <typename T>
void printDequeReverse(const deque<T>&);

template <typename T>
void printList(const list<T>&);

int main() {
    // VECTOR
    vector<int> V1;

    cout << "Input 5 integer elements of a vector:" << endl;
    for (int i = 0; i < 5; i++) {
        istream_iterator<int> Input(cin);
        V1.push_back(*Input);
    }
    cout << endl << "Vector:" << endl;
    printVector(V1);

    cout << endl << "Max element of a vector: " << *max_element(V1.begin(), V1.end()) << endl;

    cout << endl << "Copied vector if x is odd:" << endl;
    vector<int> V3(V1.size());
    copy_if(V1.begin(), V1.end(), V3.begin(), [](int x) { return x % 2; });
    printVector(V3);

    cout << endl << "Transformed vector (x^2):" << endl;
    vector<int> V4(V1.size());
    transform(V1.begin(), V1.end(), V4.begin(), [](int x) { return x * x; });
    printVector(V4);

    cout << endl << "Copied vector with all 1 replaced with 10:" << endl;
    vector<int> V5(V1.size());
    replace_copy(V1.begin(), V1.end(), V5.begin(), 1, 10);
    printVector(V5);

    cout << endl << "Shuffled list:" << endl;
    vector<int> V6(V1);
    random_device rd;
    mt19937 g(rd());
    shuffle(V6.begin(), V6.end(), g);
    printVector(V6);


    // LIST
    list<char> L1;

    cout << endl << "Input 5 char elements of a list:" << endl;
    for (int i = 0; i < 5; i++) {
        istream_iterator<char> Input(cin);
        L1.push_back(*Input);
    }
    cout << endl << "List:" << endl;
    printList(L1);

    cout << endl << "Number of 'a' in list: " << count(L1.begin(), L1.end(), 'a') << endl;

    cout << endl << "List with 3 chars generated randomly:" << endl;
    list<char> L2(L1);
    generate_n(L2.begin(), 3, []() {return char(rand() % 128 + 32);});
    printList(L2);

    cout << endl << "List, filled with 'F':" << endl;
    list<char> L3(7);
    fill(L3.begin(), L3.end(), 'F');
    printList(L3);

    cout << endl << "List after removing vowels:" << endl;
    list<char> L4(L1);
    L4.erase(remove_if(L4.begin(), L4.end(), [](char c) { c = tolower(c); return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'; }), L4.end());
    printList(L4);

    cout << endl << "Backward copied list:" << endl;
    list<char> L5(L1.size());
    copy(L1.rbegin(), L1.rend(), back_inserter(L5));
    printList(L5);


    // DEQUE
    deque<double> D1;

    cout << endl << "Input 5 double elements of a deque:" << endl;
    for (int i = 0; i < 5; i++) {
        istream_iterator<double> Input(cin);
        D1.push_back(*Input);
    }
    cout << endl << "Deque:" << endl;
    printDequeReverse(D1);

    cout << endl << "Min element in deque: " << *min_element(D1.begin(), D1.end()) << endl;

    cout << endl << "Sum of all elements (accumulate): " <<  accumulate(D1.begin(), D1.end(), 0) << endl;

    cout << endl << "Elements multiplied by 2 (for_each): " << endl;
    for_each(D1.begin(), D1.end(), [](int x) { cout << x * 2 << ' ';});
    cout << endl;

    deque<double> D2 = {12.5, 20.3, 35.6};
    cout << endl << "Before swap: " << endl;
    printDequeReverse(D2);
    swap(D2[1], D2[2]);
    cout << "After swap of first and second elements: " << endl;
    printDequeReverse(D2);

    deque<int> D3 = {1, 2, 2, 3, 3, 3, 4, 5, 5, 1};
    deque<int> D4;

    cout << endl << "Original deque with duplicates: " << endl;
    printDequeReverse(D3);
    unique_copy(D3.begin(), D3.end(), back_inserter(D4));
    cout << "After unique_copy: " << endl;
    printDequeReverse(D4);


    // MAP
    map<string, int> M;

    M.insert({"Forest", 5});
    M.insert(make_pair("Bear", 3));
    M["Car"] = 7;
    M["Fire"] = 2;
    M["Anekdot"] = 4;

    cout << endl << "Reversed Map: ";
    printMapReverse(M);

    auto found = M.find("Bear");
    if (found != M.end()) {
        cout << endl << "Found Bear: " << found->second << endl;
    }

    cout << endl << "Count of 'Car': " << M.count("Car") << endl;

    auto lower = M.lower_bound("Bear");
    auto upper = M.upper_bound("Fire");
    cout << endl << "Elements from 'Bear' to 'Fire': ";
    for (auto it = lower; it != upper; ++it) {
        cout << it->first << " ";
    }
    cout << endl;

    M.erase("Bear");
    cout << endl << "Reversed Map with 'Bear' erased: ";
    printMapReverse(M);

    return 0;
}

template <typename T>
void printVector(const vector<T>& V) {
    typename vector<T>::const_iterator iter;
    ostream_iterator<T> Output(cout, " ");

    for (iter = V.begin(); iter != V.end(); iter++) {
        *Output = *iter;
    }
    cout << endl;
}

template <typename T>
void printList(const list<T>& L) {
    typename list<T>::const_iterator iter;
    ostream_iterator<T> Output(cout, " ");

    for (iter = L.begin(); iter != L.end(); iter++) {
        *Output = *iter;
    }
    cout << endl;
}

template <typename Key, typename Value, typename Compare>
void printMapReverse(const map<Key, Value, Compare>& M) {
    cout << endl;
    typename map<Key, Value, Compare>::const_reverse_iterator iter;
    for (iter = M.rbegin(); iter != M.rend(); ++iter) {
        cout << "[" << iter->first << ":" << iter->second << "] ";
    }
    cout << endl;
}

template <typename T>
void printDequeReverse(const deque<T>& Q) {
    typename deque<T>::const_reverse_iterator iter;
    ostream_iterator<T> Output(cout, " ");

    for (iter = Q.rbegin(); iter != Q.rend(); iter++) {
        *Output = *iter;
    }
    cout << endl;
}
