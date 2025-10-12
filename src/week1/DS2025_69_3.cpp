//Determine the frequency counts for all statements in the following two pro-
//gram segments:
//for (i = 1; i <= n; i++)                  s1
//    for (j = 1; j <= i; j++)              s2
//        for (k = 1; k <= j; k++)          s3
//            x++;                          s4
//            (a)
//i = 1;
//while (i <= n)                            s5
//{
//    x++;                                  s6
//    i++;                                  s7  
//}
//            (b)

#include <iostream>

int main() {
    int n;
    // (a) program segment
    std::cout << "Enter a positive integer n: ";
    std::cin >> n;
    int s1 = 0, s2 = 0, s3 = 0, s4 = 0;
    for (int i = 1; i <= n; i++) {
        s1++;
        for (int j = 1; j <= i; j++) {
            s2++;
            for (int k = 1; k <= j; k++) {
                s3++;
                s4++;
            }
        }
    }
    std::cout << "s1: " << s1 << "\ns2: " << s2 << "\ns3: " << s3 << "\ns4: " << s4 << std::endl;

    std::cout << "----------------------------------" << std::endl;

    // (b) program segment
    std::cout << "Enter a positive integer n: ";
    std::cin >> n;
    int s5 = 0, s6 = 0, s7 = 0;
    int i = 1;
    while (i <= n) {
        s5++;
        s6++;
        s7++;
        i++;
    }
    std::cout << "s5: " << s5 << "\ns6: " << s6 << "\ns7: " << s7 << std::endl;
    return 0;
}