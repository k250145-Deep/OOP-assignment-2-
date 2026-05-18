#include "Marketplace.h"

Marketplace::Marketplace(string n) : name(n) {}

void Marketplace::display() {
    cout << "Marketplace: " << name << endl;
}
