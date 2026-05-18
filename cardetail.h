#ifndef CARDETAIL_H
#define CARDETAIL_H
#include <iostream>
#include <string>
using namespace std;
class Cardetail {
private:
    int doors;
    string fueltype;
public:
    Cardetail(int d=4, string f="PETROL");
    void displaycar() const;
    bool operator==(const Cardetail& other) const;
    Cardetail operator+(const Cardetail& other) const;
    friend ostream& operator<<(ostream&, const Cardetail&);
    friend istream& operator>>(istream&, Cardetail&);
};
#endif
