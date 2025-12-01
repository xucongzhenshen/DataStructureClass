// Write a C++ function to make an in-place reversal of the order of elements
// in the array list. That is, the function should transform list such that fol-
// lowing the transformation, list [i] contains the element originally in
// list [n -i - 1]th, where n is the total number of elements in list. The only
// additional space available to your function is that for simple variables.
// How much time does your function take to accomplish the reversal?

#include <iostream>
#include <vector>

void reverseArray(int list[], int n)
{
    int start = 0;
    int end = n - 1;

    while (start < end)
    {
        // exchange list[i] and list[n-i-1]
        int temp = list[start];
        list[start] = list[end];
        list[end] = temp;

        // move towards middle
        start++;
        end--;
    }
}

int main()
{
    // Example usage
    std::vector<int> S={0,1,2,3,4,5,6,7,8,9};

    // Reverse the array in place
    reverseArray(S.data(), S.size());

    // Print the reversed array
    std::cout << "Reversed S = {" << S[0];
    for (size_t i = 1; i < S.size(); ++i)
    {
        std::cout << ',' << S[i];
    }
    std::cout << "}\n";

    return 0;
}

// Time Complexity: O(n), where n is the number of elements in the array. Each element is swapped once.
// Space Complexity: O(1), as the reversal is done in place using only a few additional variables.