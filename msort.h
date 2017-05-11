#ifndef MSORT_H
#define MSORT_H

#include <iostream>
#include <vector>
#include <string>


struct comp {
    bool operator()(const int lhs, const int rhs) 
    { 
      return lhs > rhs; 
    }
 };

 struct doubleRating {
    bool operator()(const std::pair<std::string, double> lhs, const std::pair<std::string, double> rhs) 
    { 
        if (lhs.second == rhs.second) {
            return lhs.first < rhs.first;
        }
      return lhs.second > rhs.second; 
    }
 };

struct productName {
    bool operator()(const Product* lhs, const Product* rhs) 
    { 
      return lhs->getName() < rhs->getName(); 
    }
 };

struct averageRating {
    bool operator()(const Product* lhs, const Product* rhs) 
    { 
      return lhs->getAverageRating() < rhs->getAverageRating(); 
    }
 };

 struct reviewDate {
    bool operator()(const Review* lhs, const Review* rhs) 
    { 
      return lhs->getDate() > rhs->getDate(); 
    }
 };

template <class T, class Comparator>
void mergeHelper(std::vector<T> &myArray, int i1, int j1, int i2, int j2, Comparator comp) {
    std::vector<T> a(myArray);
    int index = i1;
    while(i1 <= j1 && i2 <= j2) {
        if (comp(a[i1], a[i2])) {
            myArray[index++] = a[i1++];
        } else {
            myArray[index++] = a[i2++];
        }
    }
    while(i1 <= j1) {
        myArray[index++] = a[i1++];
    }
    while(i2 <= j2) {
        myArray[index++] = a[i2++];
    }
}

template <class T, class Comparator>
void mergeSortHelper(std::vector<T> &myArray, int index1, int index2, Comparator comp) {
    //one or none 
    if (index1 >= index2) {
        return;
    }
    //recursive call
    int midIndex = (index1+index2) / 2;
    mergeSortHelper(myArray, index1, midIndex, comp);
    mergeSortHelper(myArray, midIndex+1, index2, comp);

    mergeHelper(myArray, index1, midIndex, midIndex+1, index2, comp);
}


template <class T, class Comparator>
void mergeSort (std::vector<T>& myArray, Comparator comp) {
    mergeSortHelper(myArray, 0, myArray.size() - 1, comp);
}


#endif