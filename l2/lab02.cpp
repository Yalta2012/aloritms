#include <iostream>
#include <cstdlib>
#include "arrgen.h"
#include <cstdio>

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
    size_t StepSizeN = n;
    size_t *StepSize = (size_t *)malloc(StepSizeN * sizeof(size_t));
    StepSize[0] = 1;
    for (size_t i = 1; i < StepSizeN; i++)
    {
        StepSize[i] = 3 * StepSize[i - 1] - 1;
    }

    for (size_t i = StepSizeN - 1; ;i--)
    {

        size_t h = StepSize[i];
        //std::cout<<"("<<h<<")"<<std::endl;
        printf("H: %ld\n",h);
        for (size_t j = 0; j + h < StepSizeN; j++)
        {
            printf("(%ld %ld)[%d %d]",j,j+h,array[j],array[j+h]);
            CompTimes++;
            if (Compare(array[j], array[j + h])<0)
            {
                printf("SWITCH\n");
                T temp = array[j];
                array[j] = array[j + h];
                array[j + h] = temp;
                PrintArray(array,n);
            }
            printf("\n");
        }
        if(i == 0) break;
    }
    free(StepSize);
    return CompTimes;
}
// template <typename T>
// size_t CountingSort(bool(*Compare), , T *array, size_t n);


template <typename T>
size_t SelectionSort(int(*Compare)(T, T), T *array, size_t n){
    size_t CompTimes = 0;  
    for(size_t i = 0; i<n-1; i++){
        size_t min_index = i;
        for (size_t j = i+1; j<n; j++){
            CompTimes++;
            if(Compare(array[min_index],array[j])<0){
                min_index = j;
            }
        }
        if (min_index != i){
            T temp = array[i];
            array[i] = array[min_index];
            array[min_index] = temp;
        }
    }
    return CompTimes;
}

int CompFunc(int a, int b)
{
    return b - a;
}

using namespace std;

int main()
{
    int len = 10;
    int a[len];
    ArrGen::RandomSequence<int>(a, len, 0, 10);
    cout << "Generation Done" << endl;
    PrintArray(a, len);
    cout << "Comparations: " << SelectionSort<int>(CompFunc, a, len) << endl;
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