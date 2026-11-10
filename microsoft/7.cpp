#include <iostream>

using namespace std;

int consecutiveNumbersSum(int n) {
    int count = 0;
    
    // We iteratively subtract k from n. 
    // This implicitly reduces n by k(k-1)/2 over the iterations.
    for (int k = 1; n > 0; n -= k, k++) {
        // If the remaining n is divisible by k, a valid starting integer 'a' exists
        if (n % k == 0) {
            count++;
        }
    }
    
    return count;
}