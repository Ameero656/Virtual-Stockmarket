#pragma once

#include <string>
#include <vector>
#include <map>

#include "stock.h"
#include "investor.h"

class Company {
public:
    Company(std::string name, int shareValue, std::pair<int, int> forecast, std::pair<float, float> rateOfChange, int forecastInfluence);
    std::string getName();
    float getShareValue();
    std::vector<float> getShareValueHistory();
    std::pair<int, int> getForecast();
    int getForecastInfluence();
    std::pair<float, float> getRateOfChange();
    std::map<double, Stock> getInventory();

private:
    friend class Market;
    std::string name;
    float shareValue;
    std::vector<float> shareValueHistory;
    std::pair<int, int> forecast; // {-5, 5}
    int forecastInfluence;
    std::pair<float, float> rateOfChange; //%
    std::map<double, Stock> inventory;
    double companyID;

    void buy(Investor& investor, int amount);
};