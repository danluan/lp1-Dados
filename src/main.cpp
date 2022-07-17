#include <iostream>
#include "../lib/Data.hpp"

int main(){

    Data test;
    test.readFiles("test.txt");
    //test.showData();
    std::cout << std::endl;
    float P = 0.35;
    int C = 2;
    test.analysisFiles(P, C);

    /*Data mixed;
    Data mixedE;
    Data categoric;
    Data categoricE;
    Data numeric;
    Data numericE;*/

    //mixed.readFiles("../samples/Mixed.txt");
    //mixedE.readFiles("../samples/Mixed_-_Error_L7C25.txt");
    //categoric.readFiles("../samples/Categoric.txt");
    //categoricE.readFiles("../samples/Categoric_-_Error_L46C10.txt");
    //numeric.readFiles("../samples/Numeric.txt");
    //numericE.readFiles("../samples/Numeric_-_Error_L35C14.txt");

    //mixed.showData();
    //mixedE.showData();
    //categoric.showData();
    //categoricE.showData();
    //numeric.showData();
    //numericE.showData();
    
    return 0;
}