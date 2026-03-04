#include "address.h"

Address::Address() : country(), city(), street(), house(0), apartment(0) {}

Address::Address(string c, string ci, string s, unsigned int h, unsigned int ap)
    : country(c), city(ci), street(s), house(h), apartment(ap) {}

Address::~Address() {}

void Address::setAddressManually(string c, string ci, string s, unsigned int h, unsigned int ap) {
    country = c;
    city = ci;
    street = s;
    house = h;
    apartment = ap;
}

void Address::setAddressRandomly() {
    int k = rand() % 8;
    const string countries[] = {"Россия", "Беларусь", "Сербия", "Германия", "Великобритания", "Италия", "Франция", "США"};
    const string cities[] = {"Москва", "Санкт-Петербург", "Минск", "Бобруйск", "Белград", "Нови-Сад", "Берлин", "Мюнхен",
                            "Лондон", "Манчестер", "Рим", "Флоренция", "Париж", "Марсель", "Вашингтон", "Майами"};
    const string streets[] = {"Лесная", "Центральная", "Университетская", "Парковая", "Главная", "Школьная"};

    setAddressManually(countries[k], cities[k * 2 + (rand() % 2)], streets[rand() % 6], rand() % 50 + 1, rand() % 500 + 1);
}

string Address::getCountry() const { return country; }

string Address::getCity() const { return city; }

string Address::getStreet() const { return street; }

unsigned int Address::getHouse() const { return house; }

unsigned int Address::getApartment() const { return apartment; }

const Address& Address::operator=(const Address& right) {
    if (this != &right) {
        country = right.country;
        city = right.city;
        street = right.street;
        house = right.house;
        apartment = right.apartment;
    }

    return *this;
}

bool Address::operator==(const Address& other) const {
    return country == other.country && city == other.city &&
           street == other.street && house == other.house &&
           apartment == other.apartment;
}

bool Address::operator!=(const Address& other) const {
    return !(country == other.country && city == other.city &&
             street == other.street && house == other.house &&
             apartment == other.apartment);
}

bool Address::operator<(const Address& other) const {
    if (apartment < other.apartment) return true;
    else return false;
}

bool Address::operator>(const Address& other) const {
    return !(*this < other || *this == other);
}

bool Address::operator<=(const Address& other) const {
    return (*this < other || *this == other);
}

bool Address::operator>=(const Address& other) const {
    return !(*this < other);
}

ostream& operator<<(ostream& output, const Address& a) {
    output << "Страна: " << a.country << ", Город: " << a.city
        << ", Улица: " << a.street
        << ", Дом: " << a.house
        << ", Квартира: " << a.apartment << endl;

    return output;
}

istream& operator>>(istream& input, Address& a) {
    cout << "Введите страну: ";
    getline(input, a.country);
    cout << "Введите город: ";
    getline(input, a.city);
    cout << "Введите улицу: ";
    getline(input, a.street);
    cout << "Введите номер дома: ";
    input >> a.house;
    cout << "Введите номер квартиры: ";
    input >> a.apartment;
    input.ignore();

    return input;
}

Address Address::operator++(){
    house++;
    apartment++;
    return *this;
}

Address Address::operator++(int){
    Address temp = *this;
    house++;
    apartment++;
    return temp;
}

Address& Address::operator+=(int add){
    house+=add;
    apartment+=add;
    return *this;
}
