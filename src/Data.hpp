#include <vector>
#include <string>

enum type {NUM, CAT};


class AttributeNum{
    std::string name;
    std::vector<double> attributeNums;

    AttributeNum(std::string name_);
};

class AttributeCat{
    std::string name;
    std::vector<std::string> attributeCats;

    AttributeCat(std::string name_);
};

class Data{
    std::vector<AttributeNum> collumnsNUM;
    std::vector<AttributeCat> collumnsCAT;
};