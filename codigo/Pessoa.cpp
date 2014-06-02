#include "Pessoa.h"

Pessoa::Pessoa(string nome, string apelido, int contacto , string email) {
	this->ID=0;
	this->nome = nome;
	this->apelido = apelido;
	this->contacto = contacto;
	this->email = email;
}


	void Pessoa::setNome (string nome) {

		this->nome = nome;

	}


	void Pessoa::setApelido(string apelido) {

		this->apelido = apelido;
	}


	void Pessoa::setContacto(int contacto) {

		this->contacto = contacto;
	}

	void Pessoa::setEmail(string email)	{
		this->email = email;
	}


	const string Pessoa::getNome() {
		return nome;
	}


	const string Pessoa::getApelido() {
		return apelido;
	}


	const int Pessoa::getContacto() {
		return contacto;
	}


	const string Pessoa::getEmail() {
		return email;
	}

	string Pessoa::imprimeDados(){

		string S;
		stringstream ss;

		ss << "[" << ID << "] " << apelido << ", " << nome << " ; Contact: " << contacto << " ; Email: " << email;

		getline(ss, S);

		return S;
	}
