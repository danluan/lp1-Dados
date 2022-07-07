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

void startReadFiles(Data newRead){

    std::ifstream file;
    file.open("test.txt"); //Mudar diretório

    if(file.is_open()){
        std::string line;
        int row = 0, col = 0;

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
            std::cout << row << "-" << buffer << std::endl;
            std::cout << row << "-'" << pointer << "'" << std::endl;
            
            if(pointer == '\n'){
                buffer = "";
                row++;
            }
            
        }
    }
}