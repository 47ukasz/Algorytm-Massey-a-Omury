#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>

using namespace std;

int generate_prime_number();
int find_coprime(int number);
int euclidean_algorithm(int x, int y);
int extended_euclidean_algorithm(int number_value, int mod_value);
void calculate_ascii_values(vector <int> & vector_ptr, string text);
int calculate_modular_exponentiation(int number_value, int exponent_value, int mod);
void handle_encryption_decryption(vector<int> arr_from, vector<int> & arr_to, int exponent, int prime);

int main() {
    srand((unsigned)time(NULL));

    string decrypted_message;
    string message;
    vector<int> ascii_values;
    vector<int> C1_values;
    vector<int> C2_values;
    vector<int> C3_values;
    vector<int> decrypted_values;

    cout << "Podaj wiadomosc: ";
    getline(cin, message);

    int p = generate_prime_number();
    int eA = find_coprime(p - 1);
    int dA = extended_euclidean_algorithm(eA, p - 1);
    int eB = find_coprime(p - 1);
    int dB = extended_euclidean_algorithm(eB, p - 1);
    
    calculate_ascii_values(ascii_values, message);
    handle_encryption_decryption(ascii_values, C1_values, eA, p); // szyfrowanie
    handle_encryption_decryption(C1_values ,C2_values, eB, p); // szyfrowanie
    handle_encryption_decryption(C2_values, C3_values, dA, p); // szyfrowanie 
    handle_encryption_decryption(C3_values, decrypted_values, dB, p); // deszyfrowanie

    for (auto val : decrypted_values) {
        decrypted_message.push_back((char)val);
    }

    cout << "--- WYNIKI ---" << endl;

    cout << "Wylosowana liczba pierwsza p: " << p << endl;
    
    cout << "Nadawca (A) wybral eA: " << eA << ", dA: " << dA << endl;

    cout << "Odbiorca (B) wybral eB: " << eB << ", dB: " << dB << endl;

    cout << "Kody ASCII: ";
    for (auto val : ascii_values) cout << val << " ";
    cout << endl;

    cout << "C1 (po 1. szyfrowaniu): ";
    for (auto c : C1_values) cout << c << " ";
    cout << endl;

    cout << "C2 (po 2. szyfrowaniu): ";
    for (auto c : C2_values) cout << c << " ";
    cout << endl;

    cout << "C3 (po 3. szyfrowaniu): ";
    for (auto c : C3_values) cout << c << " ";
    cout << endl;

    cout << "Odszyfrowane kody ASCII: ";
    for (auto val : decrypted_values) {
        cout << val << " ";
    }
    cout << endl;

    cout << "Odszyfrowana wiadomosc: " << decrypted_message << endl;

    return 0;
}

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

void calculate_ascii_values(vector <int> & vector_ptr, string text) {
    for (int i = 0; i < text.length(); i++) {
        vector_ptr.push_back((int)text[i]);
    }   
}

int calculate_modular_exponentiation(int number_value, int exponent_value, int mod) {
    int result = 1;            
    int number = number_value % mod; 
    int exponent = exponent_value;

    while (exponent > 0) {
        if (exponent & 1) {
            result = (result * number) % mod; 
        }

        exponent = exponent >> 1;

        number = (number * number) % mod;
    }

    return result;
}

int find_coprime(int number) {
    int co_prime = 0;
    vector<int> co_primes;

    for (int i = 2; i < number; i++) { // szukamy liczby wzglednie pierwszej z liczba number w przedziale (1, number - 1) i dodajemy do vektora co_primes
        if (euclidean_algorithm(number, i) == 1) {
            co_primes.push_back(i);
        }
    }

    co_prime = co_primes[rand() % co_primes.size()]; // losujemy liczbe pierwsza z przedzialu (1, number - 1)

    return co_prime;
}

int euclidean_algorithm(int x, int y) {
    int tmp;
    
	while (y != 0) {
		tmp = y;
		y = x%y;
		x = tmp;	
	}
	
    return x;
}

int extended_euclidean_algorithm(int number_value, int mod_value) {
    int number, mod, temp, q, x, y;
 
    x = 0; 
    y = 1; 
    number = number_value; 
    mod = mod_value; 

    while (number > 1) {
        q = number / mod;

        temp = mod;

        mod = number % mod;
        number = temp;

        temp = x;
        x = y - q * x;
        y = temp;
    }

    if (y < 0) {
        y += mod_value;
    }

    return y;
}

void handle_encryption_decryption(vector<int> arr_from, vector<int> & arr_to, int exponent, int prime) {
    int value; 

    for (auto number : arr_from) {
        value = calculate_modular_exponentiation(number, exponent, prime);
        arr_to.push_back(value);
    }
}