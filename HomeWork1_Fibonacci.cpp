#include<iostream>
using namespace std;
long long Fibo[91];

bool isFibo(int n) {
	return Fibo[n] == 0;
}

long long Fibonacci(int n) {
	if (n > 90 || n < 0) return -1;
	if (isFibo(n)) {
		Fibo[0] = Fibo[1] = 1;
		if (n >= 2) {
			Fibo[n] = Fibonacci(n - 1) + Fibonacci(n - 2);
		}
	}
	return Fibo[n];
}

int main() {
	int n = 0;
	cin >> n;
	long long p = Fibonacci(n);
	if (p == -1) cout << "WRONG!";
	else cout << p;
	return 0;
}