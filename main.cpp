#include <iostream>
#include <map>
#include <random>
#include <string>
#include <vector>
#include <time.h>

struct Company
{
    Company(std::string name, int shareValue, int changeCap, int changeGap,
            int forecast)
        : name(name), shareValue(shareValue), changeCap(changeCap),
          changeGap(changeGap), forecast(forecast) {}

    std::string name;
    float shareValue;
    std::vector<float> shareValueHistory;
    int changeCap; // Highest company shares can increase. (%)
    int changeGap; // size/dist between max increase and min decrease.
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
            if (company.shareValueHistory.size() >= 2) {
                shareValueIncrease = roundToDecimal((1 - (company.shareValueHistory[company.shareValueHistory.size() - 2] / company.shareValue))*100, 3);
            }
            
            std::string op = shareValueIncrease >= 0 ? "+" : "";
            std::cout << "\tL ShareValue=" << company.shareValue << "(" << op << shareValueIncrease << "%)\n";

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
            int maxChange = company.changeCap;
            int minChange = maxChange - company.changeGap;

            float change = std::ceil((rand() % (maxChange + minChange)) - minChange);
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
    Company company1("Apple", 100, 100, 200, 0);
    market.addCompany(company1);
    market.advancedListCompanies();

    for (int i=0; i<100; i++) {
        market.update();
        market.advancedListCompanies();
    }
    
}