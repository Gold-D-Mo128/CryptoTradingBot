#include "AdvisorBot.h"
#include <iostream>
#include <vector>
#include "HelperFunction.h"
#include <string>
#include <map>

void Advisor::advisorbot()
{
}

void Advisor::init()
{
    std::string input;
    // currentTime = orderBook.getEarliestTime();
    while (true)
    {

        printMenu();
        input = getUserOption();
        processUserOption(input);
    }
}

void Advisor::printMenu()
{
    std::cout << "[================]" << std::endl;
    // 1 print help
    std::cout << "[*] help       [*]" << std::endl;
    // explains what a command does
    std::cout << "[*] help <cmd> [*]" << std::endl;
    // list available products
    std::cout << "[*] prod       [*]" << std::endl;
    // find minimum bid or ask for product in current time step
    std::cout << "[*] min        [*]" << std::endl;
    // max product bid/ask
    std::cout << "[*] max        [*]" << std::endl;
    // avg product ask/bid timesteps
    std::cout << "[*] avg        [*]" << std::endl;
    // predict max/min product ask/bid
    std::cout << "[*] predict    [*]" << std::endl;
    // state current time in dataset, i.e. which timeframe are we looking at
    std::cout << "[*] time       [*]" << std::endl;
    // move to next time step
    std::cout << "[*] step       [*]" << std::endl;

    std::cout << "[================]" << std::endl;

    std::cout << "Current time is: " << currentTime << std::endl;
}
// HELP******************************
void Advisor::printHelp(std::vector<std::string> inputs)
{
    try
    {

        if (inputs[0].compare("help") == 0)
        {

            std::cout << "[The available commands are]" << std::endl;
            // explains what a command does
            std::cout << "[+] help <cmd> " << std::endl;
            // list available products
            std::cout << "[+] products " << std::endl;
            // find minimum bid or ask for product in current time step
            std::cout << "[+] min " << std::endl;
            // max product bid/ask
            std::cout << "[+] max " << std::endl;
            // avg product ask/bid timesteps
            std::cout << "[+] average " << std::endl;
            // predict max/min product ask/bid
            std::cout << "[+] predict " << std::endl;

            // state current time in dataset, i.e. which timeframe are we looking at
            std::cout << "[+] time " << std::endl;

            // move to next time step
            std::cout << "[+] step " << std::endl;
            std::cout << "\n " << std::endl;
        }
        else
        {
            throw(inputs);
        }
    }
    catch (std::vector<std::string> inputs)
    {
        std::cout << "UNKNOWN COMMAND\n"
                  << std::endl;
    }
}
// HELP CMD******************************
void Advisor::HelpCmd(std::vector<std::string> inputs)
{
    std::vector<std::string> commands = {
        "prod",
        "min",
        "max",
        "avg",
        "predict",
        "time",
        "step"};

    std::vector<std::string> discription = {
        "[+] porpuse: list available products [+]",
        "[+] porpuse: find minimum bid or ask for product in current time step (min ETH/BTC ask)[+]",
        "[+] porpuse : max product bid / ask(max ETH / BTC ask)[+]",
        "[+] porpuse: avg product ask/bid timesteps, (avg ETH/BTC 10)[+]",
        "[+] porpuse: predicts the product in the next timestep, (predict ETH/BTC bid/ask)[+]",
        "[+] porpuse: state current time in dataset, i.e. which timeframe are we looking at [+]",
        "[+] porpuse: move to next time step"};
    int i = 0;
    while (i < commands.size())
    {
        if (inputs[1].compare(commands[i]) == 0)
        {
            std::cout << discription[i]
                      << "\n"
                      << std::endl;
        }
        i++;
    }
}
// PRODUCT******************************
void Advisor::products(std::vector<std::string> inputs)
{

    std::map<std::string, bool> prodMap;

    for (Parser &e : entries)
    {
        prodMap[e.product] = true;
    }

    // now flatten the map to a vector of strings
    for (auto const &e : prodMap)
    {
        productsList.push_back(e.first);
    }
    std::cout << "[product]\n"
              << std::endl;
    for (int i = 0; i < productsList.size(); i++)
    {
        std::cout << productsList[i] << std::endl;
    }
    std::cout << "\n"
              << std::endl;
}
// min******************************
void Advisor::min(std::vector<std::string> inputs)
{
    Helper help{};
    std::vector<Parser> filtered = help.filter(Helper::stringToType(inputs[2]), inputs[1]);
    float min = filtered[0].price;

    if (inputs[2] == "ask")
    {
        for (Parser e : entries)
        {
            if (e.price < min)
            {
                min = e.price * 100;
            }
        }
        std::cout << "The minimum ask for " << inputs[1] << " is: " << std::to_string(min) << "\n"
                  << std::endl;
    }
    if (inputs[2] == "bid")
    {
        for (Parser e : entries)
        {
            if (e.price < min)
            {
                min = e.price * 100;
            }
        }
        std::cout << "The minimum bid for " << inputs[1] << " is: " << std::to_string(min) << "\n"
                  << std::endl;
    }
}

// MAX******************************
void Advisor::max(std::vector<std::string> inputs)
{

    Helper help{};

    std::vector<Parser> filtered = help.filter(Helper::stringToType(inputs[2]), inputs[1]);
    double max = filtered[0].price;

    if (inputs[2].compare("ask") == 0)
    {
        for (Parser e : entries)
        {
            if (e.price > max)
            {
                max = e.price;
            }
        }

        std::cout << "The maximum ask for " << inputs[1] << " is: " << std::to_string(max) << "\n"
                  << std::endl;
    }
    if (inputs[2].compare("bid") == 0)
    {
        for (Parser e : entries)
        {
            if (e.price > max)
            {
                max = e.price;
            }
        }

        std::cout << "The maximum bid for " << inputs[1] << " is: " << std::to_string(max) << "\n"
                  << std::endl;
    }
}
void Advisor::average(std::vector<std::string> inputs)
{
    Helper help{};
    std::vector<Parser> filtered = help.filter(Helper::stringToType(inputs[2]), inputs[1]);
    int counter = stoi(inputs[3]);
    int i = filtered.size();
    int sum, avg = 0;
    while (counter != 0)
    {
        sum = filtered[i].price + filtered[i - 1].price;
        avg = sum / stoi(inputs[3]);
        counter--;
    }

    std::cout << "The average " << inputs[1] << " " << inputs[2] << " price over the last " << inputs[3] << " timesteps was " << std::to_string(avg) << "\n"
              << std::endl;
}
// PREDICT******************************
void Advisor::predict(std::vector<std::string> inputs)
{
    std::vector<Parser> orders_sub;
    for (Parser &e : entries)
    {
        if (e.product == inputs[1] && e.timestamp == inputs[2] && e.timestamp == "2020/06/01 11:57:30.328127")
        {
            orders_sub.push_back(e);
        }
    }
    // Helper help{};
    int counter = orders_sub.size();
    int i = 0;
    int sum, avg = 0;
    while (i < counter)
    {
        sum = orders_sub[i].price + orders_sub[i + 1].price;
        avg = sum / stoi(inputs[3]);
        i--;
    }
    std::cout << "The Prediction of " << inputs[1] << " " << inputs[2] << " price calculated over the last timesteps was " << std::to_string(avg) << "\n"
              << std::endl;
}

// STEP***********************************
void Advisor::step(std::vector<std::string> inputs)
{
    std::string next_timestamp = "";
    for (Parser &e : entries)
    {
        if (e.timestamp > currentTime)
        {
            next_timestamp = e.timestamp;
            break;
        }
    }
    if (next_timestamp == "")
    {
        next_timestamp = entries[0].timestamp;
    }
    std::cout << "now at " << next_timestamp << std::endl;
}

std::string Advisor::getUserOption()
{
    std::string userOption = " ";
    std::string line;
    std::cout << "Type in you command" << std::endl;
    std::getline(std::cin, line);
    try
    {
        userOption = line;
    }
    catch (const std::exception &e)
    {
        //
    }
    std::cout << "Your input is: " << userOption << "\n"
              << std::endl;
    return userOption;
}

void Advisor::processUserOption(std::string userOption)
{
    std::vector<std::string> inputs = Helper::Line_parser(userOption, ' ');
    if (inputs.size() > 4)
    {
        std::cout << "Invalid input" << std::endl;
    }
    else if (inputs.size() == 1) // bad input
    {
        if (inputs[0].compare("prod") == 0)
        {
            products(inputs);
        }
        else if (inputs[0].compare("help") == 0)
        {
            printHelp(inputs);
        }
        else if (inputs[0].compare("time") == 0)
        {
            std::cout << "you are at: " << currentTime << std::endl;
        }
        else if (inputs[0].compare("step") == 0)
        {
            step(inputs);
        }
        else
        {
            std::cout << "Invalid input, please check out help <cmd>" << std::endl;
        }
    }
    else if (inputs.size() == 2)
    {
        if (inputs[0].compare("help") == 0)
        {
            HelpCmd(inputs);
        }
        else
        {
            std::cout << "Invalid input, please check out help <cmd>" << std::endl;
        }
    }
    else if (inputs.size() == 3) // bad input
    {
        if (inputs[0].compare("min") == 0)
        {
            min(inputs);
        }
        else if (inputs[0].compare("max") == 0)
        {
            max(inputs);
        }
        else
        {
            std::cout << "Invalid input, please check out help <cmd>" << std::endl;
        }
    }
    else if (inputs.size() == 4)
    {
        if (inputs[0].compare("avg") == 0)
        {
            average(inputs);
        }
        else if (inputs[0].compare("predict") == 0)
        {
            predict(inputs);
        }
        else
        {
            std::cout << "Invalid input, please check out help <cmd>" << std::endl;
        }
    }
    else
    {
        std::cout << "Invalid input, please check out help <cmd>" << std::endl;
    }
}

// predict max ETH / BTC bid;
// avg ETH / BTC ask 10;