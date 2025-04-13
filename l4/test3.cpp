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
  }

  for (int i = m - 1; res == nullptr && i < n; i++) {
    int j = m - 1;
    for (; res == nullptr && substring[j] == string[i]; i--, j--) {
      if (j == 0) {
        res = string + i;
      }
      i += max(suffix_offset[m - 1 - j], char_offset[string[i]]);
    }
  }
  return res;
}

int main() {
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

  size_t fun_time_succ, fun_time_fail, str_time_succ, str_time_fail;
  size_t succ_times, fail_times;
  char *text;
  char *str;
  for (int i = 5; i <= 50; i += 5) {
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

    for (int j = 0; j < repeat; j++) {
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

      log << i * 1000 << " " << fun_time << " " << str_time << " " << str << " "
          << (fun_res == str_res ? "SUCC" : "FAIL") << endl;
      if (fun_res != str_res) {
        cout << text << endl << str << endl;
        printf("%ld\n", fun_res - str_res);
        exit(1);
      }
      if (str_res == nullptr) {
        fun_time_fail += fun_time;
        str_time_fail += str_time;
        fail_times++;
      } else {
        fun_time_succ += fun_time;
        str_time_succ += str_time;
        succ_times++;
      }
    }
    output_TN << i * 1000 << "|" << fun_time_fail / fail_times << "|"
              << str_time_fail / fail_times << "|" << fail_times << endl;
    output_TY << i * 1000 << "|" << fun_time_succ / succ_times << "|"
              << str_time_succ / succ_times << "|" << succ_times << endl;
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