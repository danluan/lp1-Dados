#ifndef ATTRIBUTES_H_
#define ATTRIBUTES_H_

#include <string>
#include <vector>

class Attributes{
public:
    std::vector<std::string> attribute; 
    std::string name;

    Attributes(std::string name_);
};

#endif