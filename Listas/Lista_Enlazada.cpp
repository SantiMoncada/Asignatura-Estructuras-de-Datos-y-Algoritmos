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
		delete[]p;
	}
}

void eliminarNumero(struct TLista *L, int v) {
	NodoLista *q = busca(L, v);
	if (q != NULL) {
		elimina(L, q);
	}
}

void imprime(struct TLista *L) {
	NodoLista *p = L->inicio;
	if (p == NULL)
		cout << "Lista vacia " << std::endl;
	else {
		cout << "Lista {";
		while (p != NULL) {
			cout << p->dato << ",";
			p = p->siguiente;
		}
		cout << "}" << std::endl;
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
			insertaFin(L, v);
		}
		else {
			insertaAntes(L, v, q);
		}
	}
}

void eliminaTodos(struct TLista *L, int v) {
	while (busca(L, v) != NULL) {
		eliminarNumero(L, v);
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

void invierte(struct TLista *L1, struct TLista *L2){
	NodoLista *q;
	q = L1->inicio;
	while (q != NULL) {
		insertaInicio(L2, q->dato);
		q = q->siguiente;
	}
}

void inicializa_pila(struct TLista *P) {
	inicializa(P);
}

bool vacia_pila(struct TLista *P) {
	return(vacia(P));
}

void apila_pila(struct TLista *P, int x) {
	insertaFin(P,x);
}

void desapila_pila(struct TLista *P, int &x) {
	x = P->fin->dato;
	elimina(P,P->fin);
}

void tope_pila(struct TLista *P,int &x) {
	x = P->fin->dato;
}

int main() {
	TLista sup;
	inicializa(&sup);
	insertaInicio(&sup, 10);
	insertaInicio(&sup, 6);
	insertaInicio(&sup, 1);
	insertaInicio(&sup, 7);
	insertaInicio(&sup, 1);
	insertaInicio(&sup, 2);
	insertaInicio(&sup, 1);
	imprime(&sup);
	eliminaTodos(&sup, 1);
	imprime(&sup);

	system("pause>null");
	return 0;


}