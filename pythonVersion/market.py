import random

class Market():
    def __init__(self):
        self._companies = []

    def add_company(self, company):
        self._companies.append(company)
    def advanced_list_companies(self):
        for i, company in enumerate(self._companies):
            print(f"->{i}|{company.name}")

        share_value_increase = float(0)

        if (len(company.share_value_history) >= 2):
            share_value_increase = round((1 - company.share_value_history[-2] / company.share_value), 3) * 100
        
        share_value_op = ""
        forecast_op = ["*", "*"]
        if share_value_increase >= 0:
            share_value_op = "+"
        else:
            share_value_op = "-"

        for n in range(2):
            if company.forecast[n] > 0:
                forecast_op[n] = "+"
            else:
                forecast_op[n] = "-"
        print(f"""
\tL share_value={round(company.share_value, 3)} ({round(share_value_increase, 3)}%)
\tL Forecast= {forecast_op[0]}{forecast_op[1]}""")

    def update(self):
        for i, company in enumerate(self._companies):
            forecast_roll = 0
            if random.randint(1, 100) >= 50 - company.forecast_influence * (company.forecast[0] + company.forecast[1] - 1):
                forecast_roll = 1
            else:
                forecast_roll = -1
            rate_of_change_roll = float(random.randint(0, round((company.rate_of_change[1] - company.rate_of_change[0])*1000))) / 1000 + company.rate_of_change[0]
            new_share_value = company.share_value + company.share_value * rate_of_change_roll * forecast_roll 
            
            company.share_value_history.append(new_share_value)
            company.share_value = company.share_value_history[-1]

            company.forecast = (random.randint(0, 1), random.randint(0, 1))

    def getCompanies(self):
        return self.companies
