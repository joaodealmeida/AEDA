/*
 * Livraria.h
 *
 *  Created on: 19/12/2013
 *      Author: João
 */

#ifndef LIVRARIA_H_
#define LIVRARIA_H_

#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Disciplina;

class Livraria {
	string denominacao;
	int localizacao;
	vector <string> especialidade;
	vector <int> escolaridade;
	static int IDL;
	int ID;


public:

	/**
	 *  Construtor of class Livraria
 	 *  @param denominacao Bookstore's Name
 	 *  @param localizacao Distance from School
 	 *   */
	Livraria(string denominacao, int localizacao);

	/**
	 *  Changes Bookstore's Courses
	 *  @param v Courses Name
	 * 	 */
	void setEspecialidade(vector<string> &v);

	/**
	 *  Changes Bookstore's Year
	 *  @param v Change Bookstore's year
	 * 	 */
	void setEscolaridade(vector<int> &v);

	/**
	 *  Compares 2 bookstores
	 *  @param l1 Bookstore's Object
	 *  @return true or false depending on which bookstore is closer to the school
	 * 	 */
	bool operator<(const Livraria &l1);

	/**
	 *  Compares 2 bookstores
	 *  @param l1 Bookstore's Object
	 *  @return true if they are the same bookstores, or false if they aren't
	 * 	 */
	bool operator==(const Livraria &l1);

	/**
		 *  Returns Bookstore's ID
		 *  @return integer with bookstore's ID
		 *   */
	int getID() const;

	/**
	 *  Returns Bookstore's name
	 *  @return string with bookstore's name
	 *   */
	string getDenominacao() const;

	/**
	*  Returns bookstore's distance from school
	*  @return integer with distance in km
	*   */
	int getLocalizacao() const;

	/**
	 *  Returns bookstore's courses
	 *  @return string vector with the names of bookstore's courses
	 *   */
	vector <string> getEspecialidade();

	/**
	 *  Returns bookstore's year
	 *  @return integer vector with the school years that bookstore support
	 *   */
	vector <int> getEscolaridade();

	 /**
	  *  Prints bookstore's information
	  *  @return string with bookstore's information
	  *   */
	string imprimeDados();

	/**
		  *  Returns the next ID of a new bookstore
		  *  @return integer with bookstore's next ID
		  *   */
	static int getID_max();

	/**
	 *  checks if the bookstore sells books for one year
	 *  @param ano integer year to check
	 *  @return true if the year exists, false otherwise
	 *   */
	bool existeAno(int ano);

	/**
		 *  checks if the bookstore sells books for one course
		 *  @param nome string course's name to check
		 *  @return true if the course exists, false otherwise
		 *   */
	bool existeDisciplina(string nome);
};

#endif /* LIVRARIA_H_ */
