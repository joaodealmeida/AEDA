//
//  Escola.h
//  AEDA
//
//  MIEIC 2013/2014
//  Joao Almeida, Joao Ramos and Miguel Fernandes
//
//  This contains the class Escola used in the project.
//
#ifndef ESCOLA_H_
#define ESCOLA_H_

#include <string>
#include <vector>
#include <iostream>
#include <tr1/unordered_set>
#include <queue>

#include "Turma.h"
#include "BST.h"
#include "Professor.h"
#include "Livraria.h"

class Disciplina;
class Horario;
class Aluno;
class Funcionarios;
class Livraria;

using namespace std;

struct hProfessor{
	int operator()(const Professor *p1) const{
		Professor p3=*p1;
		int v = 0;
		for ( unsigned int i=0; i< p3.getNome().length(); i++ )
			v = 37*v + p3.getNome()[i];
		return v;
	}
	bool operator()(const Professor *p1, const Professor *p2) const{
		Professor p3=*p1;
		Professor p4=*p2;
		return p3.getNome()==p4.getNome() && p3.getApelido() == p4.getApelido();
	}

};

typedef tr1::unordered_set<Professor*,hProfessor,hProfessor> HProfessor;

class Escola {

private:

	vector<Turma *> turmas;
	vector<Disciplina *> disciplinas;
	vector<Horario*> horarios;
	vector<Aluno*> estudantesescola;
	vector<Professor*> professoresescola;
	HProfessor exprofessores;
	BST <Funcionarios *> funcionarios;
	priority_queue <Livraria *> livrarias;

	Escola(); // There can only be one user manager, so a singleton here is completely appropriate.

	Escola(Escola const&); // Copy constructor is private.
	Escola& operator=(Escola const&); // Assignment operator is private.

	static Escola *um_pInstance;


public:

	/**
		 *  Returns Singleton for Escola
		 * @return Singleton for Escola
	 	 *   */
	static Escola* Instance();

	/**
		 *  Associates a Professor with the School
		 * @param p1 Professor's Object
	 	 *   */
	void addProfessor(Professor *p1);

	/**
		 *  Checks if there is already a Tecaher with the same name
		 * @param nome First Name of Teacher
		 * @param apelido Surname of Teacher
		 * @return true or false depending on the existence of a teacher
		 *   */
	bool checkProfessor(string nome, string apelido);

	/**
		 *  Del a Professor from the School
		 * @param p1 Professor's Object
		 * @return true or false depending on the possibility to Delete the Professor
	 	 *   */
	bool delProfessor(Professor *p1);

	/**
		 *  Associates a Class with the School
		 * @param t1 Class's Object
		 * @return true or false depending on the possibility to Associate the Class
	 	 *   */
	bool addTurma(Turma *t1);

	/**
		 *  Deletes a Class from the School
		 * @param t1 Class's Object
		 * @return true or false depending on the possibility to Delete the Class
	 	 *   */
	bool delTurma(Turma *t1);

	/**
		 *  Associates a Course with the School
		 * @param d1 Course's Object
		 * @return true or false depending on the possibility to Associate the Courses
	 	 *   */
	bool addDisciplina(Disciplina *d1);

	/**
		 *  Deletes a Class from the School
		 * @param d1 Class's Object
		 * @return true or false depending on the possibility to Delete the Class
	 	 *   */
	bool delDisciplina(Disciplina *d1);

	/**
		 *  Associates a Student with the School
		 * @param a1 Student's Object
		 * @return true or false depending on the possibility to Associate the Student
	 	 *   */
	bool addAluno(Aluno *a1);

	/**
		 *  Deletes a Student from the School
		 * @param a1 Student's Object
	 	 *   */
	void delAluno(Aluno *a1);

	/**
		 *  Deletes a Student from a Class
		 * @param a1 Student's Object
	 	 *   */
	void delAlunoTurma(Aluno *a1);

	/**
		 *  Return the number of Class in the School
		 * @return integer with the number of Class in the School
	 	 *   */
	int getNTurmas() const;

	/**
		 *  Return the number of Students in the School
		 * @return integer with the number of Students in the School
	 	 *   */
	int getNEstudantes() const;

	/**
		 *  Return the number of Teachers in the School
		 * @return integer with the number of Teachers in the School
	 	 *   */
	int getNProfessores() const;

	/**
		 *  Return the number of Courses in the School
		 * @return integer with the number of Courses in the School
	 	 *   */
	int getNDisciplinas()const;


	/**
		 *  Returns School's Courses
		 * @return string with the name of School's Courses
	 	 *   */
	string getDisciplinas() const;

	/**
		 *  Search Course through ID
		 * @param ID Course's ID
		 * @return Course
	 	 *   */
	Disciplina* searchDisciplina(int ID);

	/**
		 *  Search Class through ID
		 * @param ID Class's ID
		 * @return Class
	 	 *   */
	Turma* searchTurma(int ID);

	/**
		 *  Search Class through Year
		 * @param ano Class's Year
		 * @return vector with Class from that Year
	 	 *   */
	vector<Turma*> searchTurmas(int ano);

	/**
		 *  Search Class through Teacher
		 * @param id Teacher's ID
		 * @return vector with Class from that Teacher
		 *   */
	vector<Turma*> searchTurmasProf(int ID);

	/**
		 *  Counts How many Students school has with that First Name and Prints each student Information
		 * @param nome Student's First Name
		 * @return integer with number of Students with that First Name
	 	 *   */
	int searchAlunos(string nome);

	/**
	 	 *  Counts How many Students school has with that Surname and Prints each student Information
		 * @param apelido Student's Surname
		 * @return integer with number of Students with that Surname
		 *   */
	int searchAlunos2(string apelido);

	/**
		 *  Search Student through ID
		 * @param ID Student's ID
		 * @return Student
	 	 *   */
	Aluno* searchAluno(unsigned int ID);

	/**
		 *  Returns the Class where the Student is
		 * @param a1 Student's Object
		 * @return Class
	 	 *   */
	Turma* getTurmaAluno (Aluno *a1);

	/**
		 *  Counts How many Teachers school has with that First Name and Prints each Teacher Information
		 * @param nome Teacher's First Name
		 * @return integer with number of Teachers with that First Name
	 	 *   */
	int searchProfs(string nome);

	/**	*  Counts How many Teachers school has with that Surname and Prints each Teacher Information
		* @param apelido Teacher's Surname
		* @return integer with number of Teachers with that Surname
		*	 */
	int searchProfs2(string apelido);

	/**
		*  Search Teacher through ID
		* @param ID Teachers's ID
		* @return Teacher
		*   */
	Professor* searchProf(unsigned int ID);

	/**
		*  Search Course through Teacher
		* @param p1 Teacher's Object
		* @return Course
		*   */
	Disciplina* getDisciplinaProf(Professor* p1);

	/**
		*  Returns All Teachers in the School
		* @return vector with all Teachers in the School
		*   */
	vector <Professor*> getAllProf();

	/**
	  	*  Returns All Students in the School
	  	* @return vector with all Students in the School
		* */
	vector <Aluno*> getAllStudents();

	/**
		*  Returns All Courses in the School
		* @return vector with all Courses in the School
		*   */
	vector <Disciplina*> getAllCourses();

	/**
	 	*  Finds a course through it's name
	 	* @param nome Course's name
	 	* @return true if a course was found and false otherwise
	 	*/

	bool searchDisciplinaNome(string nome);

	/**
		*  Returns All Schedules in the School
		* @return vector with all Schedule in the School
		*   */
	vector <Horario*> getAllSchedules();
	/**
		*  Returns All Classes in the School
		* @return vector with all Classes in the School
		*   */
	vector <Turma *> getAllClasses();

	/**
		*  Returns a teacher's schedule
		* @param object Professor
		* @return vector with a teacher's schedule
		*   */
	vector <Horario *> getHorarioProf(Professor* p1);

	/**
		*  Returns a director's additional schedule
		* @param object Professor
		* @return vector with a director's additional schedule
		*   */
	vector <Horario *> getHorarioAtend(Professor* p1);

	/**
		*  Adds a lesson to a class
		* @param object Horario
		* @param object Turma
		* @return true if the lesson was created, false otherwise
		*   */

	bool addLesson(Horario *h1, Turma *t1);

	/**
		*  Adds a director schedule to a class
		* @param object Horario
		* @param object Turma
		* @return true if the lesson was created, false otherwise
		*   */
	bool addDirectorSchedule (Horario *h1, Turma *t1);

	/**
		*  Returns the schedule
		* @param ID Schedule's ID
		* @return schedule object
		*   */
	Horario * getHorario(int ID);

	/**
		*  Adds a class lesson
		* @param h1 schedule object
		* @return true if the lesson was added, false otherwise
		*   */
	bool addAula(Horario *h1);

	/**
		*  Moves the director schedule from 1 teacher to another
		* @param oldD teacher1 object
		* @param newD teacher2 object
		* @return vectors with schedule's ID that need to be changed
		*   */
	vector<int> TransferDiretorSchedule(Professor *oldD, Professor *newD,Turma *t1);

	/**
		*  Deletes a class lesson
		* @param h1 schedule's object
		*   */
	void delHorario(Horario *h1);

	/**
		*  Associates a Employee with the School
		* @param f1 Employee's Object
		* @return true or false depending on the possibility to Associate employee
	 	*   */
	bool addFuncionario(Funcionarios *f1);

	/**
		 *  Deletes an Employee from the School
		 * @param f1 Employee's Object
		 * @return true or false depending on the possibility to delete the Employee
	 	 *   */
	bool delFuncionario(Funcionarios *f1);

	/**
		 *  Gets all Employes from the School
		 * @return a BST with all Employees from the School
	 	 *   */
	BST <Funcionarios *> getAllFuncionarios() const;

	/**
		 *  Search an assistant through his ID
		 * @param ID Assistant's ID
		 * @return an assistant object
	 	 *   */
	Funcionarios *searchFunc(int ID);

	/**
		 *  Returns classes that an assistant is taking care
		 * @param IDFunc Assistant's ID
		 * @return vector with classes
	 	 *   */
	vector<Turma*> searchTurmasFunc(int IDFunc);

	/**
		 *  Search an assistant through a class
		 * @param IDTurma Class's ID
		 * @return vector of assistants
	 	 *   */
	vector<Funcionarios *> searchFuncTurma(int IDTurma);

	/**
		 *  Search an assistant through his name
		 * @param nome Assistant's name
		 * @return an assistant object
	 	 *   */
	Funcionarios * searchFunc(string nome);

	/**
		 *  Returns the number of assistants working at the school
		 * @return an integer with number of assistants
	 	 *   */
	int getNFuncionarios() const;

	/**
		 *  Returns ex-Teachers
		 * @return hashtable with all ex-teachers
	 	 *   */
	HProfessor getExProfessores() const;

	/**
		*  Associates a bookstore with the school
		* @param l11 Employee's Object
		* @return true or false depending on the possibility to Associate the bookstore
	 	*   */
	bool addLivraria(Livraria *l1);

	/**
		*  Deletes an ex-teacher from hashtable
		* @param IDProf Teacher's ID
	 	*   */
	void delExProfessor(int IDProf);

	/**
		*  Removes a bookstore
		* @param l1 Bookstore object
	 	*   */
	void delLivraria(Livraria *l1);

	/**
		*  Search the closed bookstore by courses
		* @param disciplinas Courses to be searched
		* return vector with bookstores
	 	*   */
	vector <Livraria*> searchLivraria(vector<Disciplina *> disciplinas);

	/**
		*  Find a bookstore by ID
		* @param ID bookstore's ID
		* return bookstore object
		*   */
	Livraria* searchLivrariaID(int ID);


	/**
		*  Find a bookstore by name
		* @param denominacao name
		* return bookstore object
	 	*   */

	Livraria* searchLivrariaDenom(string denominacao);

	/**
		*  Return all bookstores available
		* return priority_queue with all bookstores
	 	*   */
	priority_queue<Livraria *> getLivrarias();

	/**
		*  Gets and ex-Teacher to teach again
		* @param p1 Professor object
		* return true or false depending on the possibility to put the teacher teaching again
	 	*   */

	bool recolocarProf(Professor *p1);

	/**
		*  Returns all bookstores with that course
		* @param nomeDisc Course's Name
		* return priority queue with the bookstores
	 	*   */
	priority_queue<Livraria *> getLivrariasDisc(string nomeDisc);

	/**
		*  Returns all bookstores with that year
		* @param ano bookstore's year
		* return priority queue with the bookstores
	 	*   */
	priority_queue<Livraria*> searchLivrariasAno(int ano);


};

#endif
