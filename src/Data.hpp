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
    std::vector<std::string> attributeCats;

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

class Data{
    std::vector<std::string> attributesList; //List of {CAT, NUM, NUM ... }
    std::vector<ObjectRow> objects;
};

void startReadFiles(Data newRead);