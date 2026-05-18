#ifndef MARKETPLACE_H
#define MARKETPLACE_H
#include <iostream>
#include "User.h"
using namespace std;
class Marketplace {
private:
    string name;
public:
    Marketplace(string n);
    void display();
};
#endif
