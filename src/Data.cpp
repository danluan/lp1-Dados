#include "../lib/Data.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>

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
            int k = 0;
            if(isNumeric(j)){
                while(objects[i].collumnsNUM[k].indexColN != j){
                    k++;
                }
                if(objects[i].collumnsNUM[k].attributeNum == UNKNOWK_NUMERIC)
                    std::cout << "?, ";
                else
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
    std::vector<Object> testers; 
    std::vector<Object> trainers;
    std::vector<Object> objCopy = objects;

    int numTesters = objects.size()*P;
    int numTrainers = objects.size()-numTesters;
    int size = objects.size();
    srand(time(NULL));

    int randIndex;
    for(int i = 0; i < numTesters; i++){ // Set the testers
        randIndex = rand()%size;
        testers.push_back(objCopy[randIndex]);
        objCopy.erase(objCopy.begin()+randIndex);
    }
        
    for(int i = 0; i < numTrainers; i++){ // Set the testers
        trainers.push_back(objCopy[i]);
    }


    //Calculo Dist
    //Calculo Diff
}