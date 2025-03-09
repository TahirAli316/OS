#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

#define N 100000000 // Find primes up to 1 million

void sieve_sequential(bool *is_prime, int n) {
    for (int i = 2; i <= n; i++) {
        is_prime[i] = true; // Assume all numbers are prime
    }

    for (int i = 2; i * i <= n; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= n; j += i) {
                is_prime[j] = false; // Mark multiples as non-prime
            }
        }
    }
}

int main() {
    double totaltime;
    for(int i = 0; i < 10; i++){
    bool *is_prime = (bool *)malloc((N + 1) * sizeof(bool));
    clock_t start = clock(); // Start timer

    sieve_sequential(is_prime, N);

    clock_t end = clock(); // End timer
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    totaltime += time_taken;
    printf("Sequential Execution Time: %.6f seconds\n", time_taken);

    free(is_prime);
    }
    printf("Average time: %.6f seconds\n", totaltime/10);
    return 0;
}
