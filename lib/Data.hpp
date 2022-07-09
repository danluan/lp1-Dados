#ifndef DATA_H_
#define DATA_H_

#include <vector>
#include <string>

#include "Attributes.hpp"
#include "Object.hpp"

class Data{
public:
    std::vector<Attributes> attributesList; //Lista que armazena os nomes e os tipos dos atributos, assim como os conjuntos categóricos
    std::vector<Object> objects; //Lista dos objetos, cada um possui uma lista de atributos numéricos e categóricos

    void readFiles(std::string directory);
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

#endif