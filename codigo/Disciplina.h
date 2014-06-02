//
//  Disciplina.h
//  AEDA
//
//  MIEIC 2013/2014
//  Joao Almeida, Joao Ramos and Miguel Fernandes
//
//  This contains the class Disciplina used in the project.
//
#ifndef DISCIPLINA_H_
#define DISCIPLINA_H_


#include <string>
#include <vector>
#include <iostream>
#include "Pessoa.h"
#include "Horario.h"
#include "stdlib.h"
#include "Professor.h"

using namespace std;

class Disciplina {
	int ID;
	string nome;
	vector<Professor *> profdisc;
	static int IDDisciplina;

public:

	/**
	 *  Construtor of class Disciplina
 	 *  @param nome Course's Name
 	 *   */
	Disciplina(string nome);

	/**
	 *  Changes Course's Name
	 * @param nome Course's Name
	 * @return true or false depending on the possibility to edit the Course's Name
 	 *   */
	bool setNome(string nome);

	/**
		 *  Returns the Course's Name
		 * @return string with the Course's Name
	 	 *   */
	string getNome() const;

	/**
		 *  Returns the Course's ID
		 * @return integer with the Course's ID
	 	 *   */
	const int getID();

	/**
		 *  Associates a Professor to a Course
		 * @param p1 Professor's Object
		 * @return true or false depending on the possibility to add the Professor
	 	 *   */
	bool addProfessor(Professor *p1);

	/**
		 *  Delete a Professor from a Course
		 * @param p1 Professor's Object
		 * @return true or false depending on the possibility to delete the Professor
	 	 *   */
	bool delProfessor(Professor *p1);

	/**
		 *  Returns the Teacher's Name of the Course
		 * @return string with Teacher's Name of the Course
	 	 *   */
	string getNomeProfs() const;

	/**
		 *  Returns the Course's Professors
		 * @return vector with the Course's Professors
	 	 *   */
	vector<Professor *> getProfessoresDisc();

	/**
	 	 * Prints Courses's Information
	 	 * @return string with Course's Information
	 	 */
	string imprimeDados();

	/**
	 * Returns Number of Courses created
	 * @return integer with number of Courses created
	 */
	static int getIDmax();

	/**
	 * Checks if a certain Teacher is associated with this course
	 * @param p1 Professor Object
	 * @return true if p1 is lecturing the course, false otherwise
	 */
	bool isProf(Professor *p1) const;

};


#endif /*DISCIPLINA_H_*/
