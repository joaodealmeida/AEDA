#include <string>
#include <vector>
#include <iostream>
#include <string.h>
#include <sstream>
#include "Horario.h"
#include "Pessoa.h"
#include "Disciplina.h"
#include "Professor.h"

Horario::Horario (string dia , int h) {
	this->ID = IDHorario;
	this->dia = dia;
	this->h=h;
	d1=NULL;
	p1=NULL;
	IDHorario++;
}


bool Horario::setDia(string dia) {
	if(dia != "Monday" && dia != "Tuesday" && dia !="Wednesday" && dia != "Thursday" && dia != "Friday")
		return false;

	this->dia = dia;
	return true;
}


bool Horario::setHora(int h){
	if(h < 24 || h > -1) {
		this->h=h;
		return true;
	}
	return false;
}
void Horario::setDisciplina(Disciplina *d1){
	this->d1 = d1;
}

void Horario::setProfessor(Professor *p1){
	this->p1 = p1;
	}


const int Horario::getHora() {

	return h;
}


const string Horario::getDia() {
	return dia;
}

const int Horario::getID() {
	return ID;
}
int Horario::IDHorario = 1;

Disciplina* Horario::getDisciplinaAula() {
	return d1;
}
Professor* Horario::getProfessorAula() {
	return p1;
}

string Horario::ImprimeDados(){

	string S;
	stringstream ss;
	if(p1==NULL)
		ss << "Error\n";
	else if(d1==NULL)
		ss << "Attending time: ID [" << ID<< "]; Day " << dia << "; Hour " << h << "; Teacher: " << p1->getApelido() << ", "<< p1->getNome();
	else
		ss <<"ID [" << ID << "]; Day " << dia << "; Hour " << h << "; Teacher " <<  p1->getApelido() << ", "<< p1->getNome() << "; Course " << d1->getNome();

	getline(ss,S);
	return S;
}


