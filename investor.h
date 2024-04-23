#pragma once

class Investor {
public:
    Investor();

    bool withdraw(int amount);
    void recieveStock();
private:
    double balance;
};