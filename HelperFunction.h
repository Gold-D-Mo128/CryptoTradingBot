#pragma once
#include <tuple>
#include <vector>
#include <string>
#include <iostream>
enum class Type_parser
{
    bid,
    ask,
    unknown,
};

struct Parser
{
    double price;
    double amount;
    std::string timestamp;
    std::string product;
    Type_parser orderType;
    int display()
    {
        std::cout << "store price: " << price << std::endl;
        std::cout << "store amount: " << amount << std::endl;
        std::cout << "store timestep: " << timestamp << std::endl;
        std::cout << "store product: " << product << std::endl;
        if (orderType == Type_parser::bid)
        {
            std::cout << "store type: "
                      << "bid" << std::endl;
        }
        if (orderType == Type_parser::ask)
        {
            std::cout << "store type: "
                      << "ask" << std::endl;
        }
        std::cout << "\n"
                  << std::endl;
        return 0;
    }
};

class Helper
{
public:
    static void loading(bool active);
    void helper();
    static std::vector<Parser> readCSV(std::string csvFile);
    static Parser organiser(std::vector<std::string> tokens);
    static std::vector<std::string> Line_parser(std::string csvLine, char separator);
    static Type_parser stringToType(std::string s);
    std::vector<Parser> filter(Type_parser type, std::string product);
    static std::string getmin(std::vector<Parser> &inputs);
    static std::string getmax(std::vector<Parser> &inputs);
};
