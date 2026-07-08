#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace chrono;

void bubbleSort(vector<int> &vetor)
{
    int aux;

    for(int i = 0; i < vetor.size() - 1; i++)
    {
        for(int j = 0; j < vetor.size() - 1 - i; j++)
        {
            if(vetor[j] > vetor[j + 1])
            {
                aux = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = aux;
            }
        }
    }
}

void selectionSort(vector<int> &vetor)
{
    int menor;
    int aux;

    for(int i = 0; i < vetor.size() - 1; i++)
    {
        menor = i;

        for(int j = i + 1; j < vetor.size(); j++)
        {
            if(vetor[j] < vetor[menor])
            {
                menor = j;
            }
        }

        aux = vetor[i];
        vetor[i] = vetor[menor];
        vetor[menor] = aux;
    }
}

void mostrarVetor(vector<int> vetor)
{
    for(int i = 0; i < vetor.size(); i++)
    {
        cout << vetor[i] << " ";
    }

    cout << endl;
}

int main()
{
    srand(time(0));

    int tamanho;

    cout << "Digite o tamanho do vetor: ";
    cin >> tamanho;

    vector<int> vetorOriginal(tamanho);

    for(int i = 0; i < tamanho; i++)
    {
        vetorOriginal[i] = rand() % 100000;
    }

    vector<int> vetorBubble = vetorOriginal;
    vector<int> vetorSelection = vetorOriginal;

    auto inicioBubble = high_resolution_clock::now();

    bubbleSort(vetorBubble);

    auto fimBubble = high_resolution_clock::now();

    auto tempoBubble = duration_cast<milliseconds>(fimBubble - inicioBubble);

    auto inicioSelection = high_resolution_clock::now();

    selectionSort(vetorSelection);

    auto fimSelection = high_resolution_clock::now();

    auto tempoSelection = duration_cast<milliseconds>(fimSelection - inicioSelection);

    cout << "\nTempo Bubble Sort: "
         << tempoBubble.count()
         << " ms" << endl;

    cout << "Tempo Selection Sort: "
         << tempoSelection.count()
         << " ms" << endl;

    return 0;
}