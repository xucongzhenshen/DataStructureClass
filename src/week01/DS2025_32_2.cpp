#include <iostream>
#include <vector>
#include <cmath>

// Program: generate all combinations of n Boolean variables x1..xn
// and compute frequency counts (how many times each xi is true).

int main() {
	std::cout << "Enter number of Boolean variables n (0 <= n <= 20): ";
	long long n;
	if (!(std::cin >> n)) {
		std::cerr << "Invalid input. Expected an integer n.\n";
		return 1;
	}
	if (n < 0) {
		std::cerr << "n must be non-negative.\n";
		return 1;
	}
	if (n > 20) {
		std::cerr << "n too large; this program limits n to 20 to avoid huge output.\n";//avoid too much runtime
		return 1;
	}

	unsigned long long total = 1ULL << n; // number of combinations (safe for n<=63)
	std::vector<unsigned long long> trueCount(n, 0);

	std::cout << "Total combinations: " << total << "\n\n";

	// Iterate through all bitmasks from 0 to 2^n - 1
	//frequency count
	unsigned long long s1 = 0, s2 = 0;
	for (unsigned long long mask = 0; mask < total; ++mask) {
		s1++;
		for (long long i = n - 1; i >= 0; --i) {
			s2++;
			bool val = (mask >> i) & 1ULL;					
			std::cout << (val ? "true" : "false");			
			if (i > 0) std::cout << ", ";
		}
		std::cout << "\n";
	}

	//Frequency count
	std::cout << "\nFrequency counts:\n";
	std::cout << "s1: " << s1 << "\ns2: " << s2 << std::endl;

	return 0;
}

