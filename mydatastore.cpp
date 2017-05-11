#include <string>
#include <set>
#include <vector>
#include <map>
#include <list>
#include "product.h"
#include "user.h"
#include "datastore.h"
#include "mydatastore.h"
#include "util.h"
#include "product_parser.h"
#include "review.h"
#include <stdlib.h>
#include <limits>
#include <fstream>
using namespace std;

MyDataStore::MyDataStore(){
}

void MyDataStore::addProduct(Product* p) {
    productSet_.insert(p);
    productVector_.push_back(p);
    
//used in search
    std::set<std::string> keywordsSet = p->keywords(); //set of all keywords
    std::set<std::string>::iterator itSet;
    std::map<std::string, std::set<Product*> >::iterator itMap;
// insert in map keyword->set of products , all keywords from product 
    for (itSet = keywordsSet.begin();
        itSet != keywordsSet.end();
        itSet++) {
            myMap_[*itSet].insert(p);   
    }

}

void MyDataStore::addUser(User* u) {
    userMap_.insert(std::make_pair(u->getName(),u));
    userVector_.push_back(u);
//when add a user update map of user carts
    std::list<Product*> cart;
    userCarts_.insert(std::make_pair(u, cart));
}

//search is not called after add so the for loop for keywords is never run
//make another method to store all strings from database.txt
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
std::vector<Product*> products;
   std::set<Product*> setProducts;
   std::set<Product*> tempSet;
   std::set<Product*>::iterator it;
   string temp = "";

   for (unsigned int i = 0; i < terms.size(); i++) {
            temp = terms[i];
           // if no elements
            if (setProducts.empty() && i == 0) {
                setProducts = myMap_[temp];
            } else {
            tempSet = myMap_[temp];
           
            // set intersection
            if (type == 0) {
                setProducts = setIntersection(setProducts, tempSet);  
            } 
            // set union
            else if (type == 1) {
                setProducts = setUnion(setProducts, tempSet);
            }
        }
   }

   for (it = setProducts.begin(); it != setProducts.end(); it++) {
           products.push_back(*it);
   }
   //save product
   prevSearch_ = products;
   return products;
}

void MyDataStore::dump(std::ostream& ofile) {
    ofile << "<products>" << endl;
    for (unsigned int i = 0; i < productVector_.size(); i++) {
       productVector_[i]->dump(ofile);
    }
   ofile  << "</products>" << endl;
   ofile << "<users>" <<  endl;
   for (unsigned int i = 0; i < userVector_.size(); i++) {
       userVector_[i]->dump(ofile);
    }
   ofile << "</users>" << endl;
    ofile  << "<reviews>" << std::endl;
   std::vector<Review*> temp;
    for (unsigned int i = 0; i < productVector_.size(); i++) {
        temp = productVector_[i]->getReviews();
        for (int j = 0; j <(int)temp.size(); j++) {
            temp.at(j)->dump(ofile);
        }
    }
    ofile  << "</reviews>" << std::endl; 
}

void MyDataStore::addToCart(string user, int i) {
    if (userMap_.find(user) == userMap_.end()) {
        cout << "Invalid request , wrong username" << endl;
        return;
    }
//add the product to cart list at the specified user
    User* myUser = userMap_[user];
    Product* p = prevSearch_[i-1];
    userCarts_[myUser].push_back(p);
    cout << p->displayString() << endl;
    std::map<User*, std::list<Product*> >::iterator itTempMap;
    std::list<Product*> tempListPrint;

}

void MyDataStore::removeFromCart(string user, Product* p) {
    if (userMap_.find(user) == userMap_.end()) {
        cout << "Invalid request , wrong username" << endl;
        return;
    }
    std::list<Product*> cart;
    std::list<Product*>::iterator it;
    User* myUser = userMap_[user];
    cart = userCarts_[myUser];
	cart.remove(p);
    userCarts_[myUser] = cart;
}

void MyDataStore::viewCart(string user) {
    if (userMap_.find(user) == userMap_.end()) {
        cout << "Invalid username" << endl;
        return;
    }
    User* u = userMap_[user];
    std::list<Product*> temp = userCarts_[u];
    std::list<Product*>::iterator it;

    int count = 0;
    for (it = temp.begin(); it != temp.end(); it++) {
        count++;
    }
}

void MyDataStore::buyCart(string user) {
    // check Invalid input
     if (userMap_.find(user) == userMap_.end()) {
         cout << "Invalid username" << endl;
         return;
     }
    User* u = userMap_[user];
    //user's credit
    double credit = u->getBalance();
    std::list<Product*> temp = userCarts_[u];
    std::list<Product*> t;
    while (!temp.empty()) {
         //if cannot afford or not inside the datastore of products
        std::set<Product* >::iterator itSet = productSet_.find(temp.front());
        if ( temp.front()->getPrice() > credit  || (*temp.front()).getQty() == 0 ) {
            t.push_back(temp.front());
            temp.pop_front();
        } 
        //can buy 
        else {
            //update credit
            u->deductAmount(temp.front()->getPrice());
            credit -= (temp.front()->getPrice());
            //update datastore
            (*itSet)->subtractQty(1);
            userCarts_[u].pop_front();
            //pop
            temp.pop_front(); 
        }
    }
    while (!t.empty()) {
        temp.push_back(t.front());
            t.pop_front();
    }
}

void MyDataStore::addReview(Review* r) {
    std::set<Product* >::iterator it;
    bool found = false;
    for (it = productSet_.begin(); it != productSet_.end(); it++) {
        if ((*it)->getName() == r->prodName) {
            (*it)->getReviews().push_back(r);
            found = true;
            break;
        }
    }
    // not found prodName
    if (found == false) {
        orphanReviews_.push_back(r);
    }
    else {
        (*it)->addReview(r);
    }

Product *pr;
User *u;
for (int i = 0; i < (int)userVector_.size(); i++) {
        if (r->getUsername() == userVector_[i]->getName()) {
            pr = findProduct(r->prodName);
            u = findUser(r->getUsername());
            u->reviewsU_.insert(pr);
        }  
    }
}



double MyDataStore::getSimilarity(User* a, User* b) {
   
    std::set<Product*> setA = a->reviewsU_;
    std::set<Product*> setB = b->reviewsU_;
    std::set<Product*> setI = setIntersection(setA, setB);
    std::set<Product*>::iterator sit;
    Product* p;
    int aRating = 0;
    int bRating = 0;
    double sim = 0.0;
    double simSum = 0.0;
    
    if (setI.size() == 0) 
    {
        return 1.0;
    }

    for (sit = setI.begin(); sit != setI.end(); sit++) 
    {
        std::vector<Review*> reviews = (*sit)->getReviews();
        for (int i = 0; i < (int)reviews.size(); i++) 
        {
            if (reviews[i]->username == a->getName()) 
            {
                aRating = reviews[i]->rating;
            }
            else if (reviews[i]->username == b->getName()) 
            {
                bRating = reviews[i]->rating;
            } 
        }  
        sim = (double)abs(aRating-bRating)/4;
        simSum = simSum + sim; 
    }
    return simSum/setI.size();

}

map<string, map<string, double> >MyDataStore::getSimilarityUserMap() {
    map<string, map<string, double> > myMap;
    for (int i = 0; i < (int)userVector_.size(); i++) {
            map<string, double> tempMap;
        for (int j = 0; j < (int)userVector_.size(); j++) {
            if (userVector_[j]->getName() != userVector_[i]->getName()) {
                tempMap[userVector_[j]->getName()] = getSimilarity(userVector_[j], userVector_[i]);
            }
        }
         myMap[userVector_[i]->getName()] = tempMap;
    }
    return myMap;
}

// djikstra function that instantiates heap and calls in decrease key from heap
map<string, double> MyDataStore::djikstra(string username) 
{
    //every node is a username string
    Heap<string> pq;
    double inf = std::numeric_limits<double>::infinity();
    std::map<string, map<string, double> > myMap = getSimilarityUserMap();
    map<string, double> simMap; //return make suggestion use
    pq.push(0.0, username);
    for (int i = 0; i < (int)userVector_.size(); i++) 
    {
        if (userVector_[i]->getName() != username) 
        {
            pq.push(inf, userVector_[i]->getName());
        }
    }
    while (!pq.empty()) {
        string u = pq.top().second;
        pq.pop();
        for (int j = 0; j < (int)userVector_.size(); j++ ) 
        {
            if (userVector_[j]->getName() != u) 
            {
                string v = userVector_[j]->getName(); 
                double sumDist = myMap[u][v];
                pq.decreaseKey(sumDist,v);
                if (!pq.empty() ) 
                {
                    simMap[v] = pq.top().first;
                }
                
            }
        }           
    }
  
    return simMap;
}

//helper function to find users from usernames
User* MyDataStore::findUser(string username) {
    User* user;
    vector<User*>::iterator vit;
     for (vit = userVector_.begin(); vit != userVector_.end(); vit++) {
            if ((*vit)->getName() == username) {
                user = (*vit);
            } 
     }
     return user;       
}

//helper function to find products from their names
Product* MyDataStore::findProduct(string productName) {
    Product * p;
    vector<Product*>::iterator vit;
     for (vit = productVector_.begin(); vit != productVector_.end(); vit++) 
     {
            if ((*vit)->getName() == productName) {
                p = (*vit);
            } 
     }
     return p;       
}

std::vector<std::pair<std::string, double> > MyDataStore::makeSuggestion(std::string currentUser) {
    double totalSim = 0.0;
    double totalRatings = 0.0;
    double rating = 0.0;
    double finalRating = 0.0;
    double sim = 0.0;
    Product *p;
    Review *r;
     std::set<Product*> setP;

    vector<std::pair<string, double> > recommendations;
    map<string, double> simMap = djikstra(currentUser);
    set<string> userReviewSet;
   
  
for (int i = 0; i < userVector_.size(); i++) {
    cout << "Similarity of user: " << userVector_[i]->getName() << getSimilarity(userLoggedIn, userVector_[i]) << endl;
}
    //for each product
    for (int i = 0; i < (int)productVector_.size(); i++) 
    {
        p = productVector_[i];
        vector<Review*> reviews = p->getReviews();
        
        for (int j = 0; j < (int)reviews.size(); j++) 
        {
            r = reviews[j];

            User* u = findUser(r->username);

            if ( u != NULL) 
            {
                userReviewSet.insert(r->username);
            }
           
            // if the logged in user did not review item
            if (userLoggedIn != u) 
            {
               sim = simMap[u->getName()];
            } 

            rating = (double)r->rating;
            totalRatings = totalRatings + (1-sim)*rating;
            totalSim = totalSim + (1-sim);
            
        }

        if (userReviewSet.find(userLoggedIn->getName()) == userReviewSet.end()) {
             if (totalRatings == 0.0 && totalSim == 0.0) 
            {
                finalRating =  0.0;
            }
            else 
            {
            finalRating = totalRatings/totalSim;
            }
       
            recommendations.push_back(make_pair(p->getName(), finalRating));
            }
       
        }       
        return recommendations;
    }