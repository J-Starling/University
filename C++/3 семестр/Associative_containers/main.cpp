#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <map>
#include <string>
#include <sstream>

using namespace std;

template <typename T>
void printVector(const vector<T>&);

int main()
{
    char choice;
    do {
        unsigned int f = 0;
        string s;
        vector<string> coms;
        ifstream input("table.txt", ios::in);
        getline(input, s);
        s+='\t';

        while (s.find('\t') != string::npos) {
            int n;
            if (f < 2) {
                n = s.find('\t');
                s = s.substr(n + 1, s.size());
                f++;
            } else {
                n = s.find('\t');
                coms.push_back(s.substr(0, n));
                s = s.substr(n + 1, s.size());
            }
        }

        cout << "Companies: " << endl;
        printVector(coms);

        multimap<string, multimap<string, string>> M;

        string line;
        while (getline(input, line)) {
            if (line.empty()) continue;

            stringstream ss(line);
            string departure, arrival;
            ss >> departure >> arrival;

            vector<unsigned int> prices(coms.size(), 0);

            for (unsigned int i = 0; i < coms.size() && ss; i++) {
                if (ss >> prices[i]) {
                } else {
                    prices[i] = 0;
                    ss.clear();
                }
            }


            bool hasValidPrice = false;
            for (unsigned int i = 0; i < prices.size(); i++) {
                if (prices[i] != 0) {
                    hasValidPrice = true;
                    break;
                }
            }

            if (!hasValidPrice) {

                multimap<string, string> innerMap;
                innerMap.insert(make_pair(arrival, "No flights available"));
                M.insert(make_pair(departure, innerMap));
            } else {

                unsigned int minPrice = 0;
                string minCompany;
                bool firstValidFound = false;

                for (unsigned int i = 0; i < prices.size(); i++) {
                    if (prices[i] != 0) {
                        if (!firstValidFound) {
                            minPrice = prices[i];
                            minCompany = coms[i] + " (" + to_string(prices[i]) + ")";
                            firstValidFound = true;
                        } else if (prices[i] < minPrice) {
                            minPrice = prices[i];
                            minCompany = coms[i] + " (" + to_string(minPrice) + ")";
                        }
                    }
                }


                bool allSame = true;
                unsigned int firstValidPrice = 0;
                unsigned int validCount = 0;

                for (unsigned int i = 0; i < prices.size(); i++) {
                    if (prices[i] != 0) {
                        validCount++;
                        if (firstValidPrice == 0) {
                            firstValidPrice = prices[i];
                        } else if (prices[i] != firstValidPrice) {
                            allSame = false;
                            break;
                        }
                    }
                }

                multimap<string, string> innerMap;
                if (allSame && validCount > 1) {
                    innerMap.insert(make_pair(arrival, "All companies have the same prices (" + to_string(firstValidPrice) + ")"));
                } else {
                    innerMap.insert(make_pair(arrival, minCompany));
                }
                M.insert(make_pair(departure, innerMap));
            }
        }

        string userDeparture, userArrival;
        cout << "\nEnter departure city: ";
        cin >> userDeparture;
        cout << "Enter arrival city: ";
        cin >> userArrival;

        bool found = false;
        string bestCompany;

        auto range = M.equal_range(userDeparture);
        for (auto it = range.first; it != range.second; ++it) {
            auto& innerMap = it->second;
            auto innerRange = innerMap.equal_range(userArrival);
            for (auto innerIt = innerRange.first; innerIt != innerRange.second; ++innerIt) {
                bestCompany = innerIt->second;
                found = true;
            }
        }

        if (found) {
            cout << endl << "Company with minimum price: " << bestCompany << endl;

            cout << endl << "Do you want to save the map of all the cheapest prices to file? (Y/N)" << endl;
            char choice1;
            cin >> choice1;
            if (choice1 == 'Y' || choice1 == 'y') {
                cout << endl;
                ofstream output("output.txt", ios::out);
                typename multimap<string, multimap<string, string>>::const_iterator iter;
                for (iter = M.begin(); iter != M.end(); ++iter) {
                    const string& departure = iter->first;
                    const multimap<string, string>& innerMap = iter->second;
                    typename multimap<string, string>::const_iterator innerIter;
                    for (innerIter = innerMap.begin(); innerIter != innerMap.end(); ++innerIter) {
                        output << departure << "\t" << innerIter->first << "\t" << innerIter->second << endl;
                    }
                }
                cout << "All cheapest flights have been saved to 'output.txt'" << endl;
            }

        } else {
            cout << endl << "No flights found for the specified route." << endl;
        }

        cout << endl << "Do you wish to find another price? (Y/N)" << endl;
        cin >> choice;
        cout << endl;

    } while (choice == 'Y' || choice == 'y');

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
