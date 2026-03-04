#ifndef ADDRESS_H
#define ADDRESS_H

#include <string>
#include <iostream>

using namespace std;

class Address {
    friend ostream& operator<<(ostream&, const Address&);
    friend istream& operator>>(istream&, Address&);
    friend class Developer;
public:
    Address();
    Address(string, string, string, unsigned int, unsigned int);
    ~Address();
    void setAddressManually(string, string, string, unsigned int, unsigned int);
    void setAddressRandomly();
    string getCountry() const;
    string getCity() const;
    string getStreet() const;
    unsigned int getHouse() const;
    unsigned int getApartment() const;
    const Address& operator=(const Address&);
    bool operator==(const Address&) const;
    bool operator!=(const Address&) const;
    bool operator<(const Address&) const;
    bool operator>(const Address&) const;
    bool operator<=(const Address&) const;
    bool operator>=(const Address&) const;
    Address operator++();
    Address operator++(int);
    Address& operator+=(int);
private:
    string country;
    string city;
    string street;
    unsigned int house;
    unsigned int apartment;
};

#endif
