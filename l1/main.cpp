#include <iostream>
#include <random>
#include <cmath>
#include <chrono>
#include <fstream>

template <typename T>
void IncreasingSequence(T *array, size_t len, T min, T max)
{
    if (nullptr == array || 0 == len)
        return;
    if (min > max)
    {
        T temp = min;
        min = max;
        max = temp;
    }

    double step = (max - min) / len;
    array[0] = min;
    for (size_t i = 1; i < len; i++)
    {
        array[i] = array[i - 1] + step;
    }
}

template <typename T>
void DecreasingSequence(T *array, size_t len, T min, T max)
{
    if (nullptr == array || 0 == len)
        return;
    if (min > max)
    {
        T temp = min;
        min = max;
        max = temp;
    }
    double step = -(max - min) / len;
    array[0] = max;
    for (size_t i = 1; i < len; i++)
    {
        array[i] = array[i - 1] + step;
    }
}

template <typename T>
void RandomSequence(T *array, size_t len, T min, T max)
{
    if (nullptr == array || 0 == len)
        return;
    if (min > max)
    {
        T temp = min;
        min = max;
        max = temp;
    }
    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_real_distribution distribution((double)min, (double)max);
    for (size_t i = 0; i < len; i++)
    {
        array[i] = distribution(generator);
    }
}

template <typename T>
void SawtoothSequence(T *array, size_t len, T start, T end, size_t period, size_t offset = 0)
{
    if (nullptr == array || 0 == len)
        return;
    double local_step = 1.0 * (end - start) / period;
    for (size_t i = 0; i < len; i++)
    {
        array[i] = start + local_step * ((i + offset) % period);
    }
}

template <typename T>
void SinSequence(T *array, size_t len, T start, T end, double period = 2 * M_2_PI, T offset = 0)
{
    if (nullptr == array || 0 == len)
        return;
    for (size_t i = 0; i < len; i++)
    {
        array[i] = sin(i * M_2_PI / period + offset) * (end - start) / 2 + (end + start) / 2;
    }
}

template <typename T>
void StepSequence(T *array, size_t len, T start, T end, size_t period)
{
    if (nullptr == array || 0 == len || 0 == period || len < period)
        return;
    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_real_distribution distribution((double)0, (double)(end - start) / (len / period));
    for (size_t i = 0; i < len; i++)
    {
        double ran = distribution(generator);
        array[i] = (i / period) * (end - start) / (len / period) + ran;
    }
}

template <typename T>
void QuasiOrderedSequence(T *array, size_t len, T start, T end, T spread)
{
    if (nullptr == array || 0 == len)
        return;
    double step = (end - start) / len;
    std::random_device random_device;
    std::mt19937 generator(random_device());
    T max = start > end ? start : end;
    T min = start < end ? start : end;
    double direct = start;
    for (size_t i = 0; i < len; i++, direct += step)
    {
        double up_limit = max > direct + spread ? direct + spread : max;
        double low_lomit = min < direct - spread ? direct - spread : min;
        std::uniform_real_distribution distribution(low_lomit, up_limit);
        double ran = distribution(generator);
        array[i] = ran;
    }
}
using namespace std;
using namespace std::chrono;

void (*funarrint[])(int*,size_t, int, int ) = {IncreasingSequence};
int main()
{
    ofstream outstream("out.txt");
    outstream << "<type> Alg size\n";
    auto begin = steady_clock::now();
    auto end = steady_clock::now();
    for (int i = 5; i <= 50; i += 5)
    {
        int *array = (int *)malloc(sizeof(int) * i * pow(10, 5));
       

        begin = steady_clock::now();
        IncreasingSequence(array, i * pow(10, 5), INT16_MIN, INT16_MAX);
        end = steady_clock::now();
        cout<<"<int> ";
        std::cout << "Elapsed microseconds: "
                  << duration_cast<microseconds>(end - begin).count()
                  << "us\n";
    }

    outstream.close();
    return 0;
}