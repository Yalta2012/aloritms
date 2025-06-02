#include <algorithm>
#include <exception>
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <stdlib.h>
#include <values.h>

using namespace std;

struct Pair {
  int higth;
  int lenght;
};

int realSolution(vector<int> &heights, vector<int> &lengths,
                 vector<Pair> &sol) {
  if (heights.size() != lengths.size()) {
    return -1;
  }
  sol.clear();

  sort(heights.begin(), heights.end());
  sort(lengths.begin(), lengths.end());
  int res = 0;
  for (int i = 0; i < lengths.size(); i++) {
    res += abs(heights[i] - lengths[i]);
    sol.push_back(Pair{heights[i], lengths[i]});
  }

  return res;
}

int solution(const vector<int> &heights, const vector<int> &_lengths,
             vector<Pair> &sol) {
  sol.clear();
  vector<int> lengths(_lengths.begin(), _lengths.end());

  for(auto h: heights){
	int mx = -1;
	for(int i = 0; i< lengths.size(); i++){
		if(lengths[i]!=-1 &&  (mx==-1 || (abs(lengths[mx] - h) > abs(lengths[i] - h))) ){
			mx = i;
			if(lengths[i]-h == 0) break;
		}

	}
	sol.push_back(Pair{h,lengths[mx]});
	lengths[mx] = -1;

  }
  int res = 0;
  for (auto i : sol) {
    res += abs(i.higth - i.lenght);
  }
  return res;
}

int main(int argc, char *argv[]) {
  try {
    ifstream in("input.txt");
    int a, b;
    in >> a;
    vector<int> heights(a);
    for (int i = 0; i < a; i++) {
      in >> heights[i];
    }
    in >> b;
    vector<int> lengths(b);
    for (int i = 0; i < b; i++) {
      in >> lengths[i];
    }
    if (a > b) {
      throw "Лыж меньше чем спортсменов";
    }
    vector<Pair> sol;
    cout << "Итог:" << solution(heights, lengths, sol) << endl;
    for (auto i : sol) {
      cout << i.higth << " " << i.lenght << endl;
    }
    cout << "Настоящий итог:" << realSolution(heights, lengths, sol) << endl;
    for (auto i : sol) {
      cout << i.higth << " " << i.lenght << endl;
    }
  } catch (const exception &e) {
    cerr << e.what() << endl;
  }
}
