#include <iostream>
#include <map>
#include <random>
#include <string>
#include <time.h>
#include <vector>
#include <math.h>

struct Company
{
    Company(std::string name, int shareValue, float changeMin, float changeMax,
            std::pair<int, int> forecast, float rateOfChange, int forecastInfluence)
        : name(name), shareValue(shareValue), changeMin(changeMin),
          changeMax(changeMax), forecast(forecast), rateOfChange(rateOfChange), forecastInfluence(forecastInfluence)
    {
        shareValueHistory.push_back(shareValue);
        changeValueHistory.push_back({changeMin, changeMax});
    }

    std::string name;
    float shareValue;
    std::vector<float> shareValueHistory;
    float changeMax; // Highest company shares can increase. (%)
    float changeMin;
    std::vector<std::pair<float, float>> changeValueHistory;
    std::pair<int, int> forecast; // {-5, 5}
    int forecastInfluence;
    float rateOfChange; //%
};

float roundToDecimal(float number, int decimalPlaces)
{
    float multiplier = std::pow(10.0, decimalPlaces);
    return std::round(number * multiplier) / multiplier;
}

class Market
{
public:
    Market() {}

    void addCompany(Company &company) { companies.push_back(company); }
    void advancedListCompanies()
    {

        for (int i = 0; i < companies.size(); i++)
        {
            Company &company = companies[i];
            std::cout << "->" << i << "..." << company.name << "\n";

            float shareValueIncrease = 0;
            float maxChangeIncrease = 0;
            float minChangeIncrease = 0;

            if (company.shareValueHistory.size() >= 2)
            {
                shareValueIncrease = roundToDecimal(
                    (1 -
                     (company.shareValueHistory[company.shareValueHistory.size() - 2] /
                      company.shareValue)) *
                        100,
                    3);
            }
            if (company.changeValueHistory.size() >= 2)
        {
            maxChangeIncrease = roundToDecimal(
                (1 -
                 (company.changeValueHistory[company.changeValueHistory.size() - 2]
                      .second / company.changeValueHistory[company.changeValueHistory.size() - 1].second)) * 100, 3);
            minChangeIncrease = roundToDecimal(
                (1 -
                 (company.changeValueHistory[company.changeValueHistory.size() - 2]
                      .first / company.changeValueHistory[company.changeValueHistory.size() - 1].first)) * 100, 3);
        }

            std::string shareValueOp = shareValueIncrease >= 0 ? "+" : "";
            std::string maxChangeOp = maxChangeIncrease >= 0 ? "+" : "";
            std::string minChangeOp = minChangeIncrease >= 0 ? "+" : "";
            std::pair<std::string, std::string> forecastOp = {
                company.forecast.first == 1 ? "+" : "-",
                company.forecast.second == 1 ? "+" : "-"};

            std::cout << "\tL ShareValue=" << company.shareValue << " ("
                      << shareValueOp << shareValueIncrease << "%)\n";
            std::cout << "\tMaxChange=" << company.changeMax << " (" << maxChangeOp
                      << maxChangeIncrease << "%)\n";
            std::cout << "\tMinChange=" << company.changeMin << " (" << minChangeOp
                      << minChangeIncrease << "%)\n";
            std::cout << "\tForecast=" << forecastOp.first << forecastOp.second
                      << "\n";
            // << "|SV=" << company.shareValue << "|CC=" << company.changeCap
            // << "|CG=" << company.changeGap << "|FC=" << company.forecast
            // << "\n";
        }
    }

    void update()
    {

        for (int i = 0; i < companies.size(); i++)
        {
            Company &company = companies[i];

            int forecastRoll = rand() % 100 >= 50 - company.forecastInfluence * (company.forecast.first + company.forecast.second - 1) ? 1 : -1;

            float newChangeMin = company.changeMin + company.changeMin * -forecastRoll * company.rateOfChange;
            float newChangeMax = company.changeMax + company.changeMax * forecastRoll * company.rateOfChange;

            company.changeValueHistory.push_back({newChangeMin, newChangeMax});

            company.changeMin = newChangeMin;
            company.changeMax = newChangeMax;

            float change = ((rand() % static_cast<int>(std::ceil(1000 * (company.changeMax - company.changeMin)))) + company.changeMin*1000) / 1000;
            float finalChangeMultiplier = 1 + change / 100;
            company.shareValueHistory.push_back(company.shareValue *
                                                finalChangeMultiplier);
            company.shareValue =
                company.shareValueHistory[company.shareValueHistory.size() - 1];
            std::pair<int, int> newForecast = {(rand() % 2), (rand() % 2)};
            company.forecast = newForecast;
        }
    }

    std::vector<Company> getCompanies() { return companies; }

private:
    std::vector<Company> companies;
};

int main()
{
    srand(time(NULL));
    Market market;
    Company company1("Apple", 100, -10, 10, {1, 0}, .05, 25);
    market.addCompany(company1);
    market.advancedListCompanies();

    for (int i = 0; i < 500; i++)
    {
        market.update();
        market.advancedListCompanies();
        auto changeHistory = company1.changeValueHistory;
        std::cout << "\n";
    }
}