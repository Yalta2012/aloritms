#include "arrgen.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include <cstdlib>

void PrintArray(int *array, size_t size)
{
	for (size_t i = 0; i < size; i++)
		std::cout << array[i] << " ";
	std::cout << std::endl;
}

template <typename T>
T *LineSearch(T *array, size_t size, T val, size_t *counter)
{
	T *result = nullptr;
	*counter = 0;
	for (size_t i = 0; i < size && result == nullptr; i++)
	{
		(*counter)++;
		if (array[i] == val)
			result = array + i;
	}

	return result;
}

template <typename T>
T *JumpSearchLVL1(T *array, size_t size, T val, size_t jump, size_t *counter)
{
	*counter = 0;
	T *result = nullptr;
	size_t pos;
	size_t pre_pos;
	for (pos = 0, pre_pos = 0; pos < size && array[pos] <= val && result == nullptr; pos += jump)
	{
		(*counter)++;
		if (array[pos] == val)
			result = array + pos;
		else
			pre_pos = pos;
	}
	if (pos >= size)
		pos = size - 1;
	for (; pos > pre_pos && array[pos] >= val && result == nullptr; pos--)
	{
		(*counter)++;
		if (array[pos] == val)
			result = array + pos;
	}
	return result;
}

template <typename T>
T *JumpSearchLVL2(T *array, size_t size, T val, size_t jump1, size_t jump2, size_t *counter)
{
	T *result = nullptr;
	size_t pos;
	size_t pre_pos;
	size_t post_pos;
	*counter = 0;
	for (pos = 0, pre_pos = 0; pos < size && array[pos] <= val && result == nullptr; pos += jump1)
	{
		(*counter)++;
		if (array[pos] == val)
			result = array + pos;
		else
			pre_pos = pos;
	}

	if (pos >= size)
		pos = size - 1;

	for (; pos > pre_pos && pos - jump2 < pos && array[pos] >= val && result == nullptr; pos -= jump2)
	{
		(*counter)++;
		if (array[pos] == val)
			result = array + pos;
		else
			post_pos = pos;
	}

	if (pos - jump2 > pos)
		pos = 0;
	if (post_pos == 0)
		post_pos = size - 1;

	for (; pos <= post_pos && array[pos] <= val && result == nullptr; pos++)
	{
		(*counter)++;
		if (array[pos] == val)
			result = array + pos;
	}
	return result;
}

template <typename T>
T *BinarySearch(T *array, size_t size, T val, size_t *counter)
{
	T *result = nullptr;
	size_t low = 0, high = size - 1, pos = size / 2;
	*counter = 0;
	for (; (low <= high) && (result == nullptr) && low >= 0 && high <= size - 1; pos = (low + high) / 2)
	{
		(*counter)++;
		if (array[pos] == val)
			result = array + pos;
		else if (val < array[pos])
		{
			(*counter)++;
			high = pos - 1;
		}
		else
			low = pos + 1;
	}
	return result;
}
template <typename T>
T *FibonacciSearch(T *array, size_t size, T val, size_t *counter)
{
	int result;
	int f1 = 1, f2 = 1, temp;
	*counter = 0;
	for (; f1 <= size; f1 += f2, f2 = f1 - f2)
		;

	result = f2 - 1;
	f1 -= f2;
	f2 -= f1;
	while (f1 + f2 > 0 && f1 >= 0 && f2 >= 0)
	{
		(*counter)++;
		if (val < array[result])
		{
			result -= f2;
			temp = f2;
			f2 = f1 - f2;
			f1 = temp;
		}
		else if (val > array[result])
		{
			(*counter)++;
			result += f2;
			result = size - 1 > result ? result : size - 1;
			f1 -= f2;
			f2 -= f1;
		}
		else
			return array + result;
	}
	return nullptr;
}

template <typename T>
T *InterpolationSearch(T *array, size_t size, T val, size_t *counter)
{
	T *result = nullptr;
	*counter = 0;
	int left = 0, right = size - 1;
	int pos = left + val * (right - left) / (array[right] - array[left]);
	while (array[left] <= val && array[right] >= val && result == nullptr)
	{
		(*counter)++;
		pos = (array[right] * left - array[left] * right + val * (right - left)) / (array[right] - array[left]);
		if (array[pos] < val)
			left = pos + 1;
		else
		{
			(*counter)++;
			if (array[pos] > val)
				right = pos - 1;
			else
				result = array + pos;
		}
	}

	return result;
}
using namespace std;
using namespace ArrGen;
using namespace std::chrono;


int main()
{
	srand(time(0));
	ofstream outstream_find("out3_find.txt");
	ofstream outstream_none("out3_none.txt");
	ofstream outstream_jump("out3_jump.txt");
	ofstream log("log.txt");
	outstream_find << "Search | Len | Compares | X | Status\n";
	size_t len;
	int *a;
	size_t counter;
	size_t m_counter = 0;
	size_t n_counter = 0;
	int times = 1000;
	for (int i = 2; i <= 20; i += 2)
	{
		len = i * 1'000;
		a = (int *)malloc(len * sizeof(int));
		ArrGen::IncreasingSequence<int>(a, len, -len, len);

		// line
		m_counter = 0;
		n_counter = 0;
		for (int k = 0; k < times; k++)
		{
			int x = (rand() % (len - 1 - (-len + 1) + 1) - (len - 1)) / 2 * 2;
			int *f = LineSearch<int>(a, len, x, &counter);
			m_counter += counter;
			log << "LineSearch " << len << " " << counter << " " << x << " " << (*f == x ? "SUCCES" : "FAIL") << endl;

			f = LineSearch<int>(a, len, x + 1, &counter);
			n_counter += counter;
			log << "LineSearch " << len << " " << counter << " " << x + 1 << " " << (f == nullptr ? "SUCCES" : "FAIL") << endl;
		}
		outstream_find << "LineSearch " << len << " " << m_counter / times << " - -" << endl;
		outstream_none << "LineSearch " << len << " " << n_counter / times << " - -" << endl;

		// jump 1
		m_counter = 0;
		n_counter = 0;
		for (int k = 0; k < times; k++)
		{
			int x = (rand() % (len - 1 - (-len + 1) + 1) - (len - 1)) / 2 * 2;
			int *f = JumpSearchLVL1<int>(a, len, x, i * 10, &counter);
			m_counter += counter;
			log << "JumpSearchLVL1 " << len << " " << counter << " " << x << " " << (*f == x ? "SUCCES" : "FAIL") << endl;

			f = JumpSearchLVL1<int>(a, len, x + 1, i * 10, &counter);
			n_counter += counter;
			log << "JumpSearchLVL1 " << len << " " << counter << " " << x + 1 << " " << (f == nullptr ? "SUCCES" : "FAIL") << endl;
		}
		outstream_find << "JumpSearchLVL1 " << len << " " << m_counter / times << " - -" << endl;
		outstream_none << "JumpSearchLVL1 " << len << " " << n_counter / times << " - -" << endl;

		// jump 2
		m_counter = 0;
		n_counter = 0;
		for (int k = 0; k < times; k++)
		{
			int x = (rand() % (len - 1 - (-len + 1) + 1) - (len - 1)) / 2 * 2;
			int *f = JumpSearchLVL2<int>(a, len, x, i * 100, i * 10, &counter);
			m_counter += counter;
			log << "JumpSearchLVL2 " << len << " " << counter << " " << x << " " << (*f == x ? "SUCCES" : "FAIL") << endl;

			f = JumpSearchLVL2<int>(a, len, x + 1, i * 100, i * 10, &counter);
			n_counter += counter;
			log << "JumpSearchLVL2 " << len << " " << counter << " " << x + 1 << " " << (f == nullptr ? "SUCCES" : "FAIL") << endl;
		}
		outstream_find << "JumpSearchLVL2 " << len << " " << m_counter / times << " - -" << endl;
		outstream_none << "JumpSearchLVL2 " << len << " " << n_counter / times << " - -" << endl;

		// bin

		m_counter = 0;
		n_counter = 0;
		for (int k = 0; k < times; k++)
		{
			int x = (rand() % (len - 1 - (-len + 1) + 1) - (len - 1)) / 2 * 2;
			int *f = BinarySearch<int>(a, len, x, &counter);
			m_counter += counter;
			log << "BinarySearch " << len << " " << counter << " " << x << " " << (*f == x ? "SUCCES" : "FAIL") << endl;

			f = BinarySearch<int>(a, len, x + 1, &counter);
			n_counter += counter;
			log << "BinarySearch " << len << " " << counter << " " << x + 1 << " " << (f == nullptr ? "SUCCES" : "FAIL") << endl;
		}
		outstream_find << "BinarySearch " << len << " " << m_counter / times << " - -" << endl;
		outstream_none << "BinarySearch " << len << " " << n_counter / times << " - -" << endl;

		// interpol

		m_counter = 0;
		n_counter = 0;
		for (int k = 0; k < times; k++)
		{
			int x = (rand() % (len - 1 - (-len + 1) + 1) - (len - 1)) / 2 * 2;
			int *f = InterpolationSearch<int>(a, len, x, &counter);
			m_counter += counter;
			log << "InterpolationSearch " << len << " " << counter << " " << x << " " << (*f == x ? "SUCCES" : "FAIL") << endl;

			f = InterpolationSearch<int>(a, len, x + 1, &counter);
			n_counter += counter;
			log << "InterpolationSearch " << len << " " << counter << " " << x + 1 << " " << (f == nullptr ? "SUCCES" : "FAIL") << endl;
		}
		outstream_find << "InterpolationSearch " << len << " " << m_counter / times << " - -" << endl;
		outstream_none << "InterpolationSearch " << len << " " << n_counter / times << " - -" << endl;

		// fibonacci

		m_counter = 0;
		n_counter = 0;
		for (int k = 0; k < times; k++)
		{
			int x = (rand() % (len - 1 - (-len + 1) + 1) - (len - 1)) / 2 * 2;
			int *f = FibonacciSearch<int>(a, len, x, &counter);
			m_counter += counter;
			log << "FibonacciSearch " << len << " " << counter << " " << x << " " << (*f == x ? "SUCCES" : "FAIL") << endl;

			f = FibonacciSearch<int>(a, len, x + 1, &counter);
			n_counter += counter;
			log << "FibonacciSearch " << len << " " << counter << " " << x + 1 << " " << (f == nullptr ? "SUCCES" : "FAIL") << endl;
		}
		outstream_find << "FibonacciSearch " << len << " " << m_counter / times << " - -" << endl;
		outstream_none << "FibonacciSearch " << len << " " << n_counter / times << " - -" << endl;

		free(a);
	}

	len = 4'096;
	int jumparr[13] = {0};
	a = (int *)malloc(len * sizeof(int));
	ArrGen::IncreasingSequence<int>(a, len, 0, len);
	times = 100;
	for (int i = 0; i < times; i++)
	{
		int x = (rand() % len) / 2 * 2;
		for (int j = len; j; j /= 2)
		{

			int *f = JumpSearchLVL1<int>(a, len, x, j, &counter);
			n_counter += counter;
			log << "JUMP" << i << " " << j << " " << counter << endl;
			jumparr[(int)log2(j)] += counter;
		}
	}
	for (int i = 0; i < 13; i++)
		outstream_jump << "JUMP " << (1 << i) << " " << jumparr[i] / times << endl;
	free(a);

	outstream_find.close();
	log.close();
	return 0;
}

#include "arrgen.cpp"