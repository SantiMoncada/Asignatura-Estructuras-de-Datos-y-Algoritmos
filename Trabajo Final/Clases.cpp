#include "stdafx.h"
#include "iostream"
#include "Clases.h"

Alumno::Alumno(const char* matricula, const char* nombre, Nodo* cursos) {
	this->tipo = 'A';
	this->matricula = matricula;
	this->nombre = nombre;
	this->cursos = cursos;
}
void Alumno::imprime() {
	std::cout << this->matricula << " " << this->nombre;
}

Curso::Curso(const char* codigo, const char* nombre,
	Nodo* alumnos) {
	this->tipo = 'C';
	this->codigo = codigo;
	this->nombre = nombre;
	this->alumnos = alumnos;
}
void Curso::imprime() {
	std::cout << this->codigo << " " << this->nombre;
}

Matricula::Matricula() {
	this->tipo = 'M';
	this->nota = 0;
	this->siguienteCurso = NULL;
	this->siguienteAlumno = NULL;
}
