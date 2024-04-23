#include "company.h"

Company::Company(std::string name, int shareValue, std::pair<int, int> forecast, std::pair<float, float> rateOfChange, int forecastInfluence)
    : name(name), shareValue(shareValue), forecast(forecast), rateOfChange(rateOfChange), forecastInfluence(forecastInfluence) {
    shareValueHistory.push_back(shareValue);
}
std::string Company::getName() {
    return name;
}
float Company::getShareValue() {
    return shareValue;
}
std::vector<float> Company::getShareValueHistory() {
    return shareValueHistory;
}
std::pair<int, int> Company::getForecast() {
    return forecast;
}
int Company::getForecastInfluence() {
    return forecastInfluence;
}
std::pair<float, float> Company::getRateOfChange() {
    return rateOfChange;
}
std::map<double, Stock> Company::getInventory() {
    return inventory;
}
void Company::buy(Investor& investor, int amount) {
    double price = inventory.begin()->first * amount;
    bool approvedTransaction = investor.withdraw(price);

    Stock newStock(amount, companyID);

    investor.recieveStock();
}