#include <iostream>
#include <cstdlib>
#include "arrgen.h"
#include <cstdio>
#include <concepts>

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
    size_t h;
    for (h = 1; h <= n / 9; h = 3 * h + 1)
        ;
    for (; h > 0; h /= 3)
    {
        for (size_t i = h; i < n; i++)
        {
            T temp = array[i];
            size_t j = i;
            for (; j >= h && array[j - h] > temp; j -= h)
            {
                CompTimes++;
                array[j] = array[j - h];
            }
            array[j] = temp;
            CompTimes++;
        }
    }

    return CompTimes;
}

void PrintBin(int *array, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {

        for (int j = sizeof(int) * 8 - 1; j >= 0; j--)
            std::cout << ((array[i] & (1 << j)) ? 1 : 0);
        std::cout << " ";
    }

    std::cout << std::endl;
}
void PrintBin(unsigned int *array, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {

        for (int j = sizeof(unsigned int) * 8 - 1; j >= 0; j--)
            std::cout << ((array[i] & (1 << j)) ? 1 : 0);
        std::cout << " ";
    }

    std::cout << std::endl;
}

void RadixSortLSD1(unsigned *array, size_t n, int power)
{
    if (power < 0)
        return;
    int bits = 1 << power;
    int counter_size = (1 << bits) + 1;

    unsigned int counter[counter_size];
    unsigned int mask;
    int *buf_array = (int *)malloc(n * sizeof(int));
    int hight;
    int max_hight = sizeof(int) * 8 / bits - 1;
    for (int i = 0; i < n; i++)
        mask |= array[i];

    for (hight = max_hight; hight >= 0; hight--)
        if (mask & ((counter_size - 2) << (hight * bits)))
            break;
    for (unsigned int b = 0; b <= hight; b++)
    {
        mask = (counter_size - 2) << (b*bits);
        for (int i = 0; i < counter_size; i++)
            counter[i] = 0;

        for (int i = 0; i < n; i++)
            counter[((array[i] & mask) >> (b * bits)) + 1]++;

        for (int i = 1; i < counter_size; i++)
            counter[i] += counter[i - 1];

        for (int i = 0; i < n; i++)
            buf_array[counter[((array[i] & mask) >> (b * bits))]++] = array[i];

        for (int i = 0; i < n; i++)
            array[i] = buf_array[i];
    }

    free(buf_array);
}


template <typename T>
size_t SelectionSort(int (*Compare)(T, T), T *array, size_t n)
{
    size_t CompTimes = 0;
    for (size_t i = 0; i < n - 1; i++)
    {
        size_t min_index = i;
        for (size_t j = i + 1; j < n; j++)
        {
            CompTimes++;
            if (Compare(array[min_index], array[j]) < 0)
            {
                min_index = j;
            }
        }
        if (min_index != i)
        {
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
int CompFunc(char a, char b)
{
    return b - a;
}
int CompFunc(size_t a, size_t b)
{
    if (a > b)
        return -1;
    if (a == b)
        return 0;
    return 1;
}
int CompFunc(unsigned int a, unsigned int b)
{
    if (a > b)
        return -1;
    if (a == b)
        return 0;
    return 1;
}
int CompFunc(double a, double b)
{
    if (a > b)
        return -1;
    if (a == b)
        return 0;
    return 1;
}

using namespace std;

int main()

{
    size_t len = 6;
    unsigned int a[len];
    // ArrGen::RandomSequence<char>(a, len, 0, 10);
    ArrGen::RandomSequence<unsigned int>(a, len, 0, 21412412);
    cout << "Generation Done" << endl;
    PrintArray(a, len);
    PrintBin(a, len);
    RadixSortLSD1(a, len, 2);
    PrintArray(a, len);
    PrintBin(a, len);
    if (IsSorted<unsigned int>(CompFunc, a, len))
    {
        cout << "DONE" << endl;
    }
    else
    {
        cout << "FAIL" << endl;
    }
}

#include "arrgen.cpp"