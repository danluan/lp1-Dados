#include "../lib/Data.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <string>

double Data::getNumValueInIndex(int row, int col){
    return objects[row].getNumInIndex(col);
}

std::string Data::getCatValueInIndex(int row, int col){
    return objects[row].getCatInIndex(col);
}

void Data::readFiles(std::string directory){

    std::ifstream file;
    file.open(directory);

    if(file.is_open()){
        std::string line;
        int row = 1;
        int stage = 0; //0 - procurando @info; 1 - Adicionando atributos; 2 - Lendo @data

        while(line != "@info" && !file.eof()){
            getline(file, line);
            row++;
        }
        if(file.eof()){
            std::cout << "ERROR: PROGRAMA ENCERRADO.\n'@info' NÃO FOI ENCONTRADO.\n";
            return;
        }
        stage = 1;

        char pointer;
        std::string buffer;
        while(buffer != "@data" && !file.eof() && stage == 1){
            file.get(pointer);
            buffer.push_back(pointer);            
            if(pointer == '\n'){
                buffer.clear();
                row++;
            }
            if(buffer == "@attribute"){
                buffer.clear();
                getline(file, buffer);
                if(!(lineIsValid(buffer))){
                    std::cout << "ERROR - ATRIBUTO DECLARADO INDEVIDAMENTE NA LINHA "<< row << ".\n";
                    return;
                }
                if(addAttributeInList(buffer)){
                    buffer = "";
                    row++;
                } else {
                    break;
                }
            }
        }
        stage = 2;
        getline(file, buffer);
        if(file.eof()){
            std::cout << "ERRO C" << row << " - @data not found." << std::endl;
        }
        int indexRow = 0;
        while(!file.eof() && stage == 2){
            row++;
            getline(file, buffer);
            if(buffer == "\n" || buffer == ""){
                //just ignore
            } else if(addAttributeData(buffer, indexRow)){
                buffer.clear();
                indexRow++;
            } else {
                std::cout << "ERRO! NÃO EXISTEM REGISTROS PARA OS "<<attributesList.size() <<" CAMPOS NA LINHA "<< row <<"."<< std::endl;
                std::cout << "ENCERRANDO PROGRAMA..." << std::endl;
                exit(0);
            }
        }
        file.close();
    } else {
        std::cout << "ERRO! ARQUIVO NÃO ENCONTRADO, ENCERRANDO PROGRAMA..." << std::endl;
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
        return false;
    }
    Object tempObj(index);
    double tempNum;
    for(size_t i = 0; i < attbData.size(); i++){
        if(isNumeric(i)){
            if(attbData[i] == "?"){
                attbData[i] = "-123.457";
            }
            AttributeNum AttbNumTemp(attributesList[i].name, i);
            tempNum = stringToDouble(attbData[i]);
            AttbNumTemp.attributeNum = tempNum;
            tempObj.collumnsNUM.push_back(AttbNumTemp);
        } else {
            AttributeCat AttbCatTemp(attributesList[i].name, i);
            if(validCatData(attbData[i], i)){
                AttbCatTemp.attributeCat = attbData[i];
                tempObj.collumnsCAT.push_back(AttbCatTemp);
            } else {
                return false;
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

bool Data::validCatData(std::string str, int indexCol){
    if(str == "?"){
        return true;
    }
    bool exists = false;
    for(size_t i = 0; i < attributesList[indexCol].attribute.size(); i++){
        if(attributesList[indexCol].attribute[i] == str){
            exists = true;
        }
    }
    if(exists == false){
        return false;
    }

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
    size_t i = 0;
    while(i < str.size()){
        std::string temp;
        while(str[i] != ',' && i < str.size()){
            temp.push_back(str[i]);
            i++;
        }
        
        temp = cutScrap(temp);
        if(temp[0] == '"'){
            for(size_t j = 0; j < temp.size(); j++){
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
    size_t i = 0;
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
    size_t i = 0;
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
    int sizeAttb = attributesList.size();

    for(size_t i = 0; i < objects.size(); i++){
        for(int j = 0; j < sizeAttb; j++){
            if(isNumeric(j)){
                if(getNumValueInIndex(i,j) == UNKNOWK_NUMERIC)
                    std::cout << "?, ";
                else
                    std::cout << getNumValueInIndex(i,j) << ", ";
            }
            else
                std::cout << getCatValueInIndex(i,j) << ", ";
        }
        std::cout << std::endl;
    }
}

bool Data::lineIsValid(std::string str){
    std::string validate = "numeric";
    size_t i, j = 0, ver = 0, aux;
    for(i = 0; i < str.size(); i++){
        if(str[i] == '{'){
            return true;
        }
        aux = i;
        while(j < validate.size() && str[i] == validate[j]){
            ver++;
            i++;
            j++;
        }
        if(ver == validate.size()){
            return true;
        }
        ver = 0;
        j = 0;
        i = aux;
    }
    return false;

}

void Data::analysisFiles(float P, int C){
    
    std::vector<Object> testersData; 
    std::vector<Object> trainersData;
    std::vector<Object> objCopy = objects;
    std::vector<std::string> classDistCalc;
    std::vector<std::string> classDistReal;

    const size_t end = attributesList.size()-1;
    
    size_t numTesters = static_cast<size_t>(objects.size()*P);
    size_t numTrainers {objects.size()-numTesters};
    srand(time(NULL));
    
    int randIndex;
    for(int i = 0; i < numTesters; i++){ // Set the testers
        randIndex = rand()%objCopy.size();
        testersData.push_back(objCopy[randIndex]);
        classDistReal.push_back(objCopy[randIndex].collumnsCAT[objCopy[randIndex].collumnsCAT.size()-1].attributeCat);
        objCopy.erase(objCopy.begin()+randIndex);
    }
    for(int i = 0; i < numTrainers; i++){ // Set the trainers
        trainersData.push_back(objCopy[i]);
    }

    testersData.shrink_to_fit();
    trainersData.shrink_to_fit();

    for(size_t i = 0; i < testersData.size(); i++){
        for(size_t j = 0; j < trainersData.size(); j++){
            trainersData[j].dist = distFunc(testersData[i], trainersData[j]);
        }
        sortTrainers(trainersData);
        classDistCalc.push_back(setDistClass(trainersData, C));
    }
    std::vector<std::vector<int>> output(attributesList[end].attribute.size(), std::vector<int>(attributesList[end].attribute.size()));
    for(size_t i = 0; i < attributesList[end].attribute.size(); i++){
        for(size_t j = 0; j < attributesList[end].attribute.size(); j++){
            output[i][j] = 0;
        }
    }
    for(size_t i = 0; i < classDistReal.size(); i++){
        std::pair<int, int> pos = getIndexOutput(classDistReal[i], classDistCalc[i]);
        output[pos.first][pos.second] += 1;
    }
    std::cout << "\n  ";
    for(size_t i = 0; i < attributesList[end].attribute.size(); i++){
        std::cout << attributesList[end].attribute[i] << "  ";
    }
    std::cout << "\n";
    for(size_t i = 0; i < attributesList[end].attribute.size(); i++){
        std::cout << attributesList[end].attribute[i] << " ";
        for(size_t j = 0; j < attributesList[end].attribute.size(); j++){
             std::cout << output[i][j] << ", ";
        }
        std::cout << "\n";
    }
}

double Data::distFunc(Object tester, Object trainer){
    double dist = 0;
    int size = attributesList.size()-1;
    for(int i = 0; i < size; i++){
        if(isNumeric(i)){
            if(tester.getNumInIndex(i) == UNKNOWK_NUMERIC || trainer.getNumInIndex(i) == UNKNOWK_NUMERIC){
                dist += 1;
            } else {
                dist += pow(tester.getNumInIndex(i) - trainer.getNumInIndex(i), 2);
            }
        } else {
            if(tester.getCatInIndex(i) == "?" || trainer.getCatInIndex(i) == "?"){
                dist += 1;
            } else {
                if(tester.getCatInIndex(i) == trainer.getCatInIndex(i)){
                dist += 0;
                } else {
                    dist += 1;
                }
            }
            
        }
    }
    return dist;
}

std::pair<int, int> Data::getIndexOutput(std::string classReal, std::string classCalc){
    //left = real_index
    //right = calc_index
    const size_t end = attributesList.size()-1;

    int k = 0;
    while(attributesList[end].attribute[k] != classReal)
        k++;
    
    int l = 0;
    while(attributesList[end].attribute[l] != classCalc)
        l++;
    

    return { k, l };
    
}

void sortTrainers(std::vector<Object> &objList){
    int size = objList.size();
    int i, j; 
    for (i = 0; i < size - 1; i++)
        for (j = 0; j < size - i - 1; j++) 
            if (objList[j].dist > objList[j + 1].dist)
                swapObject(objList[j], objList[j + 1]);
    
}

void swapObject(Object &obj1, Object &obj2){
    Object temp = obj1;
    obj1 = obj2;
    obj2 = temp;
}

std::string Data::setDistClass(std::vector<Object> trainers, int C){
    std::vector<std::string> selected;
    size_t end = attributesList.size()-1;
    for(int i = 0; i < C; i++){
        selected.push_back(trainers[i].getCatInIndex(end));
    }
    
    std::vector<int> count;
    int tempCount = 0;
    int max = 0;
    int maxIndex = 0;
    for(size_t i = 0; i < attributesList[end].attribute.size(); i++){
        
        tempCount = std::count(selected.begin(), selected.end(), attributesList[end].attribute[i]);
        count.push_back(tempCount);
        if(tempCount >= max){
            maxIndex = i;
        }
    }
    
    return selected[maxIndex];
}