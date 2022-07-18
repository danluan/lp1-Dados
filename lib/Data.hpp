#ifndef DATA_H_
#define DATA_H_

#include <vector>
#include <string>

#include "Attributes.hpp"
#include "Object.hpp"

const double UNKNOWK_NUMERIC = -123.457;

class Data{
public:
    std::vector<Attributes> attributesList; //Lista que armazena os nomes e os tipos dos atributos, assim como os conjuntos categóricos
    std::vector<Object> objects; //Lista dos objetos, cada um possui uma lista de atributos numéricos e categóricos

    void readFiles(std::string directory);
    void analysisFiles(float P, int C);
    std::string setDistClass(std::vector<Object> trainers, int C);

    bool addAttributeInList(std::string line);
    bool addAttributeData(std::string line, int index);
    bool isNumeric(int index);
    bool validCatData(std::string str, int index);
    bool lineIsValid(std::string str);
    double distFunc(Object tester, Object trainer);

    void showData();

    double getNumValueInIndex(int row, int col);
    std::string getCatValueInIndex(int row, int col);
    double stringToDouble(std::string str);
    std::pair<int, int> getIndexOutput(std::string classReal, std::string classCalc);
};

void sortTrainers(std::vector<Object> &objList);

void swapObject(Object &obj1, Object &obj2);
std::string cutSpaces(std::string str);
std::string cutScrap(std::string str);
std::vector<std::string> split(std::string str);
bool hasSpaces(std::string str);

#endif