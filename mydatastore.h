#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <set>
#include <map>
#include <vector>
#include <list>
#include "product.h"
#include "user.h"
#include "datastore.h"
#include "util.h"
#include "review.h"
#include "heap.h"

class MyDataStore : public DataStore {
public:

    MyDataStore();

    ~MyDataStore() { }

    void addProduct(Product* p);

    void addUser(User* u);

    std::vector<Product*> search(std::vector<std::string>& terms, int type);

    void dump(std::ostream& ofile);

    void addToCart(std::string user, int i);

    void removeFromCart(std::string user, Product* p);

    void viewCart(std::string user);

    void buyCart(std::string user); 

    void addReview(Review* r);

    std::vector<User*> getUserVector() {
        return userVector_;
    }
    std::vector<Product*> getProductVector() {
        return productVector_;
    }
    std::map<User*, std::list<Product*> > getUserCartsMap() {
        return userCarts_;
    }
    std::map<std::string, User*> getUserMap() {
        return userMap_;
    }
    User* userLoggedIn;
    Product* findProduct(std::string productName);    
    double getSimilarity(User* a, User* b);
    std::map<std::string, std::map<std::string, double> > getSimilarityUserMap() ;
    std::map<std::string, double> djikstra(std::string username);
    std::vector<std::pair<std::string, double> > makeSuggestion(std::string currentUser);
    User* findUser(std::string username);

private:
    std::vector<Product*> productVector_;
    std::vector<User*> userVector_;
    std::set<Product*> productSet_;
    std::map<std::string, User*> userMap_;
    std::map<std::string, std::set<Product*> > myMap_;
    std::map<User*, std::list<Product* > > userCarts_;
    std::vector<Product* > prevSearch_;
    std::vector<Review*> orphanReviews_;
    std::map<User*, std::set<Review*> > userReviews_;
    std::map<User*, std::set<Product*> > userReviewsProducts_;


    
};

#endif


