#ifndef INPUTREADER_H
#define INPUTREADER_H

#include <string>
#include <stdio.h>
#include <sstream>
#include <vector>
#include <fstream>
#include <iostream>
#include <stdlib.h>

class InputReader
{
    public:
        InputReader();
        virtual ~InputReader();

        int get_low(int value);//get lower bound of value
        float get_diameter(int index){return diameters[index];}



    protected:

    private:
    std::string fileName;
    std::vector<float> diameters;
    std::vector<int> prob;
};

#endif // INPUTREADER_H
