#include "stdafx.h"
#include "iostream"
#include "Clases.h"

void altaMatricula(Alumno *&alumno, Curso *&curso) {

	if (alumno != NULL && curso != NULL) {

		if (alumno->cursos == NULL && curso->alumnos == NULL) {
			Matricula * aux = new Matricula;
			aux->siguienteAlumno = curso;
			aux->siguienteCurso = alumno;
			alumno->cursos = aux;
			curso->alumnos = aux;
		}
		else if (curso->alumnos == NULL) {
			Matricula * aux = new Matricula;
			aux->siguienteCurso = alumno;
			aux->siguienteAlumno = curso;

			curso->alumnos = aux;

			Nodo * M;
			for (M = alumno->cursos; static_cast<Matricula*>(M)->siguienteCurso->tipo != 'A'; M = static_cast<Matricula*>(M)->siguienteCurso);
			static_cast<Matricula*>(M)->siguienteCurso = aux;

		}
		else if (alumno->cursos == NULL) {
			Matricula * aux = new Matricula;
			aux->siguienteCurso = alumno;
			aux->siguienteAlumno = curso;

			alumno->cursos = aux;

			Nodo *M;
			for (M = curso->alumnos; static_cast<Matricula*>(M)->siguienteAlumno->tipo != 'C'; M = static_cast<Matricula*>(M)->siguienteAlumno);
			static_cast<Matricula*>(M)->siguienteAlumno = aux;
		}
		else {
			Matricula * aux = new Matricula;
			aux->siguienteCurso = alumno;
			aux->siguienteAlumno = curso;

			Nodo *M;

			for (M = alumno->cursos; static_cast<Matricula*>(M)->siguienteCurso->tipo != 'A'; M = static_cast<Matricula*>(M)->siguienteCurso);
			static_cast<Matricula*>(M)->siguienteCurso = aux;

			for (M = curso->alumnos; static_cast<Matricula*>(M)->siguienteAlumno->tipo != 'C'; M = static_cast<Matricula*>(M)->siguienteAlumno);
			static_cast<Matricula*>(M)->siguienteAlumno = aux;
		}
	}
}

//Faltan Precondiciones
void bajaMatricula(Alumno *&alumno, Curso *&curso) {
	if (alumno != NULL && curso != NULL) {
		Nodo * aux;
		for (aux = alumno->cursos; aux->tipo != 'A'; aux = static_cast<Matricula*>(aux)->siguienteCurso) {
			Nodo * auxCur;
			for (auxCur = static_cast<Matricula*>(aux)->siguienteAlumno; auxCur->tipo != 'C'; auxCur = static_cast<Matricula*>(auxCur)->siguienteAlumno);
			if (static_cast<Curso*>(auxCur) == curso) {
				break;
			}
		}

		Matricula* M = static_cast<Matricula*>(aux);

		if (static_cast<Matricula*>(alumno->cursos)->siguienteCurso == alumno && static_cast<Matricula*>(curso->alumnos)->siguienteAlumno == curso) {
			alumno->cursos = NULL;
			curso->alumnos = NULL;
			delete M;
		}
		else if (static_cast<Matricula*>(alumno->cursos)->siguienteCurso == alumno) {
			Nodo * C;
			for (C = curso->alumnos; static_cast<Matricula*>(C)->siguienteAlumno != M; C = static_cast<Matricula*>(C)->siguienteAlumno);
			static_cast<Matricula*>(C)->siguienteAlumno = M->siguienteAlumno;
			alumno->cursos = NULL;
			delete M;

		}
		else if (static_cast<Matricula*>(curso->alumnos)->siguienteAlumno == curso) {
			Nodo * A;
			for (A = alumno->cursos; static_cast<Matricula*>(A)->siguienteCurso != M; A = static_cast<Matricula*>(A)->siguienteCurso);
			static_cast<Matricula*>(A)->siguienteCurso = M->siguienteCurso;
			curso->alumnos = NULL;
			delete M;
		}
		else {
			Nodo * C;
			for (C = curso->alumnos; static_cast<Matricula*>(C)->siguienteAlumno != M; C = static_cast<Matricula*>(C)->siguienteAlumno);
			static_cast<Matricula*>(C)->siguienteAlumno = M->siguienteAlumno;
			Nodo * A;
			for (A = alumno->cursos; static_cast<Matricula*>(A)->siguienteCurso != M; A = static_cast<Matricula*>(A)->siguienteCurso);
			static_cast<Matricula*>(A)->siguienteCurso = M->siguienteCurso;
			delete M;

		}
	}
}

void modificaNota(Alumno *alumno, Curso *curso, int nota) {
	if (alumno != NULL && curso != NULL) {
		Nodo * aux;
		bool encontrado = false;
		for (aux = alumno->cursos; aux->tipo != 'A'; aux = static_cast<Matricula*>(aux)->siguienteCurso) {
			Nodo * auxCur;
			for (auxCur = static_cast<Matricula*>(aux)->siguienteAlumno; auxCur->tipo != 'C'; auxCur = static_cast<Matricula*>(auxCur)->siguienteAlumno);
			if (static_cast<Curso*>(auxCur) == curso) {
				encontrado = true;
				break;
			}
		}
		if (encontrado) {
			static_cast<Matricula*>(aux)->nota = nota;
		}
		else {
			std::cout << "El alumno no esta matriculado en esta asignatura \n";
		}
	}
}

double promedioNotasAlumno(Alumno *alumno) {
	float resultado = 0;
	int divisor = 0;

	if (alumno != NULL) {
		if (alumno->cursos != NULL) {
			Nodo * aux;
			for (aux = alumno->cursos; aux->tipo != 'A'; aux = static_cast<Matricula*>(aux)->siguienteCurso) {
				resultado += static_cast<Matricula*>(aux)->nota;
				divisor++;
			}

		}
	}
	return (resultado/ float(divisor));
}

double promedioNotasCurso(Curso *curso) {
	float resultado = 0;
	int divisor = 0;

	if (curso != NULL) {
		if (curso->alumnos != NULL) {
			Nodo * aux;
			for (aux = curso->alumnos; aux->tipo != 'C'; aux = static_cast<Matricula*>(aux)->siguienteAlumno) {

				resultado += static_cast<Matricula*>(aux)->nota;
				divisor++;
			}

		}
	}
	return (resultado / float(divisor));
}

void imprimeAlumnos(Curso *curso) {
	if (curso != NULL) {
		std::cout << "Alumnos Matriculados en ";
		curso->imprime();
		std::cout << std::endl << std::endl;
		if (curso->alumnos != NULL) {
			for (Nodo * aux = curso->alumnos; aux->tipo != 'C'; aux = static_cast<Matricula*>(aux)->siguienteAlumno) {
				Nodo * auxAlu;
				for (auxAlu = static_cast<Matricula*>(aux)->siguienteCurso; auxAlu->tipo != 'A'; auxAlu = static_cast<Matricula*>(auxAlu)->siguienteCurso);
				static_cast<Alumno*>(auxAlu)->imprime();
				std::cout << "\t" << static_cast<Matricula*>(aux)->nota << std::endl;
			}
			std::cout << std::endl << "Promedio: \t" << promedioNotasCurso(curso) << std::endl << std::endl;
		}
	}
}

void imprimeCursos(Alumno *alumno) {
	if (alumno != NULL) {
		std::cout << "Cursos en los que esta matriculado el alumno ";
		alumno->imprime();
		std::cout << std::endl << std::endl;
		if (alumno->cursos != NULL) {
			for (Nodo * aux = alumno->cursos; aux->tipo != 'A'; aux = static_cast<Matricula*>(aux)->siguienteCurso) {
				Nodo * auxCur;
				for (auxCur = static_cast<Matricula*>(aux)->siguienteAlumno; auxCur->tipo != 'C'; auxCur = static_cast<Matricula*>(auxCur)->siguienteAlumno);
				static_cast<Curso*>(auxCur)->imprime();
				std::cout << "\t" << static_cast<Matricula*>(aux)->nota << std::endl;
			}
			std::cout << std::endl << "Promedio: \t" << promedioNotasAlumno(alumno) << std::endl << std::endl;
		}
	}
}

int main() {

	Alumno *a1 = new Alumno("A001", "Juan", NULL);
	Alumno *a2 = new Alumno("A002", "Alberto", NULL);
	Alumno *a3 = new Alumno("A003", "Luis", NULL);
	Alumno *a4 = new Alumno("A004", "Maria", NULL);
	Alumno *a5 = new Alumno("A005", "Ana", NULL);
	Alumno *a6 = new Alumno("A006", "Marta", NULL);

	Curso *c1 = new Curso("I001", "Estructuras", NULL);
	Curso *c2 = new Curso("I002", "Matematicas", NULL);
	Curso *c3 = new Curso("I003", "Programacion", NULL);
	Curso *c4 = new Curso("I004", "Negocios web", NULL);

	altaMatricula(a1, c1);
	altaMatricula(a1, c2);
	altaMatricula(a2, c1);
	altaMatricula(a2, c3);
	altaMatricula(a1, c3);
	altaMatricula(a3, c2);
	altaMatricula(a1, c4);
	altaMatricula(a4, c2);
	altaMatricula(a5, c3);
	altaMatricula(a6, c3);
	altaMatricula(a4, c4);
	altaMatricula(a3, c4);

	imprimeAlumnos(c1);
	imprimeAlumnos(c2);
	imprimeAlumnos(c3);
	imprimeAlumnos(c4);

	imprimeCursos(a1);
	imprimeCursos(a2);
	imprimeCursos(a3);
	imprimeCursos(a4);
	imprimeCursos(a5);
	imprimeCursos(a6);

	modificaNota(a1, c1, 10);
	modificaNota(a1, c2, 8);
	modificaNota(a2, c1, 7);
	modificaNota(a2, c3, 6);
	modificaNota(a1, c3, 10);
	modificaNota(a3, c2, 8);
	modificaNota(a1, c4, 8);
	modificaNota(a4, c2, 10);
	modificaNota(a5, c3, 7);
	modificaNota(a6, c3, 9);
	modificaNota(a4, c4, 5);
	modificaNota(a3, c4, 6);

	imprimeAlumnos(c1);
	imprimeAlumnos(c2);
	imprimeAlumnos(c3);
	imprimeAlumnos(c4);

	imprimeCursos(a1);
	imprimeCursos(a2);
	imprimeCursos(a3);
	imprimeCursos(a4);
	imprimeCursos(a5);
	imprimeCursos(a6);

	return 0;
}