#include <iostream>
#include <conio.h>
#include <string>
#include <stdlib.h>
#include "Aluno.h"
#include "Escola.h"
#include "Additions.h"
#include "Professor.h"
#include "Disciplina.h"
#include "Turma.h"
#include "Funcionarios.h"
#include "BST.h"


static const int baseASCIIn = 48;

static const int escKey = 27;

void mainMenu();
void createObjects();
void exitMenu();
void studentsManagementMenu();
void teachersManagementMenu();
void classesManagementMenu();
void coursesManagementMenu();
void AssistantsManagementMenu();
void BookstoresManagementMenu();
void lists();
void addStudent();
void addTeacher();
void addClass();
void addCourse();
void addAssistant();
void addBookstore();
void delStudent(int IDAluno);
void delProfessor(int IDProf);
void deleteClass(int IDTurma);
void delAssistant(int IDAssist);
void delBookstore(int IDBS);
void searchStudentInfo();
void searchTeacherInfo();
void searchCoursesInfo();
void searchClassInfo();
void searchAssistantInfo();
void searchBookstoreInfo();
void changeStudentInfo(int IDAluno);
void changeClassInfo(int IDTurma);
void changeTeacherInfo(int IDProf);
void changeCourseInfo(int IDCourse);
void changeAssistantInfo(int IDAssist);
void changeBookstoreInfo(int IDBS);
void anotherChange(int IDAluno);
void anotherChangeProf(int IDProf);
void anotherChangeCourse(int IDCourse);
void anotherChangeClass(int IDTurma);
void anotherChangeAssist(int IDAssist);
void anotherChangeAssistClasses(int IDAssist);
void anotherChangeBookstore(int IDBS);
void courseChange(int IDCourse);
void addTeacherCourse(int IDCourse);
void assignTeacher(int IDCourse);
void moveClassStudent(int IDTurma, int IDAluno);
void configLessons (int IDTurma);
void changeSchedule(int ID, int IDTurma);
void setDirectorSchedule(int IDDir,int IDTurma, int nschedules);
void setClassSchedules(int IDTurma);
void addCourseSchedules(Disciplina *d1);
void assistantClasses(int IDAssist);
void reHire(Professor *p1);
void findBooks(int ID);


void findBooks(int ID){

	string str;
	int nID,opt;
	bool should_finish=false,should_stop=false;
	vector<Disciplina *> Disc;
	vector<Livraria *> liv;


	std::cout << "COURSES:\n";

	std::cout << Escola::Instance()->getDisciplinas();

	std::cout << "\n\nDo you want to find books for all courses? (y/n)";
	opt=_getch();

	switch (opt){
		case 89:
		case 121:
			Additions::clearConsole();
			std::cout << "You selected all the courses!\n\n";
			liv = Escola::Instance()->searchLivraria(Escola::Instance()->getAllCourses());
			std::cout << "The closest bookstores to buy books for the courses you selected are:\n\n";
			for(int i=0; i < liv.size();i++){
				std::cout << liv[i]->imprimeDados() << std::endl;
			}

			std::cout << "\n\nPress Return to go back to changing the student's info...";
			Additions::waitForReturn();
			Additions::clearConsole();
			should_finish=true;
			break;


		case 78:
		case 110:
			Additions::clearConsole();
			break;

		case escKey:
			Additions::clearConsole();
			changeStudentInfo(ID);
			break;

		default:
			std::cout << "Invalid option, try again!\n";
			findBooks(ID);
			break;
	}

	if(should_finish){

		changeStudentInfo(ID);
		return;
	}
	do{
		std::cout << "Write an ID of the course you want to find books... (to stop write 12345) "<< "\n";
		str=Additions::getline();

		if(Additions::gotESC(str)){
			Additions::clearConsole();
			searchBookstoreInfo();
			should_finish=true;
			break;
		}

		if(!atoi(str.c_str()))
			std::cout << "\nError: you didn't write an integer!\n\n";

		else{
			nID=atoi(str.c_str());

			if(nID==12345)
				break;

			if(Escola::Instance()->searchDisciplina(nID)==NULL){
				std::cout << "\nError: a course with the ID " << nID << " doesn't exist!\n\n";
				should_stop=true;
			}
			if(!should_stop){
				for(int i = 0; i < Disc.size(); i++)
					if(Disc[i]->getID()==nID){
						std::cout << "\nError: a course with the ID " << nID << " has already been selected!\n\n";
						should_stop=true;
					}
				if(!should_stop)
					Disc.push_back(Escola::Instance()->searchDisciplina(nID));
			}
		}


	}while(true);

	if(Disc.size()==0){
		Additions::clearConsole();
		std::cout << "You didn't select any course!\n";
		std::cout << "Press Return to go back to changing the student's info...";
		Additions::waitForReturn();
		Additions::clearConsole();
		changeStudentInfo(ID);
	}

	liv = Escola::Instance()->searchLivraria(Disc);
	Additions::clearConsole();
	std::cout << "The courses you selected are:\n\n";

	for(int j=0; j < Disc.size(); j++){
		std::cout << Disc[j]->imprimeDados() << std::endl;
	}
	std::cout << "\n\nThe closest bookstores to buy books for the courses you selected are:\n\n";
	for(int i=0; i < liv.size();i++){
		std::cout << liv[i]->imprimeDados() << std::endl;
	}
	std::cout << "\n\nPress Return to go back to changing the student's info...";
	Additions::waitForReturn();
	Additions::clearConsole();
	changeStudentInfo(ID);


}

void BookstoresManagementMenu(){
	int opc;

	std::cout << "What do you want to do?" << std::endl << std::endl;
	std::cout << "(1) Add a Bookstore" << std::endl;
	std::cout << "(2) Change an existing bookstore's information" << std::endl;

	opc=_getch();

	switch (opc){
	case (baseASCIIn+1):
		Additions::clearConsole();
		addBookstore();
		break;

	case (baseASCIIn+2):
		Additions::clearConsole();
		searchBookstoreInfo();
		break;

	case escKey:
		Additions::clearConsole();
		mainMenu();
		break;

	default:

		Additions::clearConsole();
		BookstoresManagementMenu();
		break;
	}

}

void searchBookstoreInfo(){
	string nome , apelido , contato ;
	vector <string> especialidade;
	unsigned int ID,idDisc, opc, escolaridade;
	int NID=-1;
	string opt,str;
	vector<Aluno*> alunosturma;
	priority_queue<Livraria*> liv;
	Livraria *l2;
	Livraria *l1;


	std::cout << "Search closest bookstore by..." << std::endl;
	std::cout << " (1) Name " << std::endl;
	std::cout << " (2) ID" << std::endl;
	std::cout << " (3) Courses" << std::endl;
	std::cout << " (4) Years" << std::endl;

	std::cout << "\nPlease choose an option... ";

	bool should_finish=false;

	opc=_getch();

	switch (opc){

	case (baseASCIIn+1):
			Additions::clearConsole();
			std::cout << "Name: ";
			nome=Additions::getline();

			if(Additions::gotESC(nome)){
				Additions::clearConsole();
				searchBookstoreInfo();
				should_finish=true;
				break;
			}
			if(Escola::Instance()->searchLivrariaDenom(nome)==NULL){
				Additions::clearConsole();
				std::cout << "\n\nYour search got no results! Try again...\n";
				should_finish=true;
				searchBookstoreInfo();
			}
			else{
				std::cout << std::endl << Escola::Instance()->searchLivrariaDenom(nome)->imprimeDados() << std::endl;

			}

			break;
			case (baseASCIIn+2):
					Additions::clearConsole();

					do {
						std::cout << "ID: (Between 1 and " << Livraria::getID_max()-1 << ") ";

						str=Additions::getline();

						if(Additions::gotESC(str)){
							Additions::clearConsole();
							searchBookstoreInfo();
							should_finish=true;
							break;
						}
					}while(!Additions::checkForOnlyNumeric(str));
					ID=atoi(str.c_str());

					l1=Escola::Instance()->searchLivrariaID(ID);
					if(l1==NULL){
						Additions::clearConsole();
						std::cout << "There is no bookstore with the ID (" << ID << ")\n\n Press Return to continue... \n";
						Additions::waitForReturn();
						Additions::clearConsole();
						searchBookstoreInfo();
						should_finish=true;
						break;
					}
					std::cout << "\n\n";
					changeBookstoreInfo(ID);
					should_finish=true;
					break;
			case (baseASCIIn+3):

					do{
						Additions::clearConsole();
						std::cout << "Courses:\n";
						for(int i=0 ; i < Escola::Instance()->getAllCourses().size(); i++){
							std::cout << std::endl << Escola::Instance()->getAllCourses()[i]->imprimeDados() << std::endl;
						}
						std::cout << "\nChoose the ID of the course... ";
						str=Additions::getline();

						if(Additions::gotESC(str)){
							Additions::clearConsole();
							searchBookstoreInfo();
							should_finish=true;
							break;
						}
						if(atoi(str.c_str()))
							idDisc=atoi(str.c_str());

					}while(!Additions::checkForOnlyNumeric(str) && Escola::Instance()->searchDisciplina(idDisc)==NULL);


					liv=Escola::Instance()->getLivrariasDisc(Escola::Instance()->searchDisciplina(idDisc)->getNome());
					if(liv.size()==0){
						std::cout << "\n\nThe course " << Escola::Instance()->searchDisciplina(idDisc)->getNome() << " has currently no books being sold!\n";
						std::cout << "Press Return to continue...";
						Additions::waitForReturn();
						Additions::clearConsole();
						should_finish=true;
						searchBookstoreInfo();
					}
					else{
						while(!liv.empty()){
							std::cout << liv.top()->imprimeDados() << std::endl;
							liv.pop();
						}
						do {
							std::cout << "\nChoose the ID of the bookstore you want to change: ";

							str=Additions::getline();

							if(Additions::gotESC(str)){
								Additions::clearConsole();
								searchAssistantInfo();
								should_finish=true;
								break;
							}
						}while(!Additions::checkForOnlyNumeric(str));

						ID=atoi(str.c_str());

						l2=Escola::Instance()->searchLivrariaID(ID);
						if(l2==NULL){
							Additions::clearConsole();
							std::cout << "There is no bookstore with the ID (" << ID << ")\n\n Press Return to continue... \n";
							Additions::waitForReturn();
							Additions::clearConsole();
							searchBookstoreInfo();
							should_finish=true;
							break;
						}
						Additions::clearConsole();
						changeBookstoreInfo(ID);
						should_finish=true;
					}


					break;

			case (baseASCIIn+4):
				Additions::clearConsole();
				do {
					std::cout << "Year: (Between 8 and 12) ";

					str=Additions::getline();

					if(Additions::gotESC(str)){
						Additions::clearConsole();
						searchBookstoreInfo();
						should_finish=true;
						break;
					}
					if(atoi(str.c_str()))
						escolaridade=atoi(str.c_str());

				}while(!Additions::checkForOnlyNumeric(str) &&  (escolaridade!=8 || escolaridade!=9 || escolaridade!=10 || escolaridade!=11 || escolaridade!=12));

				liv=Escola::Instance()->searchLivrariasAno(escolaridade);

				if(liv.size()==0){
					std::cout << "\n\nThe year " << escolaridade << " has currently no books being sold anywhere!\n";
					std::cout << "Press Return to continue...";
					Additions::waitForReturn();
					Additions::clearConsole();
					should_finish=true;
					searchBookstoreInfo();
				}
				else
					while(!liv.empty()){
						std::cout << liv.top()->imprimeDados() << std::endl;
						liv.pop();
					}

				break;
			case escKey :
						Additions::clearConsole();
						BookstoresManagementMenu();
						break;

			default:
						Additions::clearConsole();
						searchBookstoreInfo();
						break;


			}

			if(should_finish)
					return;

			std::cout << "\nChoose the ID of the bookstore you want to change: ";
			opt=Additions::getline();

			if(Additions::gotESC(opt)){
				Additions::clearConsole();
				searchBookstoreInfo();
				return;
			}
			if (atoi(opt.c_str()))
				NID=atoi(opt.c_str());

			while(!Additions::checkForOnlyNumeric(opt) && (NID < 0 || NID >= Livraria::getID_max())){
				std::cout << "\nPlease choose a correct ID value: ";
				opt=Additions::getline();

				if(Additions::gotESC(opt)){
					Additions::clearConsole();
					searchBookstoreInfo();
					return;
				}
				if (atoi(opt.c_str()))
					NID=atoi(opt.c_str());
			}
			l1 = Escola::Instance()->searchLivrariaID(ID);

			if(l1==NULL){
				Additions::clearConsole();
				std::cout << "A bookstore with that ID (" << NID << ") seems to have been deleted from the database!\n";
				std::cout << "Please try again!";
				searchBookstoreInfo();
				return;

			}


			Additions::clearConsole();
			changeBookstoreInfo(l1->getID());

		}

void changeBookstoreInfo(int IDBS){
	int opc, year, course;
	string nyear, ncourse;
	Livraria *l1 = Escola::Instance()->searchLivrariaID(IDBS);
	vector<int > escolaridade = Escola::Instance()->searchLivrariaID(IDBS)->getEscolaridade();
	vector<string > especialidade = Escola::Instance()->searchLivrariaID(IDBS)->getEspecialidade();

	std::cout << "What do you want to do?\n\n";
	std::cout << "(1) Add a school year\n";
	std::cout << "(2) Delete a school year\n";
	std::cout << "(3) Insert a course\n";
	std::cout << "(4) Delete a course\n";
	std::cout << "(5) Delete bookstore\n";
	std::cout << "(6) Show information\n";

	std::cout << "Please choose an option... \n";
	opc=_getch();

	bool should_break=false;

	switch (opc){

	case (baseASCIIn+1):
			do{
				std::cout << "\nNew year: ";
				nyear= Additions::getline();

				if(Additions::gotESC(nyear)){
						Additions::clearConsole();
						changeBookstoreInfo(IDBS);
						should_break=true;
				}
				if(atoi(nyear.c_str()))
					year=atoi(nyear.c_str());


			}while(!Additions::checkForNumeric(nyear) &&  (year!=8 || year!=9 || year!=10 || year!=11 || year!=12));



			if (should_break)
				break;

			if(l1->existeAno(year)){

				std::cout << "\n\nError: that year already exists!\n";
				std::cout << "Please return to continue...";
				Additions::waitForReturn();
				Additions::clearConsole();
				anotherChangeBookstore(IDBS);
			}
			else{

				escolaridade.push_back(year);
				l1->setEscolaridade(escolaridade);
				std::cout << "\n\nSuccess!\n";
				std::cout << "Please return to continue...";
				Additions::waitForReturn();
				Additions::clearConsole();
				anotherChangeBookstore(IDBS);
			}

			break;


		case (baseASCIIn+2):
				do{
					std::cout << "\nYear to delete: ";
					nyear= Additions::getline();

					if(Additions::gotESC(nyear)){
						Additions::clearConsole();
						changeBookstoreInfo(IDBS);
						should_break=true;
					}
					if(atoi(nyear.c_str()))
						year=atoi(nyear.c_str());


				}while(!Additions::checkForNumeric(nyear) &&  (year!=8 || year!=9 || year!=10 || year!=11 || year!=12));



				if (should_break)
					break;

				if(!l1->existeAno(year)){

					std::cout << "\n\nError: that year doesn't exist!\n";
					std::cout << "Please return to continue...";
					Additions::waitForReturn();
					Additions::clearConsole();
					anotherChangeBookstore(IDBS);
				}
				else{

					for(int i = 0 ; i < escolaridade.size();i++){
						if(escolaridade[i]==year){
							escolaridade.erase(escolaridade.begin()+i);
							break;
						}
					}
					l1->setEscolaridade(escolaridade);
					std::cout << "\n\nSuccess!\n";
					std::cout << "Please return to continue...";
					Additions::waitForReturn();
					Additions::clearConsole();
					anotherChangeBookstore(IDBS);
				}

				break;

			case (baseASCIIn+3):

				Additions::clearConsole();

				std::cout << Escola::Instance()->getDisciplinas() << std::endl;

				do{
					std::cout << "\nWhich course do you want to add? (write the name) ";
					ncourse= Additions::getline();

					if(Additions::gotESC(ncourse)){
						Additions::clearConsole();
						changeBookstoreInfo(IDBS);
						should_break=true;
					}

				}while(!Additions::checkValidDisciplina(ncourse) && Escola::Instance()->searchDisciplinaNome(ncourse)==NULL);

				if(l1->existeDisciplina(ncourse)){

					std::cout << "\n\nError: that course already exists in the bookstore!\n";
					std::cout << "Please return to continue...";
					Additions::waitForReturn();
					Additions::clearConsole();
					anotherChangeBookstore(IDBS);
				}
				else{

					especialidade.push_back(ncourse);
					l1->setEspecialidade(especialidade);
					std::cout << "\n\nSuccess!\n";
					std::cout << "Please return to continue...";
					Additions::waitForReturn();
					Additions::clearConsole();
					anotherChangeBookstore(IDBS);
				}

				break;

			case (baseASCIIn+4):

				Additions::clearConsole();

				for(int i =0; i < especialidade.size();i++){
					std::cout << especialidade[i] << std::endl;
				}

				do{
					std::cout << "\nWhich course do you want to delete?";
					ncourse= Additions::getline();

					if(Additions::gotESC(ncourse)){
						Additions::clearConsole();
						changeBookstoreInfo(IDBS);
						should_break=true;
					}

				}while(!Additions::checkValidDisciplina(ncourse) && Escola::Instance()->searchDisciplinaNome(ncourse)==NULL);

				if(!l1->existeDisciplina(ncourse)){

					std::cout << "\n\nError: that course doesn't exist in the bookstore!\n";
					std::cout << "Please return to continue...";
					Additions::waitForReturn();
					Additions::clearConsole();
					anotherChangeBookstore(IDBS);
				}
				else{

					for(int j =0; j < especialidade.size();j++){
						if(especialidade[j]==ncourse){
							especialidade.erase(especialidade.begin()+j);
							break;
						}
					}
					l1->setEspecialidade(especialidade);
					std::cout << "\n\nSuccess!\n";
					std::cout << "Please return to continue...";
					Additions::waitForReturn();
					Additions::clearConsole();
					anotherChangeBookstore(IDBS);
				}

				break;
			case (baseASCIIn+5):

					delBookstore(IDBS);
					break;

			case (baseASCIIn+6):
					Additions::clearConsole();
					std::cout << Escola::Instance()->searchLivrariaID(IDBS)->imprimeDados() << std::endl << std::endl;
					changeBookstoreInfo(IDBS);
					break;

			case escKey :
					Additions::clearConsole();
					searchBookstoreInfo();
					break;

			default:
					Additions::clearConsole();
					changeBookstoreInfo(IDBS);
					break;


		}
}

void addBookstore(){

	Disciplina *d1;
	string nome,localizacao_str,disciplina_str,escolaridade_str;
	int disciplina,localizacao,escolaridade;
	vector <string> especialidade;
	vector <int> escolaridades;

	Additions::clearConsole();

	std::cout << "NEW BOOKSTORE\n";


	do{
		std::cout << "\nName: ";
		nome= Additions::getline();

		if(Additions::gotESC(nome)){
			Additions::clearConsole();
			BookstoresManagementMenu();
			return;
		}

	}while(!Additions::checkValidDisciplina(nome));

	do{
			std::cout << "\nDistance from School (in Km): ";
			localizacao_str=Additions::getline();

			if(Additions::gotESC(localizacao_str)){
				Additions::clearConsole();
				BookstoresManagementMenu();
				return;
			}


	}while(!Additions::checkForOnlyNumeric(localizacao_str));

	localizacao=atoi(localizacao_str.c_str());

	bool finish=false;
	bool move=false;

	if(Escola::Instance()->getNDisciplinas()==0){
			std::cout << "\nThere are still no courses in your school!\n";
			std::cout << "You can add a course and assign it to the bookstore later!\n";
			move=true;

	}

	if(!move){
			do{
				std::cout << "\nAssign a course to the bookstore \n";
				std::cout << "Notes: You can assign more courses later... If we ask you again then that ID doesn't exist!\nWrite the ID of the course from 1 to " << Disciplina::getIDmax()-1<< ") ";
				disciplina_str=Additions::getline();

				if(Additions::gotESC(disciplina_str)){
					Additions::clearConsole();
					addAssistant();
					finish=true;
					break;
				}

				if(atoi(disciplina_str.c_str()))
					disciplina=atoi(disciplina_str.c_str());

				//d1=Escola::Instance()->searchDisciplina(disciplina);
				//especialidade.push_back(d1->getNome());


			}while(!Additions::checkForOnlyNumeric(disciplina_str) && Escola::Instance()->searchDisciplina(disciplina)==NULL);

			especialidade.push_back(Escola::Instance()->searchDisciplina(disciplina)->getNome());

			do{
				std::cout << "\nAssign a year to the bookstore  (Write from 8 to 12??) \n";
				std::cout << "Notes: You can assign more years later... If we ask you again then that year isn't valid! ";
				escolaridade_str=Additions::getline();

				if(Additions::gotESC(escolaridade_str)){
					Additions::clearConsole();
					addAssistant();
					finish=true;
					break;
				}

				if(atoi(disciplina_str.c_str()))
					escolaridade=atoi(escolaridade_str.c_str());




			}while(!Additions::checkForOnlyNumeric(escolaridade_str) &&  (escolaridade!=8 || escolaridade!=9 || escolaridade!=10 || escolaridade!=11 || escolaridade!=12) );

			escolaridades.push_back(escolaridade);
	}
	if(finish)
		return;
	Livraria *l1= new Livraria(nome,localizacao);
	l1->setEscolaridade(escolaridades);
	l1->setEspecialidade(especialidade);
	Escola::Instance()->addLivraria(l1);
	std::cout << "\nSuccess!\n\n" << "Press Enter to continue...";
	Additions::waitForReturn();
	Additions::clearConsole();
	BookstoresManagementMenu();

}

void anotherChangeBookstore(int IDBS){
	std::cout << "\nDo you want to make any more changes to that bookstore? (y/n)\n";
	int opt=_getch();

	switch(opt){
	case 89:
	case 121:
		Additions::clearConsole();
		changeBookstoreInfo(IDBS);
		break;


	case 78:
	case 110:
		Additions::clearConsole();
		BookstoresManagementMenu();
		break;

	default:
		std::cout << "Invalid option, try again!\n";
		anotherChangeBookstore(IDBS);
		break;
	}
}

void delBookstore(int IDBS){

	int option;

	std::cout << "\nAre you sure you want to delete this bookstore? (y/n)\n";

	option=_getch();

	switch(option){

	case 89:
	case 121:
		Escola::Instance()->delLivraria(Escola::Instance()->searchLivrariaID(IDBS));
		std::cout << "Bookstore was deleted with success!\n\n";
		std::cout << "Press Enter to continue...";
		Additions::waitForReturn();
		Additions::clearConsole();
		BookstoresManagementMenu();
		break;

	case 78:
	case 110:
		Additions::clearConsole();
		changeBookstoreInfo(IDBS);
		break;

	case escKey:
		Additions::clearConsole();
		changeBookstoreInfo(IDBS);
		break;

	default:
		std::cout << "Invalid option, try again!\n\n";
		delBookstore(IDBS);
		break;
	}
}

void AssistantsManagementMenu(){

	int opc;

	std::cout << "What do you want to do?" << std::endl << std::endl;
	std::cout << "(1) Add an assistant" << std::endl;
	std::cout << "(2) Change an existing assistant's information" << std::endl;

	opc=_getch();

	switch (opc){
	case (baseASCIIn+1):
		Additions::clearConsole();
		addAssistant();
		break;

	case (baseASCIIn+2):
		Additions::clearConsole();
		searchAssistantInfo();
		break;

	case escKey:
		Additions::clearConsole();
		mainMenu();
		break;

	default:

		Additions::clearConsole();
		AssistantsManagementMenu();
		break;
	}

}

void addAssistant(){

	Turma *t1;
	string nome,contato_str,turma_str;
	int turma;
	long contato=0;

	Additions::clearConsole();

	std::cout << "NEW ASSISTANT\n";


	do{
		std::cout << "\nName: (Instead of 'space' use 'underscore') ";
		nome= Additions::getline();

		if(Additions::gotESC(nome)){
			Additions::clearConsole();
			AssistantsManagementMenu();
			return;
		}

	}while(!Additions::checkForNumeric(nome));

	do{
			std::cout << "\nContact: ";
			contato_str=Additions::getline();

			if(Additions::gotESC(contato_str)){
				Additions::clearConsole();
				AssistantsManagementMenu();
				return;
			}

			if(atoi(contato_str.c_str()))
				contato=atoi(contato_str.c_str());

	}while(!Additions::checkForOnlyNumeric(contato_str));

	bool finish=false;
	bool move=false;

	if(Escola::Instance()->getNTurmas()==0){
			std::cout << "\nThere are still no classes in your school!\n";
			std::cout << "You can add a class and assign this assistant to supervise that class later!\n";
			move=true;

	}
	Funcionarios *f1 = new Funcionarios(nome,contato);
	Funcionarios *f2 = new Funcionarios("qwer");

	if(!move){
			do{
				std::cout << "\nChoose one class to supervise: (Write the ID of the class from 1 to " << Turma::getIDMax()-1<< ") ";
				turma_str=Additions::getline();

				if(Additions::gotESC(turma_str)){
					Additions::clearConsole();
					addAssistant();
					finish=true;
					break;
				}

				if(atoi(turma_str.c_str()))
					turma=atoi(turma_str.c_str());

				t1=Escola::Instance()->searchTurma(turma);

			}while(t1==NULL);

			if(!finish)
				f1->addTurmaFunc(t1);

	}
	if(finish)
		return;

	if(!Escola::Instance()->addFuncionario(f1)){
			std::cout << "\n\nError: An assistant with that name already exists!\n";
			std::cout << "Press any key to try again...\n";
			int opt=_getch();
			switch(opt){
			default :
				Additions::clearConsole();
				addAssistant();
				break;
			}
	}
	else{

			std::cout << "\nSuccess!\n\n" << "Press Enter to continue...";
			Additions::waitForReturn();
			Additions::clearConsole();
			AssistantsManagementMenu();
	}
}

void searchAssistantInfo(){

	string nome , apelido , contato ;
	unsigned int ID,idturma, opc;
	int NID=-1;
	string opt,str;
	vector<Aluno*> alunosturma;
	vector <Funcionarios *> vecFunc;


	std::cout << "Search assistants by..." << std::endl;
	std::cout << " (1) Name " << std::endl;
	std::cout << " (2) ID " << std::endl;
	std::cout << " (3) Class " << std::endl;

	bool should_finish=false;

	opc=_getch();

	switch (opc){

	case (baseASCIIn+1):
				Additions::clearConsole();
				std::cout << "Name: ";
				nome=Additions::getline();

				if(Additions::gotESC(nome)){
					Additions::clearConsole();
					searchAssistantInfo();
					should_finish=true;
					break;
				}
				if(Escola::Instance()->searchFunc(nome)==NULL){
					Additions::clearConsole();
					std::cout << "\n\nYour search got no results! Try again...\n";
					should_finish=true;
					searchAssistantInfo();
				}
				else{
					std::cout << std::endl << Escola::Instance()->searchFunc(nome)->imprimeDados() << std::endl;
				}

				break;


	case (baseASCIIn+2):
				Additions::clearConsole();
				Funcionarios *f2;
				do {
					std::cout << "ID: (Between 1 and " << Funcionarios::getID_max()-2 << ") ";

					str=Additions::getline();

					if(Additions::gotESC(str)){
						Additions::clearConsole();
						searchAssistantInfo();
						should_finish=true;
						break;
					}
				}while(!Additions::checkForOnlyNumeric(str));

				ID=atoi(str.c_str());

				f2=Escola::Instance()->searchFunc(ID);
				if(f2==NULL){
					Additions::clearConsole();
					std::cout << "There is no assistant with the ID (" << ID << ")\n\n Press Return to continue... \n";
					Additions::waitForReturn();
					Additions::clearConsole();
					searchAssistantInfo();
					should_finish=true;
					break;
				}
				std::cout << "\n\n";
				changeAssistantInfo(ID);
				should_finish=true;
				break;

	case (baseASCIIn+3):
				Additions::clearConsole();
				do{
					std::cout << "Class: (Between 1 and " << Turma::getIDMax()-1 << ") ";
					str=Additions::getline();

					if(Additions::gotESC(str)){
						Additions::clearConsole();
						searchStudentInfo();
						should_finish=true;
						break;
					}
				}while(!Additions::checkForOnlyNumeric(str));

				idturma=atoi(str.c_str());

				vecFunc = Escola::Instance()->searchFuncTurma(idturma);
				if(vecFunc.size()==0){
					std::cout << "\n\nThe class " << idturma << " is currently not being supervised!\n";
					std::cout << "Press Return to continue...";
					Additions::waitForReturn();
					Additions::clearConsole();
					should_finish=true;
					searchAssistantInfo();
				}
				else{
					for(unsigned int i=0; i < vecFunc.size(); i++){
						std::cout << std::endl << vecFunc[i]->imprimeDados() << std::endl;
					}
					do {
						std::cout << "\nChoose the ID of the assistant you want to change: ";

						str=Additions::getline();

						if(Additions::gotESC(str)){
							Additions::clearConsole();
							searchAssistantInfo();
							should_finish=true;
							break;
						}
					}while(!Additions::checkForOnlyNumeric(str));

					ID=atoi(str.c_str());

					f2=Escola::Instance()->searchFunc(ID);
					if(f2==NULL){
						Additions::clearConsole();
						std::cout << "There is no assistant with the ID (" << ID << ")\n\n Press Return to continue... \n";
						Additions::waitForReturn();
						Additions::clearConsole();
						searchAssistantInfo();
						should_finish=true;
						break;
					}
					Additions::clearConsole();
					changeAssistantInfo(ID);
					should_finish=true;
				}


				break;

	case escKey :
				Additions::clearConsole();
				AssistantsManagementMenu();
				break;

	default:
				Additions::clearConsole();
				searchAssistantInfo();
				break;


	}

	if(should_finish)
			return;

	std::cout << "\nChoose the ID of the assistant you want to change: ";
	opt=Additions::getline();

	if(Additions::gotESC(opt)){
		Additions::clearConsole();
		AssistantsManagementMenu();
		return;
	}
	if (atoi(opt.c_str()))
		NID=atoi(opt.c_str());

	while(!Additions::checkForOnlyNumeric(opt) && (NID < 0 || NID >= Funcionarios::getID_max())){
		std::cout << "\nPlease choose a correct ID value: ";
		opt=Additions::getline();

		if(Additions::gotESC(opt)){
			Additions::clearConsole();
			AssistantsManagementMenu();
			return;
		}
		if (atoi(opt.c_str()))
			NID=atoi(opt.c_str());
	}
	Funcionarios *f1 = Escola::Instance()->searchFunc(NID);

	if(f1==NULL){
		Additions::clearConsole();
		std::cout << "An assistant with that ID (" << NID << ") seems to have been deleted from the database!\n";
		std::cout << "Please try again!";
		searchAssistantInfo();
		return;

	}


	Additions::clearConsole();
	changeAssistantInfo(f1->getID());

}

void changeAssistantInfo(int IDAssist){

	int opc, contato;
	string nnome, ncontato, nturma;
	BST <Funcionarios *> func = Escola::Instance()->getAllFuncionarios();
	BSTItrIn <Funcionarios *> itr(func);

	std::cout << "What do you want to do?\n\n";
	std::cout << "(1) Change name\n";
	std::cout << "(2) Change contact\n";
	std::cout << "(3) Change classes\n";
	std::cout << "(4) Delete assistant\n";
	std::cout << "(5) Show information\n";

	std::cout << "Please choose an option... \n";
	opc=_getch();

	bool should_break=false;

	switch (opc){

	case (baseASCIIn+1):
			do{
				std::cout << "\nNew name: ";
				nnome= Additions::getline();

				if(Additions::gotESC(nnome)){
					Additions::clearConsole();
					changeAssistantInfo(IDAssist);
					should_break=true;
				}


			}while(!Additions::checkForNumeric(nnome));



				if (should_break)
					break;

				while(!itr.isAtEnd()){
						if(nnome == itr.retrieve()->getNome()){
							Additions::clearConsole();
							std::cout << "Error: The name "<< nnome << " already exists!\n\n";
							changeAssistantInfo(IDAssist);
							should_break=true;
							break;
						}
						itr.advance();
					}

				if(should_break)
					break;

				Escola::Instance()->searchFunc(IDAssist)->setNome(nnome);
				std::cout << "\nSuccess!!\n\n";
				anotherChangeAssist(IDAssist);

				break;


	case (baseASCIIn+2):
			do{
				std::cout << "\nNew contact: ";
				ncontato= Additions::getline();

				if(Additions::gotESC(ncontato)){
					Additions::clearConsole();
					changeAssistantInfo(IDAssist);
					should_break=true;
				}


			}while(!Additions::checkForOnlyNumeric(ncontato));

			if (should_break)
				break;

			contato=atoi(ncontato.c_str());

			Escola::Instance()->searchFunc(IDAssist)->setContato(contato);

			std::cout << "\nSuccess!!\n\n";
			anotherChangeAssist(IDAssist);


			break;

		case (baseASCIIn+3):

			Additions::clearConsole();
			assistantClasses(IDAssist);
			break;


		case (baseASCIIn+4):

				delAssistant(IDAssist);
				break;

		case (baseASCIIn+5):
				Additions::clearConsole();
				std::cout << Escola::Instance()->searchFunc(IDAssist)->imprimeDados() << std::endl << std::endl;
				changeAssistantInfo(IDAssist);
				break;

		case escKey :
				Additions::clearConsole();
				searchAssistantInfo();
				break;

		default:
				Additions::clearConsole();
				changeAssistantInfo(IDAssist);
				break;


	}
}

void delAssistant(int IDAssist){

	int option;

	std::cout << "\nAre you sure you want to delete this assistant? (y/n)\n";

	option=_getch();

	switch(option){
	case 89:
	case 121:
		if(Escola::Instance()->delFuncionario(Escola::Instance()->searchFunc(IDAssist))){
			std::cout << "Assistant was deleted with success!\n\n";
			std::cout << "Press Enter to continue...";
			Additions::waitForReturn();
			Additions::clearConsole();
			AssistantsManagementMenu();
		}

		break;


	case 78:
	case 110:
		Additions::clearConsole();
		changeAssistantInfo(IDAssist);
		break;

	case escKey:
		Additions::clearConsole();
		changeAssistantInfo(IDAssist);
		break;

	default:
		std::cout << "Invalid option, try again!\n\n";
		delAssistant(IDAssist);
		break;
	}
}

void assistantClasses(int IDAssist){

	int turma;
	string turma_str;
	bool finish=false;
	vector<Turma *> vecTurmas = Escola::Instance()->searchTurmasFunc(IDAssist);
	Turma * t1;
	Funcionarios * f1 = Escola::Instance()->searchFunc(IDAssist);

	if(vecTurmas.size()==0){
		std::cout << "This assistant is not supervising any class!\n\n";
	}
	else{
		std::cout << "This assistant is currently supervising the following classes:\n";
		for(int i =0 ; i < vecTurmas.size(); i++){
			if(i==0)
				std::cout << vecTurmas[i]->getID();
			else
				std::cout << ", " << vecTurmas[i]->getID();
		}
	}

	std::cout << "\n\nWhat do you want to do?\n\n";
	std::cout << "(1) Add a class to supervise\n";
	std::cout << "(2) Delete a class from supervising\n";

	std::cout << "\nPlease choose an option...";

	int opc=_getch();

		switch (opc){
		case (baseASCIIn+1):
				Additions::clearConsole();
				do{
					std::cout << "\nChoose one class to also supervise: (Write the ID of the class from 1 to " << Turma::getIDMax()-1<< ") ";
					turma_str=Additions::getline();

					if(Additions::gotESC(turma_str)){
						Additions::clearConsole();
						assistantClasses(IDAssist);
						finish=true;
						break;
					}

					if(atoi(turma_str.c_str()))
						turma=atoi(turma_str.c_str());

					t1=Escola::Instance()->searchTurma(turma);

				}while(t1==NULL);

				if(!f1->addTurmaFunc(t1)){
					std::cout << "\nError: The assistant is already supervising the class " << turma << "!\n";
					std::cout << "Press any key to continue...";
					int opt=_getch();
					switch(opt){
					default :
						Additions::clearConsole();
						assistantClasses(IDAssist);
						break;
					}
				}
				else{
					std::cout << "\n\nSuccess!\n";
					std::cout << "Press Return to continue!";
					Additions::waitForReturn();
					Additions::clearConsole();
					anotherChangeAssistClasses(IDAssist);
				}

				break;

		case (baseASCIIn+2):
				if(vecTurmas.size()==0){
					std::cout <<"\n\nError: The assistant isn't currently supervising any classes...\n";
					std::cout << "Press Return to continue...\n\n";
					Additions::waitForReturn();
					assistantClasses(IDAssist);
					break;
				}
				do{
					std::cout << "\n\nChoose one class of the above to stop supervising: ";
					turma_str=Additions::getline();

					if(Additions::gotESC(turma_str)){
						Additions::clearConsole();
						assistantClasses(IDAssist);;
						finish=true;
						break;
					}

					if(atoi(turma_str.c_str()))
						turma=atoi(turma_str.c_str());

					t1=Escola::Instance()->searchTurma(turma);

				}while(t1==NULL);

				if(!f1->delTurmaFunc(t1->getID())){
					std::cout << "\nError: The assistant is not supervising the class " << turma << "!\n";
					std::cout << "Press any key to continue...";
					int opt=_getch();
					switch(opt){
					default :
						Additions::clearConsole();
						assistantClasses(IDAssist);
						break;
					}
				}
				else{
					std::cout << "\n\nSuccess!\n";
					anotherChangeAssistClasses(IDAssist);
				}
				break;

		case escKey:
				Additions::clearConsole();
				changeAssistantInfo(IDAssist);
				break;

		default:

				Additions::clearConsole();
				assistantClasses(IDAssist);
				break;
		}


}

void anotherChangeAssistClasses(int IDAssist){
	std::cout << "\nDo you want to make any more changes to that assistant's classes? (y/n)\n";
		int opt=_getch();

		switch(opt){
		case 89:
		case 121:
			Additions::clearConsole();
			assistantClasses(IDAssist);
			break;


		case 78:
		case 110:
			Additions::clearConsole();
			changeAssistantInfo(IDAssist);
			break;

		default:
			std::cout << "Invalid option, try again!\n";
			anotherChangeAssistClasses(IDAssist);
			break;
		}
}

void anotherChangeAssist(int IDAssist){
	std::cout << "\nDo you want to make any more changes to that assistant? (y/n)\n";
	int opt=_getch();

	switch(opt){
	case 89:
	case 121:
		Additions::clearConsole();
		changeAssistantInfo(IDAssist);
		break;


	case 78:
	case 110:
		Additions::clearConsole();
		AssistantsManagementMenu();
		break;

	default:
		std::cout << "Invalid option, try again!\n";
		anotherChangeAssist(IDAssist);
		break;
	}
}

void changeStudentInfo(int IDAluno){

	int opc,turma, contato;
	string nnome,napelido, nturma, ncontato, nemail;
	Aluno *a1 = Escola::Instance()->searchAluno(IDAluno);

	std::cout << "What do you want to do?\n\n";
	std::cout << "(1) Change name\n";
	std::cout << "(2) Change surname\n";
	std::cout << "(3) Change class\n";
	std::cout << "(4) Change contact\n";
	std::cout << "(5) Change email\n";
	std::cout << "(6) Find books\n";
	std::cout << "(7) Delete student\n";
	std::cout << "(8) Show information\n";

	std::cout << "Please choose an option... \n";
	opc=_getch();

	bool should_break=false;

	switch (opc){

		case (baseASCIIn+1):
				do{
					std::cout << "\nNew name: ";
					nnome= Additions::getline();

					if(Additions::gotESC(nnome)){
						Additions::clearConsole();
						changeStudentInfo(IDAluno);
						should_break=true;
					}

				}while(!Additions::checkForNumeric(nnome));

				if (should_break)
					break;

				Escola::Instance()->searchAluno(IDAluno)->setNome(nnome);

				std::cout << "\nSuccess!!\n\n";
				anotherChange(IDAluno);

				break;

		case (baseASCIIn+2):
					do{
						std::cout << "\nNew surname: ";
						napelido= Additions::getline();

						if(Additions::gotESC(napelido)){
							Additions::clearConsole();
							changeStudentInfo(IDAluno);
							should_break=true;
						}

					}while(!Additions::checkForNumeric(napelido));

					if (should_break)
							break;

					Escola::Instance()->searchAluno(IDAluno)->setApelido(napelido);

					std::cout << "\nSuccess!!\n\n";
					anotherChange(IDAluno);


					break;

		case (baseASCIIn+3):
				do{
					std::cout << "\nNew class: (There are currently " << Escola::Instance()->getNTurmas() << " classes) ";
					nturma= Additions::getline();

					if(Additions::gotESC(nturma)){
						Additions::clearConsole();
						changeStudentInfo(IDAluno);
						should_break=true;
					}

					if (atoi(nturma.c_str()))
							turma=atoi(nturma.c_str());

				}while(!Additions::checkForOnlyNumeric(nturma) && Escola::Instance()->searchTurma(turma-1)!=NULL);

				if (should_break)
					break;

				Escola::Instance()->delAlunoTurma(Escola::Instance()->searchAluno(IDAluno));

				Escola::Instance()->searchTurma(turma)->addAluno(Escola::Instance()->searchAluno(IDAluno));

				std::cout << "\nSuccess!! \n\n";
				anotherChange(IDAluno);

				break;


		case (baseASCIIn+4):
				do{
					std::cout << "\nNew contact: ";
					ncontato= Additions::getline();

					if(Additions::gotESC(ncontato)){
						Additions::clearConsole();
						changeStudentInfo(IDAluno);
						should_break=true;
					}


				}while(!Additions::checkForOnlyNumeric(ncontato));

				if (should_break)
					break;
				contato=atoi(ncontato.c_str());

				Escola::Instance()->searchAluno(IDAluno)->setContacto(contato);

				std::cout << "\nSuccess!!\n\n";
				anotherChange(IDAluno);


				break;
		case (baseASCIIn+5):
					do{
						std::cout << "\nNew email: ";
						nemail= Additions::getline();

						if(Additions::gotESC(nemail)){
							Additions::clearConsole();
							changeStudentInfo(IDAluno);
							should_break=true;
						}

					}while(!Additions::checkValidEmail(nemail));

					if (should_break)
						break;

					Escola::Instance()->searchAluno(IDAluno)->setEmail(nemail);

					std::cout << "\nSuccess!!\n\n";
					anotherChange(IDAluno);


					break;

		case (baseASCIIn+6):
				Additions::clearConsole();
				findBooks(IDAluno);
				break;
		case (baseASCIIn+7):
				delStudent(IDAluno);

				break;

		case (baseASCIIn+8):
				Additions::clearConsole();
				std::cout << a1->imprimeDados() << std::endl;
				changeStudentInfo(IDAluno);
				break;

		case escKey :
				Additions::clearConsole();
				searchStudentInfo();
				break;

		default:
				Additions::clearConsole();
				changeStudentInfo(IDAluno);
				break;


	}


}

void anotherChange(int IDAluno){
	std::cout << "\nDo you want to make any more changes to that student? (y/n)\n";
	int opt=_getch();

		switch(opt){
		case 89:
		case 121:
			Additions::clearConsole();
			changeStudentInfo(IDAluno);
			break;


		case 78:
		case 110:
			Additions::clearConsole();
			studentsManagementMenu();
			break;

		default:
			std::cout << "Invalid option, try again!\n";
			anotherChange(IDAluno);
			break;
		}
}

void searchStudentInfo(){

	string nome , apelido , contato ;
	unsigned int ID,idturma, opc;
	int NID=-1;
	string opt,str;
	vector<Aluno*> alunosturma;



	std::cout << "Search students by..." << std::endl;
	std::cout << " (1) Name " << std::endl;
	std::cout << " (2) Surname " << std::endl;
	std::cout << " (3) ID " << std::endl;
	std::cout << " (4) Class " << std::endl;

	bool should_finish=false;

	opc=_getch();

	switch (opc){

	case (baseASCIIn+1):
			Additions::clearConsole();
			std::cout << "Name: ";
			nome=Additions::getline();

			if(Additions::gotESC(nome)){
				Additions::clearConsole();
				searchStudentInfo();
				should_finish=true;
				break;
			}
			if(Escola::Instance()->searchAlunos(nome)==0){
				Additions::clearConsole();
				std::cout << "Your search got no results! Try again...\n";
				should_finish=true;
				searchStudentInfo();
			}

			break;

	case (baseASCIIn+2):
			Additions::clearConsole();
			std::cout << "Surname: ";
			apelido=Additions::getline();

			if(Additions::gotESC(apelido)){
				Additions::clearConsole();
				searchStudentInfo();
				should_finish=true;
				break;
			}
			if(Escola::Instance()->searchAlunos2(apelido)==0){
				Additions::clearConsole();
				std::cout << "Your search got no results! Try again...\n";
				should_finish=true;
				searchStudentInfo();
			}
			break;

	case (baseASCIIn+3):
			Additions::clearConsole();
			Aluno *a2;
			do {
				std::cout << "ID: (Between 1 and " << Aluno::getID_max()-1 << ") ";

			str=Additions::getline();

			if(Additions::gotESC(str)){
				Additions::clearConsole();
				searchStudentInfo();
				should_finish=true;
				break;
			}
			}while(!atoi(str.c_str()));

			ID=atoi(str.c_str());

			a2=Escola::Instance()->searchAluno(ID);
			if(a2==NULL){
				Additions::clearConsole();
				std::cout << "There is no student with the ID (" << ID << ")\n\n Press Return to continue... \n";
				Additions::waitForReturn();
				Additions::clearConsole();
				searchStudentInfo();
				should_finish=true;
				break;
			}
			Additions::clearConsole();
			changeStudentInfo(ID);
			should_finish=true;
			break;

	case (baseASCIIn+4):
			Additions::clearConsole();
			do{
				std::cout << "Class: (Between 1 and " << Turma::getIDMax()-1 << ") ";
				str=Additions::getline();

				if(Additions::gotESC(str)){
					Additions::clearConsole();
					searchStudentInfo();
					should_finish=true;
					break;
				}
			}while(!atoi(str.c_str()));

			idturma=atoi(str.c_str());
			alunosturma=Escola::Instance()->searchTurma(idturma)->getAlunosTurma();
			if(alunosturma.size() ==0){
				std::cout << "Error: There are currently no students in that class!\n";
				searchStudentInfo();
				should_finish=true;
				break;
			}

			for(unsigned int i=0; i < alunosturma.size();i++){
				std::cout << std::endl << alunosturma[i]->imprimeDados();
			}


			break;

	case escKey :
			Additions::clearConsole();
			studentsManagementMenu();
			break;

	default:
			Additions::clearConsole();
			searchStudentInfo();
			break;


	}

	if(should_finish)
		return;

	std::cout << "\n\nChoose the ID of the student you want to change: ";
	opt=Additions::getline();

	if(Additions::gotESC(opt)){
		Additions::clearConsole();
		studentsManagementMenu();
	}
	if (atoi(opt.c_str()))
		NID=atoi(opt.c_str());

	while(!atoi(opt.c_str()) && (NID < 0 || NID >= Aluno::getID_max())){
		std::cout << "\nPlease choose a correct ID value: ";
		opt=Additions::getline();

		if(Additions::gotESC(opt)){
			Additions::clearConsole();
			studentsManagementMenu();
			return;
		}
		if (atoi(opt.c_str()))
			NID=atoi(opt.c_str());
	}
	Aluno *a1 = Escola::Instance()->searchAluno(NID);

	if(a1==NULL){
		Additions::clearConsole();
		std::cout << "A student with that ID (" << NID << ") seems to have been deleted from the database!\n";
		std::cout << "Please try again!\n\n";
		searchStudentInfo();
		return;

	}


	Additions::clearConsole();
	changeStudentInfo(NID);



}

void delStudent(int IDAluno){

	int option;
	std::cout << "\nAre you sure you want to delete the student? (y/n)\n";

	option=_getch();

	switch(option){
	case 89:
	case 121:
		Escola::Instance()->delAluno(Escola::Instance()->searchAluno(IDAluno));
		std::cout << "Student was deleted with success!\n\n";
		std::cout << "Press Enter to continue...";
		Additions::waitForReturn();
		Additions::clearConsole();
		studentsManagementMenu();
		break;


	case 78:
	case 110:
		Additions::clearConsole();
		changeStudentInfo(IDAluno);
		break;

	case escKey:
		Additions::clearConsole();
		changeStudentInfo(IDAluno);
		break;

	default:
		std::cout << "Invalid option, try again!\n";
		delStudent(IDAluno);
		break;
	}


}

void addStudent(){
	Turma *t1;
	string nome,apelido,email,contato_str,turma_str;
	int turma;
	long contato=0;

	Additions::clearConsole();

	std::cout << "NEW STUDENT\n";


	do{
		std::cout << "\nName: ";
		nome= Additions::getline();

		if(Additions::gotESC(nome)){
			Additions::clearConsole();
			studentsManagementMenu();
			return;
		}

	}while(!Additions::checkForNumeric(nome));


	do{
		std::cout << "\nSurname: ";
		apelido= Additions::getline();

		if(Additions::gotESC(apelido)){
			Additions::clearConsole();
			studentsManagementMenu();
			return;
		}

	}while(!Additions::checkForNumeric(apelido));

	do{
		std::cout << "\nContact: ";
		contato_str=Additions::getline();

		if(Additions::gotESC(contato_str)){
			Additions::clearConsole();
			studentsManagementMenu();
			return;
		}

		if(atoi(contato_str.c_str()))
			contato=atoi(contato_str.c_str());

	}while(!Additions::checkForOnlyNumeric(contato_str));

	do{
		std::cout << "\nEmail: ";
		email=Additions::getline();

		if(Additions::gotESC(email)){
			Additions::clearConsole();
			studentsManagementMenu();
			return;
		}

	}while(!Additions::checkValidEmail(email));

	Aluno *a1= new Aluno(nome, apelido, contato, email);
	bool finish=false;
	if(Escola::Instance()->getNTurmas()==0){
		std::cout << "\nThere are still no classes in your school!\n";
		std::cout << "Create a class first... Press any key to continue... ";
		finish=true;
		int opt=_getch();
		switch(opt){
		default :
			Additions::clearConsole();
			mainMenu();
			break;
		}
	}
	if(finish)
		return;

	do{
		std::cout << "\nChoose a class: (Write the ID of the class from 1 to " << Turma::getIDMax()-1<< ") ";
		turma_str=Additions::getline();

		if(Additions::gotESC(turma_str)){
			Additions::clearConsole();
			finish=true;
			studentsManagementMenu();
		}

		if(atoi(turma_str.c_str()))
			turma=atoi(turma_str.c_str());

		t1=Escola::Instance()->searchTurma(turma);

	}while(t1==NULL);

	if(finish)
		return;

	if(t1->addAluno(a1)){
		if(Escola::Instance()->addAluno(a1)){
			std::cout << "\nSuccess!\n\n" << "Press Enter to continue...";
			Additions::waitForReturn();
			Additions::clearConsole();
			studentsManagementMenu();
		}
		else{

			std::cout << "Press Enter to continue...";
			Additions::waitForReturn();
			addStudent();
		}
	}
	else{
		std::cout << "Press Enter to continue...";
		Additions::waitForReturn();
		addStudent();
	}
}

void studentsManagementMenu(){

	int opc;

	std::cout << "What do you want to do?" << std::endl << std::endl;
	std::cout << "(1) Add a student" << std::endl;
	std::cout << "(2) Change an existing student's information" << std::endl;

	opc=_getch();

	switch (opc){
	case (baseASCIIn+1):
		Additions::clearConsole();
		addStudent();
		break;

	case (baseASCIIn+2):
		Additions::clearConsole();
		searchStudentInfo();
		break;

	case escKey:
		Additions::clearConsole();
		mainMenu();
		break;

	default:

		Additions::clearConsole();
		studentsManagementMenu();
		break;



	}
}

void addTeacher(){

	int disciplina_ID=200000;
	string nome,apelido,email,contato_str,disciplina;
	long contato=0;

	std::cout << "NEW TEACHER\n";


		do{
			std::cout << "\nNome: ";
			nome= Additions::getline();

			if(Additions::gotESC(nome)){
				Additions::clearConsole();
				teachersManagementMenu();
				return;
			}

		}while(!Additions::checkForNumeric(nome));


		do{
			std::cout << "\nApelido: ";
			apelido= Additions::getline();

			if(Additions::gotESC(apelido)){
				Additions::clearConsole();
				teachersManagementMenu();
				return;
			}

		}while(!Additions::checkForNumeric(apelido));

		do{
			std::cout << "\nContato: ";
			contato_str=Additions::getline();

			if(Additions::gotESC(contato_str)){
				Additions::clearConsole();
				teachersManagementMenu();
				return;
			}

			if(atoi(contato_str.c_str()))
				contato=atoi(contato_str.c_str());

		}while(!Additions::checkForOnlyNumeric(contato_str));

		do{
			std::cout << "\nEmail: ";
			email=Additions::getline();

			if(Additions::gotESC(email)){
				Additions::clearConsole();
				teachersManagementMenu();
				return;
			}

		}while(!Additions::checkValidEmail(email));



		if(!Escola::Instance()->checkProfessor(nome,apelido)){
			Additions::clearConsole();
			std::cout << "There is already a teacher with that name! Try again...\n\n";
			addTeacher();
			return;

		}

		Professor *p1= new Professor(nome, apelido, contato, email);
		Escola::Instance()->addProfessor(p1);
		do{
			std::cout << "\nWhich course to lecture:" << std::endl << Escola::Instance()->getDisciplinas() << "\nChoose one...";
			disciplina=Additions::getline();

			if(Additions::gotESC(disciplina)){
				Additions::clearConsole();
				teachersManagementMenu();
				return;
			}
			if(atoi(disciplina.c_str()))
				disciplina_ID=atoi(disciplina.c_str());

		}while(Escola::Instance()->searchDisciplina(disciplina_ID)==NULL);


		Escola::Instance()->searchDisciplina(disciplina_ID)->addProfessor(p1);


		std::cout << "\nSuccess!\n\n";
		std::cout << "Press Return to continue... ";
		Additions::waitForReturn();
		Additions::clearConsole();
		teachersManagementMenu();

}

void searchTeacherInfo(){

	string nome , apelido , contato ;
	unsigned int ID,IDdisc, opc;
	int NID=-1;
	string opt,str,str1;
	HProfessor exprofs = Escola::Instance()->getExProfessores();
	HProfessor::iterator it;

	std::cout << "Search teachers by..." << std::endl;
	std::cout << " (1) Name " << std::endl;
	std::cout << " (2) Surname " << std::endl;
	std::cout << " (3) ID " << std::endl;
	std::cout << " (4) Courses " << std::endl;
	std::cout << " (5) Currently teaching" << std::endl;
	std::cout << " (6) Currently not teaching " << std::endl;

	bool should_finish=false;

	opc=_getch();

	switch (opc){

	case (baseASCIIn+1):
				Additions::clearConsole();
				std::cout << "Name: ";
				nome=Additions::getline();

				if(Additions::gotESC(nome)){
					Additions::clearConsole();
					searchTeacherInfo();
					should_finish=true;
					break;
				}
				if(Escola::Instance()->searchProfs(nome)==0){
					Additions::clearConsole();
					std::cout << "Your search got no results! Try again...";
					should_finish=true;
					searchTeacherInfo();
				}

				break;

		case (baseASCIIn+2):
				Additions::clearConsole();
				std::cout << "Surname: ";
				apelido=Additions::getline();

				if(Additions::gotESC(apelido)){
					Additions::clearConsole();
					searchTeacherInfo();
					should_finish=true;
					break;
				}
				if(Escola::Instance()->searchProfs2(apelido)==0){
					Additions::clearConsole();
					std::cout << "Your search got no results! Try again...";
					should_finish=true;
					searchTeacherInfo();
				}
				break;

		case (baseASCIIn+3):
				Additions::clearConsole();
				do {


					std::cout << "ID: (Between 1 and " << Professor::getID_max()-1 << ") ";


				str=Additions::getline();

				if(Additions::gotESC(str)){
					Additions::clearConsole();
					searchTeacherInfo();
					should_finish=true;
					break;
				}
				}while(!atoi(str.c_str()));

				ID=atoi(str.c_str());

				if(Escola::Instance()->searchProf(ID)==NULL){
					Additions::clearConsole();
					std::cout << "There is no teacher with the ID (" << ID << ")\n\n Press Return to continue... \n";
					Additions::waitForReturn();
					Additions::clearConsole();
					searchTeacherInfo();
					should_finish=true;
					break;
				}
				changeTeacherInfo(ID);
				should_finish=true;
				break;

		case (baseASCIIn+4):
				Additions::clearConsole();
				do{
					std::cout << "Course: (Choose one ID of)\n" << Escola::Instance()->getDisciplinas() ;
					str1=Additions::getline();

					if(Additions::gotESC(str1)){
						Additions::clearConsole();
						searchTeacherInfo();
						should_finish=true;
						break;
					}
				}while(!atoi(str1.c_str()));

				IDdisc=atoi(str1.c_str());

				if(Escola::Instance()->searchDisciplina(IDdisc)->getProfessoresDisc().size()==0){

					std::cout << "\nThere are, currently, no teachers lecturing that course!\n";


				}
				else
					for(int i = 0; i < Escola::Instance()->searchDisciplina(IDdisc)->getProfessoresDisc().size();i++){

						std::cout << std::endl<< Escola::Instance()->searchDisciplina(IDdisc)->getProfessoresDisc()[i]->imprimeDados() << std::endl;


					}
				std::cout << "\n\n";
				break;

		case (baseASCIIn+5):
				Additions::clearConsole();
				if(Escola::Instance()->getAllProf().size()==0)
					std::cout << "There are no teachers in this school";

				for(int i=0; i < Escola::Instance()->getAllProf().size();i++){
					std::cout << Escola::Instance()->getAllProf()[i]->imprimeDados() << std::endl;
					if(Escola::Instance()->getHorarioProf(Escola::Instance()->getAllProf()[i]).size()!=0){
						std::cout <<"Schedule:\n";
						for(int j=0; j < Escola::Instance()->getHorarioProf(Escola::Instance()->getAllProf()[i]).size();j++){

							std::cout << Escola::Instance()->getHorarioProf(Escola::Instance()->getAllProf()[i])[j]->ImprimeDados() << std::endl;
						}
					}
					std::cout << "\n";
				}
			break;

		case (baseASCIIn+6):
			Additions::clearConsole();

			for(it= exprofs.begin(); it != exprofs.end(); it++){
				std::cout << (*it)->imprimeDados() << std::endl;
			}

			break;

		case escKey :
				Additions::clearConsole();
				teachersManagementMenu();
				break;

		default:
				Additions::clearConsole();
				searchTeacherInfo();
				break;


		}

		if(should_finish)
			return;

		std::cout << "\n\nChoose the ID of the teacher you want to change: ";
		opt=Additions::getline();

		if(Additions::gotESC(opt)){
			Additions::clearConsole();
			searchTeacherInfo();
			return;
		}
		if (atoi(opt.c_str()))
			NID=atoi(opt.c_str());

		while(!atoi(opt.c_str()) && (NID < 0 || NID >= Professor::getID_max())){
			std::cout << "Please choose a correct ID value!";
			opt=Additions::getline();

			if(Additions::gotESC(opt)){
				Additions::clearConsole();
				searchTeacherInfo();
				return;
			}
			if (atoi(opt.c_str()))
				NID=atoi(opt.c_str());
		}

		if(Escola::Instance()->searchProf(NID)==NULL){
			Additions::clearConsole();
			std::cout << "A teacher with that ID (" << NID << ") seems to have been deleted from the database!\n";
			std::cout << "Please try again!";
			searchTeacherInfo();
			return;

		}


		Additions::clearConsole();
		changeTeacherInfo(NID);
}

void reHire(Professor *p1){

	std::cout << "\n\nAre you sure you want to re-hire this teacher? (y/n) ";
	int opt=_getch();

	switch(opt){
	case 89:
	case 121:

		Escola::Instance()->recolocarProf(p1);
		std::cout << "\n\nSuccess!!\n";
		std::cout << "Press Return to continue...";
		Additions::waitForReturn();
		anotherChangeProf(p1->getID());
		break;


	case 78:
	case 110:
		Additions::clearConsole();
		changeTeacherInfo(p1->getID());
		break;

	default:
		std::cout << "Invalid option, try again!\n";
		reHire(p1);
	}

}

void changeTeacherInfo(int IDProf){


	int opc,disciplina, contato;
	string nnome,napelido, ncontato, nemail, ndisciplina;

	std::cout << "\nWhat do you want to do?\n\n";
	std::cout << "(1) Change name\n";
	std::cout << "(2) Change surname\n";
	std::cout << "(3) Change course\n";
	std::cout << "(4) Change contact\n";
	std::cout << "(5) Change email\n";
	if(!Escola::Instance()->searchProf(IDProf)->getAtivo())
		std::cout << "(6) Delete teacher\n";
	else
		std::cout << "(6) Fire teacher\n";

	std::cout << "(7) Show information\n";
	if(!Escola::Instance()->searchProf(IDProf)->getAtivo())
		std::cout << "(8) Re-hire teacher\n";

	std::cout << "Please choose an option... \n\n";

	opc=_getch();

	bool should_break=false;

	switch (opc){

		case (baseASCIIn+1):
				do{
					std::cout << "\nNew name: ";
					nnome= Additions::getline();

					if(Additions::gotESC(nnome)){
						Additions::clearConsole();
						changeTeacherInfo(IDProf);
						should_break=true;
					}

				}while(!Additions::checkForNumeric(nnome));

				if (should_break)
					break;

				Escola::Instance()->searchProf(IDProf)->setNome(nnome);

				std::cout << "\n\nSuccess!!\n\n";
				anotherChangeProf(IDProf);

				break;

		case (baseASCIIn+2):
					do{
						std::cout << "\nNew surname: ";
						napelido= Additions::getline();

						if(Additions::gotESC(napelido)){
							Additions::clearConsole();
							changeTeacherInfo(IDProf);
							should_break=true;
						}

					}while(!Additions::checkForNumeric(napelido));

					if (should_break)
							break;

					Escola::Instance()->searchProf(IDProf)->setApelido(napelido);

					std::cout << "\n\nSuccess!!\n\n";
					anotherChangeProf(IDProf);


					break;

		case (baseASCIIn+3):
				do{
					std::cout << "New course: (Choose one ID of)\n" << Escola::Instance()->getDisciplinas() << "\n" ;
					ndisciplina= Additions::getline();

					if(Additions::gotESC(ndisciplina)){
						Additions::clearConsole();
						changeTeacherInfo(IDProf);
						should_break=true;
					}

					if (atoi(ndisciplina.c_str()))
							disciplina=atoi(ndisciplina.c_str());

				}while(!Additions::checkForOnlyNumeric(ndisciplina) && Escola::Instance()->searchDisciplina(disciplina)!=NULL);

				if (should_break)
					break;

				if(Escola::Instance()->getDisciplinaProf(Escola::Instance()->searchProf(IDProf))->getID()==disciplina){
					Additions::clearConsole();
					std::cout << "Error: This teacher is already lecturing that course!\n";
					anotherChangeProf(IDProf);
					break;
				}

				Escola::Instance()->getDisciplinaProf(Escola::Instance()->searchProf(IDProf))->delProfessor(Escola::Instance()->searchProf(IDProf));

				Escola::Instance()->searchDisciplina(disciplina)->addProfessor(Escola::Instance()->searchProf(IDProf));

				anotherChangeProf(IDProf);

				break;


		case (baseASCIIn+4):
				do{
					std::cout << "\nNew contact: ";
					ncontato= Additions::getline();

					if(Additions::gotESC(ncontato)){
						Additions::clearConsole();
						changeTeacherInfo(IDProf);
						should_break=true;
					}


				}while(!Additions::checkForOnlyNumeric(ncontato));

				if (should_break)
					break;
				contato=atoi(ncontato.c_str());

				Escola::Instance()->searchProf(IDProf)->setContacto(contato);

				std::cout << "\n\nSuccess!!\n\n";
				anotherChangeProf(IDProf);


				break;
		case (baseASCIIn+5):
					do{
						std::cout << "\nNew email: ";
						nemail= Additions::getline();

						if(Additions::gotESC(nemail)){
							Additions::clearConsole();
							changeTeacherInfo(IDProf);
							should_break=true;
						}

					}while(!Additions::checkValidEmail(nemail));

					if (should_break)
						break;

					Escola::Instance()->searchProf(IDProf)->setEmail(nemail);

					std::cout << "\n\nSuccess!!\n\n";
					anotherChangeProf(IDProf);


					break;

		case (baseASCIIn+6):
				delProfessor(IDProf);
				break;

		case (baseASCIIn+7):
				Additions::clearConsole();

				std::cout << Escola::Instance()->searchProf(IDProf)->imprimeDados() << std::endl;
				if(Escola::Instance()->getDisciplinaProf(Escola::Instance()->searchProf(IDProf))!=NULL)
					std::cout << "Course: " << Escola::Instance()->getDisciplinaProf(Escola::Instance()->searchProf(IDProf))->getNome() << std::endl;

				if(Escola::Instance()->getHorarioProf(Escola::Instance()->searchProf(IDProf)).size()!=0){
					std::cout << "Schedule:\n";
				//vector<Horario *> HP = Escola::Instance()->getHorarioProf(Escola::Instance()->searchProf(IDProf));
					for (int i=0; i < Escola::Instance()->getHorarioProf(Escola::Instance()->searchProf(IDProf)).size(); i++){
						std::cout << Escola::Instance()->getHorarioProf(Escola::Instance()->searchProf(IDProf))[i]->ImprimeDados()<<std::endl;
					}
					std::cout << std::endl;
				}
				changeTeacherInfo(IDProf);
				break;

		case (baseASCIIn+8):
				if(!Escola::Instance()->searchProf(IDProf)->getAtivo()){
					reHire(Escola::Instance()->searchProf(IDProf));


				}
				else{
					Additions::clearConsole();
					changeTeacherInfo(IDProf);
				}
			break;

		case escKey :
				Additions::clearConsole();
				searchTeacherInfo();
				break;

		default:
				Additions::clearConsole();
				changeTeacherInfo(IDProf);
				break;


	}


}

void anotherChangeProf(int IDProf){
	std::cout << "\nDo you want to make any more changes to that teacher? (y/n)\n";
	int opt=_getch();

		switch(opt){
		case 89:
		case 121:
			Additions::clearConsole();
			changeTeacherInfo(IDProf);
			break;


		case 78:
		case 110:
			Additions::clearConsole();
			teachersManagementMenu();
			break;

		default:
			std::cout << "Invalid option, try again!\n";
			anotherChangeProf(IDProf);
		}
}

void delProfessor(int IDProf){

	int option;

	if(Escola::Instance()->searchProf(IDProf)->getAtivo()){
		if(Escola::Instance()->getDisciplinaProf(Escola::Instance()->searchProf(IDProf))->getProfessoresDisc().size()==1){
			std::cout << "\nError: it's not possible to do that because the course has only one teacher!\n\n";
			std::cout << "Press Return to continue...";
			Additions::waitForReturn();
			anotherChangeProf(IDProf);
			return;
		}

		for(int i = 0 ; i < Escola::Instance()->searchTurmasProf(IDProf).size(); i++){
			if(Escola::Instance()->searchTurmasProf(IDProf)[i]->getDiretorTurma()->getID()==IDProf){
				std::cout << "\nError: it's not possible to do that because the teacher is a class director!\n\n";
				std::cout << "Press Return to continue...";
				Additions::waitForReturn();
				anotherChangeProf(IDProf);
				return;
			}
		}
	}

	std::cout << "\nAre you sure you want to delete this teacher? \n";
	std::cout << "If the teacher is active it will not delete the teacher from the database... (y/n)\n";

	option=_getch();

	switch(option){
		case 89:
		case 121:
			if(Escola::Instance()->delProfessor(Escola::Instance()->searchProf(IDProf))){
				std::cout << "Teacher was deleted with success!\n\n";
				std::cout << "Press Enter to continue...";
				Additions::waitForReturn();
				Additions::clearConsole();
				teachersManagementMenu();
			}

			break;


		case 78:
		case 110:
			Additions::clearConsole();
			changeTeacherInfo(IDProf);
			break;

		case escKey:
			Additions::clearConsole();
			changeTeacherInfo(IDProf);
			break;

		default:
			std::cout << "Invalid option, try again!\n\n";
			delProfessor(IDProf);
			break;
		}

}

void teachersManagementMenu(){

	int opc;

	std::cout << "What do you want to do?" << std::endl << std::endl;
	std::cout << "(1) Add a teacher" << std::endl;
	std::cout << "(2) Change an existing teacher's information" << std::endl;

	opc=_getch();

	switch (opc){
	case (baseASCIIn+1):
			Additions::clearConsole();
			addTeacher();
			break;

	case (baseASCIIn+2):
			Additions::clearConsole();
			searchTeacherInfo();
			break;

	case escKey:
			Additions::clearConsole();
			mainMenu();
			break;

	default:

			Additions::clearConsole();
			teachersManagementMenu();
			break;
	}

}

void setClassSchedules(int IDTurma){
	Horario *h1;
	string nday,nhour,nID;
	int n=0;
	int h=25;
	int opc,ID;
	std::cout << "::SETTING CLASS " << IDTurma << " SCHEDULE::\n\n";
	std::cout << "You can't leave this function until you have successfully set 4 different \nschedules for all " << Escola::Instance()->getNDisciplinas() << " courses\n";
	std::cout << "\nPress any key to continue...";

	bool found1=false;
	bool found2=false;

	opc=_getch();
	switch(opc){

	default:
		break;

	}
	for(int i=0; i < Escola::Instance()->getAllCourses().size();i++){
		Additions::clearConsole();
		n=0;
		std::cout << "::SETTING CLASS " << IDTurma << " SCHEDULE::\n\n";
		std::cout << "::" << Escola::Instance()->getAllCourses()[i]->getNome()<<"::\n\n";
		std::cout << "Create 4 schedules for four different days...\n";
		std::cout << "Possible choices:\nDays: 'Monday' 'Tuesday' 'Wednesday' 'Thursday' 'Friday'\nHours: '9' '10' '11' '14 '15' '16'";
		std::cout << "\nTeachers lecturing:\n";
		for(int k=0; k <Escola::Instance()->getAllCourses()[i]->getProfessoresDisc().size(); k++){
			std::cout << Escola::Instance()->getAllCourses()[i]->getProfessoresDisc()[k]->imprimeDados() << std::endl;
		}

		do{

			std::cout << "\n\nSchedule "<< n+1 << std::endl;
			do{
				std::cout << "\nDay: ";
				nday= Additions::getline();

			}while(nday != "Monday" && nday != "Tuesday" && nday !="Wednesday" && nday != "Thursday" && nday != "Friday");

			do{
				std::cout << "\nHour: ";
				nhour= Additions::getline();

				if(atoi(nhour.c_str()))
				h=atoi(nhour.c_str());

			}while(h!=9 && h!=10 && h!=11 && h!=14 && h!=15 && h!=16);


			do{
				do{
					std::cout << "\nTeacher: (ID) ";
					nID= Additions::getline();


				}while(!Additions::checkForOnlyNumeric(nID));


			if(atoi(nID.c_str()))
				ID=atoi(nID.c_str());

			}while(Escola::Instance()->searchProf(ID)==NULL);

			for(int k=0; k <Escola::Instance()->getAllCourses()[i]->getProfessoresDisc().size(); k++){
				if(Escola::Instance()->getAllCourses()[i]->getProfessoresDisc()[k]->getID()==ID){
					found1=true;
					break;
				}
			}

			if(!found1)
				std::cout << "\nThe teacher you selected doesn't teach this class...\nPlease try again...";

			else{
				for(int j=0; j < Escola::Instance()->searchTurma(IDTurma)->getHorarioTurma().size();j++){
					if(Escola::Instance()->searchTurma(IDTurma)->getHorarioTurma()[j]->getDia() == nday &&  Escola::Instance()->searchTurma(IDTurma)->getHorarioTurma()[j]->getHora() == h){
						std::cout << "\nThis class already has a schedule on that time...\nPlease try again...";
						found2=true;
					}
				}
				if(!found2){
					h1 = new Horario(nday,h);
					h1->setProfessor(Escola::Instance()->searchProf(ID));
					h1->setDisciplina(Escola::Instance()->getAllCourses()[i]);
					if(Escola::Instance()->addLesson(h1,Escola::Instance()->searchTurma(IDTurma))){
						std::cout << "\nAdded with success!";
						n++;
					}
					else
						std::cout << "\nError: teacher's schedule conflict or course on the same day...";


				}
			}

			found1=false;
			found2=false;


		}while(n<4);


	}

	anotherChangeClass(IDTurma);

}

void setDirectorSchedule(int IDDir,int IDTurma, int nschedules){

	Horario *h1;
	string nday,nhour;
	int n=0;
	int h,opc;
	std::cout << "::SETTING CLASS " << IDTurma << " DIRECTOR'S SCHEDULE::\n\n";
	std::cout << "You can't leave this function until you have successfully set " << nschedules << " different schedules\n";
	std::cout << "\nPress any key to continue...";

	bool found=false;

	opc=_getch();
	switch(opc){

	default:
		Additions::clearConsole();
		break;

	}
	std::cout << "::SETTING CLASS " << IDTurma << " DIRECTOR'S SCHEDULE::\n\n";
	std::cout << "Create " << nschedules << " schedules...\n";
	std::cout << "Possible choices:\nDays: 'Monday' 'Tuesday' 'Wednesday' 'Thursday' 'Friday'\nHours: '12' '17' '18'";

	do{

		std::cout << "\n\nSchedule "<< n+1 << std::endl;
		do{
			std::cout << "\nDay: ";
			nday= Additions::getline();

		}while(nday != "Monday" && nday != "Tuesday" && nday !="Wednesday" && nday != "Thursday" && nday != "Friday");

		do{
			std::cout << "\nHour: ";
			nhour= Additions::getline();

			if(atoi(nhour.c_str()))
				h=atoi(nhour.c_str());

		}while(!atoi(nhour.c_str()) || (h!=12 && h!=17 && h!=18));

		for(int j=0; j<Escola::Instance()->getHorarioProf(Escola::Instance()->searchProf(IDDir)).size();j++){
			if(Escola::Instance()->getHorarioProf(Escola::Instance()->searchProf(IDDir))[j]->getDia() == nday &&  Escola::Instance()->getHorarioProf(Escola::Instance()->searchProf(IDDir))[j]->getHora() == h){
				std::cout << "\nThis teacher already has a schedule on that time...\nPlease try again...";
				found=true;
			}
		}
		if(!found){
				h1 = new Horario(nday,h);
				h1->setProfessor(Escola::Instance()->searchProf(IDDir));
				if(Escola::Instance()->addDirectorSchedule(h1,Escola::Instance()->searchTurma(IDTurma))){
					std::cout << "\nAdded with success!";
					n++;
				}


		}
		found=false;

	}while(n<nschedules);

	std::cout << "\n\nSuccess!\n\n";
}

void addClass(){
		string ano, dturma;
		int nano, ndturma;

		Additions::clearConsole();

		for(int i=0; i < Escola::Instance()->getAllCourses().size();i++)
			if(Escola::Instance()->getAllCourses()[i]->getProfessoresDisc().size()==0){
				std::cout << "Error: to add a class you need to have at least one teacher lecturing each \ncourse!\n";
				std::cout << "\nPress Return to be redirected to 'Courses' menu...";
				Additions::waitForReturn();
				Additions::clearConsole();
				coursesManagementMenu();
				return;
			}


		std::cout << "NEW CLASS\n";


		do{
			std::cout << "\nYear (8 to 12):  ";
			ano= Additions::getline();

			if(Additions::gotESC(ano)){
				Additions::clearConsole();
				classesManagementMenu();
				return;
			}
			if(atoi(ano.c_str()))
				nano=atoi(ano.c_str());

		}while(!Additions::checkForOnlyNumeric(ano) || (nano!=8 && nano!=9 && nano!=10 && nano!=11  && nano!=12));


		do{
			std::cout << "\n\nClass's Diretor: \n" << std::endl;
			//	vector <Professor *> P = Escola::Instance()->getAllProf();
			for(int i=0; i<Escola::Instance()->getAllProf().size() ;i++){
				std::cout << Escola::Instance()->getAllProf()[i]->imprimeDados() << std::endl;
			}
			std::cout << "\nWhat teacher do you want to add as class's director: (ID) ";
			dturma= Additions::getline();

			if(Additions::gotESC(dturma)){
				Additions::clearConsole();
				addClass();
				return;
			}
			if(atoi(dturma.c_str()))
				ndturma=atoi(dturma.c_str());

		}while(!Additions::checkForOnlyNumeric(dturma));

		if(Escola::Instance()->searchProf(ndturma)==NULL){
			Additions::clearConsole();
			std::cout << "\nError: a teacher with that ID doesn't exist or was deleted from the database!\n";
			std::cout << "Please try again...\n\n";
			addClass();
			return;
		}

		Turma *t1= new Turma(nano,Escola::Instance()->searchProf(ndturma));

		Escola::Instance()->addTurma(t1);
		std::cout << "\n\nSuccess!\n\n";
		std::cout << "Press Return to continue...";
		Additions::waitForReturn();
		Additions::clearConsole();
		setDirectorSchedule(Escola::Instance()->searchProf(ndturma)->getID(),t1->getID(),3);
		Additions::clearConsole();
		setClassSchedules(t1->getID());

	}

void deleteClass(int IDTurma){
	int option;

		std::cout << "Are you sure you want to delete this class? (y/n)\n";

		option=_getch();

		switch(option){
			case 89:
			case 121:
				if(Escola::Instance()->delTurma(Escola::Instance()->searchTurma(IDTurma))){
					std::cout << "Class was deleted with success!\n\n";
					std::cout << "Press Enter to continue...";
					Additions::waitForReturn();
					Additions::clearConsole();
					classesManagementMenu();
				}
				break;


			case 78:
			case 110:
				Additions::clearConsole();
				changeClassInfo(IDTurma);
				break;

			default:
				std::cout << "Invalid option, try again!\n";
				deleteClass(IDTurma);
				break;
			}
}

void anotherChangeClass(int IDTurma){
	std::cout << "\nDo you want to make any more changes to that class? (y/n)\n";
	int opt=_getch();

	switch(opt){
			case 89:
			case 121:
				Additions::clearConsole();
				changeClassInfo(IDTurma);
				break;


			case 78:
			case 110:
				Additions::clearConsole();
				classesManagementMenu();
				break;

			default:
				std::cout << "Invalid option, try again!\n";
				anotherChangeClass(IDTurma);
			}
}

void changeSchedule(int ID,int IDTurma){

	int opc;
	int h=25;
	string nday,nhour;
	std::cout << Escola::Instance()->getHorario(ID)->ImprimeDados() << std::endl;

	std::cout << "\n\nWhat do you want to change?\n\n";
	std::cout << "(1) day\n";
	std::cout << "(2) hour\n";

	std::cout << "\nPlease choose an option...\n";

	bool should_break=false;
	opc=_getch();

	switch (opc){

	case (baseASCIIn+1):
		do{
			std::cout << "\nNew day: ";
			nday= Additions::getline();

			if(Additions::gotESC(nday)){
				Additions::clearConsole();
				changeSchedule(ID,IDTurma);
				should_break=true;
			}

		}while(nday != "Monday" && nday != "Tuesday" && nday !="Wednesday" && nday != "Thursday" && nday != "Friday");

		for(int i=0; i < Escola::Instance()->searchTurma(IDTurma)->getHorarioTurma().size();i++)
			if((Escola::Instance()->searchTurma(IDTurma)->getHorarioTurma()[i]->getDia()==nday && Escola::Instance()->getHorario(ID)->getDisciplinaAula()==Escola::Instance()->searchTurma(IDTurma)->getHorarioTurma()[i]->getDisciplinaAula())|| (Escola::Instance()->searchTurma(IDTurma)->getHorarioTurma()[i]->getDia()==Escola::Instance()->getHorario(ID)->getDia() && h==Escola::Instance()->searchTurma(IDTurma)->getHorarioTurma()[i]->getHora())){
				Additions::clearConsole();
				std::cout << "Error: " << Escola::Instance()->getHorario(ID)->getDisciplinaAula()->getNome() << " is already lectured to that class on " << nday << std::endl;
				std::cout << "Please try again...\n\n";
				changeSchedule(ID,IDTurma);
				should_break=true;
			}
		if(should_break)
			break;

		Escola::Instance()->getHorario(ID)->setDia(nday);



		break;

	case (baseASCIIn+2):
			do{
				std::cout << "\nNew hour: ";
				nhour= Additions::getline();

				if(Additions::gotESC(nday)){
					Additions::clearConsole();
					changeSchedule(ID,IDTurma);
					should_break=true;
				}
				if(atoi(nhour.c_str()))
					h=atoi(nhour.c_str());

			}while(h!=9 && h!=10 && h!=11 && h!=14 && h!=15 && h!=16);

			for(int i=0; i < Escola::Instance()->searchTurma(IDTurma)->getHorarioTurma().size();i++)
				if(Escola::Instance()->searchTurma(IDTurma)->getHorarioTurma()[i]->getDia()==Escola::Instance()->getHorario(ID)->getDia() && h==Escola::Instance()->searchTurma(IDTurma)->getHorarioTurma()[i]->getHora()){
					Additions::clearConsole();
					std::cout << "Error: A course is already lectured to that class on " << Escola::Instance()->getHorario(ID)->getDia() << " at " << h << std::endl;
					std::cout << "Please try again...\n\n";
					changeSchedule(ID,IDTurma);
					should_break=true;
				}

			if(should_break)
				break;

			Escola::Instance()->getHorario(ID)->setHora(h);

			break;
	case escKey :
			Additions::clearConsole();
			configLessons(IDTurma);
			break;

	default:
			Additions::clearConsole();
			changeSchedule(ID,IDTurma);
			break;


	}
}

void configLessons (int IDTurma){

	int opc,ID;
	string IDS;

	std::cout << "\n::LESSONS CONFIGURATION:: CLASS " << IDTurma << std::endl << std::endl;

	std::cout << "(1) Change lessons\n";
	std::cout << "(2) View class schedule\n";

	std::cout << "\nPlease choose one...\n";

	opc=_getch();

	switch (opc){

	case (baseASCIIn+1):

		do {
			Additions::clearConsole();
			std::cout << "\nChoose the ID of the schedule you want to change: ";
			IDS=Additions::getline();

			if(Additions::gotESC(IDS)){
				Additions::clearConsole();
				configLessons(IDTurma);
				break;
			}
		}while(!atoi(IDS.c_str()));

		ID=atoi(IDS.c_str());

		if(!Escola::Instance()->searchTurma(IDTurma)->searchHorario(ID)){
			Additions::clearConsole();
			std::cout<< "\nError: the schedule (" << ID << ") doesn't belong to that class or doesn't exist!\n\n";
			configLessons(IDTurma);
			break;
		}
		changeSchedule(ID,IDTurma);

		break;

	case (baseASCIIn+2):

		Additions::clearConsole();
		//vector<Horario *> H = Escola::Instance()->searchTurma(IDTurma)->getHorarioTurma();
		for(int i=0; i < Escola::Instance()->searchTurma(IDTurma)->getHorarioTurma().size();i++){
			std::cout << Escola::Instance()->searchTurma(IDTurma)->getHorarioTurma()[i]->ImprimeDados() << std::endl;
		}
		configLessons(IDTurma);
		break;

	case escKey :
		Additions::clearConsole();
		changeClassInfo(IDTurma);
		break;

	default:
		Additions::clearConsole();
		configLessons(IDTurma);
		break;
	}

}

void searchClassInfo(){
	string Ano_str , ID_str, IDProf_str;
	unsigned int NID,ID, IDProf, ano;
	int opc;
	string opt,str,str1;
	BST <Funcionarios *> func = Escola::Instance()->getAllFuncionarios();
	BSTItrIn <Funcionarios *> itr(func);


	std::cout << "Search classes by..." << std::endl;
	std::cout << " (1) Year " << std::endl;
	std::cout << " (2) ID " << std::endl;
	std::cout << " (3) Teachers " ;
	if(Escola::Instance()->getNProfessores()==0)
		std::cout << "(there are no teachers in the school)\n";
	else std::cout << std::endl;
	std::cout << " (4) Assistants \n";

	std::cout << "\nPlease choose an option...";

	bool should_finish=false;

	opc=_getch();

	switch (opc){

	case (baseASCIIn+1):
			do {
				Additions::clearConsole();
				std::cout << "\nYear: ";
				Ano_str=Additions::getline();

				if(Additions::gotESC(Ano_str)){
					Additions::clearConsole();
					searchClassInfo();
					should_finish=true;
					break;
				}
			}while(!atoi(Ano_str.c_str()));

		ano= atoi(Ano_str.c_str());

		if(Escola::Instance()->searchTurmas(ano).size() == 0){
			Additions::clearConsole();
			std::cout << "\nYour search got no results! Try again...";
			should_finish=true;
			searchClassInfo();
			break;
		}
		//vector<Turma *> T1=Escola::Instance()->searchTurmas(ano);
		for(int i=0; i < Escola::Instance()->searchTurmas(ano).size();i++ ){
			std::cout << Escola::Instance()->searchTurmas(ano)[i]->imprimeDados() << std::endl;
		}
		do{
			std::cout <<"\nWhich class do you want to change:" <<std::endl;

			str1=Additions::getline();
			if(Additions::gotESC(str1)){
				Additions::clearConsole();
				searchClassInfo();
				should_finish=true;
				break;
			}
		}while(!atoi(str1.c_str()));

		ID=atoi(str1.c_str());

		if(Escola::Instance()->searchTurma(ID)==NULL){
			Additions::clearConsole();
			std::cout << "\nError: a class with that ID (" << ID << ") doesn't exist!\nTry again...\n\n";
			searchClassInfo();
			should_finish=true;
			break;
		}

		std::cout << endl;
		changeClassInfo(ID);

		break;

			case (baseASCIIn+2):
						Additions::clearConsole();

						do {

							std::cout << "\nID: (Between 1 and " << Turma::getIDMax()-1 << ") ";
							str=Additions::getline();

							if(Additions::gotESC(str)){
								Additions::clearConsole();
								searchClassInfo();
								should_finish=true;
								break;
							}
						}while(!atoi(str.c_str()) || atoi(str.c_str())>Turma::getIDMax()|| atoi(str.c_str())<0);

						ID=atoi(str.c_str());

						if(Escola::Instance()->searchTurma(ID)==NULL){
							Additions::clearConsole();
							std::cout << "\nThere is no course with the ID (" << ID << ")\n\n Press Return to continue... \n";
							Additions::waitForReturn();
							Additions::clearConsole();
							searchClassInfo();
							should_finish=true;
							break;
						}

						changeClassInfo(ID);
						should_finish=true;
						break;

				case (baseASCIIn+3):

						//vector<Professor*> allProfs1 = Escola::Instance()->getAllProf();
						Additions::clearConsole();
						do{
							for(int i=0; i< Escola::Instance()->getAllProf().size();i++){
								std::cout << Escola::Instance()->getAllProf()[i]->imprimeDados() << std::endl;
							}
							std::cout << "\nChoose a teacher: ";
							str=Additions::getline();

							if(Additions::gotESC(str)){
								Additions::clearConsole();
								searchClassInfo();
								should_finish=true;
								break;
							}
						}while(!atoi(str.c_str()));

						IDProf=atoi(str.c_str());

						//vector<Turma*> tVec1 = Escola::Instance()->searchTurmasProf(IDProf);
						if(Escola::Instance()->searchTurmasProf(IDProf).size()==0){

							Additions::clearConsole();
							std::cout << "\nError: There are no classes with the Teacher (" << IDProf << ")!\n\n";
							searchClassInfo();
							should_finish=true;
							break;

						}
						Additions::clearConsole();
						std::cout << "Classes the teacher (" << Escola::Instance()->searchProf(IDProf)->imprimeDados() << ") lectures...\n\n";
						for(int i=0; i<Escola::Instance()->searchTurmasProf(IDProf).size();i++)
							std::cout << Escola::Instance()->searchTurmasProf(IDProf)[i]->imprimeDados() << std::endl;

						break;

				case (baseASCIIn+4):
						Additions::clearConsole();

						while(!itr.isAtEnd()){
							std::cout << itr.retrieve()->imprimeDados() << std::endl;
							itr.advance();
						}

						break;
				case escKey :
						Additions::clearConsole();
						classesManagementMenu();
						break;

				default:
						Additions::clearConsole();
						searchClassInfo();
						break;


				}

				if(should_finish)
					return;

				std::cout << "\n\nChoose the ID of the class you want to change: ";
				opt=Additions::getline();

				if(Additions::gotESC(opt)){
					Additions::clearConsole();
					searchClassInfo();
				}
				if (atoi(opt.c_str()))
					NID=atoi(opt.c_str());

				while(!atoi(opt.c_str()) && (NID < 0 || NID >= Turma::getIDMax())){
					std::cout << "\nPlease choose a correct ID value: ";
					opt=Additions::getline();

					if(Additions::gotESC(opt)){
						Additions::clearConsole();
						searchClassInfo();
						return;
					}
					if (atoi(opt.c_str()))
						NID=atoi(opt.c_str());
				}

				if(Escola::Instance()->searchTurma(NID)==NULL){
					Additions::clearConsole();
					std::cout << "A class with that ID (" << NID << ") seems to have been deleted from the database!\n";
					std::cout << "Please try again...\n\n";
					searchClassInfo();
					return;

				}
				Additions::clearConsole();
				changeClassInfo(NID);


}

void moveClassStudent(int IDTurma, int IDAluno){

	string class_str;
	int nclass;

	std::cout << "\n\nOther classes are:\n";
	vector<Turma *> TT= Escola::Instance()->getAllClasses();
	if (TT.size() == 0){
		std::cout << "Error: there are no other classes...\nCreate other classes first...\n\n";
		std::cout << "Press Return to continue...";
		Additions::waitForReturn();
		Additions::clearConsole();
		anotherChangeClass(IDTurma);
		return;
	}
	for(int j=0; j < TT.size();j++){
		if(TT[j]->getID()!=IDTurma)
			std::cout << TT[j]->imprimeDados() << std::endl;
	}


	do{
		std::cout << "\nPlease select the class you want to move the student to:\n\n";
		class_str= Additions::getline();

		if(Additions::gotESC(class_str)){
			Additions::clearConsole();
			changeClassInfo(IDTurma);
			break;
		}
		if(atoi(class_str.c_str()))
			nclass=atoi(class_str.c_str());

	}while(!Additions::checkForOnlyNumeric(class_str));

	bool found=false;

	for(int i=0; i < TT.size(); i++){
		if(TT[i]->getID()==nclass)
			found=true;
	}

	if(!found){
		Additions::clearConsole();
		std::cout << "\nError: class with the ID (" << nclass << ") doesn't exist or is already the class the student is in!\n\n";
		moveClassStudent(IDTurma,IDAluno);
		return;
	}

	Escola::Instance()->delAlunoTurma(Escola::Instance()->searchAluno(IDAluno));

	Escola::Instance()->searchTurma(nclass)->addAluno(Escola::Instance()->searchAluno(IDAluno));

	std::cout << "\n\nSuccess!\n";
	anotherChangeClass(IDTurma);
}

void changeClassInfo(int IDTurma){

	int opc,nano,ndir, nclass;
	vector<int> IDs;
	int pos=-1;
	string ano,dir, class_str;

	bool found=false;


	std::cout << "Class " << IDTurma << std::endl << std::endl;
	std::cout << "What do you want to do?\n\n";
	std::cout << "(1) Change year\n";
	std::cout << "(2) Configure lessons\n";
	std::cout << "(3) Change director\n";
	std::cout << "(4) Move student from class";
	if(Escola::Instance()->searchTurma(IDTurma)->getAlunosTurma().size()==0)
		std::cout << " (there are no students in this class)\n";
	else std::cout << std::endl;
	std::cout << "(5) Show full information\n";

	std::cout << "\nPlease choose an option... \n";

	opc=_getch();


	bool should_break=false;

	switch (opc){

	case (baseASCIIn+1):
		do{
			std::cout << "\nNew Year: (8 to 12) ";
			ano= Additions::getline();

			if(Additions::gotESC(ano)){
				Additions::clearConsole();
				changeClassInfo(IDTurma);
				break;
			}
			if(atoi(ano.c_str()))
				nano=atoi(ano.c_str());

		}while(!Additions::checkForOnlyNumeric(ano) && nano!=8 && nano!=9 && nano!=10 && nano!=11  && nano!=12);

		Escola::Instance()->searchTurma(IDTurma)->setAno(nano);

		std::cout << "\n\nSuccess!\n";
		anotherChangeClass(IDTurma);


		break;

	case (baseASCIIn+2):
			Additions::clearConsole();
			configLessons(IDTurma);
			break;

	case (baseASCIIn+3):

		Additions::clearConsole();

		if(Escola::Instance()->searchTurma(IDTurma)->getDiretorTurma()==NULL){
			std::cout << "\nThere is no director for this class...\n\n";
			for(int i=0; i < Escola::Instance()->getAllProf().size(); i++ ){
				std::cout << Escola::Instance()->getAllProf()[i]->imprimeDados() << std::endl;
			}
		}
		else{
			std::cout << "\nCurrent diretor is: " << Escola::Instance()->searchTurma(IDTurma)->getDiretorTurma()->imprimeDados() << "\n\n";

			for(int i=0; i < Escola::Instance()->getAllProf().size(); i++ ){
			if (Escola::Instance()->getAllProf()[i]->getID()!=Escola::Instance()->searchTurma(IDTurma)->getDiretorTurma()->getID())
				std::cout << Escola::Instance()->getAllProf()[i]->imprimeDados() << std::endl;
			}
		}

		do{
			std::cout << "\nPlease select one of these teachers to be the new director... ";
			dir= Additions::getline();

			if(Additions::gotESC(dir)){
				Additions::clearConsole();
				changeClassInfo(IDTurma);
				break;
			}
			if(atoi(dir.c_str()))
				ndir=atoi(dir.c_str());

		}while(!Additions::checkForOnlyNumeric(dir));


		if(Escola::Instance()->searchProf(ndir)==NULL)
			found=true;


		if(found){
			Additions::clearConsole();
			std::cout << "\nError: one teacher with the ID (" << ndir << ") doesn't exist or is already director of the class!\n\n";
			changeClassInfo(IDTurma);
			break;
		}

		IDs=Escola::Instance()->TransferDiretorSchedule(Escola::Instance()->searchTurma(IDTurma)->getDiretorTurma(),Escola::Instance()->searchProf(ndir),Escola::Instance()->searchTurma(IDTurma));
		if(IDs.size()==0)
			Escola::Instance()->searchTurma(IDTurma)->setDiretor(Escola::Instance()->searchProf(ndir));

		else{
			std::cout << "\n\n" <<IDs.size() << " schedules need changing!\n";
			std::cout << "Press Return to continue...";
			Additions::waitForReturn();
			Additions::clearConsole();
			for(int i=0; i < IDs.size();i++)
				Escola::Instance()->delHorario(Escola::Instance()->getHorario(IDs[i]));
			setDirectorSchedule(ndir,IDTurma,IDs.size());

		}

		anotherChangeClass(IDTurma);
		break;


	case (baseASCIIn+4):

				Additions::clearConsole();
			if(Escola::Instance()->searchTurma(IDTurma)->getAlunosTurma().size()==0){

				std::cout << "Error: No students in the class... Add students first to move from this class...\n\n";
				changeClassInfo(IDTurma);
				break;
			}

			std::cout << "Current students in class are:\n";
			//vector<Aluno*> A =Escola::Instance()->searchTurma(IDTurma)->getAlunosTurma();

			for(int i=0; i < Escola::Instance()->searchTurma(IDTurma)->getAlunosTurma().size(); i++){
				std::cout << Escola::Instance()->searchTurma(IDTurma)->getAlunosTurma()[i]->imprimeDados() << std::endl;
			}

			do{
				std::cout << "\nPlease select one of these students to move them to another class...";
				dir= Additions::getline();

				if(Additions::gotESC(dir)){
					Additions::clearConsole();
					changeClassInfo(IDTurma);
					break;
				}
				if(atoi(dir.c_str()))
					ndir=atoi(dir.c_str());

			}while(!Additions::checkForOnlyNumeric(dir));

			found=false;

			for(int i=0; i < Escola::Instance()->searchTurma(IDTurma)->getAlunosTurma().size(); i++){
				if(Escola::Instance()->searchTurma(IDTurma)->getAlunosTurma()[i]->getID()==ndir)
					found=true;
			}

			if(!found){
				Additions::clearConsole();
				std::cout << "\nError: one student with the ID (" << ndir << ") doesn't exist or doesn't belong in this class!\n\n";
				changeClassInfo(IDTurma);
				break;

			}

			moveClassStudent(IDTurma,ndir);

			break;

	case(baseASCIIn+5):

			Additions::clearConsole();
			std::cout << Escola::Instance()->searchTurma(IDTurma)->imprimeDados() << std::endl;
			std::cout << std::endl << std::endl;
			changeClassInfo(IDTurma);
			break;

	case escKey :
					Additions::clearConsole();
					searchClassInfo();
					break;

	default:
					Additions::clearConsole();
					changeClassInfo(IDTurma);
					break;

	}


}

void classesManagementMenu(){

	int opc;

	std::cout << "What do you want to do?" << std::endl << std::endl;
	std::cout << "(1) Add a Class" << std::endl;
	std::cout << "(2) Change Class Information" << std::endl;

	opc=_getch();

	switch (opc){
	case (baseASCIIn+1):
			Additions::clearConsole();
			addClass();
			break;

	case (baseASCIIn+2):
			Additions::clearConsole();
			searchClassInfo();
			break;

	case escKey:
			Additions::clearConsole();
			mainMenu();
			break;

	default:

			Additions::clearConsole();
			classesManagementMenu();
			break;
	}

}

void addCourseSchedules(Disciplina *d1){

	Horario * h1;
	int opc, opt, h,n,ID;
	string nhour,nday, nID;
	int disciplina_ID=200000;
	string nome,apelido,email,contato_str,disciplina;
	long contato=0;
	bool found1 = false;
	bool found2 = false;

	std::cout << "::SETTING COURSE " << d1->getNome() << " SCHEDULES::\n\n";
	std::cout << "You can't leave this function until you have successfully set 4 different \nschedules for all " << Escola::Instance()->getNTurmas() << " classes for " << d1->getNome() <<"\n";
	std::cout << "\nPress any key to continue...";

	opc=_getch();
	switch(opc){

	default:
		break;

	}

	Additions::clearConsole();
	std::cout << "Create a teacher for this new course (You can change this later)\n";
	std::cout << "You can press Esc while creating a new teacher to redo one!\n\n";



	std::cout << "NEW TEACHER\n";


	do{
		std::cout << "\nNome: ";
		nome= Additions::getline();

		if(Additions::gotESC(nome)){
			Additions::clearConsole();
			addCourseSchedules(d1);
			return;
		}

	}while(!Additions::checkForNumeric(nome));


	do{
		std::cout << "\nApelido: ";
		apelido= Additions::getline();

		if(Additions::gotESC(apelido)){
			Additions::clearConsole();
			addCourseSchedules(d1);
			return;
		}

	}while(!Additions::checkForNumeric(apelido));

	do{
		std::cout << "\nContato: ";
		contato_str=Additions::getline();

		if(Additions::gotESC(contato_str)){
			Additions::clearConsole();
			addCourseSchedules(d1);
			return;
		}

		if(atoi(contato_str.c_str()))
			contato=atoi(contato_str.c_str());

	}while(!Additions::checkForOnlyNumeric(contato_str));

	do{
		std::cout << "\nEmail: ";
		email=Additions::getline();

		if(Additions::gotESC(email)){
			Additions::clearConsole();
			addCourseSchedules(d1);
			return;
		}

	}while(!Additions::checkValidEmail(email));



	if(!Escola::Instance()->checkProfessor(nome,apelido)){
		Additions::clearConsole();
		std::cout << "There is already a teacher with that name! Try again...\n\n";
		addCourseSchedules(d1);
		return;

	}

	Professor *p1= new Professor(nome, apelido, contato, email);
	Escola::Instance()->addProfessor(p1);
	d1->addProfessor(p1);

	std::cout << "\n\nSuccess!\nDo you want to add another teacher? (y/n) ";
	if(Escola::Instance()->getNTurmas()>1)
		std::cout <<"(Recommended because of schedule conflict) ";
	opt=_getch();
	switch(opt){
				case 89:
				case 121:
					Additions::clearConsole();
					addCourseSchedules(d1);
					break;


				case 78:
				case 110:
					break;

	}




	for(int i=0; i < Escola::Instance()->getNTurmas();i++){
			Additions::clearConsole();
			n=0;
			std::cout << "::SETTING CLASS " << Escola::Instance()->getAllClasses()[i]->getID() << " SCHEDULE::\n\n";
			std::cout << "::" << d1->getNome()<<"::\n\n";
			std::cout << "Create 4 schedules for four different days...\n";
			std::cout << "Possible choices:\nDays: 'Monday' 'Tuesday' 'Wednesday' 'Thursday' 'Friday'\nHours: '9' '10' '11' '14 '15' '16'";
			std::cout << "\nTeachers lecturing:\n";
			for(int k=0; k <d1->getProfessoresDisc().size(); k++){
				std::cout << d1->getProfessoresDisc()[k]->imprimeDados() << std::endl;
			}

			do{

				std::cout << "\n\nSchedule "<< n+1 << std::endl;
				do{
					std::cout << "\nDay: ";
					nday= Additions::getline();

				}while(nday != "Monday" && nday != "Tuesday" && nday !="Wednesday" && nday != "Thursday" && nday != "Friday");

				do{
					std::cout << "\nHour: ";
					nhour= Additions::getline();

					if(atoi(nhour.c_str()))
					h=atoi(nhour.c_str());

				}while(h!=9 && h!=10 && h!=11 && h!=14 && h!=15 && h!=16);

				do{
					do{
						std::cout << "\nTeacher: (ID) ";
						nID= Additions::getline();


					}while(!Additions::checkForOnlyNumeric(nID));


					if(atoi(nID.c_str()))
						ID=atoi(nID.c_str());

				}while(Escola::Instance()->searchProf(ID)==NULL);

				for(int k=0; k <d1->getProfessoresDisc().size(); k++){
					if(d1->getProfessoresDisc()[k]->getID()==ID){
						found1=true;
						break;
					}
				}

				if(!found1)
					std::cout << "\nThe teacher you selected doesn't teach this class...\nPlease try again...";

				if(found1){
					for(int j=0; j < Escola::Instance()->getAllClasses()[i]->getHorarioTurma().size();j++){
						if(Escola::Instance()->Escola::Instance()->getAllClasses()[i]->getHorarioTurma()[j]->getDia() == nday &&  Escola::Instance()->Escola::Instance()->getAllClasses()[i]->getHorarioTurma()[j]->getHora() == h){
							std::cout << "\nThis class already has a schedule on that time...\nPlease try again...";
							found2=true;
						}
					}
					if(!found2){
						h1 = new Horario(nday,h);
						h1->setProfessor(Escola::Instance()->searchProf(ID));
						h1->setDisciplina(d1);
						if(Escola::Instance()->addLesson(h1,Escola::Instance()->getAllClasses()[i])){
							std::cout << "\nAdded with success!";
							n++;
						}
						else
							std::cout << "\nError: teacher's schedule conflict or course on the same day...";


					}


				}

				found1=false;
				found2=false;

				}while(n<4);

		}

}

void addCourse(){

	int opt;
	string nome;
	bool should_return=false;

	if(Escola::Instance()->getNDisciplinas()>=7){
		std::cout << "Error: the maximum number of courses in this school was reached\n\n";
		std::cout << "Press any key to continue...";
		opt=_getch();

		switch (opt){
		default:
			Additions::clearConsole();
			classesManagementMenu();
			should_return=true;
			break;
		}
	}

	if(should_return)
		return;

	std::cout << "NEW COURSE\n";


	do{
		std::cout << "\nNome: ";
		nome= Additions::getline();

		if(Additions::gotESC(nome)){
			Additions::clearConsole();
			coursesManagementMenu();
			return;
		}

	}while(!Additions::checkValidDisciplina(nome));

	Disciplina *d1 = new Disciplina ( nome);

	while(!Escola::Instance()->addDisciplina(d1)){
		std::cout << "\nError: a course with that name already exists! Try again... \n";
		do{
			std::cout << "\nNome: ";
			nome= Additions::getline();

			if(Additions::gotESC(nome)){
				Additions::clearConsole();
				coursesManagementMenu();
				return;
			}

		}while(!Additions::checkValidDisciplina(nome));
	}

	if(Escola::Instance()->getNTurmas()>0){
		Additions::clearConsole();
		addCourseSchedules(d1);
	}
	std::cout << "\nSuccess!\n\n";
	std::cout << "Press Return to continue... ";
	Additions::waitForReturn();
	Additions::clearConsole();
	coursesManagementMenu();




}

void searchCoursesInfo(){

		string nome , Ano_str , ID_str, IDProf_str;
		unsigned int ID, NID;
		int opc;
		string opt,str,str1;

		std::cout << "Search courses by..." << std::endl;
		std::cout << " (1) Name " << std::endl;
		std::cout << " (2) ID " << std::endl;
		std::cout << " (3) Professores ";
		if(Escola::Instance()->getNProfessores()==0)
			std::cout << "\n(there are no teachers in the school... Create teachers first...)";

		std::cout << "\n\nPlease choose an option...";

		bool should_finish=false;

		opc=_getch();

		switch (opc){

		case (baseASCIIn+1):
					Additions::clearConsole();
					std::cout << "\nName: ";
					nome=Additions::getline();

					if(Additions::gotESC(nome)){
						Additions::clearConsole();
						searchCoursesInfo();
						should_finish=true;
						break;
					}
					if(!Escola::Instance()->searchDisciplinaNome(nome)){
						Additions::clearConsole();
						std::cout << "Your search got no results! Try again...";
						should_finish=true;
						searchCoursesInfo();
					}

					break;

		case (baseASCIIn+2):


					do {
						Additions::clearConsole();
						std::cout << "ID: (Between 1 and " << Disciplina::getIDmax()-1 << ") ";
						str=Additions::getline();

						if(Additions::gotESC(str)){
							Additions::clearConsole();
							searchCoursesInfo();
							should_finish=true;
							break;
						}
					}while(!atoi(str.c_str()));

					ID=atoi(str.c_str());

					if(Escola::Instance()->searchDisciplina(ID)==NULL){
						Additions::clearConsole();
						std::cout << "There is no course with the ID (" << ID << ")\n\n Press Return to continue... \n";
						Additions::waitForReturn();
						Additions::clearConsole();
						searchCoursesInfo();
						should_finish=true;
						break;
					}
					changeCourseInfo(ID);
					should_finish=true;
					break;

			case (baseASCIIn+3):

					if(Escola::Instance()->getNProfessores()==0){
						Additions::clearConsole();
						searchCoursesInfo();
						should_finish=true;
						break;
					}

					Additions::clearConsole();
						std::cout << "Teachers by course: \n\n";

						//vector<Disciplina *> D = Escola::Instance()->getAllCourses();

						for(int i=0; i < Escola::Instance()->getAllCourses().size(); i++){
							//vector<Professor *> P = Escola::Instance()->getAllCourses()[i]->getProfessoresDisc();
							std::cout << Escola::Instance()->getAllCourses()[i]->getNome() << "[" << Escola::Instance()->getAllCourses()[i]->getID() << "]:\n";
							if(Escola::Instance()->getAllCourses()[i]->getProfessoresDisc().size()==0)
								std::cout << "There are currently no teachers lecturing that course!\n\n";
							else
								for(int j=0; j < Escola::Instance()->getAllCourses()[i]->getProfessoresDisc().size();j++){
									std::cout << std::endl << Escola::Instance()->getAllCourses()[i]->getProfessoresDisc()[j]->imprimeDados() << std::endl;

								}
							std::cout << std::endl;

						}
					break;

			case escKey:
					Additions::clearConsole();
					coursesManagementMenu();
					break;

			default:
					Additions::clearConsole();
					searchCoursesInfo();
					break;


			}


		if(should_finish)
			return;

		std::cout << "\n\nChoose the ID of the course you want to change: ";
		opt=Additions::getline();

		if(Additions::gotESC(opt)){
			Additions::clearConsole();
			coursesManagementMenu();
			return;
		}
		if (atoi(opt.c_str()))
			NID=atoi(opt.c_str());

		while(!atoi(opt.c_str()) && (NID < 0 || NID >= Disciplina::getIDmax())){
			std::cout << "\nPlease choose a correct ID value: ";
			opt=Additions::getline();

			if(Additions::gotESC(opt)){
				Additions::clearConsole();
				coursesManagementMenu();
				return;
			}
			if (atoi(opt.c_str()))
				NID=atoi(opt.c_str());
		}

		if(Escola::Instance()->searchDisciplina(NID)==NULL){
			Additions::clearConsole();
			std::cout << "\nA course with that ID (" << NID << ") seems to have been deleted from the database!\n";
			std::cout << "Please try again!";
			searchCoursesInfo();
			return;

		}



		changeCourseInfo(NID);

}

void anotherChangeCourse(int IDCourse){
	std::cout << "\nDo you want to make any more changes to that course? (y/n)\n";
	int opt=_getch();

	switch(opt){
	case 89:
	case 121:
		Additions::clearConsole();
		changeCourseInfo(IDCourse);
		break;


	case 78:
	case 110:
		Additions::clearConsole();
		coursesManagementMenu();
		break;

	default:
		std::cout << "Invalid option, try again!\n";
		anotherChangeCourse(IDCourse);
	}
}

void assignTeacher(int IDCourse){

	vector<Professor *> profsEsc=Escola::Instance()->getAllProf();
	string str,opc;
	int IDProf,IDNCourse;

	std::cout << "Which teacher do you want to assign to another course?\n\n";
	for(int i=0; i < profsEsc.size(); i++){
		if(Escola::Instance()->searchDisciplina(IDCourse)->isProf(profsEsc[i]))
			std::cout << profsEsc[i]->imprimeDados() << std::endl;
	}
	do{
		std::cout << "\nChoose a teacher's ID: ";
		str=Additions::getline();

		if(Additions::gotESC(str)){
			Additions::clearConsole();
			courseChange(IDCourse);
			return;
		}
	}while(!atoi(str.c_str()));

	IDProf=atoi(str.c_str());

	if(Escola::Instance()->searchProf(IDProf)==NULL){
		assignTeacher(IDCourse);
		return;
	}

	if(!Escola::Instance()->searchDisciplina(IDCourse)->isProf(Escola::Instance()->searchProf(IDProf))){
		Additions::clearConsole();
		std::cout << "\nError: the teacher with the ID (" << IDProf << ") is not currently lecturing this course...\nPlease try again...\n\n";
		assignTeacher(IDCourse);
		return;
	}
	//Escola::Instance()->searchDisciplina(IDCourse)->delProfessor(Escola::Instance()->searchProf(IDProf));

	if(Escola::Instance()->searchDisciplina(IDCourse)->getProfessoresDisc().size()==1){
		Additions::clearConsole();
		std::cout << "\nError: that course "<< IDCourse << " has only one teacher...\nPlease try again...\n\n";
		courseChange(IDCourse);
		return;
	}

	do{
		do{
			Additions::clearConsole();
			std::cout << "\nWhat course do you want to assign the teacher (" << IDProf << ") to: (Choose one) \n\n";

			std::cout << Escola::Instance()->getDisciplinas() << std::endl;
			opc=Additions::getline();

			if(Additions::gotESC(opc)){
				Additions::clearConsole();
				assignTeacher(IDCourse);
				return;
			}

		}while(!atoi(opc.c_str()));

		IDNCourse=atoi(opc.c_str());

		if(IDNCourse==IDCourse){
			std::cout << "\n\nPlease choose a different course ID than the one you are changing (" << IDCourse << ")\n";
		}

	}while(Escola::Instance()->searchDisciplina(IDNCourse)==NULL || IDNCourse==IDCourse);

	Escola::Instance()->searchDisciplina(IDCourse)->delProfessor(Escola::Instance()->searchProf(IDProf));

	Escola::Instance()->searchDisciplina(IDNCourse)->addProfessor(Escola::Instance()->searchProf(IDProf));

	std::cout << "\n\nSuccess!!\n\n";
	std::cout << "Press Return to continue... \n";
	Additions::waitForReturn();
	anotherChangeCourse(IDCourse);
}

void addTeacherCourse(int IDCourse){

	vector<Professor *> profsEsc=Escola::Instance()->getAllProf();
	int opc, ID;
	string str;

	if(profsEsc.size()==0){

		std::cout << "Error: there are no teachers in this school! Add a teacher first...\n\n";
		std::cout << "Press any key to continue...";
		opc=_getch();
		switch (opc){
		default:
			Additions::clearConsole();
			courseChange(IDCourse);
			return;
		}
	}
	do{
		std::cout << "Which teacher do you want to add?\n\n";
		for(int i=0; i < profsEsc.size(); i++){
			if(Escola::Instance()->searchDisciplina(IDCourse)->isProf(profsEsc[i]))
				std::cout << profsEsc[i]->imprimeDados() << " (Already lecturing this course)\n";
			else
				std::cout << profsEsc[i]->imprimeDados() << "\n";
		}
		std::cout << "\nChoose a teacher's ID to add: ";

		str=Additions::getline();

		if(Additions::gotESC(str)){
			Additions::clearConsole();
			searchCoursesInfo();
			return;
		}
	}while(!atoi(str.c_str()));

	ID=atoi(str.c_str());

	if(Escola::Instance()->searchProf(ID)==NULL){
		addTeacherCourse(IDCourse);
		return;
	}

	if(Escola::Instance()->searchDisciplina(IDCourse)->isProf(Escola::Instance()->searchProf(ID))){

		Additions::clearConsole();
		std::cout << "Error: the teacher with that ID (" << ID << ") is already lecturing the course!\n";
		addTeacherCourse(IDCourse);
		return;
	}

	Escola::Instance()->getDisciplinaProf(Escola::Instance()->searchProf(ID))->delProfessor(Escola::Instance()->searchProf(ID));

	Escola::Instance()->searchDisciplina(IDCourse)->addProfessor(Escola::Instance()->searchProf(ID));

	std::cout << "\n\nSuccess!!\n\n";
	std::cout << "Press Return to continue... \n";
	Additions::waitForReturn();
	anotherChangeCourse(IDCourse);
}

void courseChange(int IDCourse){

		Escola::Instance()->searchDisciplina(IDCourse)->imprimeDados();
		int opc,opt;
		std::cout << "\n\nWhat do you want to do?\n\n";
		std::cout << "(1) Add a teacher (Currently there are " << Escola::Instance()->getNProfessores() << " teachers)\n";
		std::cout << "(2) Assign one teacher to another course ";
		if(Escola::Instance()->getNDisciplinas()==1)
			std::cout<< "(there are no other courses)\n";
		else std::cout << "\n";

		std::cout << "\nPlease choose an option... \n";
		opc=_getch();

		switch (opc){
		case (baseASCIIn+1):
				Additions::clearConsole();
				addTeacherCourse(IDCourse);
				break;

		case (baseASCIIn+2):
				if(Escola::Instance()->getNDisciplinas()==1){
					Additions::clearConsole();
					std::cout << "Error: impossible to do that when there is only this course! Create another course first!\n";
					std::cout << "\nPress Esc to create another course...\n";
					std::cout << "Press another key to go back to the previous menu...";
					opt=_getch();
					switch(opt){
					case escKey:
						Additions::clearConsole();
						addCourse();
						break;
					default:
						courseChange(IDCourse);
						break;
					}
				}
				else{
					Additions::clearConsole();
					assignTeacher(IDCourse);
				}
				break;

		case escKey:

				Additions::clearConsole();
				changeCourseInfo(IDCourse);
				break;

		default :
			courseChange(IDCourse);
			break;
		}

}

void changeCourseInfo(int IDCourse){

	int opc;
	string nnome,napelido, nturma, ncontato, nemail;


	std::cout << "\n\nWhat do you want to do?\n\n";
	std::cout << "(1) Change name\n";
	std::cout << "(2) Show information\n";
	std::cout << "(3) Change teachers\n";

	std::cout << "\nPlease choose an option... \n";
	opc=_getch();

	bool should_break=false;

	switch (opc){

		case (baseASCIIn+1):
				do{
					std::cout << "\nNew name: ";
					nnome= Additions::getline();

					if(Additions::gotESC(nnome)){
						Additions::clearConsole();
						changeCourseInfo(IDCourse);
						should_break=true;
					}

				}while(atoi(nnome.c_str()));

				if (should_break)
					break;

				Escola::Instance()->searchDisciplina(IDCourse)->setNome(nnome);

				std::cout << "\nSuccess!!\n\n";
				anotherChangeCourse(IDCourse);

				break;

		case (baseASCIIn+2):
				Additions::clearConsole();
				std::cout << Escola::Instance()->searchDisciplina(IDCourse)->imprimeDados();
				changeCourseInfo(IDCourse);
				break;

		case (baseASCIIn+3):

				courseChange(IDCourse);
				break;

		case escKey :
				Additions::clearConsole();
				searchCoursesInfo();
				break;

		default:
				Additions::clearConsole();
				changeCourseInfo(IDCourse);
				break;


	}
}

void coursesManagementMenu(){

	int opc;

	std::cout << "What do you want to do?" << std::endl << std::endl;

	std::cout << "(1) Add a course (maximum 7 courses, currently " << Escola::Instance()->getNDisciplinas() << ") " << std::endl;
	std::cout << "(2) Change a course's information \n";

	std::cout << "\nPlease choose an option!\n";

	opc=_getch();

		switch (opc){
		case (baseASCIIn+1):
				Additions::clearConsole();
				addCourse();
				break;

		case (baseASCIIn+2):
				Additions::clearConsole();
				searchCoursesInfo();
				break;

		case escKey:
				Additions::clearConsole();
				mainMenu();
				break;

		default:

				Additions::clearConsole();
				coursesManagementMenu();
				break;

		}


}

void exitMenu(){

	string opc;
	std::cout << "AEDA PROJECT MADE BY:\n\nJOAO ALMEIDA\nJOAO RAMOS\n\n";
	std::cout << "Press ESC to exit program! ";
	opc=Additions::getline();
	if(Additions::gotESC(opc)){
		exit(0);
	}
}

void lists(){

	int opc;
	BST<Funcionarios *> func = 	Escola::Instance()->getAllFuncionarios();
	BSTItrIn<Funcionarios *> itr (func);
	HProfessor::iterator it;
	HProfessor exprofs = Escola::Instance()->getExProfessores();
	priority_queue<Livraria *> temp = Escola::Instance()->getLivrarias();


	std::cout << "Right now the school has ";
	std::cout << Escola::Instance()->getNProfessores() << " teachers, lecturing ";
	std::cout << Escola::Instance()->getNDisciplinas() << " courses to ";
	std::cout << Escola::Instance()->getNEstudantes() << " students in ";
	std::cout << Escola::Instance()->getNTurmas() << " classes, supervised by ";
	std::cout << Escola::Instance()->getNFuncionarios() << " assistants!\n\n";
	std::cout << "What list do you want to see?\n\n";
	std::cout << "(1) Students\n";
	std::cout << "(2) Teachers\n";
	std::cout << "(3) Ex-teachers\n";
	std::cout << "(4) Assistants\n";
	std::cout << "(5) Courses\n";
	std::cout << "(6) Classes\n";
	std::cout << "(7) Bookstores\n";


	opc=_getch();

	switch (opc){

	case (baseASCIIn+1):
		Additions::clearConsole();
		if(Escola::Instance()->getAllStudents().size()==0)
			std::cout << "There are no students in this school";

		for(int i=0; i< Escola::Instance()->getAllStudents().size();i++){
			std::cout << Escola::Instance()->getAllStudents()[i]->imprimeDados() << std::endl;
		}
		std::cout << "\n\nPress Return to continue...";
		Additions::waitForReturn();
		Additions::clearConsole();
		lists();
		break;

	case (baseASCIIn+2):
		Additions::clearConsole();
		if(Escola::Instance()->getAllProf().size()==0)
			std::cout << "There are no teachers in this school";

		for(int i=0; i < Escola::Instance()->getAllProf().size();i++){
			std::cout << Escola::Instance()->getAllProf()[i]->imprimeDados() << std::endl;
			if(Escola::Instance()->getHorarioProf(Escola::Instance()->getAllProf()[i]).size()!=0){
				std::cout <<"Schedule:\n";
				for(int j=0; j < Escola::Instance()->getHorarioProf(Escola::Instance()->getAllProf()[i]).size();j++){

					std::cout << Escola::Instance()->getHorarioProf(Escola::Instance()->getAllProf()[i])[j]->ImprimeDados() << std::endl;
				}
			}
			std::cout << "\n";
		}
		std::cout << "\n\nPress Return to continue...";
		Additions::waitForReturn();
		Additions::clearConsole();
		lists();
		break;

	case (baseASCIIn+3):

		Additions::clearConsole();

		for(it= exprofs.begin(); it != exprofs.end(); it++){
			std::cout << (*it)->imprimeDados() << std::endl;
		}

		std::cout << "\nPress Return to continue...";
		Additions::waitForReturn();
		Additions::clearConsole();
		lists();
		break;

	case (baseASCIIn+4):
		Additions::clearConsole();
		if(itr.isAtEnd())
			std::cout << "There are no assistants working in this school";

	while(!itr.isAtEnd()){
			std::cout << itr.retrieve()->imprimeDados() << std::endl << std::endl;
			itr.advance();
		}

		std::cout << "\nPress Return to continue...";
		Additions::waitForReturn();
		Additions::clearConsole();
		lists();
		break;

	case (baseASCIIn+5):
		Additions::clearConsole();
		if(Escola::Instance()->getAllCourses().size()==0)
			std::cout << "There are no courses in this school";
		for(int i=0; i< Escola::Instance()->getAllCourses().size();i++){
			std::cout << Escola::Instance()->getAllCourses()[i]->imprimeDados() << std::endl;
		}
		std::cout << "\n\nPress Return to continue...";
		Additions::waitForReturn();
		Additions::clearConsole();
		lists();
		break;

	case (baseASCIIn+6):
		Additions::clearConsole();
		if(Escola::Instance()->getAllClasses().size()==0)
			std::cout << "There are no classes in this school";
		for(int i=0; i< Escola::Instance()->getAllClasses().size();i++){
			std::cout << Escola::Instance()->getAllClasses()[i]->imprimeDados() << std::endl;
		}
		std::cout << "\n\nPress Return to continue...";
		Additions::waitForReturn();
		Additions::clearConsole();
		lists();
	break;

	case (baseASCIIn+7):

		Additions::clearConsole();
		while(!temp.empty()){
			std::cout << temp.top()->imprimeDados() << std::endl;
			temp.pop();
		}

		std::cout << "Press Return to continue...";
		Additions::waitForReturn();
		Additions::clearConsole();
		lists();
		break;

	case escKey:
		Additions::clearConsole();
		mainMenu();
		break;

	default:
		Additions::clearConsole();
		lists();
		break;

	}

}

void mainMenu(){

	int opc;


	std::cout << ":::::::::HIGH SCHOOL MANAGEMENT:::::::::\n";

	std::cout << std::endl << "(1) Students Management" << std::endl;
	std::cout << "(2) Teachers Management" << std::endl;
	std::cout << "(3) Classes Management " << std::endl;
	std::cout << "(4) Courses Management" << std::endl;
	std::cout << "(5) Assistants Management" << std::endl;
	std::cout << "(6) Bookstores Management" << std::endl;
	std::cout << "(7) School information" << std::endl << std::endl;
	std::cout << "Please choose an option!";

	opc=_getch();

	switch (opc){

	case (baseASCIIn+1):
		Additions::clearConsole();
		studentsManagementMenu();
		break;

	case (baseASCIIn+2):
		Additions::clearConsole();
		teachersManagementMenu();
		break;

	case (baseASCIIn+3):
		Additions::clearConsole();
		classesManagementMenu();
		break;

	case (baseASCIIn+4):
		Additions::clearConsole();
		coursesManagementMenu();
		break;

	case (baseASCIIn+5):
			Additions::clearConsole();
			AssistantsManagementMenu();
			break;

	case (baseASCIIn+6):
		Additions::clearConsole();
		BookstoresManagementMenu();
		break;
	case (baseASCIIn+7):
		Additions::clearConsole();
		lists();
		break;

	case escKey:
		Additions::clearConsole();
		exitMenu();
		break;

	default:
		Additions::clearConsole();
		mainMenu();
		break;

	}
}

void createObjects(){

	Disciplina *d1 = new Disciplina("Matematica");
	Disciplina *d2 = new Disciplina("Portugues");
	//Disciplina *d3 = new Disciplina("AEDA");
	Professor *p1 = new Professor("Katukii","Ramos",919929392,"j@ramos.iol.pt");
	Professor *p2 = new Professor("Netforum","Almeida",919675842,"j@ramos.com");
	Professor *p3 = new Professor("Pedro", "Castro",912345678,"castro@hotmail.com");
	Professor *p4 = new Professor("Joao", "Ramos",912345678,"ramos@hotmail.com");
	Professor *p5 = new Professor("Pedro", "Ramos",912345678,"ramos@hotmail.com");
	Professor *p6 = new Professor("Joao", "Almeida",912345678,"almeida@hotmail.com");
	Funcionarios *f1 = new Funcionarios("Joao", 912312123);
	Funcionarios *f2 = new Funcionarios("Katukii", 918654132);
	Horario *h1 = new Horario("Monday", 12);
	Horario *h2 = new Horario("Monday", 17);
	Horario *h3 = new Horario("Monday", 18);
	h1->setProfessor(p1);
	h2->setProfessor(p1);
	h3->setProfessor(p1);
	Turma *t1 = new Turma(8, p1);
	Horario *h4 = new Horario("Monday", 9);
	Horario *h5 = new Horario("Tuesday",9);
	Horario *h6 = new Horario("Wednesday", 9);
	Horario *h7 = new Horario("Thursday",9);
	Horario *h8 = new Horario("Monday", 10);
	Horario *h9 = new Horario("Tuesday", 10);
	Horario *h10 = new Horario("Wednesday", 10);
	Horario *h11 = new Horario("Thursday", 10);
	h4->setProfessor(p1);
	h4->setDisciplina(d1);
	h5->setProfessor(p1);
	h5->setDisciplina(d1);
	h6->setProfessor(p1);
	h6->setDisciplina(d1);
	h7->setProfessor(p1);
	h7->setDisciplina(d1);
	h8->setProfessor(p2);
	h8->setDisciplina(d2);
	h9->setProfessor(p2);
	h9->setDisciplina(d2);
	h10->setProfessor(p2);
	h10->setDisciplina(d2);
	h11->setProfessor(p2);
	h11->setDisciplina(d2);
	Escola::Instance()->addDirectorSchedule(h1,t1);
	Escola::Instance()->addDirectorSchedule(h2,t1);
	Escola::Instance()->addDirectorSchedule(h3,t1);
	Escola::Instance()->addLesson(h4,t1);
	Escola::Instance()->addLesson(h5,t1);
	Escola::Instance()->addLesson(h6,t1);
	Escola::Instance()->addLesson(h7,t1);
	Escola::Instance()->addLesson(h8,t1);
	Escola::Instance()->addLesson(h9,t1);
	Escola::Instance()->addLesson(h10,t1);
	Escola::Instance()->addLesson(h11,t1);
	Escola::Instance()->addTurma(t1);
	Escola::Instance()->addDisciplina(d1);
	Escola::Instance()->addDisciplina(d2);
	Escola::Instance()->addProfessor(p1);
	Escola::Instance()->addProfessor(p2);
	Escola::Instance()->addProfessor(p3);
	Escola::Instance()->addProfessor(p4);
	Escola::Instance()->addProfessor(p5);
	Escola::Instance()->addProfessor(p6);
	Escola::Instance()->addFuncionario(f1);
	Escola::Instance()->addFuncionario(f2);
	f1->addTurmaFunc(t1);
	f2->addTurmaFunc(t1);
	d1->addProfessor(p1);
	d2->addProfessor(p2);
	d1->addProfessor(p3);
	d1->addProfessor(p4);
	d2->addProfessor(p5);
	d2->addProfessor(p6);
	Escola::Instance()->delProfessor(p4);
	Escola::Instance()->delProfessor(p5);
	Escola::Instance()->delProfessor(p6);
	Aluno *a1 = new Aluno("Manuel", "Ramos", 912341232, "j@ramos");
	Aluno *a2 = new Aluno("Antonio", "Ramos", 912341232, "j@ramos");
	Aluno *a3 = new Aluno("Miguel", "Ramos", 912341232, "j@ramos");
	Aluno *a4 = new Aluno("Pedro", "Ramos", 912341232, "j@ramos");
	Aluno *a5 = new Aluno("Mano", "Ramos", 912341232, "j@ramos");
	Aluno *a6 = new Aluno("League", "Ramos", 912341232, "j@ramos");
	Aluno *a7 = new Aluno("Tiago", "Ramos", 912341232, "j@ramos");
	Aluno *a8 = new Aluno("Ivo", "Ramos", 912341232, "j@ramos");
	Aluno *a9 = new Aluno("Viana", "Ramos", 912341232, "j@ramos");
	Aluno *a10 = new Aluno("Lurdes", "Ramos", 912341232, "j@ramos");
	Aluno *a11 = new Aluno("Luis", "Ramos", 912341232, "j@ramos");
	Aluno *a12 = new Aluno("Vanessa", "Ramos", 912341232, "j@ramos");
	Aluno *a13 = new Aluno("Luisa", "Ramos", 912341232, "j@ramos");
	Aluno *a14 = new Aluno("Manuela", "Ramos", 912341232, "j@ramos");
	Aluno *a15 = new Aluno("Joana", "Ramos", 912341232, "j@ramos");
	Aluno *a16 = new Aluno("Ferrari", "Ramos", 912341232, "j@ramos");
	Escola::Instance()->addAluno(a1);
	Escola::Instance()->addAluno(a2);
	Escola::Instance()->addAluno(a3);
	Escola::Instance()->addAluno(a4);
	Escola::Instance()->addAluno(a5);
	Escola::Instance()->addAluno(a6);
	Escola::Instance()->addAluno(a7);
	Escola::Instance()->addAluno(a8);
	Escola::Instance()->addAluno(a9);
	Escola::Instance()->addAluno(a10);
	Escola::Instance()->addAluno(a11);
	Escola::Instance()->addAluno(a12);
	Escola::Instance()->addAluno(a13);
	Escola::Instance()->addAluno(a14);
	Escola::Instance()->addAluno(a15);
	Escola::Instance()->addAluno(a16);
	t1->addAluno(a1);
	t1->addAluno(a2);
	t1->addAluno(a3);
	t1->addAluno(a4);
	t1->addAluno(a5);
	t1->addAluno(a6);
	t1->addAluno(a7);
	t1->addAluno(a8);
	t1->addAluno(a9);
	t1->addAluno(a10);
	t1->addAluno(a11);
	t1->addAluno(a12);
	t1->addAluno(a13);
	t1->addAluno(a14);
	t1->addAluno(a15);
	t1->addAluno(a16);


	//TURMA 2

	h1 = new Horario("Tuesday", 12);
	h2 = new Horario("Monday", 17);
	h3 = new Horario("Wednesday", 18);
	h1->setProfessor(p3);
	h2->setProfessor(p3);
	h3->setProfessor(p3);
	Turma *t2 = new Turma(9, p3);
	h4 = new Horario("Monday", 11);
	h5 = new Horario("Tuesday", 11);
	h6 = new Horario("Wednesday", 11);
	h7 = new Horario("Thursday",11);
	Horario *h12 = new Horario("Monday", 15);
	Horario *h13 = new Horario("Tuesday", 15);
	Horario *h14 = new Horario("Wednesday", 15);
	Horario *h15 = new Horario("Thursday", 15);
	h4->setProfessor(p3);
	h4->setDisciplina(d1);
	h5->setProfessor(p3);
	h5->setDisciplina(d1);
	h6->setProfessor(p3);
	h6->setDisciplina(d1);
	h7->setProfessor(p3);
	h7->setDisciplina(d1);
	h12->setProfessor(p2);
	h12->setDisciplina(d2);
	h13->setProfessor(p2);
	h13->setDisciplina(d2);
	h14->setProfessor(p2);
	h14->setDisciplina(d2);
	h15->setProfessor(p2);
	h15->setDisciplina(d2);
	Escola::Instance()->addDirectorSchedule(h1,t2);
	Escola::Instance()->addDirectorSchedule(h2,t2);
	Escola::Instance()->addDirectorSchedule(h3,t2);
	Escola::Instance()->addLesson(h4,t2);
	Escola::Instance()->addLesson(h5,t2);
	Escola::Instance()->addLesson(h6,t2);
	Escola::Instance()->addLesson(h7,t2);
	Escola::Instance()->addLesson(h12,t2);
	Escola::Instance()->addLesson(h13,t2);
	Escola::Instance()->addLesson(h14,t2);
	Escola::Instance()->addLesson(h15,t2);
	Escola::Instance()->addTurma(t2);
	a1 = new Aluno("Manuel", "Viana", 914515489, "j@viana");
	a2 = new Aluno("Antonio", "Viana", 912341232, "j@viana");
	a3 = new Aluno("Miguel", "Viana", 978546898, "j@viana");
	a4 = new Aluno("Pedro", "Viana", 912341232, "j@viana");
	a5 = new Aluno("Mano", "Viana", 912341232, "j@viana");
	a6 = new Aluno("League", "Viana", 912341232, "j@viana");
	a7 = new Aluno("Tiago", "Viana", 912341232, "j@viana");
	a8 = new Aluno("Ivo", "Viana", 912341232, "j@viana");
	a9 = new Aluno("Viana", "Viana", 912341232, "j@viana");
	a10 = new Aluno("Lurdes", "Viana", 912341232, "j@viana");
	a11 = new Aluno("Luis", "Viana", 912341232, "j@viana");
	a12 = new Aluno("Vanessa", "Viana", 912341232, "j@viana");
	a13 = new Aluno("Luisa", "Viana", 912341232, "j@viana");
	a14 = new Aluno("Manuela", "Viana", 912341232, "j@viana");
	a15 = new Aluno("Joana", "Viana", 912341232, "j@viana");
	a16 = new Aluno("Ferrari", "Viana", 912341232, "j@viana");
	Aluno *a17 = new Aluno("Daniel", "Viana", 912341232, "j@viana");
	Aluno *a18 = new Aluno("Afonso", "Viana", 912341232, "j@viana");
	Escola::Instance()->addAluno(a1);
	Escola::Instance()->addAluno(a2);
	Escola::Instance()->addAluno(a3);
	Escola::Instance()->addAluno(a4);
	Escola::Instance()->addAluno(a5);
	Escola::Instance()->addAluno(a6);
	Escola::Instance()->addAluno(a7);
	Escola::Instance()->addAluno(a8);
	Escola::Instance()->addAluno(a9);
	Escola::Instance()->addAluno(a10);
	Escola::Instance()->addAluno(a11);
	Escola::Instance()->addAluno(a12);
	Escola::Instance()->addAluno(a13);
	Escola::Instance()->addAluno(a14);
	Escola::Instance()->addAluno(a15);
	Escola::Instance()->addAluno(a16);
	Escola::Instance()->addAluno(a17);
	Escola::Instance()->addAluno(a18);
	t2->addAluno(a1);
	t2->addAluno(a2);
	t2->addAluno(a3);
	t2->addAluno(a4);
	t2->addAluno(a5);
	t2->addAluno(a6);
	t2->addAluno(a7);
	t2->addAluno(a8);
	t2->addAluno(a9);
	t2->addAluno(a10);
	t2->addAluno(a11);
	t2->addAluno(a12);
	t2->addAluno(a13);
	t2->addAluno(a14);
	t2->addAluno(a15);
	t2->addAluno(a16);
	t2->addAluno(a17);
	t2->addAluno(a18);

	//Livraria 1
	Livraria *l1 = new Livraria("Papelaria Joaquim", 8);
	vector<string> especialidade;
	especialidade.push_back(d1->getNome());
	especialidade.push_back(d2->getNome());
	vector <int> escolaridade;
	escolaridade.push_back(8);
	l1->setEscolaridade(escolaridade);
	l1->setEspecialidade(especialidade);
	Escola::Instance()->addLivraria(l1);
	//Livraria 2
	Livraria *l2 = new Livraria("Papelaria Convivio", 5);
	especialidade.clear();
	especialidade.push_back(d2->getNome());
	escolaridade.clear();
	escolaridade.push_back(8);
	escolaridade.push_back(9);
	l2->setEscolaridade(escolaridade);
	l2->setEspecialidade(especialidade);
	Escola::Instance()->addLivraria(l2);
}

int main(){

	createObjects();



	mainMenu();

	return 0;
}
