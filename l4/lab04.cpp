#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <random>
#include <chrono>
#include <cmath>

using namespace std;
using namespace std::chrono;

char RandChar(char a, char b)
{
	return rand() % (b - a + 1) + a;
}
int RandInt(int a, int b)
{
	return rand() % (b - a + 1) + a;
}

void RandGen(char *string, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		string[i] = RandChar('A', 'F');
	}
}
char *LasySearch(char *string, int n, char *substring, int m)
{
	int j;
	int i;
	for (i = 0; i < n - m; i++)
	{
		for (j = 0; j < m && *(substring + j) == *(string + i + j); j++)
			;
		if (j == m)
			return string + i;
	}
	return nullptr;
}

int max(int a, int b)
{
	return a > b ? a : b;
}

void Prefics(int *Next, char *substring, int m)
{
	int j, i;
	for (Next[0] = j = -1, i = 1; i < m; i++)
	{
		// Префикс-функция (индексы)
		for (; j > -1 && substring[j + 1] != substring[i]; j = Next[j])
			;
		if (substring[j + 1] == substring[i])
			j++;
		Next[i] = j;
	}
}

char *BoyerMooreStringSearch(char *string, int n, char *substring, int m)
{
	char *res = nullptr;
	int char_offset[256]; // LO
	int suffix_offset[m]; // GS
	int Next0[m];
	int Next1[m];
	char substring_buffer[m]; // P1

	for (int i = 0; i < 256; char_offset[i++] = -1)
		;

	for (int i = 0; i < m; i++)
		char_offset[substring[i]] = i;

	Prefics(Next0, substring, m);

	for (int i = 0; i < m; i++)
		substring_buffer[m - 1 - i] = substring[i];

	Prefics(Next1, substring_buffer, m);

	for (int i = 0; i < m; i++)
		suffix_offset[i] = m - Next0[m - 1];

	for (int i = 0; i < m; i++)
	{
		int j = m - 1 - Next1[i];
		if (suffix_offset[j] > i + 1 - Next1[i])
			suffix_offset[j] = i + 1 - Next1[i];
	}
	int count = 0;

	for (int i = 0; i <= n - m && res == nullptr;)
	{
		int j;
		for (j = m - 1; j >= 0; j--)
		{

			if (string[i + j] != substring[j])
			{
				count++;
				int a =  max((j-char_offset[string[i + j]]), suffix_offset[j]);
				i += max((j-char_offset[string[i + j]]), suffix_offset[j]);
				// cout<<a<<endl;
				break;
			}
		}
		if (j == -1)
			res = string + i;
	}
	return res;
}


int main()
{
	srand(time(0));

	int repeat = 1000;
	int str_len = 5;
	ofstream output_TY("ouput_TY.txt");
	ofstream output_TN("output_TN.txt");
	ofstream output_SY("ouput_SY.txt");
	ofstream output_SN("output_SN.txt");
	ofstream log("log.txt");

	auto start = steady_clock::now();
	auto end = steady_clock::now();

	size_t fun_time, str_time;

	size_t fun_time_succ, fun_time_fail,
		str_time_succ, str_time_fail;
	size_t succ_times, fail_times;
	char *text;
	char *str;
	for (int i = 5; i <= 50; i += 5)
	{
		int len = i * 1000;
		text = (char *)calloc(len + 1, sizeof(char));
		RandGen(text, len);
		str = (char *)calloc(str_len + 1, sizeof(char));

		fun_time_succ = 0;
		fun_time_fail = 0;
		str_time_succ = 0;
		str_time_fail = 0;

		fail_times = 0;
		succ_times = 0;

		for (int j = 0; j < repeat; j++)
		{
			fun_time = 0;
			str_time = 0;

			char *fun_res;
			char *str_res;

			RandGen(str, str_len);
			str[str_len / 2] = 'F' + (j % 2);

			start = steady_clock::now();
			str_res = strstr(text, str);
			end = steady_clock::now();
			str_time = duration_cast<nanoseconds>(end - start).count();

			start = steady_clock::now();
			fun_res = BoyerMooreStringSearch(text, len, str, str_len);
			end = steady_clock::now();
			fun_time = duration_cast<nanoseconds>(end - start).count();

			log << i * 1000 << " " << fun_time << " " << str_time << " " << str << " " << (fun_res == str_res ? "SUCC" : "FAIL") << endl;
			if (fun_res != str_res) {
				cout<<"FAIL\n";
				cout<<text<<endl<<str<<endl;
				exit(0);
			}
			if (str_res == nullptr)
			{
				fun_time_fail += fun_time;
				str_time_fail += str_time;
				fail_times++;
			}
			else
			{
				fun_time_succ += fun_time;
				str_time_succ += str_time;
				succ_times++;
			}
		}
		output_TN << i * 1000 << "|" << fun_time_fail / fail_times << "|" << str_time_fail / fail_times << "|" << fail_times << endl;
		output_TY << i * 1000 << "|" << fun_time_succ / succ_times << "|" << str_time_succ / succ_times << "|" << succ_times << endl;
		free(str);
		free(text);
	}

	// free(text);
	output_TY.close();
	output_TN.close();
	output_SY.close();
	output_SN.close();
	log.close();
	return 0;
}