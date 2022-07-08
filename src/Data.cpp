#include "Data.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

AttributeNum::AttributeNum(std::string name_, int index_){
    indexColN = index_;
    name = name_;
}
ObjectRow::ObjectRow(int index_){
    indexRow = index_;
}
AttributeCat::AttributeCat(std::string name_, int index_){
    indexColC = index_;
    name = name_;
}
Attributes::Attributes(std::string name_){
    name = name_;
}
void Data::startReadFiles(){

    std::ifstream file;
    file.open("test.txt"); //Mudar diretório

    if(file.is_open()){
        std::string line;
        int row = 1, col = 0;

        while(line != "@info" && !file.eof()){
            getline(file, line);
            row++;
        }
        if(file.eof()){
            std::cout << "ERROR: PROGRAMA ENCERRADO\n'@info' NÃO FOI ENCONTRADO.\n";
            return;
        }

        char pointer;
        std::string buffer;
        while(buffer != "@data" && !file.eof()){
            file.get(pointer);
            buffer.push_back(pointer);            
            if(pointer == '\n'){
                buffer.clear();
                row++;
            }
            if(buffer == "@attribute"){
                buffer.clear();
                getline(file, buffer);
                if(addAttributeInList(buffer)){
                    buffer = "";
                    row++;
                } else {
                    break;
                }
            }
        }
        getline(file, buffer);
        if(file.eof()){
            std::cout << "ERRO C" << row << " - @data not found." << std::endl;
        }
        int index = 0;
        while(!file.eof()){
            getline(file, buffer);
            
            if(addAttributeData(buffer, index)){
                
                buffer.clear();
                index++;
            } else {

            }
        }
        
    }
}

bool Data::addAttributeInList(std::string line){   
    line = cutSpaces(line);
    std::string name;
    if(line[line.size()-1] != '}'){ //Ser numerico 
        for(int i = 0; line[i] != ' '; i++){
            name.push_back(line[i]);
        }
        Attributes attbNUM(name);
        attbNUM.attribute.push_back("Numeric--");
        attributesList.push_back(attbNUM);
    } else {
        int i = 0;
        for(; line[i] != ' '; i++){
            name.push_back(line[i]);
        }
        line.erase(line.begin(),line.begin()+i);
        line = cutSpaces(line);
        Attributes attbCAT(name);
        attbCAT.attribute = split(line);
        attributesList.push_back(attbCAT);
    }
    return true;
}

bool Data::addAttributeData(std::string line, int index){
    std::vector<std::string> attbData;
    attbData = split(line);

    if(attbData.size() != attributesList.size()){
        std::cout << "ERRO, NÃO EXISTEM REGISTROS PARA OS "<<attributesList.size() <<" CAMPOS."<< std::endl;
        exit(0);
    }

    ObjectRow tempObj(index);

    double tempNum;
    for(size_t i = 0; i < attbData.size(); i++){
        if(isNumeric(i)){
            AttributeNum AttbNumTemp(attributesList[i].name, i);
            tempNum = stringToDouble(attbData[i]);
            AttbNumTemp.attributeNum = tempNum;

            tempObj.collumnsNUM.push_back(AttbNumTemp);
        } else {
            if(attbData[i] == "?"){

            }
            AttributeCat AttbCatTemp(attributesList[i].name, i);
            if(validCatData(attbData[i])){
                AttbCatTemp.attributeCat = attbData[i];
                tempObj.collumnsCAT.push_back(AttbCatTemp);
            } else {
                std::cout << "ERRO, REGISTROS NÃO FUNCIONANDO CORRETAMENTE" << std::endl;
                exit(0);
            }
            
        }
    }
    objects.push_back(tempObj);
    return true;
}

double Data::stringToDouble(std::string str){
    if(hasSpaces(str)){
        std::cout << "ERRO, REGISTROS NÃO FUNCIONANDO CORRETAMENTE" << std::endl;
        exit(0);
    }
    std::stringstream converter;
    converter << str;
    double numeric;
    converter >> numeric;
    return numeric;
}

bool Data::isNumeric(int index){
    if(attributesList[index].attribute[0] == "Numeric--"){
        return true;
    }
    return false;
}

bool hasSpaces(std::string str){
    for(size_t i = 0; i < str.size(); i++){
        if(str[i] == ' '){
            return true;
        }
    }
    return false;
}

bool validCatData(std::string str){
    if(hasSpaces(str)){
        if(str[0] == '"' && str[str.size()-1] == '"'){
            return true;
        } else {
            return false;
        }
    }
    return true;
}

std::vector<std::string> split(std::string str){
    std::vector<std::string> attbCats;
    int i = 0;
    while(i < str.size()){
        std::string temp;
        while(str[i] != ',' && i < str.size()){
            temp.push_back(str[i]);
            i++;
        }
        
        temp = cutScrap(temp);
        if(temp[0] == '"'){
            for(int j = 0; j < temp.size(); j++){
            if(temp[j] == ' '){
                break;
            } else if(j == temp.size()-1){
                temp.erase(temp.begin());
                temp.pop_back();
            }
            }
        }
        attbCats.push_back(temp);
        temp.clear();
        i++;        
    }    
    return attbCats;
}

std::string cutSpaces(std::string str){
    int j = str.size()-1;

    while(j > 0){
        if(str[j] == ' '){
            j--;
        } else {
            break;
        }  
    }
    str.erase(str.begin()+j+1, str.end());
    int i = 0;
    while(i < str.size()){
        if(str[i] == ' '){
            i++;
        } else {
            break;
        }  
    }
    str.erase(str.begin(), str.begin()+i);
    return str;
}

std::string cutScrap(std::string str){
    int j = str.size()-1;

    while(j > 0){
        if(str[j] == ' ' || str[j] == '{' || str[j] == '}'){
            j--;
        } else {
            break;
        }  
    }
    str.erase(str.begin()+j+1, str.end());
    int i = 0;
    while(i < str.size()){
        if(str[i] == ' ' || str[i] == '{' || str[i] == '}'){
            i++;
        } else {
            break;
        }  
    }
    str.erase(str.begin(), str.begin()+i);
    return str;
}

void Data::showData(){
for(size_t i = 0; i < objects.size(); i++){
    for(size_t j = 0; j < attributesList.size(); j++){
        int k = 0;
        if(isNumeric(j)){
            while(objects[i].collumnsNUM[k].indexColN != j){
                k++;
            }
            std::cout << objects[i].collumnsNUM[k].attributeNum << ", ";
        } else {
            while(objects[i].collumnsCAT[k].indexColC != j){
                k++;
            }
            std::cout << objects[i].collumnsCAT[k].attributeCat << ", ";
        }
    }
    std::cout << std::endl;
}
}