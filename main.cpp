#include <iostream>
#include <map>
#include <random>
#include <string>
#include <vector>
#include <time.h>

struct Company
{
    Company(std::string name, int shareValue, int changeMin, int changeMax,
            int forecast)
        : name(name), shareValue(shareValue), changeMin(changeMin), changeMax(changeMax),
        forecast(forecast) {}

    std::string name;
    float shareValue;
    std::vector<float> shareValueHistory;
    int changeMax; // Highest company shares can increase. (%)
    int changeMin;
    std::vector<std::pair<int, int>> changeValueHistory;
    int forecast;  // {-5, 5}
};

float roundToDecimal(float number, int decimalPlaces) {
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

            if (company.shareValueHistory.size() >= 2) {
                shareValueIncrease = roundToDecimal((1 - (company.shareValueHistory[company.shareValueHistory.size() - 2] / company.shareValue))*100, 3);
            }
            if (company.changeValueHistory.size() >= 2) {
                maxChangeIncrease = roundToDecimal((1 - (company.changeValueHistory[company.changeValueHistory.size() - 2].first / company.changeMax))*100, 3);
                minChangeIncrease = roundToDecimal((1 - (company.changeValueHistory[company.changeValueHistory.size() - 2].second / company.changeMin))*100, 3);
            }
            
            std::string shareValueOp = shareValueIncrease >= 0 ? "+" : "";
            std::string maxChangeOp = maxChangeIncrease >= 0 ? "+" : "";
            std::string minChangeOp = minChangeIncrease >= 0 ? "+" : "";
            std::string forecast = forecastIncrease >= 0 ? "+" : "";

            std::cout << "\tL ShareValue=" << company.shareValue << " (" << shareValueOp << shareValueIncrease << "%)\n";
            std::cout << "\tMaxChange=" << company.changeMax << " (" << maxChangeOp << maxChangeIncrease << "%)\n";
            std::cout << "\tMinChange=" << company.changeMin << " (" << minChangeOp << minChangeIncrease << "%)\n";
            std::cout << "\tForecast=" << company.forecast << " (" << forecastOp << 
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

            float change = (rand() % (company.changeMax - company.changeMin)) + company.changeMin;
            float finalChangeMultiplier = 1 + change / 100;
            company.shareValueHistory.push_back(company.shareValue * finalChangeMultiplier);
            company.shareValue = company.shareValueHistory[company.shareValueHistory.size() - 1];
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
    Company company1("Apple", 100, -10, 10, 0);
    market.addCompany(company1);
    market.advancedListCompanies();

    for (int i=0; i<500; i++) {
        market.update();
        market.advancedListCompanies();
    }
    
}