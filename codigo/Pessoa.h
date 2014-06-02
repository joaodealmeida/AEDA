//
//  Pessoa.h
//  AEDA
//
//  MIEIC 2013/2014
//  Joao Almeida, Joao Ramos and Miguel Fernandes
//
//  This contains the class Pessoa used in the project.
//
#ifndef PESSOA_H_
#define PESSOA_H_

#include <string>
#include <vector>
#include <iostream>
#include <sstream>

#include "Additions.h"

using namespace std;

class Pessoa{

protected:

	int ID;
	string nome;
	string apelido;
	int contacto;
	string email;
public:


	/**
	 *  Construtor of class Pessoa
 	 *  @param nome Persons's Name
 	 *  @param apelido Person's Surname
 	 *  @param contacto Person's Contact
 	 *  @param email Person's email
 	 *   */
	Pessoa(string nome, string apelido, int contacto , string email);

	/**
		 *  Changes Person's First Name
		 *  @param nome Person's First Name
	 	 *   */
	void setNome(string nome);

	/**
		 *  Changes Person's Surname
		 *  @param apelido Person's Surname
	 	 *   */
	void setApelido(string apelido);

	/**
		 *  Changes Person's Contact
		 *  @param contacto Person's Name
	 	 *   */
	void setContacto(int contacto);

	/**
		 *  Changes Person's email
		 *  @param email Person's email
	 	 *   */
	void setEmail(string email);

	/**
		 *  Returns Person's First Name
		 *  @return string with Person's FirstName
	 	 *   */
	const string getNome();

	/**
		 *  Returns Person's Surname
		 *  @return string with Person's Surname
	 	 *   */
	const string getApelido();

	/**
		 *  Returns Person's Contact
		 *  @return integer with Person's Contact
	 	 *   */
	const int getContacto();

	/**
		 *  Returns Person's Email
		 *  @return string with Person's Email
	 	 *   */
	const string getEmail();

	/**
		 *  Prints Person's Information
		 *  @return string with Person's Information
	 	 *   */
	virtual string imprimeDados();

	/**
		 *  Returns Person's ID
		  * @return integer with Person's ID
	 	 *   */
	virtual const int getID() = 0;

};

#endif
