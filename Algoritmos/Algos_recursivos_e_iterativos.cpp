#include "stdafx.h"
#include "iostream"
using namespace std;

bool numPar(int n) {
	bool r;
	if (n == 0) {
		r = true;
	}
	else if (n == 1) {
		r = false;
	}
	else {
		r = numPar(n - 2);
	}
	return r;
}

/*

bool esImpar(int n) {
	if (n == 0)
		return false;
	else
		return esPar(n - 1);
}
*/

/*
bool esPar(int n) {
	if (n == 0) {
		return true;
	}
	else {
		return esImpar(n - 1);
	}
}
*/

int producto(int x, int n) {
	int p;
	if (x == 0) {
		p = 0;
	}
	else if (x == 1) {
		p= n;
	}
	else
		p = n + producto(x - 1, n);
	return p;
}

int potencia1(int x, int n) {
	int p;
	if (n == 0) {
		p = 1;
	}
	else {
		p= x * potencia1(x , n - 1);
	}
	return p;
}

int potencia2(int x, int n) {
	int p;

	if (n == 0) {
		p = 1;
	}
	else {
		if (n % 2 == 0) {
			p = potencia2(x*x, n / 2);
		}
		else {
		
		p = x*potencia2(x*x, n / 2);
		}
	}
	return p;
}

int factorial(int n) {
	int f;

	if (n == 0) {
		f = 1;
	}
	else {
		f = n*factorial(n - 1);
	}
	return f;
}

int fibonacci(int n) {
	int f;
	if (n == 0 || n == 1)
		f = n;
	else
		f = fibonacci(n - 1) + fibonacci(n - 2);
	return f;
}

int cociente(int dividendo, int divisor) {
	int c;
	if (dividendo == divisor)
		c = 1;
	else if (dividendo < divisor)
		c = 0;
	else
		c= 1 + cociente(dividendo - divisor, divisor);
	return c;
}

int resto(int dividendo, int divisor) {
	int r;
	if (dividendo < divisor)
		r = dividendo;
	else
		r = resto(dividendo - divisor, divisor);
	return r;
}

bool multiplo(int a, int b) {
	bool m;
	if (a < b)
		m = (a == 0) ? true : false;
	else
		m = multiplo(a - b, b);
	return m;
}

int sumatoria(int n) {
	if (n == 0)
		return 0;
	else
		return n + sumatoria(n - 1);
}

int sumatoriaPar(int n) {
	if (n == 0)
		return 0;
	else
		return n + sumatoriaPar(n - 2);
}

int sumatoriaImpar(int n) {
	if (n == 1)
		return 1;
	else
		return n + sumatoriaImpar(n - 2);
	return 0;
}

int mcd(int a, int b) {
	int m;
	if (b == 0) {
		m = a;
	}
	else {
		m = mcd(b, a%b);
	}
	return m;
}

int main()
{
	int n;
	int a;
	int m;
	cin >> m;
	switch (m)
	{
	case 1:
		cout << "resto y cociente \n";
		
		cin >> n;
		cin >> a;
		cout << "cociente " << cociente(n, a) << endl;
		cout << "resto  " << resto(n, a);
		break;
	case 2:
		cout << "multiplo\n";
			cin >> n;
			cin >> a;
			cout << endl << multiplo(n, a);
		break;
	case 3:
		cout << "producto\n";
		cin >> n;
		cin >> a;
		cout << endl << producto(n, a);
		break;
	case 4:
		cout << "sumatoria\n";
		cin >> n;
		cout << endl << sumatoria(n);
		break;
	case 5:
		cout << "mcd\n";
		cin >> n;
		cin >> a;
		cout << endl << mcd(n, a);
		break;
	case 6:
		break;
	default:
		break;
	}
	
	system("pause>null");
	return 0;
}