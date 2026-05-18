#include <iostream>
#include "Vehicle.h"
#include "User.h"
#include "Marketplace.h"

using namespace std;

int main() {

    Vehicle v1("Toyota", "Corolla", 3000000);
    Vehicle v2("Honda", "Civic", 2500000);

    v1.displayDetails();
    cout << (v1 < v2 ? "v1 cheaper" : "v2 cheaper") << endl;

    User u1("Ahmed");
    u1.verify();
    u1.displayDetails();

    Marketplace m("PakWheels Clone");
    m.display();

    return 0;
}
