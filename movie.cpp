#include "movie.h"
#include "product.h"
#include "util.h"
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating) 
    :Product(category, name, price, qty), genre_(genre), rating_(rating)
{
}
    
Movie::~Movie() {}

std::set<std::string> Movie::keywords() const {
    string total = name_ + " " + genre_ + " ";
    std::set<std::string> tempSet = parseStringToWords(total);
    return tempSet;
}

    /**
     * Returns a string to display the product info for hits of the search
     */
std::string Movie::displayString() const {
    std::stringstream ss;
    ss << price_;
    string price = ss.str();
    std::stringstream ss1;
    ss1 << qty_;
    string qty = ss1.str();
    string temp = name_ + "\n" + "Genre: " + genre_ + " Rating: " + rating_ + "\n" + price + " " + qty + " left.";
    return temp;
}

    /**
     * Outputs the product info in the database format
     */
void Movie::dump(std::ostream& os) const {
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << endl;
}

