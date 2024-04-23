#include "market.h"
#include "myArith.h"
#include <iostream>

MyArith myArith;

Market::Market() {}

void Market::addCompany(Company& company) { companies.push_back(company); }
void Market::advancedListCompanies() {
    for (int i = 0; i < companies.size(); i++)
    {
        Company& company = companies[i];
        std::cout << "->" << i << "..." << company.getName() << "\n";

        float shareValueIncrease = 0;
        float maxChangeIncrease = 0;
        float minChangeIncrease = 0;

        if (company.getShareValueHistory().size() >= 2) {
            shareValueIncrease = myArith.roundToDecimal((1 - (company.getShareValueHistory()[company.getShareValueHistory().size() - 2] / company.getShareValue())) * 100, 3);
        }

        std::string shareValueOp = shareValueIncrease >= 0 ? "+" : "";
        std::string maxChangeOp = maxChangeIncrease >= 0 ? "+" : "";
        std::string minChangeOp = minChangeIncrease >= 0 ? "+" : "";
        std::pair<std::string, std::string> forecastOp = {
            company.getForecast().first == 1 ? "+" : "-",
            company.getForecast().second == 1 ? "+" : "-" };

        std::cout << "\tL ShareValue=" << company.getShareValue() << " ("
            << shareValueOp << shareValueIncrease << "%)\n";
        std::cout << "\tForecast=" << forecastOp.first << forecastOp.second
            << "\n";
    }
}

void Market::update()
{

    for (int i = 0; i < companies.size(); i++)
    {
        Company& company = companies[i];

        int forecastRoll = rand() % 100 >= 50 - company.getForecastInfluence() * (company.getForecast().first + company.getForecast().second - 1) ? 1 : -1;

        float rateOfChangeRoll = static_cast<float>(rand() % static_cast<int>((company.getRateOfChange().second - company.getRateOfChange().first) * 1000)) / 1000 + company.rateOfChange.first;
        float shareValueChange = company.getShareValue() + company.getShareValue() * forecastRoll * rateOfChangeRoll;

        company.getShareValueHistory().push_back(shareValueChange);
        company.shareValue = company.getShareValueHistory()[company.getShareValueHistory().size() - 1];
        std::pair<int, int> newForecast = { (rand() % 2), (rand() % 2) };
        company.forecast = newForecast;
    }
}

std::vector<Company> Market::getCompanies() { return companies; }