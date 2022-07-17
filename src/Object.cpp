#include "../lib/Object.hpp"
#include <iostream>

Object::Object(int index_){
    indexRow = index_;
}

void Object::showObjects(){

    int sizeAttbs = collumnsCAT.size()+collumnsNUM.size();
    for(int i = 0; i < sizeAttbs; i++){
        int k = 0;
        int j = 0;
        while(collumnsNUM[k].indexColN != i && k < collumnsNUM.size()){
            k++;
        }
        while(collumnsCAT[j].indexColC != i && j < collumnsCAT.size()){
            j++;
        }
        if(collumnsNUM[k].indexColN == i){
            std::cout << collumnsNUM[k].attributeNum << ", ";
        } else if(collumnsCAT[j].indexColC == i){
            std::cout << collumnsCAT[j].attributeCat << ", ";
        }
    }
}