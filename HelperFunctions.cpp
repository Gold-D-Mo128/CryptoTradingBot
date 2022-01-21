#include "HelperFunction.h"
#include "AdvisorBot.h"
#include <iostream>
#include <fstream>
#include <string>
#include <tuple>
#include <typeinfo>
#include <unistd.h>
#include <stdlib.h>

void Helper::helper()
{
}

std::vector<Parser> Helper::readCSV(std::string csvfilename)
{

    std::vector<Parser> entries;

    std::ifstream csvFile{csvfilename};
    std::string line;
    if (csvFile.is_open())
    {
        while (std::getline(csvFile, line, '\n'))
        {
            try
            {
                entries.push_back(Helper::organiser(Helper::Line_parser(line, ',')));
            }
            catch (const std::exception &e)
            {
                std::cout << "CSVReader::readCSV bad data" << std::endl;
            }

        } // end of while
    }
    return entries;
}

std::vector<std::string> Helper::Line_parser(std::string csvLine, char separator)
{
    std::vector<std::string> tokens;
    signed int start, end;
    std::string token;
    start = csvLine.find_first_not_of(separator, 0);
    do
    {
        end = csvLine.find_first_of(separator, start);
        if (start == csvLine.length() || start == end)
            break;
        if (end >= 0)
            token = csvLine.substr(start, end - start);
        else
            token = csvLine.substr(start, csvLine.length() - start);
        tokens.push_back(token);
        start = end + 1;

    } while (end > 0);

    return tokens;
}

Parser Helper::organiser(std::vector<std::string> tokens)
{
    double price, amount;
    struct Parser store;
    if (tokens.size() != 5) // bad
    {
        std::cout << "Bad line " << std::endl;
        throw std::exception{};
    }
    // we have 5 tokens
    try
    {
        price = std::stod(tokens[3]);
        amount = std::stod(tokens[4]);
    }
    catch (const std::exception &e)
    {
        std::cout << "CSVReader::stringsToOBE Bad float! " << tokens[3] << std::endl;
        std::cout << "CSVReader::stringsToOBE Bad float! " << tokens[4] << std::endl;
        throw;
    }
    // 2020 / 06 / 01 11 : 57 : 30.328127, ETH / BTC, bid, 0.02480883, 8.05447423;
    store.price = price;
    store.amount = amount;
    store.timestamp = tokens[0];
    store.product = tokens[1],
    store.orderType = stringToType(tokens[2]);

    return store;
}

Type_parser Helper::stringToType(std::string s)
{
    if (s == "ask")
    {
        return Type_parser::ask;
    }
    if (s == "bid")
    {
        return Type_parser::bid;
    }
    else
    {

        return Type_parser::unknown;
    }
}

void Helper::loading(bool active)
{
    int i = 0;
    char load[100];
    while (true)
    {
        system("clear");
        load[i++] = '*';
        load[i] = '\0';

        printf("\n\nLOADING [%-50s]", load);
        usleep(199900);
    }

    system("clear");
    printf("\n");
}

std::vector<Parser> Helper::filter(Type_parser type, std::string product)
{
    Advisor borrow{};
    std::vector<Parser> entires = borrow.entries;

    std::vector<Parser> orders_sub;
    for (Parser &e : entires)
    {
        if (e.orderType == type && e.product == product)
        {
            orders_sub.push_back(e);
        }
    }

    return orders_sub;
}
std::string Helper::getmax(std::vector<Parser> &inputs)
{
    Advisor x;
    double max = x.entries[0].price;
    for (Parser &e : x.entries)
    {
        if (e.price > max)
            max = e.price;
    }
    std::string maximum = std::to_string(max);
    return maximum;
}
std::string Helper::getmin(std::vector<Parser> &inputs)
{
    Advisor x;
    double min = x.entries[0].price;
    for (Parser &e : x.entries)
    {
        if (e.price < min)
            min = e.price;
    }

    std::string minimum = std::to_string(min);
    return minimum;
}