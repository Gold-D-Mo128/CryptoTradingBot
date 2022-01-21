#pragma once
#include "HelperFunction.h"
#include <vector>

class Advisor
{
public:
    void advisorbot();
    /** Call this to start the sim */
    void init();
    std::vector<Parser> entries = Helper::readCSV("20200601.csv");
    std::string cuurent = entries[0].timestamp;

private:
    void printMenu();
    void printHelp(std::vector<std::string> inputs);
    void HelpCmd(std::vector<std::string> inputs);
    void products(std::vector<std::string> inputs);
    void min(std::vector<std::string> inputs);
    void max(std::vector<std::string> inputs);
    void average(std::vector<std::string> inputs);
    void predict(std::vector<std::string> inputs);
    void step(std::vector<std::string> inputs);
    void status(std::vector<std::string> inputs);
    std::string getUserOption();
    void processUserOption(std::string userOption);
    std::string currentTime = entries[0].timestamp;
    std::vector<std::string> productsList;
};
