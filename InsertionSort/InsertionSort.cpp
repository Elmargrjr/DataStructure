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

    for (int i = 0; i < vetor.size() - 1; i++)
    {
        for (int j = 0; j < vetor.size() - 1 - i; j++)
        {
            if (vetor[j] > vetor[j + 1])
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
    int menor, aux;

    for (int i = 0; i < vetor.size() - 1; i++)
    {
        menor = i;

        for (int j = i + 1; j < vetor.size(); j++)
        {
            if (vetor[j] < vetor[menor])
            {
                menor = j;
            }
        }

        aux = vetor[i];
        vetor[i] = vetor[menor];
        vetor[menor] = aux;
    }
}

void insertionSort(vector<int> &vetor)
{
    int chave, j;

    for (int i = 1; i < vetor.size(); i++)
    {
        chave = vetor[i];
        j = i - 1;

        while (j >= 0 && vetor[j] > chave)
        {
            vetor[j + 1] = vetor[j];
            j--;
        }

        vetor[j + 1] = chave;
    }
}

vector<int> gerarVetor(int tamanho)
{
    vector<int> vetor;

    for (int i = 0; i < tamanho; i++)
    {
        vetor.push_back(rand() % 100000);
    }

    return vetor;
}

int main()
{
    srand(time(0));

    int tamanho;

    cout << "Digite o tamanho do vetor: ";
    cin >> tamanho;

    vector<int> vetorOriginal = gerarVetor(tamanho);

    vector<int> bubble = vetorOriginal;
    vector<int> selection = vetorOriginal;
    vector<int> insertion = vetorOriginal;

    auto inicioBubble = high_resolution_clock::now();

    bubbleSort(bubble);

    auto fimBubble = high_resolution_clock::now();

    auto tempoBubble =
        duration_cast<milliseconds>(fimBubble - inicioBubble);

    auto inicioSelection = high_resolution_clock::now();

    selectionSort(selection);

    auto fimSelection = high_resolution_clock::now();

    auto tempoSelection =
        duration_cast<milliseconds>(fimSelection - inicioSelection);

    auto inicioInsertion = high_resolution_clock::now();

    insertionSort(insertion);

    auto fimInsertion = high_resolution_clock::now();

    auto tempoInsertion =
        duration_cast<milliseconds>(fimInsertion - inicioInsertion);

    cout << "\n===== TEMPOS =====\n";

    cout << "Bubble Sort: "
         << tempoBubble.count()
         << " ms" << endl;

    cout << "Selection Sort: "
         << tempoSelection.count()
         << " ms" << endl;

    cout << "Insertion Sort: "
         << tempoInsertion.count()
         << " ms" << endl;

    cout << "\n===== MAIS EFICIENTE =====\n";

    if (tempoBubble.count() < tempoSelection.count() &&
        tempoBubble.count() < tempoInsertion.count())
    {
        cout << "Bubble Sort foi o mais eficiente.\n";
    }
    else if (tempoSelection.count() < tempoBubble.count() &&
             tempoSelection.count() < tempoInsertion.count())
    {
        cout << "Selection Sort foi o mais eficiente.\n";
    }
    else
    {
        cout << "Insertion Sort foi o mais eficiente.\n";
    }

    return 0;
}