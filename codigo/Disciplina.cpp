#include "Disciplina.h"

Disciplina::Disciplina(string nome) {
	this->ID = IDDisciplina;
	this->nome = nome;
	IDDisciplina++;

}
int Disciplina::IDDisciplina = 1;

bool Disciplina::setNome(string nome) {
	if(atoi(nome.c_str()))
		return false;

	this->nome = nome;
	return true;
}


string Disciplina::getNome() const{

	return nome;

}

const int Disciplina::getID() {
	return ID;
}

bool Disciplina::addProfessor(Professor *p1){

	string nomeprof = p1->getNome();

	for(int i=0; i < profdisc.size() ; i++){
		if (nomeprof == profdisc[i]->getNome() && p1->getApelido()==profdisc[i]->getApelido() ){
			std::cout << "\nError:That name already exists!\n";
			return false;
		}
	}

	profdisc.push_back(p1);
	return true;

}


bool Disciplina::delProfessor(Professor *p1){


	for(int i=0; i < profdisc.size() ; i++){
		if (profdisc[i]->getID()==p1->getID()){
			profdisc[i]->setNome(nome);
			profdisc.erase(profdisc.begin()+i);
			return true;
		}
	}

	return false;
}


string Disciplina::getNomeProfs() const{

	string profs;

	if(profdisc.size()==0)
		return "";

	for(int i=0; i< profdisc.size(); i++){

		profs.append(profdisc[i]->getNome());
		profs.append(" ");
		profs.append(profdisc[i]->getApelido());
		profs.append(";/n ");
	}

	return profs;
}

vector<Professor *> Disciplina::getProfessoresDisc() {
	return profdisc;
}

string Disciplina::imprimeDados(){

	string S;
	stringstream ss;
	int i;

	ss << "[ " << ID << "] " << nome;
	if (profdisc.size()!=0){
		ss << ", Teachers: ";
		for(i=0; i < profdisc.size(); i++){
			if(i==0)
				ss << "[" <<  profdisc[i]->getID() << "] " << profdisc[i]->getApelido() << ", " << profdisc[i]->getNome();
			else
				ss << "; " <<" [" <<  profdisc[i]->getID() << "] " << profdisc[i]->getApelido() << ", " << profdisc[i]->getNome();
		}
	}
	else{
		ss<< " (there are no teachers lecturing this class)";
	}
	getline(ss, S);

	return S;
}

int Disciplina::getIDmax(){
		return IDDisciplina;
}

bool Disciplina::isProf(Professor *p1) const{

	for (int i=0; i < profdisc.size(); i++){
		if(profdisc[i]==p1)
			return true;
	}

	return false;
}
