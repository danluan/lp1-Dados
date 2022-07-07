#include "Data.hpp"
#include <iostream>
#include <fstream>

AttributeNum::AttributeNum(std::string name_, int index_){
    indexColN = index_;
    name = name_;
}

AttributeCat::AttributeCat(std::string name_, int index_){
    indexColC = index_;
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
            std::cout << row << "-" << line << std::endl;
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
            //std::cout << row << "-" << buffer << std::endl;
            
            if(pointer == '\n'){
                buffer = "";
                row++;
            }

            if(buffer == "@attribute"){
                buffer = "";
                getline(file, buffer);
                std::cout << "Achô '" << buffer << "'" << std::endl;
                if(addAttributeInList(buffer)){
                    buffer = "";
                    row++;
                } else {
                    break;
                }
                
            }
        }
        
    }
}
Attributes::Attributes(std::string name_){
    name = name_;
}
bool Data::addAttributeInList(std::string line){
    
    line = cutSpaces(line);
    std::string name;
    if(line[line.size()-1] != '}'){ //Ser numerico 
        for(int i = 0; line[i] != ' '; i++){
            name.push_back(line[i]);
        }
        Attributes attbNUM(name);
        attbNUM.attribute.push_back("Numeric");
        std::cout << "Attb '" << name << "'" << std::endl;
        std::cout << "Type '" << "Numeric" << "'" << std::endl;
        attributesList.push_back(attbNUM);
    } else {
        int i = 0;
        for(; line[i] != ' '; i++){
            name.push_back(line[i]);
        }
        line.erase(line.begin(),line.begin()+i);
        line = cutSpaces(line);

        std::cout << "Attb name '" << name << "'" << std::endl;
        std::cout << "Type '" << "Categoric" << "'" << std::endl;
        Attributes attbCAT(name);
        attbCAT.attribute = split(line);
        for(int i = 0; i < attbCAT.attribute.size(); i++){
            std::cout << "   -'" << attbCAT.attribute[i] << "'" << std::endl;
        }
        std::cout << "\n";
        attributesList.push_back(attbCAT);
    }
    return true;
}

std::vector<std::string> split(std::string str){
    std::vector<std::string> attbCats;
    int i = 0;
    while(i < str.size()-1){
        std::string temp;
        while(str[i] != ',' && i < str.size()-1){
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