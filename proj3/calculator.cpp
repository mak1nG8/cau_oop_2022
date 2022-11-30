#include "calculator.h"

void calculator::showMenu() {
    std::cout << "---------------Menu---------------" << std::endl;
    std::cout << "Choose number 1~5 " << std::endl;
    std::cout << "1. Calculator" << std::endl;
    std::cout << "2. Show all of enrolled Formulae" << std::endl;
    std::cout << "3. Insert a new Formula" << std::endl;
    std::cout << "4. Delete a enrolled Formula" << std::endl;
    std::cout << "5. Colsole Clear" << std::endl;
    std::cout << "----------------------------------" << std::endl << std::endl;
}
int calculator::priority(std::string s) {
    if (s == "+") return 1;
    else if (s == "-") return 1;
    else if (s == "*") return 2;
    else if (s == "/") return 2;
    else if (s == "^") return 3;
    else return -1;
};
bool calculator::verifyNumber(std::string s) {
    if (verifyOperator(s)) return false;
    if (s[0] < '0' || s[0] > '9') {
        if (s[0] != '-') return false;
    }
    for (int i = 1; i < s.length(); i++) {
        if (s[i] < '0' || s[i] > '9') {
            return false;
        }
    }
    return true;
}
bool calculator::verifyOperator(std::string s) {
    if (s == "(" || s == ")" || s == "+" || s == "-" || s == "*" || s == "/"||s=="^") return true;
    return false;
}
bool calculator::verifyVariable(std::string s) {
     if (verifyOperator(s)) return false;
     if (s[0] < '0' || s[0] > '9') {
         if (s[0] != '-') return true;
     }
     for (int i = 1; i < s.length(); i++) {
        if (s[i] < '0' || s[i] > '9') {
            return true;
        }
    }
    return false;
}
void calculator::divideByToken(const std::string& input, std::vector<std::string>& token){
    int length = input.length();
    int index = 0;
    for (int i = 0; i < length; i++) {                                   //divide token by spacebar
        if (input[i] == ' ') {
            std::string addToken = input.substr(index, i - index);
            if (!(verifyOperator(addToken)||verifyNumber(addToken))) throw addToken;
            token.push_back(addToken);
            index = i + 1;
        }
    }
    std::string addToken = input.substr(index);
    if (!(verifyOperator(addToken)||verifyNumber(addToken))) throw addToken;
    token.push_back(addToken);
}
void calculator::divideByTokenVariable(const std::string& input, std::vector<std::string>& token) {
    int length = input.length();
    int index = 0;
    for (int i = 0; i < length; i++) {                                   //divide token by spacebar
        if (input[i] == ' ') {
            std::string addToken = input.substr(index, i - index);
            token.push_back(addToken);
            index = i + 1;
        }
    }
    std::string addToken = input.substr(index);
    token.push_back(addToken);
}
void calculator::covertToPostFix(const std::vector<std::string>& token,std::vector<std::string>& postFix) {
    std::vector<std::string> stack;
    int parentheses = 0;  //parentheses = 괄호
    for (int i = 0; i < token.size(); i++) {                            
        if (token[i] == "(") {
            stack.push_back(token[i]);
            parentheses++;
        }
        else if (token[i] == ")") {
            if (parentheses <= 0) throw "ERROR";
            std::string pop = stack[stack.size() - 1];
            while (pop != "(") {
                postFix.push_back(pop);
                stack.pop_back();
                pop = stack[stack.size() - 1];
            }
            stack.pop_back();
            parentheses--;
        }
        else if (token[i] == "+" || token[i] == "-" || token[i] == "*" || token[i] == "^" || token[i] == "/") {
            if (stack.empty())
                stack.push_back(token[i]);
            else {
                while (priority(token[i]) <= priority(stack[stack.size() - 1])) {
                    std::string pop = stack[stack.size() - 1];
                    postFix.push_back(pop);
                    stack.pop_back();
                    if (stack.empty()) break;
                }
                stack.push_back(token[i]);
            }
        }
        else {
            postFix.push_back(token[i]);
        }
    }
    while (!stack.empty()) {
        postFix.push_back(stack[stack.size() - 1]);
        stack.pop_back();
    }
    if (parentheses != 0) throw "ERROR";
}
inf_int calculator::calculatePostFix(const std::vector<std::string>& postFix) {
    std::vector<inf_int> postStack;
    inf_int result;
    for (int i = 0; i < postFix.size(); i++) {                
        if (verifyOperator(postFix[i])){
            inf_int n1, n2;
            if (postStack.size() > 0) {
                n2 = postStack[postStack.size() - 1];
                postStack.pop_back();
            }
            else throw "ERROR";
            if (postStack.size() > 0) {
                n1 = postStack[postStack.size() - 1];
                postStack.pop_back();
            }
            else throw "ERROR";

            if (postFix[i] == "+") {
                postStack.push_back(n1 + n2);
            }
            else if (postFix[i] == "-") {
                postStack.push_back(n1 - n2);
            }
            else if (postFix[i] == "*") {
                postStack.push_back(n1 * n2);
            }
            else if (postFix[i] == "/") {
                if (n2 == 0) throw n2;
                postStack.push_back(n1 / n2);
            }
            else if (postFix[i] == "^") {
                if (n2 < 0) throw n2;
                postStack.push_back(n1 ^ n2);
            }
        }
        else {
            postStack.push_back(inf_int(postFix[i].c_str()));
        }
    }
    result = postStack[0];
    return result;
}
void calculator::run() {
    std::cout << "Format : (infinite integer)(space)(operator)(space)(infinite integer)(space)(operator)(infinite integer)…" << std::endl;
    std::cout << "Operator : ( ) + - * / ^" << std::endl;
    while (true) {
    try {
            std::string menuNum;
            showMenu();
            std::cout << "Menu(exit 0) : ";                                              
            std::getline(std::cin, menuNum);                           //enter the input string
            if (menuNum == "0") {                                                   //Exit the program
                std::cout << "Exit the program!";
                break;
            }
            else if (menuNum == "1") {
                std::string input;
                std::vector<std::string> token;
                std::vector<std::string> postFix;
                inf_int output;
                std::cout << "Input(exit 0) : ";
                std::getline(std::cin, input);
                if (input == "0") {                                                   //Exit the program
                    std::cout << "Exit the program!";
                    break;
                }
                auto begin = std::chrono::high_resolution_clock::now();
                divideByToken(input, token); 
                covertToPostFix(token, postFix);
                output = calculatePostFix(postFix);
                auto end = std::chrono::high_resolution_clock::now();
                std::cout << "Time elapsed : " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[microseconds]" << std::endl;
                std::cout << "Output : " << output << std::endl << std::endl;
            }
            else if (menuNum == "2") {
                std::ifstream inFile("Formula.txt", std::ios::in);
                std::vector<std::string> formula;
                std::string line;
                std::string chooseNum;
                int index = 0;
                std::cout << "-----------Show Formula-----------"<<std::endl;
                while (std::getline(inFile, line)) {
                    formula.push_back(line);
                    std::cout<< (index+1) <<". "<< formula[index] << std::endl;
                    index++;
                }
                inFile.close();
                std::cout << "-----------------------------------" << std::endl;
                std::cout << "Choose the number of which formula you use(exit 0) : " << std::endl;
                std::getline(std::cin, chooseNum);
                if (chooseNum == "0") {                                                   //Exit the program
                    std::cout << "Exit the program!";
                    break;
                }
                index = stoi(chooseNum) - 1; if (index >= formula.size()) throw index;
                std::vector<std::string> token;
                std::vector<std::string> postFix;
                inf_int output; 
                divideByTokenVariable(formula[index], token); 
                for (int i = 0; i < token.size(); i++) {
                    std::string s;
                    if (verifyVariable(token[i])) {
                        std::cout << token[i] << " : ";
                        getline(std::cin, s); if (verifyVariable(s)||verifyOperator(s)) throw s;
                        token[i] = s;
                        for (int j = i+1; j < token.size(); j++) {
                            if (token[j] == token[i]) token[j] = s;
                        }
                    }
                }
                covertToPostFix(token, postFix);
                output = calculatePostFix(postFix);
                std::cout << "Output : " << output << std::endl << std::endl;
            
            }
            else if (menuNum == "3") {
                std::string input;
                std::cout << "Enroll Formula by using operator and variable (exit 0) " << std::endl;
                std::cout << "Formula : ";
                std::getline(std::cin, input);
                if (input == "0") {                                                   //Exit the program
                    std::cout << "Exit the program!";
                    break;
                }
                std::ofstream outFile("Formula.txt", std::ios::app | std::ios::out);
                if (outFile.is_open()) {
                    outFile << input<< std::endl;
                    std::cout << "Success to enroll formula" << std::endl << std::endl;
                }
                else {
                    outFile << input<< std::endl;
                    std::cout << "Success to enroll formula" << std::endl << std::endl;
                }
                outFile.close();
            }
            else if (menuNum == "4") {
                std::string deleteNum;
                std::ifstream inFile("Formula.txt", std::ios::in);
                std::vector<std::string> formula;
                std::string line;
                int index = 0;
                if (inFile.is_open()) {
                    std::cout << "--------------DeleteFormula--------------" << std::endl;
                    while (std::getline(inFile, line)) {
                        std::cout << (index + 1) << ". " << line << std::endl;
                        formula.push_back(line);
                        index++;
                    }
                    std::cout << "-----------------------------------------" << std::endl;
                    inFile.close();
                }
                else {
                    inFile.close();
                }
                std::cout << "Which of formula's number you want to delete?" << std::endl;
                std::cout << "Number(exit 0) : ";
                std::getline(std::cin, deleteNum);
                if (menuNum == "0") {                                                   //Exit the program
                    std::cout << "Exit the program!";
                    break;
                }
                index = stoi(deleteNum) - 1; if (index >= formula.size()) throw index;
                std::ofstream outFile("Formula.txt", std::ios::out);
                if (outFile.is_open()) {
                    formula.erase(begin(formula) + index);
                    for (int i = 0; i < formula.size(); i++) {
                        outFile << formula[i] << std::endl;
                    }
                    std::cout << "Success to delete formula" << std::endl << std::endl;
                    outFile.close();
                }
                else {
                    std::cout << "There's no file." << std::endl << std::endl;
                    outFile.close();
                }
            }
            else if (menuNum == "5") {
                for (int i = 0; i < 30; i++) std::cout << std::endl;
            }
            else {
                std::cout << "Error, Please enter number 1 ~ 5"<<std::endl<<std::endl;
            }
        }
         catch (inf_int n) {
            if(n==0) std::cout << "Cannot divide by " << n  <<"."<<std::endl<< std::endl;
            if(n<0) std::cout << "Cannot power by negative integer." << std::endl<< std::endl;
        }
         catch (std::string token) {
            std::cout << "Format Error : Invaild number or operator." << std::endl<<std::endl;
        }
         catch (int num) {
             std::cout << "Format Error : Invaild number or operator." << std::endl << std::endl;
         }
         catch (...) {
            std::cout << "Error : please try again." << std::endl<< std::endl;
        }
    }
}
