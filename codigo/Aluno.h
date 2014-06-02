//
//  Aluno.h
//  AEDA
//
//  MIEIC 2013/2014
//  Joao Almeida, Joao Ramos and Miguel Fernandes
//
//  This contains the class Aluno used in the project.
//
#ifndef ALUNO_H_
#define ALUNO_H_

#include <string>
#include <vector>
#include <iostream>
#include "Pessoa.h"

using namespace std;


class Aluno: public Pessoa {

	static int IDAluno;


public:

		/**
	     *  Construtor of class Aluno
	     *  @param nome Student's First Name
	     *  @param apelido Student's Surname
	     *  @param contacto Student's Contact
	     *  @param email Student's Email
	     *   */

	Aluno (string nome, string apelido, int contacto, string email);

		/**
	     *  Gets the Student ID
	     *  @return ID of the Student
	     *   */
	const int getID();
		/**
		 *  Gets the value of static IDAluno
		 *  @return Highest ID possible of Students
		 *  */

	static const int getID_max();

		/**
		 *  Organizes the Student Information
		 *  @return string with Student Information
		 *   */
	string imprimeDados();

};

#endif /* ALUNO_H_ */
