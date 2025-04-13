#include <chrono>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>
#include <cstring>

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

char *KMPSearch(char *string, int n, char *substring, int m) {
  int *Next, i, j;
  char *result = nullptr;
  Next = (int *)malloc(m * sizeof(int));
  for (Next[0] = j = -1, i = 1; i < m; i++) {
    for (; j > -1 && substring[j + 1] != substring[i]; j = Next[j])
      ;
    if (substring[j + 1] == substring[i])
      j++;
    Next[i] = j;
  }

  for (j = -1, i = 0; i < n && nullptr == result; i++) {
    for (; j > -1 && substring[j + 1] != string[i] && nullptr == result; j = Next[j])
      ;
    if (substring[j + 1] == string[i])
      j++;
    if (j == m - 1) {
      result = string + i - j;
    }
  }

  free(Next);
  return result;
}

int main() {
  srand(time(0));

  int repeat = 10000;
  int str_len = 10;
  int text_len;
  ofstream output_TY("ouput_TY.txt"); //different text, find
  ofstream output_TN("output_TN.txt"); //different text, not find
  ofstream output_SY("ouput_SY.txt"); //different string, find
  ofstream output_SN("output_SN.txt"); // different string, not find
  ofstream log("log.txt");

  auto start = steady_clock::now();
  auto end = steady_clock::now();

  size_t fun_time, str_time;

  size_t fun_time_succ, fun_time_fail, str_time_succ, str_time_fail;
  size_t succ_times, fail_times;
  char *text;
  char *str;
  for (int i = 5; i <= 50; i += 5) {
    text_len = i * 1000;
    text = (char *)calloc(text_len + 1, sizeof(char));
    RandGen(text, text_len);
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

      int a = (rand()%text_len -str_len-10 -1);
      // cout<<a<<" " << a + str_len << endl;;
      memcpy(str, text+a-1, str_len);

      start = steady_clock::now();
      str_res = strstr(text, str);
      end = steady_clock::now();
      str_time = duration_cast<nanoseconds>(end - start).count();

      start = steady_clock::now();
      fun_res = KMPSearch(text, text_len, str, str_len);
      end = steady_clock::now();
      fun_time = duration_cast<nanoseconds>(end - start).count();

      log << i * 1000 << " " << fun_time << " " << str_time << " " << str << " "
          << (fun_res == str_res ? "SUCC" : "FAIL") << endl;

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

  log<<"/*text tests end*/"<<endl;
  text_len = 50'000;

  for (int i = 5; i <= 100; i += 5) {
    str_len = i;
    text = (char *)calloc(text_len + 1, sizeof(char));
    RandGen(text, text_len);
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

      int a = (rand()%text_len -str_len-10 -1);
      // cout<<a<<" " << a + str_len << endl;;
      memcpy(str, text+a-1, str_len);
      str[str_len / 2] = 'F' + (j % 2);
      start = steady_clock::now();
      str_res = strstr(text, str);
      end = steady_clock::now();
      str_time = duration_cast<nanoseconds>(end - start).count();

      start = steady_clock::now();
      fun_res = KMPSearch(text, text_len, str, str_len);
      end = steady_clock::now();
      fun_time = duration_cast<nanoseconds>(end - start).count();

      log << i * 1000 << " " << fun_time << " " << str_time << " " << str << " "
          << (fun_res == str_res ? "SUCC" : "FAIL") << endl;

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
    output_SN << i  << "|" << fun_time_fail / fail_times << "|"
              << str_time_fail / fail_times << "|" << fail_times << endl;
    output_SY << i  << "|" << fun_time_succ / succ_times << "|"
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