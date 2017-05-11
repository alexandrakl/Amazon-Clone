#include <sstream>
#include <iomanip>
#include "product.h"

using namespace std;

Product::Product(const std::string category, const std::string name, double price, int qty) :
    name_(name),
    price_(price),
    qty_(qty),
    category_(category)
{

}

Product::~Product()
{}


double Product::getPrice() const
{
    return price_;
}

std::string Product::getName() const
{
    return name_;
}

void Product::subtractQty(int num)
{
    qty_ -= num;
}

int Product::getQty() const
{
    return qty_;
}

/**
 * default implementation...can be overriden in a future
 * assignment
 */
bool Product::isMatch(std::vector<std::string>& searchTerms) const
{
    return false;
}

void Product::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << endl;
}

void Product::addReview(Review* r){
    reviews_.push_back(r);
}

double Product::getAverageRating() const {
        std::vector<Review *>::const_iterator lit;
        double sum = 0.0;
        double counter = 0.0;
        for (lit = reviews_.begin(); lit != reviews_.end(); lit++) {
            sum += (*lit)->rating;
            counter++;
        }      
        return sum/counter;
    }

std::vector<Review*> Product::getReviews() {
        return reviews_;
    }


