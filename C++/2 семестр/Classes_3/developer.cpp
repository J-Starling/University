#include "developer.h"
#include "address.cpp"

Developer::Developer() : addresses(nullptr), count(0) {}

Developer::Developer(const Address* addresses, int count) {
    this->addresses = new Address[count];
    this->count = count;
    for (int i = 0; i < count; ++i) {
        this->addresses[i] = addresses[i];
    }
}

Developer::Developer(const Developer& other) {
    count = other.count;
    addresses = new Address[count];
    for (int i = 0; i < count; ++i) {
        addresses[i] = other.addresses[i];
    }
}

Developer::~Developer() {
    delete[] addresses;
}

void Developer::addAddress(const Address& addr) {
    Address* temp = new Address[count + 1];
    for (int i = 0; i < count; ++i) {
        temp[i] = addresses[i];
    }
    temp[count++] = addr;
    delete[] addresses;
    addresses = temp;
}

void Developer::setAddresses(const Address* addresses, int count) {
    delete[] this->addresses;
    this->addresses = new Address[count];
    this->count = count;
    for (int i = 0; i < count; ++i) {
        this->addresses[i] = addresses[i];
    }
}

const Address* Developer::getAddresses() const {
    return addresses;
}

int Developer::getCount() const {
    return count;
}

const Developer& Developer::operator=(const Developer& rhs) {
    if (this != &rhs) {
        delete[] addresses;
        count = rhs.count;
        addresses = new Address[count];
        for (int i = 0; i < count; ++i) {
            addresses[i] = rhs.addresses[i];
        }
    }
    return *this;
}

int Developer::QuickSortHelper(Address *a, int low, int high) {
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (a[j].apartment <= a[high].apartment) {
            i++;
            Address temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
    }
    Address temp = a[i + 1];
    a[i + 1] = a[high];
    a[high] = temp;
    return i + 1;
}

void Developer::QuickSort(int low, int high) {
    Address *a = addresses;
    if (low < high) {
        int pi = QuickSortHelper(a, low, high);
        QuickSort(low, pi - 1);
        QuickSort(pi + 1, high);
    }
}

void Developer::ShakerSort() {
    bool swapped = true;
    int start = 0;
    int end = count - 1;
    while (swapped) {
        swapped = false;
        for (int i = start; i < end; ++i) {
            if (addresses[i] > addresses[i + 1]) {
                Address temp = addresses[i + 1];
                addresses[i + 1] = addresses[i];
                addresses[i] = temp;
                swapped = true;
            }
        }
        if (!swapped) break;
        swapped = false;
        --end;
        for (int i = end - 1; i >= start; --i) {
            if (addresses[i] > addresses[i + 1]) {
                Address temp = addresses[i+1];
                addresses[i+1] = addresses[i];
                addresses[i] = temp;
                swapped = true;
            }
        }
        ++start;
    }
}

ostream& operator<<(ostream& out, const Developer& dev) {
    out << "Застройщик продаёт " << dev.getCount() << " квартир:" << endl << endl;
    for (int i = 0; i < dev.getCount(); ++i) {
        out << dev.getAddresses()[i] << '\n';
    }
    return out;
}

istream& operator>>(istream& in, Developer& dev) {
    int s, count;
    cout << endl << "Введите 0, если хотите ввести адреса вручную, иначе - любое другое число: " << endl;
    cin >> s;
    cin.ignore();
    cout << "Введите количество адресов для застройщика: " << endl;
    cin >> count;
    cin.ignore();
    Address* addresses = new Address[count];
    for (int i = 0; i < count; ++i) {
        if (s==0){
            cin >> addresses[i];
        }
        else addresses[i].setAddressRandomly();
    }
    dev.setAddresses(addresses, count);
    delete[] addresses;
    return in;
}

void Developer::increase(){
    cout << "Случайный адрес, который будет увеличен с помощью инкремента: " << endl << endl;
    int i = rand()%getCount();
    cout << addresses[i];
    cout << "Случайный адрес, увеличенный с помощью инкремента: " << endl << endl;
    addresses[i]++;
    cout << addresses[i];
}

void Developer::add(){
    cout << "Введите число, на которое нужно увеличить случайный адрес: " << endl << endl;
    int a;
    cin >> a;
    cout << "Случайный адрес, который будет увеличен: " << endl << endl;
    int i = rand()%getCount();
    cout << addresses[i];
    cout << "Случайный адрес, увеличенный с помощью инкремента: " << endl << endl;
    addresses[i]+=a;
    cout << addresses[i];
}
