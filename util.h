#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates  
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
typename std::set<T>::iterator it1 = s1.begin();
typename std::set<T>::iterator it2 = s2.begin();
    std::set<T> setI;

while (it1 != s1.end() && it2 != s2.end()) 
{
    if (*it1 < *it2) 
    {
        it1++;
    } else if (*it1 > *it2) {
        it2++;
    }
    else 
    {
        setI.insert(*it1);
        it1++;
        it2++;
    }

}
    return setI;
}


template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
    std::set<T> setU = s1;
    setU.insert(s2.begin(), s2.end());
    return setU;

}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) ;

// trim from end
std::string &rtrim(std::string &s) ;

// trim from both ends
std::string &trim(std::string &s) ;
#endif
