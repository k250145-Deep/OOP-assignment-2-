#ifndef IREVIEWABLE_H
#define IREVIEWABLE_H
#include <string>
using namespace std;
class IReviewable {
public:
    virtual void addReview(int rating, const string& comment) = 0;
    virtual double getAverageRating() const = 0;
    virtual ~IReviewable() {}
};
#endif
