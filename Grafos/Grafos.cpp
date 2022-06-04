void dfs(struct TGrafo *G, int v, bool *&visitado) {//EL ARRAy de booleanos de tamano numero de vertices para ver si cada vertice fue visitado
													// recorrido en profundidad de un grafo. concretamente un preorder
	visitado[v] = true;
	cout << v + 1 << " ";//porque en el grafo los vertices empiezan en 0
	for (int i = 0; i < G->vertices; i++)
		if (G->aristas[v][i] != INFINITO && !visitado[i])//esto significa que hay una arista desde v hasta i, porque estamos en el v y queremos comprobar todos los demas
			dfs(G, i, visitado);
	//puede que visite todos los vertices o no, pero si no lo hace, entonces hay que poner esto 
	//AMPLIAR ESTA FUNCION PARA QUE VEAMOS QUE VISITA TODOS LOS NODOS. UN DO WHILE O UN WHILE. SI TODA LA TABLA ESTA TRUE, ESTA TERMINADO, SINO, HAY QUE HACER OTRO DFS A PARTIR DE AHI.PROBAR CON EL GRAFO CHUNGO QUE TENEMOS DIBUJADO EN LOS APUNTES
}
//Esta inicializa la tabla y llama a la dfs
void profundidad(struct TGrafo *G, int inicio) {//inicio = vertice desde el que se empieza.
	bool *visitado = new bool[G->vertices]; //creamos el vector visitado booleano
	for (int i = 0; i < G->vertices; i++)
		visitado[i] = false;
	dfs(G, inicio - 1, visitado);//inicio - 1 porque los vertices para nosotros empiezan en 0, por lo que para el que lo ve seria cero, y para nosotros tiene que ser 0
	for (int i = 0; i < G->vertices; i++)
		if (!visitado[i])
			dfs(G, i, visitado);
}
//necesita una funcion que inicialice la pila y que llame a la bfs

void topologico(struct TGrafo *G, int v, bool *&visitado, Pila &vertices) {
	visitado[v] = true;
	for (int i = 0; i < G->vertices; i++) {
		if (G->aristas[v][i] != INFINITO && !visitado[i]) {
			topologico(G, i, visitado, vertices);
		}
	}
	vertices.apila(v + 1);


}
int verticeNoVisitado(bool *visitado, int vertices) {
	int vertice = -1;
	for (int i = 0; i < vertices; i++)
		if (!visitado[i]) {
			vertice = 1;
			break;
		}
	return vertice;
}
void ordenTopologico(struct TGrafo *G, int inicio) {
	bool *visitado = new bool[G->vertices];
	Pila vertices = Pila(G->vertices);

	for (int i = 0; i < G->vertices; i++)
		visitado[i] = false;
	cout << "\nOrden topologico \n";

	int v = inicio - 1;

	do {
		topologico(G, v,visitado, vertices);
		v = verticeNoVisitado(visitado, G->vertices);
	} while (v != -1);
	cout << endl;
	while (! vertices.vacia()) {
		vertices.desapila(v);
		cout << v << " ";
	}
	cout << "\n";
}
//para hacer esta necesitamos una funcion profundidad que la llame, que incluya el booleano visitados etc.

void floyd(struct TGrafo G, int vertices, int *&A, int **&P) {// 
	// algoritmo de Floyd para resolver el problema del camino
	// más corto entre todos los pares de vértices
	A = new int*[vertices];
	P = new int*[vertices];

	//define la tabla de costes A y la tabla de costes B.

	for (int i = 0; i < vertices; i++) {//Este inicializa los arrays
		A[i] = new int[vertices];
		P[i] = new int[vertices];
	}
	//Inicializa la tabla A de costes y aristas. 

	for (int i = 0; i < vertices; i++)
		for (int j = 0; j < vertices; j++) {
			P[i][j] = INFINITO;

			if (i == j)
				A[i][j] = 0;// si esta en la diagonal, lo pone a cero.
			else
				A[i][j] = coste(G, i + 1, j + 1); // sino el valor es el coste que hay entre los puntos, y + 1 porque es el vertice.
		}
	

	//Este selecciona el camino mas corto.

	for (int k = 0; k < vertices; k++)
		for (int i = 0; i < vertices; i++)
			for (int j = 0; j < vertices; j++)
				if (A[i][k] + A[k][j] < A[i][j]) {
					A[i][j] = A[i][k] + A[k][j];
					P[i][j] = k;
				}
}

void costeMinimoArista(struct TGrafo *G,Conjunto U, Conjunto W, int &u, int &w) {
	int min = INFINITO;
	for (int i = 1; i <= G->vertices; i++)
		if (U.pertenece(i))
			for (int j = 1; j <= G->vertices; j++)
				if (W.pertenece(j) )
					if (coste(G, i, j) < min) {
						min = coste(G, i, j);
						u = i;
						w = j;
					}
}
void prim(struct TGrafo *G, int vertices, struct TGrafo *&T) {
	// algoritmo de Prim para calcular el árbol de recubrimiento
	// mínimo. crea el grafo total con el minimo coste posible, aunque en algunas ocasiones para ir de un lado a otro pudiera ser mejor otra opcion
	Conjunto V = Conjunto(vertices, true);//aqui creamos el conjunto V. LLaamos al constructor que nos deja el conjunto vacio, aunque hay otro constructor
	//si dices Conjunto (6,true) te va a crear un conjunto con 6 vertices
	Conjunto U = Conjunto(vertices);
	U.inserta(1);
	Conjunto W/V-U/ = Conjunto::resta(V, U);//nos dice que w es el conjunto de v menos u
	inicializa(T, vertices);
	int u, w; //u va a ser el vertice origen y w el vertice destino
	while (!U.esIgual(V)) {//mientras el conjunto U no tiene todos los vertices(no se conectan todos)
		costeMinimoArista(G, U, W, u, w);//esta funcion hace la busqueda de la arista
		inserta(T, u, w, coste(G, u, w));//inserto en el grafo T una arista con el coste definido por el coste entre u y w
		inserta(T, w, u, coste(G, u, w));//para que pueda recorrerse tambien en el otro sentido.
		U.inserta(w);//lo insertamos en este conjunto
		W.elimina(w);//lo eliminamos en este.
	}
}



void dijkstra(struct TGrafo *G, int vertices, int *&D) {
	Conjunto V = Conjunto(vertices, true);
	Conjunto S = Conjunto(vertices);

	S.inserta(1);
	 
	//inicializa el vector D de costes minimos

	D = new int[vertices];

	for (int i = 1; i < vertices; i++)//este busca cual es el nuevo valor de
		D[i] = coste(G, 1, (i + 1));//aqui lo que esta haciendo
	int v, minimo;
	Conjunto W = Conjunto(vertices);

	for (int i = 1; i < vertices; i++) {

		//el conjunto W = V-S con los vertices pendientes de analizar, 
		//entre los que selecciona un vertice v en V-S tal que D[v] sea minimo.

		W = Conjunto::resta(V, S);
		minimo = INFINITO;//lo que hace es buscar cual es el valor minimo de la tabla D

		for (int k = 2; k<= vertices; k++)//nos busca cual es el vertice con el coste minimo de D
			if (W.pertenece(k))
				if (D[k - 1] < minimo) {
					v = k;
					minimo = D[k - 1];
				}
		S.inserta(v);
		W = Conjunto::resta(V, S);

		for (int k = 2; k <= vertices; k++)
			if (W.pertenece(k))
				D[k - 1] = min(D[k - 1], D[v - 1] + coste(G, v, k));
	}
}