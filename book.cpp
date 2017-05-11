#include "book.h"
#include "product.h"
#include "util.h"
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, std::string isbn, std::string author) 
    :Product(category, name, price, qty), isbn_(isbn), author_(author)
{
}
    
Book::~Book() {}

std::set<std::string> Book::keywords() const {
        string total = name_ + " " + author_ + " ";
        std::set<std::string> tempSet = parseStringToWords(total);
        tempSet.insert(isbn_);
        return tempSet;
}

std::string Book::displayString() const {
        std::stringstream ss;
        ss << price_;
        string price = ss.str();
        std::stringstream ss1;
        ss1 << qty_;
        string qty = ss1.str();
        string temp = name_ + "\n" + "Author: " + author_ + " ISBN: " + isbn_ + "\n" + price + " " + qty + " left.";
        return temp;
}

void Book::dump(std::ostream& os) const {
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << endl;
}

