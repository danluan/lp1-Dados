#ifndef OBJECT_H_
#define OBJECT_H_

#include "AttributeCat.hpp"
#include "AttributeNum.hpp"
#include <vector>

class Object{
public:
    int indexRow;
    std::vector<AttributeNum> collumnsNUM;
    std::vector<AttributeCat> collumnsCAT;
    double dist;

    Object(int index);

    double getNumInIndex(int col);
    std::string getCatInIndex(int col);

    void showObjects();
};

#endif