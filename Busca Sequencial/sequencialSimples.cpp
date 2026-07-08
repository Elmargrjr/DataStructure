#include <iostream>
#include <vector>

using namespace std;

int buscaSequencial(vector<int> &numeros, int numeroBusca){
    for(int i=0; i<numeros.size() ; i++){
        int comparacao = numeros[i];
        if(comparacao == numeroBusca){
            return i;
        }
    }
    return -1;
}

int main(void){
    
    vector<int>  numeros = {10,20,30,40,50,60,70,80,90,100};

    cout << "Buscando numero 20" << endl;
    int indice = buscaSequencial(numeros, 20);
    cout << "Encontrado no indice: " << indice;

    return 0;
}