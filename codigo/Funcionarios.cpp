/*
 * Funcionarios.cpp
 *
 *  Created on: 09/12/2013
 *      Author: João
 */

#include "Funcionarios.h"
#include "Turma.h"

Funcionarios::Funcionarios(string nome){
	this->nome=nome;
	this->contato=0;
	this->ID=IDFunc;
	IDFunc++;
}
int Funcionarios::getID_max() {
	return IDFunc;
}
Funcionarios::Funcionarios(string nome, int contato) {
	this->nome=nome;
	this->contato=contato;
	this->ID=IDFunc;
	IDFunc++;
}

int Funcionarios::IDFunc = 1;

string Funcionarios::getNome() const{
	return nome;
}
int Funcionarios::getID() const{
	return ID;
}
int Funcionarios::getContato() const{
	return contato;
}
void Funcionarios::setNome(string nome){
	this->nome = nome;
}
void Funcionarios::setContato(int contacto){
	this->contato= contacto;
}
bool Funcionarios::addTurmaFunc(Turma *t1){
	for(int i=0; i<turmas.size();i++){
		if(turmas[i]->getID()== t1->getID()){
			return false;
		}
	}
	turmas.push_back(t1);
	return true;
}
bool Funcionarios::delTurmaFunc(int IDTurma){
	for(int i=0; i<turmas.size();i++){
		if(turmas[i]->getID()== IDTurma){
			turmas.erase(turmas.begin()+i);
			return true;
		}
	}
	return false;
}
vector <Turma*> Funcionarios::getTurmasFunc() const{
	return turmas;
}

string Funcionarios::imprimeDados () {
	string S,appendS;
	stringstream ss;
	ss << "[" << ID << "] " << "Name: " << nome <<  ", contact: " << contato;
	getline(ss, S);
	ss.clear();
	S.append("\nSupervising classes: ");
	if(turmas.size()>0){
		for(int i=0; i< turmas.size();i++){

			if(turmas.size()>1){
				ss << ", " <<  turmas[i]->getID();
			}
			else{
				ss << turmas[i]->getID();
			}
		}
		ss << ";";
		getline(ss,appendS);
		S.append(appendS);
	}
	else{
		S.append("not supervising any classes yet!\n");
	}

	return S;
}

bool Funcionarios::operator < (Funcionarios &f1){

	return nome < f1.getNome();
}

bool Funcionarios::operator ==(Funcionarios &f1){

	return nome == f1.getNome();
}
