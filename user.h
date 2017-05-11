#ifndef USER_H
#define USER_H
#include <iostream>
#include <string>
#include <set>
#include "product.h"


/**
 * Implements User functionality and information storage
 *  You should not need to derive anything from User at this time
 */
class User {
public:
    User();
    User(std::string name, double balance, int type, unsigned int h);
    virtual ~User();

    double getBalance() const;
    std::string getName() const;
    void deductAmount(double amt);
    unsigned int getHash();
    virtual void dump(std::ostream& os);

    std::set<Product*>reviewsU_;

private:
    std::string name_;
    double balance_;
    int type_;
    unsigned int hash;
};
#endif
