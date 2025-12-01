#include <iostream>
#include <vector>
#include <string>
#include <cmath>

// A recursive function to print powerset of S
void printPowerset(
    const std::vector<std::string> &S,
    const std::string &subset = "")
{
    if (S.empty())
    {
        std::cout << "{" << subset << "}\n";
        return;
    }
    else
    {
        std::vector<std::string> S_rest(S.begin() + 1, S.end());
        printPowerset(S_rest, subset);                                      // Exclude the first element
        printPowerset(S_rest, subset.empty() ? S[0] : subset + "," + S[0]); // Include the first element
    }
}

int main()
{
    // Read strings from standard input until "end" is encountered
    std::vector<std::string> S;
    std::cout << "Enter strings (one per line). Type 'end' to finish:\n";
    while (true)
    {
        std::string s{};
        if (!(std::cin >> s)) // handle EOF or input error
        {
            std::cerr << "Input error or EOF encountered.\n";
            break;
        }
        if (s == "end")
            break;
        S.push_back(s);
    }

    // Print collected strings and a simple count
    std::cout << "Read " << S.size() << " items:\n";
    std::cout << "S = {" << S[0];
    for (size_t i = 1; i < S.size(); ++i)
    {
        std::cout << ',' << S[i];
    }
    std::cout << "}\n";

    // Print powerset of S
    printPowerset(S);
    return 0;
}