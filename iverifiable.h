#ifndef IVERIFIABLE_H
#define IVERIFIABLE_H
class IVerifiable {
public:
    virtual void verify() = 0;
    virtual bool isVerified() const = 0;
    virtual ~IVerifiable() {}
};
#endif
