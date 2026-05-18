#ifndef ISEARCHABLE_H
#define ISEARCHABLE_H
#include <string>
using namespace std;
class ISearchable {
public:
    virtual bool matchesQuery(const string& keyword) const = 0;
    virtual ~ISearchable() {}
};
#endif
