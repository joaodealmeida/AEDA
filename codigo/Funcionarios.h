/*
 * Funcionarios.h
 *
 *  Created on: 09/12/2013
 *      Author: João
 */

#ifndef FUNCIONARIOS_H_
#define FUNCIONARIOS_H_

#include <string>
#include <vector>
#include <iostream>
#include <sstream>

class Turma;

using namespace std;


class Funcionarios {
	int ID;
	string nome;
	int contato;
	vector <Turma*> turmas;
	static int IDFunc;
public:

	/**
	 *  Construtor of class Funcionarios
 	 *  @param denominacao Assistant's name
 	 *   */
	Funcionarios(string nome);

	/**
	 *  Construtor of class Funcionarios
 	 *  @param denominacao Assistant's name
 	 *  @param contato Assistant's contact
 	 *   */
	Funcionarios(string nome, int contato);

	string getNome() const;

	/**
	 *  Returns Assistant's ccontact
	 *  @return integer with assistant's contact
	 *    */
	int getContato() const;

	/**
	 *  Returns Assistant's ID
	 *  @return integer with assistant's ID
	 *    */
	int getID() const;

	/**
	 *  Returns Assistant's max ID
	 *  @return integer with assistant's max ID
	 *    */
	static int getID_max();

	/**
	 *  Returns Assistant's classes
	 *  @return vector of class
	 *    */
	vector <Turma*> getTurmasFunc() const;

	 /*  Prints assistant's information
	 *  @return string with assistant's information
	 *   */
	string imprimeDados() ;

	/**
	 *  Changes Assistant's name
	 *  @param nome Assistant's name
	 * 	 */
	void setNome(string nome);

	/**
	 *  Changes Assistant's contact
	 *  @param nome Assistant's contact
	 * 	 */
	void setContato(int contacto);

	/**
		 *  Associates an assistant to the class
		 * @param t1 Class's Object
		 * @return true or false depending on the possibility to associate the assistant
	 	 *   */
	bool addTurmaFunc(Turma *t1);

	/**
		 *  Removes an assistant from the class
		 * @param IDTurma Class's ID
		 * @return true or false depending on the possibility to remove
	 	 *   */
	bool delTurmaFunc(int IDTurma);

	/**
	 *  Compares 2 assistants
	 *  @param f1 assistant's Object
	 *  @return true or false depending on their names(alphabetic order)
	 * 	 */
	bool operator < (Funcionarios &f1);

	/**
	 *  Compares 2 assistants
	 *  @param f1 Assistant's Object
	 *  @return true if they are the same assistant, or false if they aren't
	 * 	 */
	bool operator ==(Funcionarios &f1);

};

#endif /* FUNCIONARIOS_H_ */
