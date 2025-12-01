#include <iostream>
#include <vector>
#include <string>

// Function to evaluate polynomial at x0 using Horner's method
double evaluatePolynomial(const std::vector<double>& coefficients, double x0) {
    double result = 0.0;
    for (auto it = coefficients.rbegin(); it != coefficients.rend(); ++it) {
        result = result * x0 + *it;
    }
    return result;
}

int main() {
    // Test polynomial: 2 + 3x + 4x^2 (coefficients are in increasing order of power)
    std::vector<double> coefficients = {2, 3, 4};
    double x0 = 5.0;

    double result = evaluatePolynomial(coefficients, x0);
    std::cout << "The polynomial evaluates to: " << result << std::endl;

    return 0;
}