class Nodo {
public:
	char tipo;
};

class Alumno : public Nodo {
public:
	const char* matricula;
	const char* nombre;
	Nodo* cursos;
	Alumno(const char* matricula, const char* nombre, Nodo* cursos);
	void imprime();
};

class Curso : public Nodo {
public:
	const char* codigo;
	const char* nombre;
	Nodo* alumnos;
	Curso(const char* codigo, const char* nombre, Nodo* alumnos);
	void imprime();
};

class Matricula : public Nodo {
public:
	int nota;
	Nodo* siguienteCurso;
	Nodo* siguienteAlumno;
	Matricula();
};