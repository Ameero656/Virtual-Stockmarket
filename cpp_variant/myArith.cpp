#include "myArith.h"
#include <cmath>

float MyArith::roundToDecimal(double number, int decimalPlaces) {
    float multiplier = std::pow(10.0, decimalPlaces);
    return std::round(number * multiplier) / multiplier;
}

