#include <time.h>

#include "myArith.h"
#include "stock.h"
#include "company.h"
#include "market.h"


int main() {
    srand(time(NULL));
    Market market;
    Company company1("Apple", 100, { 0, 1 }, { 0, .05 }, 25);
    market.addCompany(company1);
    market.advancedListCompanies();
    for (int i = 0; i < 1; i++) {
        market.update();
        market.advancedListCompanies();
    }

}