#include "inputreader.h"

InputReader::InputReader()
{
    std::cout << "---------------Opening input----------------- " << std::endl;

    fileName = "input";
    std::ifstream myFile(fileName);

    if(!myFile.is_open()) {
          perror("Error opening input.txt");
          exit(EXIT_FAILURE);
    }


    float diameter;
    int probability;
    while(!myFile.eof()) // reads file to end of *file*, not line
    {
        myFile >> diameter;
        myFile >> probability;
        std::cout << "diameter: "<< diameter<< std::endl;
        diameters.push_back(diameter);
        std::cout << "CDF: "<< probability<< std::endl;
        prob.push_back(probability);
        std::cout<<std::endl<< std::endl;
    }


}

InputReader::~InputReader()
{
    //dtor
}


int InputReader::get_low(int value){
    return std::distance( prob.begin(), std::lower_bound(prob.begin(),prob.end(),value));
}




