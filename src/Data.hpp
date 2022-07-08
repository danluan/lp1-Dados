#include <vector>
#include <string>

enum type {NUM, CAT};

class AttributeNum{
public:
    int indexColN;
    std::string name;
    double attributeNum;

    AttributeNum(std::string name_, int index_);
};

class AttributeCat{
public:
    int indexColC;
    std::string name;
    std::string attributeCat;

    AttributeCat(std::string name_, int index_);
    void addAttributeCats(std::string setOfCategories);
};

class ObjectRow{
public:
    int indexRow;
    std::vector<AttributeNum> collumnsNUM;
    std::vector<AttributeCat> collumnsCAT;

    void addAttrbNUM();
    void addAttrbCAT();

    ObjectRow(int index_);
};

class Attributes{
public:
    std::vector<std::string> attribute; 
    std::string name;

    Attributes(std::string name_);
};

class Data{
public:
    std::vector<Attributes> attributesList; //List of {CAT, NUM, NUM ... }
    std::vector<ObjectRow> objects;

    void startReadFiles();
    bool addAttributeInList(std::string line);
    bool addAttributeData(std::string line, int index);
    bool isNumeric(int index);

    void showData();

    double stringToDouble(std::string str);
};

std::string cutSpaces(std::string str);
std::string cutScrap(std::string str);
std::vector<std::string> split(std::string str);
bool hasSpaces(std::string str);
bool validCatData(std::string str);