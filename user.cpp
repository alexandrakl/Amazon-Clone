#include "user.h"
using namespace std;

User::User() : name_("unknown"), balance_(0.0), type_(1), hash(0)
{

}
User::User(std::string name, double balance, int type, unsigned int h) :
    name_(name), balance_(balance), type_(type), hash(h)
{

}

User::~User()
{

}


std::string User::getName() const
{
    return name_;
}

double User::getBalance() const
{
    return balance_;
}

void User::deductAmount(double amt)
{
    balance_ -= amt;
}

unsigned int User::getHash() {
    return hash;
}

void User::dump(std::ostream& os)
{
    os << name_ << " "  << balance_ << " " << type_ << " " << hash << endl;
}
