#include "arrgen.h"
#include <string>

namespace ArrGen
{
    void (*GenFunArrInt[])(int *, size_t, int, int) = {IncreasingSequence, DecreasingSequence, RandomSequence, SawtoothSequence, SinSequence, StepSequence, QuasiOrderedSequence};
    void (*GenFunarrDouble[])(double *, size_t, double, double) = {IncreasingSequence, DecreasingSequence, RandomSequence, SawtoothSequence, SinSequence, StepSequence, QuasiOrderedSequence};

    std::string GenFunNames[]{"IncreasingSequence", "DecreasingSequence", "RandomSequence", "SawtoothSequence", "SinSequence", "StepSequence", "QuasiOrderedSequence"};

    template <typename T>
    void IncreasingSequence(T * array, size_t len, T min, T max)
    {
        if (nullptr == array || 0 == len)
            return;
        if (min > max)
        {
            T temp = min;
            min = max;
            max = temp;
        }

        double step = 1.0 * (max - min) / len;
        array[0] = (T)min;
        double prev = (T)min;
        for (size_t i = 1; i < len; i++)
        {
            array[i] = prev + step;
            prev += step;
        }
    }

    template <typename T>
    void DecreasingSequence(T * array, size_t len, T min, T max)
    {
        if (nullptr == array || 0 == len)
            return;
        if (min > max)
        {
            T temp = min;
            min = max;
            max = temp;
        }
        double step = 1.0 * (max - min) / len;
        array[0] = max;
        double prev = (T)min;

        for (size_t i = 1; i < len; i++)
        {
            array[i] = prev + step;
            prev += step;
        }
    }

    template <typename T>
    void RandomSequence(T * array, size_t len, T min, T max)
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
    void SawtoothSequence(T * array, size_t len, T start, T end, size_t period, size_t offset)
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
    void SinSequence(T * array, size_t len, T start, T end, double period, T offset)
    {
        if (nullptr == array || 0 == len)
            return;
        for (size_t i = 0; i < len; i++)
        {
            array[i] = sin(i * M_2_PI * len / period / period + offset) * (end - start) / 2 + (end + start) / 2;
        }
    }

    template <typename T>
    void StepSequence(T * array, size_t len, T start, T end, size_t period)
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
    void QuasiOrderedSequence(T * array, size_t len, T start, T end, T spread)
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
            direct = start + 1.0 * i * (end - start) / len;
            double up_limit = max > direct + spread ? direct + spread : max;
            double low_limit = min < direct - spread ? direct - spread : min;
            std::uniform_real_distribution distribution(low_limit, up_limit);
            double ran = distribution(generator);
            array[i] = ran;
        }
    }

    template <typename T>
    void SawtoothSequence(T * array, size_t len, T start, T end)
    {
        SawtoothSequence(array, len, start, end, 10, 0);
    }

    template <typename T>
    void SinSequence(T * array, size_t len, T start, T end)
    {
        SinSequence<T>(array, len, start, end, 10 * M_2_PI, 0);
    }

    template <typename T>
    void StepSequence(T * array, size_t len, T start, T end)
    {
        StepSequence<T>(array, len, start, end, 10);
    }

    template <typename T>
    void QuasiOrderedSequence(T * array, size_t len, T start, T end)
    {
        QuasiOrderedSequence<T>(array, len, start, end, 10);
    }
}