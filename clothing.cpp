#include "clothing.h"
#include "product.h"
#include "util.h"
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand) 
    :Product(category, name, price, qty), size_(size), brand_(brand)
{
}
    
Clothing::~Clothing() {}

std::set<std::string> Clothing::keywords() const {
    string total = name_ + " " + brand_ + " ";
    std::set<std::string> tempSet = parseStringToWords(total);
    return tempSet;
}

/**
* Returns a string to display the product info for hits of the search
*/
std::string Clothing::displayString() const {
    std::stringstream ss;
    ss << price_;
    string price = ss.str();
    std::stringstream ss1;
    ss1 << qty_;
    string qty = ss1.str();
    string temp = name_ + "\n" + "Size: " + size_ + " Brand: " + brand_ + "\n" + price + " " + qty + " left.";
    return temp;
}

/**
* Outputs the product info in the database format
*/
void Clothing::dump(std::ostream& os) const {
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << endl;
}


