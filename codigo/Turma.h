#ifndef TURMA_H_
#define TURMA_H_


#include <string>
#include <vector>
#include <iostream>

class Horario;
class Disciplina;
class Professor;
class Aluno;
class Escola;
class Diretor;

using namespace std;

class Turma {
	int ID;
	int ano;
	//vector<Professor *> professores;
	vector<Aluno *> alunosturma;
	vector<Horario *> horarioturma;
	Professor *diretor;
	static int IDTurmas;


public:
	/**
		 *  Construtor of class ProfessorTurma
	 	 *  @param nome Class's Year
	 	 *   */
	Turma(int ano, Professor *diretor );

	/**
		 *  Associates a Student with the Class
		 * @param a1 Student's Object
		 * @return true or false depending on the possibility to Associate the Student
	 	 *   */
	bool addAluno(Aluno *a1);

	/**
		 *  Removes a Student from the Class
		 * @param a1 Student's Object
		 * @return true or false depending on the possibility to Delete the Student
	 	 *   */
	bool delAluno(Aluno *a1);

	/**
		 *  Returns Class's ID
		 * @return integer with Class's ID
	 	 *   */
	const int getID();

	/**
	 	 *  Set the Class's Diretor
	 	 * @param d1 Professor/Diretor Object
	 	 *   */
	void setDiretor(Professor *d1);

	/**
		 *  Returns Class's Year
		 * @return integer with Class's ID
		 *   */
	const int getAno();

	/**
		*  Returns Class Diretor
		* @return Class Diretor
		*   */
	Professor* getDiretorTurma();

	/**
		*  Returns Class Schedule
		* @return vector with Class Schedule
		*   */
	vector<Horario* > getHorarioTurma();


	/**
		*  Returns Class Schedule
		* @return vector with Class Schedule
		*   */
	vector<Horario* > getHorarioAtendTurma();

	/**
		*  Returns Class Students
		* @return vector with Class Students
		*   */
	 vector<Aluno *> getAlunosTurma();

	/**
		*  Adds a Lesson to a Class
		* @return true or false depending on the possibility to add the Lesson
		*   */
	bool addAula(Horario *h1);

	/**
		*  Deletes a Lesson from Class
		* @return true or false depending on the possibility to delete the Lesson
		*   */
	bool delAula(Horario *h1);

	/**
		*  Returns Class's max ID
		* @return integer with Class's max ID
	 	*   */
	static int getIDMax();

	 /**
	  	*  Prints class's information
	    *  @return string with class's information
	    *   */
	string imprimeDados();

	 /**
	  	*  Changes class's year
	    *  @param year class year
	    *   */
	void setAno(int ano);

	 /**
	  	*  Search schedule through ID
	    *  param ID schedule's id
	    *  @return true or false depending on schedule's existance
	    *   */
	bool searchHorario(int ID);

	 /**
	  	*  Adds a director schedule
	    *  param h1 Schdule object
	    *  @return true or false depending on the possibility to add
	    *   */
	bool addDirectorSchedule(Horario *h1);


};

#endif
