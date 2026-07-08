#include <iostream>

using namespace std;

class aluno{
    private:
        int matricula;
        string nome;
        string curso;

        public:

        string get_name(){
            return nome;   
        }

        int get_matricula(){
            return matricula;
        }

        aluno(int m, string n, string c){
            matricula = m;
            nome = n;
            curso = c;
        }

};