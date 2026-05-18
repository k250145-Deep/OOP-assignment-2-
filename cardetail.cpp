#include "Cardetail.h"
Cardetail::Cardetail(int d, string f) : doors(d), fueltype(f) {}
void Cardetail::displaycar() const {
    cout << "Doors: " << doors << " Fuel: " << fueltype << endl;
}
bool Cardetail::operator==(const Cardetail& other) const {
    return fueltype == other.fueltype;
}
Cardetail Cardetail::operator+(const Cardetail& other) const {
    return Cardetail(doors, fueltype);
}
ostream& operator<<(ostream& out, const Cardetail& cd) {
    out << "Doors: " << cd.doors << " Fuel: " << cd.fueltype;
    return out;
}
istream& operator>>(istream& in, Cardetail& cd) {
    in >> cd.doors >> cd.fueltype;
    return in;
}
