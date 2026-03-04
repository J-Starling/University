#include "address.h"

Address::Address() {
    country = nullptr;
    city = nullptr;
    street = nullptr;
    house = 0;
    apartment = 0;
}

Address::Address(char *c, char *ci, char *s, unsigned int h, unsigned int ap) {
    country = _strdup(c);
    city = _strdup(ci);
    street = _strdup(s);
    house = h;
    apartment = ap;
}

Address::~Address() {
    delete[] country;
    delete[] city;
    delete[] street;
}

void manual(Address *a, int n)
{
    char *c = new char[30], *ci = new char[30], *s = new char[30];
    int h, ap;

    cout<<endl<<"!Ограничение - 30 символов в каждой строке!"<<endl;

    for (int i = 0; i < n; i++)
    {
        cout<<endl<<"Введите страну ("<<i+1<<"):"<<endl;
        cin>>c;

        cout<<endl<<"Введите город ("<<i+1<<"):"<<endl;
        cin>>ci;

        cout<<endl<<"Введите улицу ("<<i+1<<"):"<<endl;
        cin>>s;

        cout<<endl<<"Введите номер дома ("<<i+1<<"):"<<endl;
        cin>>h;

        cout<<endl<<"Введите номер квартиры ("<<i+1<<"):"<<endl;
        cin>>ap;

        a[i].setAddressManually(c, ci, s, h, ap);
    }
    delete[] c;
    delete[] ci;
    delete[] s;
}

void random(Address *a, int n)
{
    for (int i = 0; i < n; i++)
        a[i].setAddressRandomly();
}

void print(Address *a, int n)
{
    char *c = nullptr, *ci = nullptr, *s = nullptr;
    unsigned int h = 0, ap = 0;
    cout<<endl<<"Адреса:"<<endl;
    for (int i = 0; i < n; i++)
    {
        c = a[i].getCountry();
        ci = a[i].getCity();
        s = a[i].getStreet();
        h = a[i].getHouse();
        ap = a[i].getApartment();
        cout<<endl<<"Страна "<<c<<", город "<<ci<<", улица "<<s<<", дом "<<h<<", квартира "<<ap<<"."<<endl;
    }
}

void Address::setAddressManually(char *c, char *ci, char *s, unsigned int h, unsigned int ap)
{
    delete[] country;
    delete[] city;
    delete[] street;

    country = _strdup(c);
    city = _strdup(ci);
    street = _strdup(s);
    house = h;
    apartment = ap;
}

void Address::setAddressRandomly()
{
    int k;
    const char *countries[] = {"Россия", "Беларусь", "Сербия", "Германия", "Великобритания", "Италия", "Франция", "Америка"};
    const char *cities[] = {"Москва", "Санкт-Петербург", "Минск", "Бобруйск", "Белград", "Нови-Сад", "Берлин", "Мюнхен", "Лондон", "Манчестер", "Рим", "Флоренция", "Париж", "Марсель", "Вашингтон", "Майами"};
    const char *streets[] = {"Лесная", "Центральная", "Университетская", "Парковая", "Главная", "Школьная"};

    delete[] country;
    delete[] city;
    delete[] street;

    k = rand() % 8;
    country = _strdup(countries[k]);

    k = k * 2 + (rand() % 2);
    city = _strdup(cities[k]);

    k = rand() % 6;
    street = _strdup(streets[k]);

    house = rand() % 50 + 1;

    apartment = rand() % 500 + 1;
}

char * Address::getCountry(){
    return country;
}

char * Address::getCity(){
    return city;
}

char * Address::getStreet(){
    return street;
}

unsigned int Address::getHouse(){
    return house;
}

unsigned int Address::getApartment(){
    return apartment;
}
