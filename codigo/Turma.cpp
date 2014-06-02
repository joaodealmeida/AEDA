#include "Turma.h"

#include "Horario.h"
#include "Disciplina.h"
#include "Professor.h"
#include "Aluno.h"
#include "Escola.h"
#include "Funcionarios.h"


	int Turma::IDTurmas=1;

	Turma::Turma(int ano, Professor *diretor )
	{
		this->ano = ano;
		this->diretor = diretor;
		ID=IDTurmas;
		IDTurmas++;
	}


	bool Turma::addAluno(Aluno *a1) {

		string nomealuno=a1->getNome();

		for( int i=0 ; i < alunosturma.size() ; i++) {
			if(a1->getNome() == alunosturma[i]->getNome() && a1->getApelido() == alunosturma[i]->getApelido()){
				std::cout << "\nError: There is already a student with that name!\n";
				return false;
			}
		}

		alunosturma.push_back(a1);
		return true;
	}


	bool Turma::delAluno(Aluno *a1) {

		string nomealuno=a1->getNome();
		string apelidoaluno=a1->getApelido();

		for( int i=0 ; i < alunosturma.size() ; i++) {
				if(nomealuno == alunosturma[i]->getNome() && apelidoaluno==alunosturma[i]->getApelido()){
					alunosturma.erase(alunosturma.begin()+i);
					return true;
				}
		}
		return false;

	}

	bool Turma::addAula(Horario *h1) {
		//n pode haver aula de disciplina naquele dia
		//n pode ter aulas aquela hora

		bool ready1=true;
		for(int i=0; i < horarioturma.size(); i++){
			if((horarioturma[i]->getDia() == h1->getDia() && horarioturma[i]->getDisciplinaAula() ==h1->getDisciplinaAula())  || (horarioturma[i]->getDia() == h1->getDia() && horarioturma[i]->getHora() == h1->getHora())){
				std::cout << "There are already courses at this time!" << std::endl;
				ready1= false;
				break;
				}
			else
				ready1= true;

		}

		if(ready1){
			horarioturma.push_back(h1);
			return true;
		}
		else
			return false;
	}

	bool Turma::addDirectorSchedule(Horario *h1){

		bool ready1=true;
		for(int i=0; i < horarioturma.size(); i++){
			if(horarioturma[i]->getDia() == h1->getDia() && horarioturma[i]->getHora() == h1->getHora()){
				std::cout << "\nError: There is already an attending schedule at this time!" << std::endl;
				ready1= false;
				break;
				}
			else
				ready1= true;
		}


		if(ready1){
			horarioturma.push_back(h1);
			return true;
		}

		return false;
	}
	bool Turma::delAula(Horario *h1){
		bool found=false;
		for(int i=0; i < horarioturma.size() ; i++){
			if(horarioturma[i]->getID() == h1->getID()){
				horarioturma.erase(horarioturma.begin()+i);
				return true;
			}
		}
		return false;
	}

	void Turma::setDiretor(Professor *d1){
		this->diretor=d1;
	}


	int Turma::getIDMax(){
		return IDTurmas;
	}

	const int Turma::getID() {
		return ID;
	}


	const int Turma::getAno(){
		return ano;
	}


	Professor* Turma::getDiretorTurma() {
		return diretor;
	}

	vector<Horario* > Turma::getHorarioTurma() {
		return horarioturma;
	}
	vector<Horario* > Turma::getHorarioAtendTurma(){
		vector <Horario*> atendimentoturma;
		for(int i=0; i< horarioturma.size();i++){
			if(horarioturma[i]->getDisciplinaAula()==NULL && horarioturma[i]->getProfessorAula()->getID()==diretor->getID() )
				atendimentoturma.push_back(horarioturma[i]);
		}
		return atendimentoturma;
	}

	vector<Aluno *> Turma::getAlunosTurma(){
		return alunosturma;
	}

	string Turma::imprimeDados(){
		string S,appendS;
		stringstream t;
		vector<Funcionarios *> func = Escola::Instance()->searchFuncTurma(ID);

		t << "Class "  << ID << "; year: " << ano << "; number of students: " << alunosturma.size();
		if(diretor!=NULL)
			t << "; director: teacher " << diretor->getApelido() << ", " << diretor->getNome();

		getline(t, S);
		S.append("\n\n");
		t.clear();
		if(func.size()>0){
			t << "Assistants: ";
			for(int j=0; j < func.size(); j++){
				if(j>0){
				t << ", [" << func[j]->getID() << "]" << func[j]->getNome();
				}
				else{
					t << "[" << func[j]->getID() << "]" << func[j]->getNome();
				}
			}
			getline(t,appendS);
			S.append(appendS);
			t.clear();
			S.append("\n");
		}
		else{
			t << "Assistants: ";
			t << "not currently being supervised!";
			getline(t,appendS);
			S.append(appendS);
			t.clear();
			S.append("\n");
		}
		S.append("\nSchedules: \n");
		for(int i =0; i< horarioturma.size();i++){
			t << horarioturma[i]->ImprimeDados();
			getline(t,appendS);
			S.append(appendS);
			S.append("\n");
			t.clear();
		}

		return S;
	}


	void Turma::setAno(int ano){
		this->ano=ano;
	}


	bool Turma::searchHorario(int ID){

		for(int i=0; i < horarioturma.size();i++){
			if(horarioturma[i]->getID()==ID)
				return true;
		}

		return false;
	}


