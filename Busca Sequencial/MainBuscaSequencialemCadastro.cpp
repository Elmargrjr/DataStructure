#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include "aluno.h"

using namespace std;

vector <aluno> sigaa;

int buscarAluno(vector <aluno> &sigaa, int matricula, int &comparacoes){
    int baixo = 0;
    int alto = sigaa.size() - 1;

    while (baixo <= alto){
        int meio = (baixo + alto) / 2;
        int chute = sigaa[meio].get_matricula();

        comparacoes++;

        if (chute == matricula){
            return meio;
        }

        if (chute > matricula){
            alto = meio - 1;
        } else {
            baixo = meio + 1;
        }
    }
    return -1;
}

int main(void){

int ch;

do{
cout << "\nescolha alguma opção abaixo" << endl;
cout << "1 - Cadastrar novo aluno" << endl;
cout << "2 - Listar todos os alunos" << endl;
cout << "3 - Buscar um aluno por busca sequencial" << endl;
cout << "4 - Buscar um aluno por busca binária" << endl;
cout << "5 - Encher o vetor com 100000 alunos" << endl;
cout << "0 - Sair" << endl;

cin >> ch;

if (ch == 1){

    string nome;
    string curso;
    int matricula;

    cout << "Digite o nome do aluno: " << endl;
    cin.ignore();
    getline (cin, nome);

    cout << "Digite o curso: " << endl;
    getline (cin, curso);

    cout << "Digite a matrícula no formato (ano)(final cpf)" << endl;
    cin >> matricula;

    sigaa.push_back(aluno(matricula,nome,curso));

    sort(sigaa.begin(), sigaa.end(), [](aluno a, aluno b){
        return a.get_matricula() < b.get_matricula();
    });
}

if(ch == 2){
    for(int i = 0; i < sigaa.size(); i++){
        cout << "\nAluno alocado na posição " << i << " :" << endl;
        sigaa[i].get_name();
        cout << "Matricula: " << sigaa[i].get_matricula() << endl;
    }
}

if(ch == 3){

    int matricula;
    cout << "Digite a matricula do aluno que voce quer buscar: " << endl;
    cin >> matricula;

    int comparacoes = 0;

    clock_t inicio = clock();

    int posicao = -1;

    for (int i = 0; i < sigaa.size(); i++){
        comparacoes++; // 🔥 conta comparação

        if (sigaa[i].get_matricula() == matricula){
            posicao = i;
            break;
        }
    }

    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    if (posicao != -1){
        cout << "\nAluno encontrado na posição " << posicao << endl;
    } else {
        cout << "\nAluno não encontrado" << endl;
    }

    cout << "Comparacoes: " << comparacoes << endl;
    cout << "Tempo: " << tempo << " segundos" << endl;
}

if (ch == 4){
    int matricula;
    cout << "Digite a matricula do aluno que voce quer buscar: " << endl;
    cin >> matricula;

    int comparacoes = 0;

    clock_t inicio = clock();

    int posicao = buscarAluno(sigaa, matricula, comparacoes);

    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    if (posicao != -1){
        cout << "\nAluno encontrado na posição " << posicao << endl;
    } else {
        cout << "\nAluno não encontrado" << endl;
    }

    cout << "Comparacoes: " << comparacoes << endl;
    cout << "Tempo: " << tempo << " segundos" << endl;
}

if(ch == 5){
    sigaa.clear();

    for (int i = 0; i < 100000; i++){
        sigaa.push_back(aluno(202400000 + i, "Aluno " + to_string(i), "Curso " + to_string(i)));
    }

    sort(sigaa.begin(), sigaa.end(), [](aluno a, aluno b){
        return a.get_matricula() < b.get_matricula();
    });

    cout << "100000 alunos inseridos com sucesso!" << endl;
}

} while (ch != 0);

return 0;
}