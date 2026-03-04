#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <list>
#include <algorithm>
#include <numeric>

using namespace std;

template<typename T> void pushElements (T&);
template<typename T> void popElements (T&);
template<typename T> void printContainer(const T& container);

int main()
{
    //Stack
    cout << "STACK" << endl;

    stack<int> intDequeStack;
    stack<int, vector<int>> intVectorStack;
    stack<int, list<int>> intListStack;

    cout << "Pushing onto intDequeStack: ";
    pushElements (intDequeStack );
    cout << "\nPushing onto intVectorStack: ";
    pushElements (intVectorStack);
    cout << "\nPushing onto intListStack: ";
    pushElements (intListStack);

    cout << endl<< endl;

    cout << "Popping from intDequeStack: ";
    popElements (intDequeStack);
    cout << "\nPopping from intVectorStack: ";
    popElements (intVectorStack);
    cout << "\nPopping from intListStack: ";
    popElements (intListStack);
    cout << endl;


    //Queue
    cout << endl << "QUEUE" << endl;

    queue<double> values;

    values.push(3.2);
    values.push(9.8);
    values.push(5.4);

    cout << "Popping from values: ";
    while (!values.empty()) {
        cout << values.front() << ' ';
        values.pop();
    }
    cout << endl;


    //Priority Queue
    cout << endl << "PRIORITY_QUEUE" << endl;

    priority_queue<double> priorities;

    priorities.push(3.2);
    priorities.push(9.8);
    priorities.push(5.4);

    cout << "Popping from priorities: ";
    while (!priorities.empty()) {
        cout << priorities.top() << ' ';
        priorities.pop();
    }


    //Algorithms
    cout << endl << "ALGORITHMS" << endl;

    //1.Merge
    cout << endl << "MERGE:" << endl;
    vector<int> v1 = {1, 3, 5, 7, 9};
    vector<int> v2 = {2, 4, 6, 8, 10};
    vector<int> merged(10);

    cout << endl << "Vector 1: " << endl;
    printContainer(v1);
    cout << endl << "Vector 2: " << endl;
    printContainer(v2);

    merge(v1.begin(), v1.end(), v2.begin(), v2.end(), merged.begin());
    cout << endl << "After merge: " << endl;
    printContainer(merged);

    //2.Heapsort
    cout << endl << "HEAPSORT:" << endl;
    vector<int> heapVec = {3, 1, 4, 1, 5, 9, 2, 6};
    cout << endl << "Before heapsort: ";
    printContainer(heapVec);

    make_heap(heapVec.begin(), heapVec.end());
    cout << endl << "After make_heap: ";
    printContainer(heapVec);

    sort_heap(heapVec.begin(), heapVec.end());
    cout << endl << "After sort_heap: ";
    printContainer(heapVec);


    //3.Find
    cout << endl << "FIND:" << endl;
    vector<int> v = {5, 2, 8, 1, 9, 3, 7, 4, 6, 2, 8, 5};
    cout << endl << "Vector: " << endl;
    printContainer(v);

    auto found = find(v.begin(), v.end(), 7);
    if (found != v.end()) {
        cout << endl << "'7' found on position: " << distance(v.begin(), found) << endl;
    } else {
        cout << "'7' not found" << endl;
    }

    //4.Equal Range
    cout << endl << "EQUAL_RANGE:" << endl;
    cout << endl << "Vector: " << endl;
    vector<int> sortedVec = {1, 2, 2, 2, 3, 4, 4, 5, 6};
    printContainer(sortedVec);

    auto range = equal_range(sortedVec.begin(), sortedVec.end(), 2);
    cout << endl << "Equal_range for '2': [" << distance(sortedVec.begin(), range.first) << ", " << distance(sortedVec.begin(), range.second) << ")" << endl;

    range = equal_range(sortedVec.begin(), sortedVec.end(), 4);
    cout << endl << "Equal_range for '4': [" << distance(sortedVec.begin(), range.first) << ", " << distance(sortedVec.begin(), range.second) << ")" << endl;

    //5.For Each
    cout << endl << "FOR_EACH:" << endl;
    cout << endl << "Vector: " << endl;
    printContainer(v);

    cout << endl << "Multiplication of each element by 2: " << endl;
    for_each(v.begin(), v.end(), [](int &n) {return n *= 2;});
    printContainer(v);

    //6.Inner Product
    cout << endl << "INNER_PRODUCT:" << endl;
    vector<int> a = {1, 2, 3, 4, 5};
    vector<int> b = {2, 3, 4, 5, 6};

    cout << endl << "Vector A: " << endl;
    printContainer(a);
    cout << endl << "Vector B: " << endl;
    printContainer(b);

    int product = inner_product(a.begin(), a.end(), b.begin(), 0);
    cout << endl << "Product of A*B: " << endl << product << endl;

    //7.Partition
    cout << endl << "PARTITION:" << endl;
    vector<int> partVec = {1, 8, 3, 6, 2, 9, 4, 7, 5};
    cout << endl << "Before partition: " << endl;
    printContainer(partVec);

    partition(partVec.begin(), partVec.end(), [](int n) {return n % 2 == 0;});
    cout << endl << "After partition (on even and odd): " << endl;
    printContainer(partVec);

    return 0;
}

template<typename T> void pushElements(T &stackRef)
{
    for (int i = 0; i < 10; i++) {
        stackRef.push(i);
        cout << stackRef.top() << ' ';
    }
}

template <typename T> void popElements(T &stackRef)
{
    while (!stackRef.empty()) {
        cout << stackRef.top() << ' ';
        stackRef.pop();
    }
}

template<typename T> void printContainer(const T& container)
{
    for (const auto& elem : container) {
        cout << elem << " ";
    }
    cout << endl;
}
