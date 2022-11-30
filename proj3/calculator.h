#ifndef OOP_PROJ2_CALCULATOR_H
#define OOP_PROJ2_CALCULATOR_H

#include <string>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "inf_int.h"
#include <chrono>

class calculator {
private:
    static void showMenu();                     //Show main menu
    static int priority(std::string);           //Priority of operator
    static bool verifyNumber(std::string);       //Verifing whether token is number
    static bool verifyVariable(std::string);    //Verifing whether token is variable
    static bool verifyOperator(std::string s);  //Verifing whether token is operator
    static void divideByToken(const std::string& , std::vector<std::string>&); //Divide token by spacebar(no variable)
    static void divideByTokenVariable(const std::string&, std::vector<std::string>&);//Divide token by spacebar(contains variable)
    static void covertToPostFix(const std::vector<std::string>& , std::vector<std::string>&); //Convert to PostFix notation
    static inf_int calculatePostFix(const std::vector<std::string>&);     //Calculating PostFix notation
public:
    static void run();
};

#endif //OOP_PROJ2_CALCULATOR_H
