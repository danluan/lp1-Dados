#ifndef ATTRIBUTE_NUM_H_
#define ATTRIBUTE_NUM_H_

#include <string>

class AttributeNum{
public:
    int indexColN;
    std::string name;
    double attributeNum;

    AttributeNum(std::string name_, int index_);
};

#endif