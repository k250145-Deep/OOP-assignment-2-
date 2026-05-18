#ifndef IDISPLAYABLE_H
#define IDISPLAYABLE_H
class IDisplayable {
public:
    virtual void displayDetails() const = 0;
    virtual ~IDisplayable() {}
};
#endif
