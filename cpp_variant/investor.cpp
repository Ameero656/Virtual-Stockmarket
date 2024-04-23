#include "investor.h"

Investor::Investor() {}

bool Investor::withdraw(int amount) {
    if (balance - amount < 0) return false;
    balance -= amount;
    return true;
}
void Investor::recieveStock() {

}