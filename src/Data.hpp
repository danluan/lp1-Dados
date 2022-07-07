#include <vector>
#include <string>

enum type {NUM, CAT};

class AttributeNum{ //
    int indexColN;
    std::string name;
    std::vector<double> attributeNums;

    AttributeNum(std::string name_, int index_);
};

class AttributeCat{
    int indexColC;
    std::string name;
    std::string attributeCats;

    AttributeCat(std::string name_, int index_);
    void addAttributeCats(std::string setOfCategories);
};

class ObjectRow{
    int indexRow;
    std::vector<AttributeNum> collumnsNUM;
    std::vector<AttributeCat> collumnsCAT;

    void addAttrbNUM();
    void addAttrbCAT();

    ObjectRow();
};

class Attributes{
public:
    std::vector<std::string> attribute; //attribute is sigleton, numeric, else is categoric
    std::string name;

    Attributes(std::string name_);
};

class Data{
public:
    std::vector<Attributes> attributesList; //List of {CAT, NUM, NUM ... }
    std::vector<ObjectRow> objects;

    void startReadFiles();
    bool addAttributeInList(std::string line);

};

std::string cutSpaces(std::string str);
std::string cutScrap(std::string str);
std::vector<std::string> split(std::string str);