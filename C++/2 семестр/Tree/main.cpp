#include <iostream>
#include <locale.h>
#include "Tree.h"

using namespace std;

int main(){
    setlocale(LC_ALL,"PL_pl.UTF-8");
    Tree intTree;
    int intVal;
    cout << "Введите 10 целых чисел:" << endl;
    for (int i = 0; i < 10; i++) {
        cin >> intVal;
        intTree.insertNode (intVal);
    }

    cout<<endl<< "обxод в ширину" <<endl;
    intTree.preOrder ();
    cout <<endl<< "Последовательный обxод" << endl;
    intTree. inOrder();
    cout <<endl<< "обратный обxод" <<endl;
    intTree.postOrder();

    return 0;
}
