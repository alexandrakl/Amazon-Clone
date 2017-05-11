#ifndef MOVIE_H
#define MOVIE_H
#include "product.h"
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

class Movie : public Product {
public:
Movie(std::string category, std::string name, double price, int qty, std::string genre, std::string rating);

~Movie();

    /**
     * Returns the appropriate keywords that this product should be associated with
     */
std::set<std::string> keywords() const;

    /**
     * Returns a string to display the product info for hits of the search
     */
std::string displayString() const;

    /**
     * Outputs the product info in the database format
     */
void dump(std::ostream& os) const;

    /**
     * Accessors and mutators
     */
double getPrice() const;
std::string getName() const;
int getQty() const;
void subtractQty(int num);

private:
    std::string genre_;
    std::string rating_;

};

#endif