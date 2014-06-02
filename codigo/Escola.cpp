#include "Escola.h"

#include "Pessoa.h"
#include "Disciplina.h"
#include "Aluno.h"
#include "Funcionarios.h"
#include "Livraria.h"

Escola *Escola::um_pInstance = NULL;

Escola* Escola::Instance() {
    if (!um_pInstance)
        um_pInstance = new Escola;

    return um_pInstance;
}


Escola::Escola(): funcionarios(new Funcionarios("",0)){}

bool Escola::addTurma(Turma *t1) {
	for (int i = 0 ; i< turmas.size() ; i++) {
		if(turmas[i]->getID() == t1->getID())
			return false;
		}
	turmas.push_back(t1);
	return true;
}


bool Escola::delTurma(Turma *t1) {
	for(int i = 0 ; i < turmas.size() ; i++) {
		if (t1->getID() == turmas[i]->getID()) {
			turmas.erase(turmas.begin()+i);
			return true;
		}

	}
	return false;
}


bool Escola::addDisciplina(Disciplina *d1){

	for (int i=0; i < disciplinas.size(); i++){
		if (d1->getNome() == disciplinas[i]->getNome())
			return false;
		}
	disciplinas.push_back(d1);
	return true;
}



bool Escola::delDisciplina(Disciplina *d1){

	bool found=false;
	for (int i=0; i < disciplinas.size(); i++){
			if (d1->getNome() == disciplinas[i]->getNome()){
				disciplinas.erase(disciplinas.begin()+i);
				found=true;
				break;
			}
	}
	if(found){
		for(int j=0; j < horarios.size(); j++)
			if(horarios[j]->getDisciplinaAula()->getID()==d1->getID()){
				horarios.erase(horarios.begin()+j);
				j--;
			}
		return true;
	}
	return false;
}

bool Escola::addAluno(Aluno *a1){
	int i;
	string nome=a1->getNome();
	string apelido=a1->getApelido();
	for (i=0; i < estudantesescola.size();i++){
		if (estudantesescola[i]->getNome()==nome && estudantesescola[i]->getApelido()==apelido){
			std::cout << "\nError:There is already a student with that name!\n";
			return false;
		}
	}
	estudantesescola.push_back(a1);
	return true;

}

void Escola::delAluno(Aluno *a1) {
	int i;
	string nome=a1->getNome();
	string apelido=a1->getApelido();

	for (i=0; i < estudantesescola.size(); i++){
			if (estudantesescola[i]->getNome()==nome && estudantesescola[i]->getApelido()==apelido)	{
				estudantesescola.erase(estudantesescola.begin()+i);
				break;
			}
	}
	delAlunoTurma(a1);


}

void Escola::delAlunoTurma(Aluno *a1){
	int j;

	for (j=0; j < turmas.size(); j++){
			if(turmas[j]->delAluno(a1))
				break;

	}
}
int Escola::getNTurmas() const{

	return turmas.size();
}

Turma* Escola::searchTurma(int ID){
	for(int i=0; i < turmas.size(); i++){
		if(turmas[i]->getID()==ID)
			return turmas[i];
	}

	return NULL;

}

int Escola::searchAlunos(string nome){

	std::cout << "\nSearch by name:\n";

	int i,n=0;

	for(i = 0; i < estudantesescola.size();i++ ){
		if(estudantesescola[i]->getNome()==nome){
			std::cout << estudantesescola[i]->imprimeDados() << std::endl;
			n++;
		}
	}

	return n;
}

int Escola::searchAlunos2(string apelido){

	std::cout << "\nSearch by surname:\n";

		int i,n=0;

		for(i = 0; i < estudantesescola.size();i++ ){
			if(estudantesescola[i]->getApelido()==apelido){
				std::cout << estudantesescola[i]->imprimeDados() << std::endl;
				n++;
			}
		}

		return n;

}

Aluno* Escola::searchAluno(unsigned int ID){

	if (ID < 0 || ID >= Aluno::getID_max()){
		Additions::clearConsole();
		std::cout << "Error: there is no student with that ID!\n";
	}

	else
		for (int i=0; i < estudantesescola.size() ; i++){
			if(estudantesescola[i]->getID()==ID)
				return estudantesescola[i];

		}
	return NULL;
}

string Escola::getDisciplinas() const{

	string returnS;
	for(int i=0;i < disciplinas.size();i++){
		if(i==0){
			returnS.append("[");
			returnS.append(Additions::convertToString(disciplinas[i]->getID()));
			returnS.append("] ");
			returnS.append(disciplinas[i]->getNome());

		}
		else{
			returnS.append("\n[");
			returnS.append(Additions::convertToString(disciplinas[i]->getID()));
			returnS.append("] ");
			returnS.append(disciplinas[i]->getNome());
		}

	}
	return returnS;
}

Disciplina* Escola::searchDisciplina(int ID){

	for(int i=0; i < disciplinas.size();i++){
		if (disciplinas[i]->getID()==ID)
			return disciplinas[i];
	}

	return NULL;
}

void Escola::addProfessor(Professor *p1){

	professoresescola.push_back(p1);

}
bool Escola::checkProfessor(string nome, string apelido){
	for(int i=0; i < professoresescola.size();i++){
			if (nome==professoresescola[i]->getNome() && apelido==professoresescola[i]->getApelido())
				return false;
		}
		return true;
}
Turma* Escola::getTurmaAluno (Aluno *a1){

	int i,j;
	vector< Aluno*> al;

	for(i=0; i < turmas.size(); i++){

		al=turmas[i]->getAlunosTurma();

		for(j=0; j < al.size(); j++){
			if(al[j]==a1){
				return turmas[i];
			}

		}
	}

	return NULL;
}

int Escola::getNEstudantes() const{
	return estudantesescola.size();
}
int Escola::getNProfessores() const{
	return professoresescola.size();
}
int Escola::getNDisciplinas()const{
	return disciplinas.size();
}

int Escola::searchProfs(string nome){

	std::cout << "\n\nSearch by name:\n";
	int i,n=0;

	for(i = 0; i < professoresescola.size();i++ ){
		if(professoresescola[i]->getNome()==nome){
			std::cout << professoresescola[i]->imprimeDados() << std::endl;
			n++;
		}
	}



	return n;
}
int Escola::searchProfs2(string apelido){

	std::cout << "\n\nSearch by surname:\n";

	int i,n=0;

	for(i = 0; i < professoresescola.size();i++ ){
		if(professoresescola[i]->getApelido() == apelido){
			std::cout << professoresescola[i]->imprimeDados() << std::endl;
			n++;
		}
	}

	return n;
}

Professor* Escola::searchProf(unsigned int ID){

	HProfessor exProfs = getExProfessores();
	HProfessor::iterator it;
	if (ID < 0 || ID >= Professor::getID_max()){
		return NULL;
	}

	for (int i=0; i < professoresescola.size() ; i++){
		if(professoresescola[i]->getID()==ID)
			return professoresescola[i];

	}

	for(it=exProfs.begin(); it != exProfs.end(); it++){
		if((*it)->getID()==ID)
			return (*it);
	}

	return NULL;
}

Disciplina* Escola::getDisciplinaProf(Professor* p1){

	int i,j;
	for (i=0; i < disciplinas.size(); i++){
		for(j=0; j < disciplinas[i]->getProfessoresDisc().size(); j++){
			if(disciplinas[i]->getProfessoresDisc()[j]==p1)
				return disciplinas[i];
		}
	}
	return NULL;
}

bool Escola::delProfessor(Professor *p1){

	if(p1->getAtivo()){
		for(int l=0; l < turmas.size() ; l++){
			if(turmas[l]->getDiretorTurma()->getID() == p1->getID())
				turmas[l]->setDiretor(NULL);
		}
		for(int i=0; i < professoresescola.size() ; i++){
			if(professoresescola[i]==p1){
				professoresescola.erase(professoresescola.begin()+i);
				break;
			}
		}

		exprofessores.insert(p1);
		p1->setAtivo();

		vector<Horario *> horarioProf = getHorarioProf(p1);

		for(int k=0; k < horarioProf.size(); k ++){
			delHorario(horarioProf[k]);
		}


		for(int j = 0 ; j < disciplinas.size(); j++){
			if(disciplinas[j]->getProfessoresDisc().size()==1)
				if(disciplinas[j]->getProfessoresDisc()[0]->getID()==p1->getID()){
					p1->setDisciplina(disciplinas[j]->getNome());
					disciplinas.erase(disciplinas.begin()+j);
					return true;
				}
			if(disciplinas[j]->delProfessor(p1))
				return true;
		}
	}
	else{
		HProfessor::iterator it ;
		for(it= exprofessores.begin(); it != exprofessores.end(); it++){
			if((*it)->getID()==p1->getID()){
				exprofessores.erase(it);
				return true;
			}
		}
	}

	return false;

}

vector <Professor*> Escola::getAllProf() {
	return professoresescola;
}

bool Escola::searchDisciplinaNome(string nome){

	int i;

	for (i=0; i < disciplinas.size(); i++){
		if(disciplinas[i]->getNome()==nome){
			std::cout << std::endl << disciplinas[i]->imprimeDados() << std::endl;
			return true;
		}
	}
	return false;
}

vector<Turma*> Escola::searchTurmasProf(int ID) {
	vector<Turma*> ReturnVec;
	for(int i=0; i< turmas.size(); i++){
		vector<Horario *> H =turmas[i]->getHorarioTurma();
		for(int j=0; j<H.size();j++){
			if(H[j]->getProfessorAula()->getID ()== ID){
				ReturnVec.push_back(turmas[i]);
				break;
			}
		}
	}

	return ReturnVec;
}

vector<Turma*> Escola::searchTurmas(int ano){
	vector<Turma*> ReturnVec;
	for(int i=0; i< turmas.size(); i++){
		if(turmas[i]->getAno() == ano)
			ReturnVec.push_back(turmas[i]);
	}

		return ReturnVec;

}

vector <Aluno*> Escola::getAllStudents(){
	return estudantesescola;
}

vector <Disciplina*> Escola::getAllCourses(){
	return disciplinas;
}

vector <Turma *> Escola::getAllClasses(){
	return turmas;
}

vector <Horario *> Escola::getHorarioProf(Professor* p1){

	vector<Horario *> returnVec;
	for(int i =0; i <horarios.size(); i++){
		if(horarios[i]->getProfessorAula()==p1)
			returnVec.push_back(horarios[i]);
	}

	return returnVec;
}

vector <Horario *> Escola::getHorarioAtend(Professor* p1){

	vector<Horario *> returnVec;
		for(int i =0; i <horarios.size(); i++){
			if(horarios[i]->getProfessorAula()->getID()==p1->getID() && horarios[i]->getDisciplinaAula()==NULL)
				returnVec.push_back(horarios[i]);
		}

	return returnVec;
}

bool Escola::addLesson(Horario *h1, Turma *t1){


	for(int i=0; i < horarios.size();i++){
		if(horarios[i]->getDisciplinaAula()!=NULL){
			if(horarios[i]->getProfessorAula()==h1->getProfessorAula() && horarios[i]->getDia()==h1->getDia()&& horarios[i]->getHora()==h1->getHora() )
				return false;
		}
	}

	if(!t1->addAula(h1))
		return false;

	horarios.push_back(h1);
	return true;

}

bool Escola::addDirectorSchedule (Horario *h1, Turma *t1){

	for(int i=0; i < horarios.size();i++)
		if(horarios[i]->getProfessorAula()==h1->getProfessorAula() && horarios[i]->getDia()==h1->getDia()&& horarios[i]->getHora()==h1->getHora() )
			return false;


	if(!t1->addDirectorSchedule(h1))
		return false;

	horarios.push_back(h1);
	return true;

}

Horario * Escola::getHorario(int ID){

	for(int i=0; i< horarios.size(); i++)
		if(horarios[i]->getID()==ID)
			return horarios[i];

	return NULL;
}

bool Escola::addAula (Horario *h1){
	for (int i = 0 ; i< horarios.size() ; i++) {
		if(horarios[i]->getID() == h1->getID())
			return false;
		}
	horarios.push_back(h1);
	return true;
}

vector<int> Escola::TransferDiretorSchedule(Professor *oldD, Professor *newD, Turma *t1){
	vector<int> n;

	if(oldD == NULL){
		Horario * h1 = new Horario("",0);
		n.push_back(h1->getID());
		return n;
	}
	vector<Horario *> atendimentoOld = t1->getHorarioAtendTurma();
	vector<Horario *> atendimentoNew = getHorarioAtend(newD);

	//verificar se é diretor
	//verificar se coincidem horarios
	//se não coincidirem, enviar horario para professor novo e alterar professor no Hatendimento da turma
	//se coincidirem, eliminar Hatendimento na turma e fazer horario atendimento para novo diretor e por tbm no HAtendimento da turma
	bool isdiretor=false;
	bool found=false;

	if(atendimentoNew.size()!=0)
		isdiretor=true;

	if(isdiretor){
		for(int i=0; i < atendimentoOld.size();i++){
			for(int j=0; j < atendimentoNew.size();j++){
				if(atendimentoOld[i]->getDia() == atendimentoNew[j]->getDia() &&  atendimentoOld[i]->getHora() == atendimentoNew[j]->getHora()){
					n.push_back(atendimentoOld[i]->getID());
					found=true;
					break;
				}
			}

			if(!found)
				t1->getHorarioAtendTurma()[i]->setProfessor(newD);

			found=false;


		}
	}

	else
		for(int h=0; h < atendimentoOld.size();h++)
				atendimentoOld[h]->setProfessor(newD);

	return n;

}

void Escola::delHorario(Horario *h1){


	for(int i=0; i < horarios.size() ; i++){
		if(horarios[i]->getID()==h1->getID())
			horarios.erase(horarios.begin()+i);
	}

	for(int j=0; j < turmas.size();j++){
		turmas[j]->delAula(h1);
	}

}

bool Escola::addFuncionario(Funcionarios *f1){
	BSTItrIn<Funcionarios *> itr(funcionarios);
	while(!itr.isAtEnd()){
		if(itr.retrieve()->getNome()==f1->getNome())
			return false;
		itr.advance();
	}

	funcionarios.insert(f1);
	return true;
}

bool Escola::delFuncionario(Funcionarios *f1){
	BSTItrIn<Funcionarios *> it(funcionarios);
	Funcionarios * f2 = funcionarios.find(f1);

	if(f2==NULL)
	return false;

	else funcionarios.remove(f1);
	return true;
}

BST <Funcionarios *> Escola::getAllFuncionarios() const{
	return funcionarios;
}

Funcionarios* Escola::searchFunc(int ID){
	BSTItrIn<Funcionarios *> itr(funcionarios);

	while(!itr.isAtEnd()){
		if(itr.retrieve()->getID()==ID)
			return itr.retrieve();
		itr.advance();
	}

	return NULL;
}

vector<Turma*> Escola::searchTurmasFunc(int IDFunc){

	BSTItrIn<Funcionarios *> itr(funcionarios);
	vector<Turma*> turmasFunc;

	while(!itr.isAtEnd()){
		if(itr.retrieve()->getID()==IDFunc){
			turmasFunc=itr.retrieve()->getTurmasFunc();
			break;
		}
		itr.advance();
	}

	return turmasFunc;
}

vector<Funcionarios *> Escola::searchFuncTurma(int IDTurma){
	BSTItrIn<Funcionarios *> itr(funcionarios);
	vector<Turma*> turmasFunc;
	vector<Funcionarios *> returnVec;

	while(!itr.isAtEnd()){
		turmasFunc=itr.retrieve()->getTurmasFunc();
		for(int i=0; i < turmasFunc.size(); i++){
			if(turmasFunc[i]->getID()==IDTurma){
				returnVec.push_back(itr.retrieve());
				break;
			}

		}
		itr.advance();
	}

	return returnVec;
}

Funcionarios * Escola::searchFunc(string nome){


	BSTItrIn<Funcionarios *> itr (funcionarios);

	while(!itr.isAtEnd()){
		if(itr.retrieve()->getNome()== nome)
			return itr.retrieve();
		itr.advance();
	}


	return NULL;

}

int Escola::getNFuncionarios() const{
	int n=0;
	BSTItrIn<Funcionarios *> itr(funcionarios);

	while(!itr.isAtEnd()){
		n++;
		itr.advance();
	}
	return n;
}

HProfessor Escola::getExProfessores() const{

	return exprofessores;

}

void Escola::delExProfessor(int IDProf){

}

bool Escola::addLivraria(Livraria *l1) {
	priority_queue <Livraria *> copia = livrarias;
	while(!copia.empty()){
		if(copia.top()==l1)
			return false;
		copia.pop();
	}
	livrarias.push(l1);
	return true;
}

void Escola::delLivraria(Livraria *l1){
	priority_queue <Livraria *> temp;
	while(!livrarias.empty()){
		if(livrarias.top() == l1)
			livrarias.pop();
		temp.push(livrarias.top());
		livrarias.pop();
	}
	livrarias=temp;
}

vector <Livraria*> Escola::searchLivraria(vector<Disciplina *> disciplinas){
	stack <string> disciplinasnome;
	vector <Livraria *> ReturnVec;
	bool found=false;
	if(disciplinas.empty()) {
		ReturnVec.push_back(livrarias.top());
		return ReturnVec;
	}

	for(int i=0; i<disciplinas.size();i++){

			disciplinasnome.push(disciplinas[i]->getNome());
	}
	while(!disciplinasnome.empty()){
		//fazer o loop consoante o numero de disciplinas
		priority_queue<Livraria *> temp=livrarias;
		while(!temp.empty()){
			vector<string> dislivraria= temp.top()->getEspecialidade();
			for(int i=0; i<dislivraria.size();i++){
					//verifica se a livraria tem a disciplina
				if(disciplinasnome.top()==dislivraria[i]){
					//se tiver, adiciona ao return vec
					ReturnVec.push_back(temp.top());
					found=true;
				}
				if (found) break;
			}
			temp.pop();
			if (found) break;
		}
		disciplinasnome.pop();
	}
	return ReturnVec;
}

bool Escola::recolocarProf(Professor * p1){

	HProfessor::iterator itProf = exprofessores.find(p1);

	if(itProf == exprofessores.end())
		return false;

	(*itProf)->setAtivo();
	professoresescola.push_back((*itProf));

	for(int i = 0 ; i < disciplinas.size(); i++){
		if(disciplinas[i]->getNome()==p1->getDisciplina()){
			disciplinas[i]->addProfessor((*itProf));
			break;
		}
	}

	exprofessores.erase(itProf);

	return true;

}

Livraria* Escola::searchLivrariaDenom(string denominacao){
	priority_queue<Livraria *> temp=livrarias;
	while(!temp.empty()){
		if(temp.top()->getDenominacao()==denominacao)
			return temp.top();
		temp.pop();
	}
	return NULL;
}

priority_queue <Livraria *> Escola::getLivrarias() {
	return livrarias;
}

Livraria* Escola::searchLivrariaID(int ID){

	priority_queue<Livraria *> temp=livrarias;
	while(!temp.empty()){
		if(temp.top()->getID()==ID)
			return temp.top();
		temp.pop();
	}
	return NULL;
}

priority_queue<Livraria *> Escola::getLivrariasDisc(string nomeDisc){

	priority_queue<Livraria *> temp=livrarias, returnQueue;
	while(!temp.empty()){
		vector<string> disc = temp.top()->getEspecialidade();
		for(int i = 0 ; i < disc.size(); i++){
			if(disc[i]==nomeDisc){
				returnQueue.push(temp.top());
				break;
			}
		}
		temp.pop();
	}

	return returnQueue;
}

priority_queue<Livraria*> Escola::searchLivrariasAno(int ano){
		priority_queue<Livraria *> temp1=livrarias, returnQueue;
		while(!temp1.empty()){
			vector<int > temp2 = temp1.top()->getEscolaridade();
			for(int i= 0 ; i < temp2.size(); i++){
				if(temp2[i]==ano){
					returnQueue.push(temp1.top());
					break;
				}
			}
			temp1.pop();
		}

		return returnQueue;
}
