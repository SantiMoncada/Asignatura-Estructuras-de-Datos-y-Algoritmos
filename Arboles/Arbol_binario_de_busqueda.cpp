#include "stdafx.h"
#include "iostream"
using namespace std;

int max(int a, int b) {
	return (a > b) ? a : b;

}

struct NodoArbol{
int dato;
NodoArbol *izquierdo, *derecho;
};

struct TArbolBinarioBusqueda {
	NodoArbol *raiz;
};

void inicializa(TArbolBinarioBusqueda *R) {
	R->raiz = NULL;
}

bool vacio(TArbolBinarioBusqueda *R) {
	return (R->raiz == NULL);
}

NodoArbol* insertaNodo(int v) {
	NodoArbol *nodo = new NodoArbol;
	nodo->dato = v;
	nodo->izquierdo = NULL;
	nodo->derecho = NULL;
	return nodo;
}

void inserta(NodoArbol *&R, int v) {
	if (R == NULL) {
		R = insertaNodo(v);
	}
	else if (v < R->dato) {
		inserta(R->izquierdo, v);
	}
	else if (v > R->dato) {
		inserta(R->derecho, v);
	}
}

NodoArbol* busca(NodoArbol *R, int v) {
	NodoArbol *aux = NULL;
	if (R != NULL) {
		if (R->dato == v) {
			aux = R;
		}
		else if (R->dato > v) {
			aux = busca(R->izquierdo, v);
		}
		else if (R->dato < v) {
			aux = busca(R->derecho, v);
		}
	}
	return aux;
}

NodoArbol* minimo(NodoArbol *R) {
	NodoArbol * aux;
	if (R == NULL) {
		aux = NULL;
	}
	else if(R->izquierdo == NULL) {
		aux = R;
	}
	else {
		aux=minimo(R->izquierdo);
	}
	return aux;
}

NodoArbol* maximo(NodoArbol *R) {
	NodoArbol * aux;
	if (R == NULL) {
		aux = NULL;
	}
	else if (R->derecho == NULL) {
		aux = R;
	}
	else {
		aux = maximo(R->derecho);
	}
	return aux;
}

NodoArbol* minimo_it(NodoArbol *R) {
	NodoArbol *aux = NULL;
	if (R != NULL) {
		while (R->izquierdo != NULL) {
			R = R->izquierdo;
		}
		aux = R;
	}
	return aux;
}

NodoArbol* maximo_it(NodoArbol *R) {
	NodoArbol * aux = NULL;
	if (R != NULL) {
		while (R->derecho != NULL) {
			R = R->derecho;
		}
		aux = R;
	}
	return aux;
}

int eliminaMinimo(NodoArbol *&R) {
	int eliminado = NULL;
	if (R != NULL) {
		if (R->izquierdo == NULL) {
			eliminado = R->dato;
			R = R->derecho;
		}
		else {
			eliminado = eliminaMinimo(R->izquierdo);
		}
	}
	return eliminado;
}

void elimina(NodoArbol *&R, int v) {
	if (R != NULL) {
		if (R->dato > v) {
			elimina(R->izquierdo, v);
		}
		else if (R->dato < v) {
			elimina(R->derecho, v);
		
		}
		else if (R->dato == v) {
			if (R->izquierdo == NULL && R->derecho == NULL) {
				NodoArbol *p = R;
				R = NULL;
				delete p;
			}
			else if (R->derecho == NULL) {
				R = R->izquierdo;
			}
			else if (R->izquierdo == NULL) {
				R = R->derecho;
			}
			else {
				R->dato = eliminaMinimo(R->derecho);
			}
		}
	}
}

int altura(NodoArbol *R) {
	int a = -1;
	if (R != NULL) {
		a = max(altura(R->izquierdo), altura(R->derecho)) + 1;
	}
	return a;
}

int nodos(NodoArbol *R) {
int n = 0;
if (R != NULL) {
n = (nodos(R->izquierdo) + nodos(R->derecho) + 1);
}
return n;
}

void preorder(NodoArbol *R) {
	if (R != NULL) {
		cout << R->dato << " ";
		preorder(R->izquierdo);
		preorder(R->derecho);
	}
}

void inorder(NodoArbol *R) {
	if (R != NULL) {
		inorder(R->izquierdo);
		cout << R->dato << " ";
		inorder(R->derecho);
	}
}

void postorder(NodoArbol *R) {
	if (R != NULL) {
		postorder(R->izquierdo);
		postorder(R->derecho);
		cout << R->dato << " ";
	}
}

void imprimeArbol(struct TArbolBinarioBusqueda *R) {
	cout << "\n";
	cout << "Preorder ";
	preorder(R->raiz);
	cout << "\n";
	cout << "Inorder ";
	inorder(R->raiz);
	cout << "\n";
	cout << "Postorder ";
	postorder(R->raiz);
	cout << "\n";
}

int main()
{
	TArbolBinarioBusqueda * R = new TArbolBinarioBusqueda;
	inicializa(R);
	inserta(R->raiz, 5);
	inserta(R->raiz, 2);
	inserta(R->raiz, 7);
	inserta(R->raiz, 1);
	inserta(R->raiz, 3);
	inserta(R->raiz, 6);
	inserta(R->raiz, 8);
	imprimeArbol(R);

	int a = eliminaMinimo(R->raiz);
	cout << endl << a << endl;

	imprimeArbol(R);
	return 0;
}
