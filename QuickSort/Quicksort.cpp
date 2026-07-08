#include <iostream>

void quicksort(int values[], int begin, int end)
{
    if (begin >= end - 1) return; // Caso base: array de 1 ou 0 elementos já está ordenado

    int i = begin, j = end - 1;
    int pivo = values[begin + (end - begin) / 2];
    int aux;

    while (i <= j)
    {
        while (i < end && values[i] < pivo)
            i++;
        while (j >= begin && values[j] > pivo)
            j--;

        if (i <= j)
        {
            aux = values[i];
            values[i] = values[j];
            values[j] = aux;
            i++;
            j--;
        }
    }

    if (begin < j)
        quicksort(values, begin, j + 1);
    if (i < end)
        quicksort(values, i, end);
}

int main()
{
    int array[10] = {5, 8, 1, 2, 7, 3, 6, 9, 4, 10};

    std::cout << "Array antes da ordenação: ";
    for (int i = 0; i < 10; i++)
    {
        std::cout << array[i] << ' ';
    }
    std::cout << std::endl;

    quicksort(array, 0, 10);

    std::cout << "Array ordenado: ";
    for (int i = 0; i < 10; i++)
    {
        std::cout << array[i] << ' ';
    }
    std::cout << std::endl;

    return 0;
}