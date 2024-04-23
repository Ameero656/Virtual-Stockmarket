from stock import Stock
from company import Company
from market import Market

def main():
    market = Market()
    company1 = Company("Apple", 100, (0, 1), (0, 0.05), 25)

    market.add_company(company1)
    market.advanced_list_companies()
    for x in range(100):
        market.update()
        market.advanced_list_companies()
        input()


if __name__ == "__main__":
    main()