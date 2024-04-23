class Company():
    def __init__(self, name, share_value, forecast, rate_of_change, forecast_influence):
        self.name = name
        self.share_value = share_value
        self.forecast = forecast
        self.rate_of_change = rate_of_change
        self.forecast_influence = forecast_influence
        
        self.share_value_history = [share_value]
        self.inventory = {}

    def buy(investor, amount):
        price = inventory[0].key() * amount
        approved_transaction = investor.withdraw(price)