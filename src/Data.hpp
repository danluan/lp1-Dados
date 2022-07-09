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
    std::vector<Attributes> attributesList; //Lista que armazena os nomes e os tipos dos atributos, assim como os conjuntos categóricos
    std::vector<ObjectRow> objects; //Lista dos objetos, cada um possui uma lista de atributos numéricos e categóricos

    void startReadFiles();
    bool addAttributeInList(std::string line);
    bool addAttributeData(std::string line, int index);
    bool isNumeric(int index);

    void showData();
    bool validCatData(std::string str, int index);
    bool lineIsValid(std::string str);

    double stringToDouble(std::string str);
};

std::string cutSpaces(std::string str);
std::string cutScrap(std::string str);
std::vector<std::string> split(std::string str);
bool hasSpaces(std::string str);