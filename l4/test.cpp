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

    for (int i : suffix_offset)
    {
        cout << i << endl;
    }
    cout << "\\\\\n";
    for (int i = 0; i <= n - m && res == nullptr;)
    {
        int j;
        for (j = m - 1; j >= 0; j--)
        {

            if (string[i + j] != substring[j])
            {
                count++;
                if ((j-char_offset[string[i + j]]) > suffix_offset[j])
                    cout << "char ";
                else
                    cout << "suf ";
                i += max((j - char_offset[string[i + j]]), suffix_offset[j]);
                cout << max((j - char_offset[string[i + j]]), suffix_offset[j]) << endl;
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
    char t[] = "cDDAADDFFDDbDDECABEBEEFA";
    char s[] = "DDAADDFFDD";

    printf("%p\n%p\n", BoyerMooreStringSearch(t, strlen(t), s, strlen(s)), strstr(t, s));

    return 0;
}