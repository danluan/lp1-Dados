#ifndef ATTRIBUTE_CAT_H_
#define ATTRIBUTE_CAT_H_

#include <string>

class AttributeCat{
public:
    int indexColC;
    std::string name;
    std::string attributeCat;

    AttributeCat(std::string name_, int index_);
    void addAttributeCats(std::string setOfCategories);
};

#endif