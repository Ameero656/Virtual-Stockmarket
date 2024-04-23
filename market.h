#pragma once

#include "company.h"

class Market {
public:
    Market();

    void addCompany(Company& company);
    void advancedListCompanies();
    void update();
    std::vector<Company> getCompanies();

private:
    std::vector<Company> companies;
};