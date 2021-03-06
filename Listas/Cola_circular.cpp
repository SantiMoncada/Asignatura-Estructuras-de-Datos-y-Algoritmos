#include "stdafx.h"
#include "iostream"
using namespace std;

struct NodoLista {
	int dato;
	NodoLista *siguiente;
};

struct TLista {
	NodoLista *inicio, *fin;
};

void inicializa(struct TLista *L) {
	L->inicio = NULL;
	L->fin = NULL;
}

bool vacia(struct TLista *L) {
	return (L->inicio == NULL);
}

NodoLista* inicio(struct TLista *L) {
	return L->inicio;
}

NodoLista* fin(struct TLista *L) {
	return L->fin;
}

NodoLista* busca(struct TLista *L, int v) {
	NodoLista *p = L->inicio;
	if (p != NULL)
		while (p != NULL) {
			if (p->dato == v)
				break;
			p = p->siguiente;
		}
	return p;
}

void insertaInicio(struct TLista *L, int v) {
	NodoLista *tmp = new NodoLista;
	tmp->dato = v;
	if (vacia(L)) {
		tmp->siguiente = NULL;
		L->inicio = tmp;
		L->fin = tmp;
	}
	else {
		tmp->siguiente = L->inicio;
		L->inicio = tmp;
	}
}

void insertaFin(struct TLista *L, int v) {
	NodoLista *tmp = new NodoLista;
	tmp->dato = v;
	if (vacia(L)) {
		tmp->siguiente = NULL;
		L->inicio = tmp;
		L->fin = tmp;
	}
	else {
		tmp->siguiente = NULL;
		L->fin->siguiente = tmp;
		L->fin = tmp;
	}
}

void insertaAntes(struct TLista *L, int v, NodoLista *p) {
	if (p != NULL)
		if (p == L->inicio) {
			insertaInicio(L, v);
		}
		else {
			NodoLista *q = L->inicio;
			while (q->siguiente != p)
				q = q->siguiente;
			if (q->siguiente == p) {
				NodoLista *tmp = new NodoLista;
				tmp->dato = v;
				tmp->siguiente = p;
				q->siguiente = tmp;
			}
		}
}

void insertaDespues(struct TLista *L, int v, NodoLista *p) {
	if (p != NULL)
		if (p == L->fin) {
			insertaFin(L, v);
		}
		else {
			NodoLista *tmp = new NodoLista;
			tmp->dato = v;
			tmp->siguiente = p->siguiente;
			p->siguiente = tmp;
		}
}

void elimina(struct TLista *L, NodoLista *p) {
	 
	if (p != NULL) {
		if (p == L->inicio) {
			L->inicio = L->inicio->siguiente;
		}
		else if (p == L->fin) {
			NodoLista *q = L->inicio;
			while (q->siguiente != p) {
				q = q->siguiente;
			}
			q->siguiente = NULL;
			L->fin = q;
		}
		else {
			NodoLista *q = L->inicio;
			while (q->siguiente != p) {
				q = q->siguiente;
			}
			q->siguiente = p->siguiente;
		}
		delete(p);
	}
}

void eliminarNumero(struct TLista *L, int v) {
	NodoLista *q = busca(L, v);
	if (q != NULL) {
		elimina(L, q);
	}
}

void insertarOrdenado(struct TLista *L, int v) {
	if (vacia(L)) {
		insertaInicio(L, v);
	}
	else {
		NodoLista *q = L->inicio;
		while (q->dato < v && q->siguiente != NULL) {
			q = q->siguiente;
		}
		if (q->dato<v) {
			insertaDespues(L, v, L->fin);
		}
		else {
			insertaAntes(L, v, q);
		}
	}
}

void imprime(struct TLista *L) {
	NodoLista *p = L->inicio;
	if (p == NULL)
		cout << "Lista vacia " << endl;
	else {
		cout << "Lista {";
		while (p != NULL) {
			cout << p->dato << ",";
			p = p->siguiente;
		}
		cout << "}" << endl;
	}
}

void concatenar(struct TLista *A, struct TLista *B, struct TLista *L) {
	if (!(vacia(A)) && !(vacia(B))) {
		NodoLista *q;
		q = A->inicio;
		do {
			insertaFin(L, q->dato);
			q = q->siguiente;
		} while (q != NULL);
		
		q = B->inicio;
		do {
			insertaFin(L, q->dato);
			q = q->siguiente;
		} while (q != NULL);
	}
}

int main()
{
	TLista sup;
	inicializa(&sup);
	insertaInicio(&sup, 10);
	insertaInicio(&sup, 6);
	insertaInicio(&sup, 7);
	insertaInicio(&sup, 1);
	insertaInicio(&sup, 2);
	imprime(&sup);

	TLista bra;
	inicializa(&bra);
	insertaInicio(&bra, 7);
	insertaInicio(&bra, 5);
	insertaInicio(&bra, 2);
	insertaInicio(&bra, 3);
	insertaInicio(&bra, 3);
	imprime(&bra);

	TLista c;
	inicializa(&c);
	concatenar(&sup, &bra, &c);
	imprime(&c);
	system("pause>null");
    return 0;
}