#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

void bubbleSort(vector<int>& vetor)
{
    int tamanho = vetor.size();

    for (int i = 0; i < tamanho - 1; i++)
    {
        for (int j = 0; j < tamanho - 1 - i; j++)
        {
            if (vetor[j] > vetor[j + 1])
            {
                int aux = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = aux;
            }
        }
    }
}

int main()
{
    srand(time(0));

    int tamanho;

    cout << "Digite o tamanho do vetor: ";
    cin >> tamanho;

    vector<int> vetor(tamanho);

    for (int i = 0; i < tamanho; i++)
    {
        vetor[i] = rand() % 100000;
    }

    cout << "\nOrdenando vetor...\n";

    clock_t inicio = clock();

    bubbleSort(vetor);

    clock_t fim = clock();

    double tempo = double(fim - inicio) / CLOCKS_PER_SEC;

    cout << "Ordenacao concluida!\n";
    cout << "Tempo gasto: " << tempo << " segundos\n";

    return 0;
}