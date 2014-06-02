#ifndef PROFESSOR_H_
#define PROFESSOR_H_

#include <string>
#include <vector>
#include <iostream>
#include "Pessoa.h"
#include "Horario.h"

using namespace std;

class Professor: public Pessoa {

protected:

	//vector<Horario *> horarioAtend;
	static int IDProf;
	bool ativo;
	string disciplina;


public:

	/**
	 *   Construtor of class Professor
 	 *  @param nome Teacher's Name
 	 *  @param apelido Teacher's Surname
 	 *  @param contacto Teacher's Contact
 	 *  @param email Teacher's Email
 	 *   */
	Professor( string nome , string apelido, int contacto , string email);

	//string getDisciplina() const;

	/**
	 *  Returns Teacher's ID
	 * @return integer with Teacher's ID
	 *   */
	const int getID();

	/**
	 *  Returns Highest Teacher's ID
	 * @return integer Highest Teacher's ID
	 *   */

	static const int getID_max();

	/**
	 *  Prints Teacher's Information
	 *  @return string with Teacher's Information
	 *   */
	string imprimeDados();


	/**
	 *  Set a teacher as active
	 *   */
	void setAtivo();


	/**
	 *  Gets teacher info(active or not)
	 *  @return true or false depending if he his teaching or no
	 *   */
	bool getAtivo() const;


	/**
	 *  Associates a course to a teacher
	 *  @param nome name of the course
	 *   */
	void setDisciplina(string nome);


	/**
	 *  Returns Teacher's Course
	 *  @return string with Teacher's Course
	 *   */
	string getDisciplina() const;


	/**
	 *  Compares 2 teachers
	 *  @return true if the teachers are the same or false if they aren't
	 *   */
	bool operator==(const Professor *p1);


};

#endif
