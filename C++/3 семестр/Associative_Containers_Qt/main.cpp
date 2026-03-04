#include <QVector>
#include <QMap>
#include <QString>
#include <QMultiMap>
#include <QFile>
#include <QTextStream>
#include <QCoreApplication>

using namespace std;

template <typename T>
void printVector(const QVector<T>& V);

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QTextStream cin(stdin);
    QTextStream cout(stdout);

    QString choice;
    do {
        unsigned int f = 0;
        QString s;
        QVector<QString> coms;

        QFile input("table.txt");
        if (!input.open(QIODevice::ReadOnly | QIODevice::Text)) {
            cout << "Cannot open file table.txt" << Qt::endl;
            return 1;
        }

        QTextStream in(&input);
        s = in.readLine();
        s += '\t';

        while (s.indexOf('\t') != -1) {
            int n;
            if (f < 2) {
                n = s.indexOf('\t');
                s = s.mid(n + 1);
                f++;
            } else {
                n = s.indexOf('\t');
                coms.push_back(s.mid(0, n));
                s = s.mid(n + 1);
            }
        }

        cout << "Companies: " << Qt::endl;
        printVector(coms);

        QMultiMap<QString, QMultiMap<QString, QString>> M;

        while (!in.atEnd()) {
            QString line = in.readLine();
            if (line.isEmpty()) continue;

            QTextStream stream(&line);
            QString departure, arrival;
            stream >> departure >> arrival;

            QVector<unsigned int> prices(coms.size(), 0);

            for (int i = 0; i < coms.size() && !stream.atEnd(); i++) {
                QString priceStr;
                stream >> priceStr;
                if (priceStr == "-" || priceStr == "-") {
                    prices[i] = 0;
                } else {
                    bool ok;
                    unsigned int price = priceStr.toUInt(&ok);
                    if (ok) {
                        prices[i] = price;
                    } else {
                        prices[i] = 0;
                    }
                }
            }

            bool hasValidPrice = false;
            for (int i = 0; i < prices.size(); i++) {
                if (prices[i] != 0) {
                    hasValidPrice = true;
                    break;
                }
            }

            if (!hasValidPrice) {
                QMultiMap<QString, QString> innerMap;
                innerMap.insert(arrival, "No flights available");
                M.insert(departure, innerMap);
            } else {
                unsigned int minPrice = 0;
                QVector<QString> minCompanies;
                bool firstValidFound = false;
                for (int i = 0; i < prices.size(); i++) {
                    if (prices[i] != 0) {
                        if (!firstValidFound) {
                            minPrice = prices[i];
                            firstValidFound = true;
                        } else if (prices[i] < minPrice) {
                            minPrice = prices[i];
                        }
                    }
                }

                for (int i = 0; i < prices.size(); i++) {
                    if (prices[i] == minPrice && prices[i] != 0) {
                        minCompanies.push_back(coms[i] + " (" + QString::number(prices[i]) + ")");
                    }
                }

                QMultiMap<QString, QString> innerMap;
                if (minCompanies.size() > 1) {
                    QString result = "Companies with minimum price " + QString::number(minPrice) + ": ";
                    for (int i = 0; i < minCompanies.size(); i++) {
                        result += minCompanies[i];
                        if (i < minCompanies.size() - 1) {
                            result += ", ";
                        }
                    }
                    innerMap.insert(arrival, result);
                } else if (minCompanies.size() == 1) {
                    innerMap.insert(arrival, minCompanies[0]);
                }
                M.insert(departure, innerMap);
            }
        }
        input.close();

        QString userDeparture, userArrival;
        cout << "\nEnter departure city: " << Qt::flush;
        userDeparture = cin.readLine();
        cout << "Enter arrival city: " << Qt::flush;
        userArrival = cin.readLine();

        bool found = false;
        QString bestCompany;

        auto range = M.equal_range(userDeparture);
        for (auto it = range.first; it != range.second; ++it) {
            auto& innerMap = it.value();
            auto innerRange = innerMap.equal_range(userArrival);
            for (auto innerIt = innerRange.first; innerIt != innerRange.second; ++innerIt) {
                bestCompany = innerIt.value();
                found = true;
            }
        }

        if (found) {
            cout << Qt::endl << "Company with minimum price: " << bestCompany << Qt::endl;

            cout << Qt::endl << "Do you want to save the cheapest price to file? (Y/N)" << Qt::endl;
            QString choice1;
            cin >> choice1;
            if (choice1 == "Y" || choice1 == "y") {
                cout << Qt::endl;
                QFile output("output.txt");
                if (output.open(QIODevice::WriteOnly | QIODevice::Text)) {
                    QTextStream out(&output);
                    out << userDeparture << "\t" << userArrival << "\t" << bestCompany << Qt::endl;
                    cout << "The cheapest flight has been saved to 'output.txt'" << Qt::endl;
                    output.close();
                }
            }

        } else {
            cout << Qt::endl << "No flights found for the specified route." << Qt::endl;
        }
        cin.readLine();

        cout << Qt::endl << "Do you wish to find another price? (Y/N)" << Qt::endl;
        choice = cin.readLine();
        cout << Qt::endl;

    } while (choice == "Y" || choice == "y");

    return 0;
}

template <typename T>
void printVector(const QVector<T>& V) {
    QTextStream cout(stdout);
    typename QVector<T>::const_iterator iter;
    for (iter = V.begin(); iter != V.end(); iter++) {
        cout << *iter << " ";
    }
    cout << Qt::endl;
}
