#define _CRT_SECURE_NO_WARNINGS
#include <locale.h>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std;

#ifndef ADDRESS_H
#define ADDRESS_H

class Address {    
public:
    Address();
    Address(char *c, char *ci, char *s, unsigned int h, unsigned int ap);
    void setAddressManually(char *c, char *ci, char *s, unsigned int h, unsigned int ap);
    void setAddressRandomly();
    char * getCountry();
    char * getCity();
    char * getStreet();
    unsigned int getHouse();
    unsigned int getApartment();
    ~Address();

private:
    char *country;
    char *city;
    char *street;
    int house;
    int apartment;
};

#endif
