#include <iostream>
#include <vector>
#include <cstdlib>

int generate_prime_number();
int find_coprime(int number);
int euclidean_algorithm(int x, int y);
using namespace std;

// funkcja generujaca liczbe pierwsza
int generate_prime_number() { 
    bool isPrime = false;
    int divisors_number = 0;
    int number = 0;
    int sqrt_number = 0;

    while (!isPrime) {
        while (number <= 256) {
            number = rand() % 10000; // losuje liczbe z przedzialu 0-9999
        }

        sqrt_number = sqrt(number);

        for (int i = 2; i <= sqrt_number; i++) {
            if (number % i == 0)
                divisors_number++;
        }

        if (divisors_number == 0) {
            isPrime = true;
        } else {
            number = 0;
            divisors_number = 0;
        }

    }

    return number;
}

int find_coprime(int number) {
    int co_prime = 0;
    vector<int> co_primes;

    for (int i = 2; i < number - 1; i++) { // szukamy liczby wzglednie pierwszej z liczba number w przedziale (1, number - 1)
        if (euclidean_algorithm(number, i) == 1) {
            co_prime = i;
            co_primes.push_back(co_prime);
        }
    }

    co_prime = co_primes[rand() % co_primes.size()]; // losujemy liczbe pierwsza z przedzialy (1, number - 1)

    return co_prime;
}

int euclidean_algorithm(int x, int y)
{
    int tmp;
    
	while(y!=0)
    {
		tmp = y;
		y = x%y;
		x = tmp;	
	}
	
    return x;
}

int main() {

    srand(time(NULL));

    // int p = generate_prime_number();
    int p = 262;
    int q = find_coprime(p);

    cout << p << " " << q << endl;

    return 0;
}