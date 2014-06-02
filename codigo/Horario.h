//
//  Schedule.h
//  AEDA
//
//  MIEIC 2013/2014
//  Joao Almeida, Joao Ramos and Miguel Fernandes
//
//  This contains the class Schedule used in the project.
//
#ifndef HORARIO_H_
#define HORARIO_H_

#include <string>
#include <vector>
#include <iostream>

class Professor;
class Disciplina;

using namespace std;


class Horario {

	int ID;
	string dia;
	int h;
	Disciplina *d1;
	Professor *p1;

	static int IDHorario;


public:

	/**
	 *  Construtor of class Horario
 	 *  @param day Lesson's day
 	 *  @param h Lesson's hour
 	 *   */
	Horario(string dia , int h);

	/**
	 *  Changes Lesson Day
	 *  @param dia Lesson's Day
	 * @return true or false depending on the possibility to edit the Lesson's Day
 	 *   */
	bool setDia(string dia);

	/**
	 *  Changes Lesson Hour
	 *  @param h Lesson's Hour
	 * @return true or false depending on the possibility to edit the Lesson's Hour
 	 *   */
	bool setHora(int h);

	/**
	 *  Associate the Schedule to a Course
	 *  @param d1 Course's Object
 	 *   */
	void setDisciplina(Disciplina *d1);

	/**
	 *  Associate the Schedule to a Teacher
	 *  @param d1 Teacher's Object
 	 *   */
	void setProfessor(Professor *p1);

	/**
	 *  Returns Lesson's Starting Hour
	 *  @return Lesson Starting Hour
 	 *   */
	const int getHora();

	/**
	 *  Returns Lesson's Day
	 *  @return Lesson's Day
 	 *   */
	const string getDia();

	/**
	 *  Returns Lesson's ID
	 *  @return Lesson's ID
 	 *   */
	const int getID();

	/**
	 *  Returns the Course in that Lesson Time
	 *  @return Course in that Lesson
 	 *   */
	Disciplina *getDisciplinaAula();

	/**
	 *  Returns the Teacher Giving the Lesson
	 *  @return Teacher Giving the Lesson
 	 *   */
	Professor *getProfessorAula();

	/**
	 *  Prints the Schedule Information
	 *  @return string with schedule information
 	 *   */
	string ImprimeDados();




};

#endif
