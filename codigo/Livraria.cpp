/*
 * Livraria.cpp
 *
 *  Created on: 19/12/2013
 *      Author: João
 */

#include "Livraria.h"

int Livraria::IDL=1;

Livraria::Livraria(string denominacao,int localizacao) {
	this->denominacao=denominacao;
	this->localizacao=localizacao;
	this->ID=IDL;
	IDL++;
}

int Livraria::getID_max(){

	return IDL;
}

int Livraria::getID() const{
	return ID;
}

bool Livraria::operator<(const Livraria &l1){
	if (localizacao>l1.localizacao)
		return true;

	if(localizacao==l1.localizacao)
		return (denominacao< l1.denominacao);

	return false;
}
bool Livraria::operator==(const Livraria &l1){
	return denominacao==l1.denominacao;
}

void Livraria::setEspecialidade(vector<string> &v){
	this->especialidade=v;
}
void Livraria::setEscolaridade(vector<int> &v){
	this->escolaridade=v;
}
string Livraria::getDenominacao() const{
	return denominacao;
}
int Livraria::getLocalizacao() const{
	return localizacao;
}
vector <string> Livraria::getEspecialidade(){
	return especialidade;
}
vector <int> Livraria::getEscolaridade(){
	return escolaridade;
}

string Livraria::imprimeDados(){
	stringstream ss,xx;
	string anos;
	for(int i=0; i<escolaridade.size();i++){

		xx << escolaridade[i] <<" " ;
	}
	ss << "ID [" << ID << "]\n";
	ss << "Name: " << denominacao << "\n";
	ss << "Years: " << xx.str() << "\n";
	ss << "Courses: ";
	for(int j=0 ; j < especialidade.size(); j++){
		ss << especialidade[j] << " ";
	}
	ss << "\nDistance: " << localizacao << " Km\n";
	return ss.str();
}

bool Livraria::existeAno(int ano){

	for(int i=0; i<escolaridade.size();i++){
		if(escolaridade[i]==ano)
			return true;
	}

	return false;
}

bool Livraria::existeDisciplina(string nome){
	for(int i=0; i<especialidade.size();i++){
		if(especialidade[i]==nome)
			return true;
	}

	return false;
}

