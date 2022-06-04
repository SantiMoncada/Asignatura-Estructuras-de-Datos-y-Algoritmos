#include "stdafx.h"
#include "iostream"
using namespace std;

struct NodoLista {
	int dato;
	NodoLista *anterior, *siguiente;
};

struct TListaDobleEnlace {
	NodoLista *inicio, *fin;
};

void inicializa(struct TListaDobleEnlace *L) {
	L->inicio = NULL;
	L->fin = NULL;
}

bool vacia(struct TListaDobleEnlace *L) {
	return (L->inicio == NULL);
}

NodoLista* inicio(struct TListaDobleEnlace *L) {
	return L->inicio;
}

NodoLista* fin(struct TListaDobleEnlace *L) {
	return L->fin;
}

NodoLista* busca(struct TListaDobleEnlace *L, int v) {
	NodoLista *p = L->inicio;
	if (p != NULL)
		while (p != NULL) {
			if (p->dato == v)
				break;
			p = p->siguiente;
		}
	return p;
}

void insertaInicio(struct TListaDobleEnlace *L, int v) {
	NodoLista *tmp = new NodoLista;
	tmp->dato = v;
	if (vacia(L)) {
		tmp->anterior = NULL;
		tmp->siguiente = NULL;
		L->inicio = tmp;
		L->fin = tmp;
	}
	else {
		tmp->anterior = NULL;
		tmp->siguiente = L->inicio;
		tmp->siguiente->anterior = tmp;
		L->inicio = tmp;
	}
}

void insertaFin(struct TListaDobleEnlace *L, int v) {
	NodoLista *tmp = new NodoLista;
	tmp->dato = v;

	if (vacia(L)) {
		tmp->siguiente = NULL;
		tmp->anterior = NULL;
		L->inicio = tmp;
		L->fin = tmp;
	}
	else {
		tmp->anterior = L->fin;
		tmp->siguiente = NULL;
		L->fin->siguiente = tmp;
		L->fin = tmp;
	}
}

void insertaAntes(struct TListaDobleEnlace *L, int v, struct NodoLista *q) {
	NodoLista *tmp = new NodoLista;
	if (q == L->inicio) {
		insertaInicio(L, v);
	}
	else {
		tmp->dato = v;
		tmp->anterior = q->anterior;
		tmp->siguiente = q;
		q->anterior->siguiente = tmp;
		q->anterior = tmp;
	}
}

void insertaDespues(struct TListaDobleEnlace *L, int v, NodoLista *q) {
	NodoLista *tmp = new NodoLista;
	if (q == L->fin) {
		insertaFin(L, v);
	}
	else {
		tmp->dato = v;
		tmp->anterior = q;
		tmp->siguiente = q->siguiente;
		q->siguiente->anterior = tmp;
		q->siguiente = tmp;
	}
}

void elimina(struct TListaDobleEnlace *L, NodoLista *q) {
	if (q == L->inicio) {
		L->inicio->siguiente->anterior = NULL;
		L->inicio = L->inicio->siguiente;
	}
	else if (q == L->fin) {
		L->fin->anterior->siguiente = NULL;
		L->fin = L->fin->anterior;
	}
	else {
		q->anterior->siguiente = q->siguiente;
		q->siguiente->anterior = q->anterior;
	}
	delete[]q;
}

void elimina(struct TListaDobleEnlace *L, int v) {
	NodoLista *p = busca(L, v);
	if (p != NULL)
		elimina(L, p);
}

void imprimeDesdeInicio(struct TListaDobleEnlace *L) {
	NodoLista *p = L->inicio;
	if (p == NULL)
		cout << "Lista vacia " << endl;
	else {
		cout << "Lista {";
		while (p != NULL) {
			cout << p->dato << ",";
			p = p->siguiente;
		}
		cout << "} \n";
	}
}

void imprimeDesdeFin(struct TListaDobleEnlace *L) {
	NodoLista *p = L->fin;
	if (p == NULL) {
		cout << "Lista vacia " << endl;
	}
	else {
		cout << "Lista {";
		while (p != NULL) {
			cout << p->dato << ",";
			p = p->anterior;
		}
		cout << "} \n";
	}
}

int main()
{

	struct TListaDobleEnlace L;
	NodoLista *p;
	int valor;
	inicializa(&L);
	if (vacia(&L))
		cout << "La lista L esta vacia \n";
	insertaInicio(&L, 5);
	insertaInicio(&L, 3);
	insertaInicio(&L, 1);
	insertaFin(&L, 7);
	insertaFin(&L, 9);
	insertaInicio(&L, 0);
	// muestra los nodos de la lista
	imprimeDesdeInicio(&L);
	imprimeDesdeFin(&L);
	
	// se inserta un nodo antes y despues de 9
	valor = 9;
	p = busca(&L, valor);
	cout << "Inserta 8 antes de 9 \n";
	insertaAntes(&L, 8, p);
	cout << "Inserta 10 despues de 9 \n";
	insertaDespues(&L, 10, p);
	// muestra los nodos de la lista
	imprimeDesdeInicio(&L);
	imprimeDesdeFin(&L);

    return 0;
}