#ifndef ARRGEN_H
#define ARRGEN_H

#include <iostream>
#include <random>
#include <cmath>
#include <fstream>
namespace ArrGen
{
    template <typename T>
    void IncreasingSequence(T *array, size_t len, T min, T max);

    template <typename T>
    void DecreasingSequence(T *array, size_t len, T min, T max);

    template <typename T>
    void RandomSequence(T *array, size_t len, T min, T max);

    template <typename T>
    void SawtoothSequence(T *array, size_t len, T start, T end, size_t period, size_t offset);

    template <typename T>
    void SinSequence(T *array, size_t len, T start, T end, double period = 2 * M_2_PI, T offset = 0);

    template <typename T>
    void StepSequence(T *array, size_t len, T start, T end, size_t period = 10);

    template <typename T>
    void QuasiOrderedSequence(T *array, size_t len, T start, T end, T spread);

    template <typename T>
    void SawtoothSequence(T *array, size_t len, T start, T end);

    template <typename T>
    void SinSequence(T *array, size_t len, T start, T end);

    template <typename T>
    void StepSequence(T *array, size_t len, T start, T end);

    template <typename T>
    void QuasiOrderedSequence(T *array, size_t len, T start, T end);

    extern void (*GenFunArrInt[])(int *, size_t, int, int);
    extern void (*GenFunarrDouble[])(double *, size_t, double, double);

    extern std::string GenFunNames[];
}
#endif