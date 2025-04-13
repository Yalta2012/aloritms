#include <chrono>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

using namespace std;
using namespace std::chrono;

char RandChar(char a, char b) { return rand() % (b - a + 1) + a; }
int RandInt(int a, int b) { return rand() % (b - a + 1) + a; }

void RandGen(char *string, size_t size) {
  for (size_t i = 0; i < size; i++) {
    string[i] = RandChar('A', 'F');
  }
}
char *LasySearch(char *string, int n, char *substring, int m) {
  int j;
  int i;
  for (i = 0; i < n - m; i++) {
    for (j = 0; j < m && *(substring + j) == *(string + i + j); j++)
      ;
    if (j == m)
      return string + i;
  }
  return nullptr;
}

int max(int a, int b) { return a > b ? a : b; }

bool IsPrefix(char *string, int m, int p) {
  int j = 0;
  for (int i = p; i >= -1; i--) {
    if (string[i] != string[j])
      return false;
  }
  return true;
}

int SuffixLen(char *string, int m, int p) {
  int result = 0;
  for (int i = p, j = m - 1; i >= 0 && string[i] == string[j];
       result++, i--, j--)
    ;
  return result;
}

char *BoyerMooreStringSearch(char *string, int n, char *substring, int m) {
  char *res = nullptr;
  int char_offset[256]; // LO
  int suffix_offset[m]; // GS
  int count = 0;

  for (int i = 0; i < 256; i++) {
    char_offset[i] = m;
  }

  for (int i = 0; i < m - 1; i++) {
    char_offset[substring[i]] = m - 1 - i;
  }
  /////////////////////////////////////
  int prefix_pos = m;

  for (int i = m - 1; i >= 0; i--) {
    if (IsPrefix(substring, m, i + 1)) {
      prefix_pos = i + 1;
    }
    suffix_offset[m - 1 - i] = prefix_pos - i + m - 1;
  }

  for (int i = 0; i < m - 1; i++) {
    int s = SuffixLen(substring, m, i);
    suffix_offset[s] = m - 1 - i + s;
    cout << "(" << suffix_offset[s] << " " << m - 1 - i + s << ")";
  }

  // for(int i: suffix_offset) cout<<i<< " ";
  // cout<<endl;

  for (int i = m - 1; res == nullptr && i < n; i++) {
    int j = m - 1;
    for (; res == nullptr && substring[j] == string[i]; i--, j--) {
      if (j == 0) {
        res = string + i;
      }
      i += max(suffix_offset[m - 1 - j], char_offset[string[i]]);
      cout << i << endl;
    }
  }
  return res;
}

int main() {
  char t[] = "AEEADDAFFEADFEDAAAFCCFEF";
  char s[] = "AFFEA";

  printf("%p\n%p\n", BoyerMooreStringSearch(t, strlen(t), s, strlen(s)),
         strstr(t, s));

  return 0;
}