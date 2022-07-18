#include "../lib/Object.hpp"
#include <iostream>

Object::Object(int index_){
    indexRow = index_;
}

void Object::showObjects(){
    int sizeAttbs = collumnsCAT.size()+collumnsNUM.size();
    for(int i = 0; i < sizeAttbs; i++){
        size_t k = 0;
        size_t j = 0;
        while(collumnsNUM[k].indexColN != i || k < collumnsNUM.size()){
            k++;
        }
        while(collumnsCAT[j].indexColC != i || j < collumnsCAT.size()){
            j++;
        }
        if(collumnsNUM[k].indexColN == i){
            if(collumnsNUM[k].attributeNum == -123.457)
                std::cout << "?, ";
            else
                std::cout << collumnsNUM[k].attributeNum << ", ";
        } else if(collumnsCAT[j].indexColC == i){
            std::cout << collumnsCAT[j].attributeCat << ", ";
        }
    }
}

double Object::getNumInIndex(int col){
    int k = 0;
    while(collumnsNUM[k].indexColN != col)
        k++;
    return collumnsNUM[k].attributeNum;
}

std::string Object::getCatInIndex(int col){
    int k = 0;
    while(collumnsCAT[k].indexColC != col){
        k++;
    }
        
    return collumnsCAT[k].attributeCat;
}