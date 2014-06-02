#include "Professor.h"

Professor::Professor(string nome , string apelido, int contacto , string email) : Pessoa (nome , apelido , contacto , email){
	this->ID=IDProf;
	IDProf++;
	this->ativo=true;
	this->disciplina="";
}

string Professor::imprimeDados(){

	string returnS;
	returnS.append(Pessoa::imprimeDados());
	returnS.append("\n");
	if(ativo)
		returnS.append("Teaching: yes;\n");
	else returnS.append("Teaching: no;\n");

	return returnS;
}


const int Professor::getID_max(){
	return IDProf;
}

const int Professor::getID() {
	return ID;
}

int Professor::IDProf = 1;

void Professor::setAtivo(){
	if(ativo)
		ativo=false;
	else
		ativo=true;
}

bool Professor::getAtivo() const{
	return ativo;
}

bool Professor::operator==(const Professor *p1){

	return nome==p1->nome && apelido == p1->apelido;
}

string Professor::getDisciplina() const{
	return disciplina;
}

void Professor::setDisciplina(string nome){
	this->disciplina=nome;
}
