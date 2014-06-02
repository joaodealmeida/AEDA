#include <string>
#include <vector>
#include <iostream>
#include "Aluno.h"
#include "Escola.h"

Aluno::Aluno(string nome, string apelido, int contacto , string email) : Pessoa(nome , apelido , contacto , email) {

	this->ID=IDAluno;
	IDAluno++;
}

string Aluno::imprimeDados(){

	string returnS, appendS;
	stringstream ss;
	returnS.append(Pessoa::imprimeDados());
	ss << "; Class " << Escola::Instance()->getTurmaAluno(this)->getID() << "; Year " << Escola::Instance()->getTurmaAluno(this)->getAno();
	getline(ss , appendS);
	returnS.append(appendS);
	returnS.append("\n");

	return returnS;
}

int Aluno::IDAluno = 1;

const int Aluno::getID() {
	return ID;
}

const int Aluno::getID_max(){
	return IDAluno;

}
