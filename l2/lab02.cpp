#include <iostream>
#include <cstdlib>
#include "arrgen.h"

template <typename T>
bool IsSorted(int (*Compare)(T, T), T *array, size_t n)
{
    for (size_t i = 0; i < n - 1; i++)
    {

        if (Compare(array[i], array[i + 1]) < 0)
        {
            return false;
        }
    }
    return true;
}

template <typename T>
void PrintArray(T *array, size_t n)
{
    for (size_t i = 0; i < n; i++)

        std::cout << array[i] << " ";

    std::cout << std::endl;
}
/**
 * h(i) = 3*h(i-1)-1
 */
template <typename T>
size_t ShellSort(int (*Compare)(T, T), T *array, size_t n)
{
    size_t CompTimes = 0;
    size_t StepSizeN = (int(log2(n - 1)));
    size_t *StepSize = (size_t *)malloc(StepSizeN * sizeof(size_t));
    StepSize[0] = 1;
    for (size_t i = 1; i < StepSizeN; i++)
    {
        StepSize[i] = 3 * StepSize[i - 1] - 1;
    }

    for (size_t i = StepSizeN - 1; i >= 0; i--)
    {
        size_t h = StepSize[i];

        for (size_t j = 0; j + h < StepSizeN; j++)
        {
            CompTimes++;
            if (Compare(array[j], array[j + h]))
            {
                T temp = array[j];
                array[j] = array[j + h];
                array[j + h] = temp;
            }
        }
    }
    free(StepSize);
    return CompTimes;
}
// template <typename T>
// size_t CountingSort(bool(*Compare), , T *array, size_t n);
// template <typename T>
// size_t SelectionSort(bool(*Compare), , T *array, size_t n);

int CompFunc(int a, int b)
{
    return b - a;
}

using namespace std;

int main()
{
    int len = 100;
    int a[len];
    ArrGen::IncreasingSequence<int>(a, 100, 0, 10000);
    cout << "Generation Done" << endl;
    PrintArray(a, len);
    cout << "Comparations: " << ShellSort(CompFunc, a, len) << endl;
    PrintArray(a, len);
    if (IsSorted<int>(CompFunc, a, len))
    {
        cout << "DONE" << endl;
    }
    else
    {
        cout << "FAIL" << endl;
    }
}