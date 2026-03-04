#ifndef DEVELOPER_H
#define DEVELOPER_H

#include "address.h"

class Developer {
    friend ostream& operator<<(ostream&, const Developer&);
    friend istream& operator>>(istream&, Developer&);
public:
    Developer();
    Developer(const Address*, int);
    Developer(const Developer&);
    ~Developer();
    void addAddress(const Address&);
    void setAddresses(const Address*, int);
    const Address* getAddresses() const;
    int getCount() const;
    const Developer& operator=(const Developer&);
    void QuickSort(int, int);
    int QuickSortHelper(Address *, int, int);
    void ShakerSort();
    void increase();
    void add();
private:
    Address* addresses;
    int count;
};

#endif
