#ifndef REVIEW_H
#define REVIEW_H
#include <string>
#include <sstream>

struct Review
{
    Review() :  prodName(), rating(), username(), date(), reviewText()
    { }
    Review(const std::string& prod,
           int rate,
           const std::string& u,
           const std::string& d,
           const std::string& review_text) :
        prodName(prod),
        rating(rate),
        username(u),
        date(d),
        reviewText(review_text)
    { }

    std::string prodName;
    int rating;
    std::string username;
    std::string date;
    std::string reviewText;

std::string getDate() const {
        return date;
    }

std::string displayString() {
    std::stringstream ss;
    ss << rating;
    std::string stringRating = ss.str();
    std::string temp = stringRating + "/5\n" + username + "\n" + date + "\n" + reviewText;
    return temp;
    }

    std::string getUsername() {
        return username;
    }

    void dump(std::ostream& ofile) {
        ofile << prodName << std::endl;
        ofile << rating << " " << username << " " << date << " " << reviewText << std::endl; 
    }
};

#endif
