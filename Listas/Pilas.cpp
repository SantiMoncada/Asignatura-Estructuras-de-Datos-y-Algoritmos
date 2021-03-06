#include "stdafx.h"
#include <iostream>
using namespace std;

#define TAMANO_PILA 5
#define NO_ERROR 0
#define ERROR_PILA_VACIA 1
#define ERROR_PILA_LLENA 2

struct TPila {
	int tope;
	int datos[TAMANO_PILA];
};

void inicializa(struct TPila *P) {
	P->tope = -1;
}

bool vacia(struct TPila *P) {
	return (P->tope == -1);
}

int apila(struct TPila *P, int v) {
	int err = NO_ERROR;
	if (P->tope < TAMANO_PILA - 1)
		P->datos[++P->tope] = v;
	else
		err = ERROR_PILA_LLENA;
	return err;
}

int desapila(struct TPila *P, int &v) {
	int err = NO_ERROR;
	if (!vacia(P))
		v = P->datos[P->tope--];
	else
		err = ERROR_PILA_VACIA;
	return err;
}

int tope(struct TPila *P, int &v) {
	int err = NO_ERROR;
	if (!vacia(P))
		v = P->datos[P->tope];
	else
		err = ERROR_PILA_VACIA;
	return err;
}

void dec2bin(unsigned short decimal) {
	struct TPila binario;
	int bit;

	cout << "decimal " << decimal << "en binario \n";

	inicializa(&binario);

	while (decimal > 0) {
		apila(&binario, (decimal % 2));

		decimal = decimal / 2;
	}

	while (!vacia(&binario)) {
		if (desapila(&binario, bit) == NO_ERROR)
			cout << bit;
	}

}

void dec2hex(unsigned short decimal, int base) {
	struct TPila digitos;
	int bit;

	cout << "decimal " << decimal << " en base " << base << " \n";

	inicializa(&digitos);

	while (decimal > 0) {
		apila(&digitos, (decimal % base));

		decimal = decimal / base;
	}

	while (!vacia(&digitos)) {
		if (desapila(&digitos, bit) == NO_ERROR) {
			if (bit < 10) {
				cout << bit;
			}
			else {
				cout << char('A' + (bit-10));
			}
		}
	}
}

int main()
{
	struct TPila P;
	int v;

	inicializa(&P);

	if (vacia(&P))
		cout << "Pila vacia " << endl;
	else
		cout << "Pila no vacia " << endl;

	for (int i = 0; i <= 10; i = i + 2)
		if (apila(&P, i) == NO_ERROR)
			cout << "insertado en la pila v=" << i << endl;
		else
			cout << "error al insertar la pila" << endl;
	if (vacia(&P))
		cout << "pila vacia " << endl;
	else {
		if (tope(&P, v) == NO_ERROR)
			cout << "el tope de la pila es " << v << endl;
		else
			cout << "error pila vacia " << endl;
	}
	while (!vacia(&P)) {
		if (desapila(&P, v) == NO_ERROR)
			cout << "desapilando " << v << endl;
		else
			cout << "error al desapilar, pila vacia " << v << endl;
	}


	if (desapila(&P, v) == NO_ERROR)
		cout << "desapilando " << v << endl;
	else
		cout << "error al desapilar , pila vacia " << endl;
	if (vacia(&P))
		cout << "pila vacia " << endl;
	else
		cout << "pila no vacia " << endl;
	cout << "\n\n" << endl;
	
	int a, b;
	cin >> a;
	cin >> b;
	dec2hex(a,b);

	system("pause>null");
	return 0;
}