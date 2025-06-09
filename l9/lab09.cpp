#include <values.h>
#include <iostream>
#include <stdlib.h>
#include <queue>
#include <fstream>
#include <vector>
#include <set>
#include <stack>
#include <random>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <random>
#include <vector>
#include <chrono>

struct Item
{
  int D;
  Item *Next;
  Item() : D(-1), Next(0) {}
  Item(int V) : D(V), Next(0) {}
};
//---------------------------------------------------------------------------
class Cont
{
protected:
  Item *_Head;
  Item *_Tail;

public:
  Cont() : _Head(0), _Tail(0) {}
  bool Empty(void) { return _Head ? false : true; }
  virtual void Push(int V) = 0;
  virtual int Pop(void);
  ~Cont();
};
//---------------------------------------------------------------------------
class CStack : public Cont
{
public:
  CStack() : Cont() {}
  virtual void Push(int V);
};
//---------------------------------------------------------------------------
class CQueue : public Cont
{
public:
  CQueue() : Cont() {}
  virtual void Push(int V);
};
//---------------------------------------------------------------------------
class Matrix
{
protected:
  double **_m;
  int _Size;
  virtual void Init(double Value);

public:
  Matrix(int Size);
  Matrix(const Matrix &M);
  double operator()(int row, int col);
  int Size(void) { return _Size; }
  void Set(int row, int col, double Value);
  virtual void Print(void);
  void PrintFloydPath(int From, int To);
  void PrintFloydPaths();
  ~Matrix();
};
//---------------------------------------------------------------------------
class Graph : public Matrix
{
  virtual void Init(double Value);

public:
  Graph(int Size) : Matrix(Size) { Init(MAXDOUBLE); }
  Graph(const Graph &G) : Matrix(G) {}
  virtual void Random(double Density, double MaxWeight = 1);
  virtual void Print(void);
  virtual void AddEdge(int V0, int V1, double Weight = 1);
  virtual void DeleteEdge(int V0, int V1);
  virtual int EdgeCount(void);
  int VertexCount(void) { return _Size; }
  virtual Graph ShortestPath(int From, int To);
  void Visit(int From, Cont &C);
  void FindMinEdge(int &V0, int &V1);
  Graph Floyd(Matrix &M);
  Graph Kruskal(void);
  int Hamiltonian(int v, int w, int Length, bool *Labelled, Graph &G);
  Graph HamiltonianPath(int From, int To);
};
//---------------------------------------------------------------------------
class SGraph : public Graph
{
public:
  SGraph(int Size) : Graph(Size) {}
  SGraph(const SGraph &G) : Graph(G) {}
  virtual void Random(double Density, double MaxWeight = 1);
  virtual int EdgeCount(void) { return Graph::EdgeCount() / 2; };
  virtual void AddEdge(int V0, int V1, double Weight = 1);

  // static SGraph Merge(Graph *graphs, int size, int n);
  // bool PathExist(int a, int b);
  bool HaveEulersCycle();
  bool IsConnected();
};
//---------------------------------------------------------------------------
struct Deikstra
{
  bool Label;
  double Path;
  int Vertex;
  Deikstra() : Label(false), Path(MAXDOUBLE), Vertex(-1) {}
};
//---------------------------------------------------------------------------
int Cont::Pop(void)
{
  if (_Head)
  {
    Item *I = _Head;
    _Head = _Head->Next;
    int V = I->D;
    delete I;
    if (!_Head)
      _Tail = 0;
    return V;
  }
  return -1;
}
//---------------------------------------------------------------------------
Cont::~Cont()
{
  while (_Head)
  {
    Item *I = _Head->Next;
    delete _Head;
    _Head = I;
  }
}
//---------------------------------------------------------------------------
void CStack::Push(int V)
{
  if (_Head)
  {
    Item *I = new Item(V);
    I->Next = _Head;
    _Head = I;
  }
  else
    _Tail = _Head = new Item(V);
}
//---------------------------------------------------------------------------
void CQueue::Push(int V)
{
  if (_Head)
  {
    _Tail->Next = new Item(V);
    _Tail = _Tail->Next;
  }
  else
    _Tail = _Head = new Item(V);
}
//---------------------------------------------------------------------------
Matrix::Matrix(int Size) : _Size(0), _m(0)
{
  if (Size > 0)
  {
    _Size = Size;
    _m = new double *[_Size];
    for (int i = 0; i < _Size; i++)
      _m[i] = new double[_Size];
    Init(0);
  }
}
//---------------------------------------------------------------------------
Matrix::Matrix(const Matrix &M)
{
  if (&M != this)
  {
    _Size = 0;
    _m = 0;
    if (M._Size > 0)
    {
      _Size = M._Size;
      _m = new double *[_Size];
      for (int i = 0; i < _Size; i++)
        _m[i] = new double[_Size];
    }
    for (int i = 0; i < _Size; i++)
      for (int j = 0; j < _Size; j++)
        _m[i][j] = M._m[i][j];
  }
}
//---------------------------------------------------------------------------
void Matrix::Init(double Value)
{
  for (int i = 0; i < _Size; i++)
    for (int j = 0; j < _Size; j++)
      _m[i][j] = Value;
}
//---------------------------------------------------------------------------
double Matrix::operator()(int row, int col)
{
  if (row < _Size && col < _Size && row >= 0 && col >= 0)
    return _m[row][col];
  return MAXDOUBLE;
}
//---------------------------------------------------------------------------
void Matrix::Set(int row, int col, double Value)
{
  if (row < _Size && col < _Size && row >= 0 && col >= 0)
    _m[row][col] = Value;
}
//---------------------------------------------------------------------------
void Matrix::Print(void)
{
  for (int i = 0; i < _Size; i++)
  {
    for (int j = 0; j < _Size; j++)
      printf("%10.2lf", _m[i][j]);
    printf("\n");
  }
}
//---------------------------------------------------------------------------
void Matrix::PrintFloydPath(int From, int To)
{
  if (From != To)
  {
    printf("Path from %d to %d :  ", From, To);
    int v = From;
    printf("%d ", v);
    do
    {
      v = _m[v][To];
      if (v == -1)
      {
        printf("--> |x|");
        break;
      }
      printf("--> %d ", v);
    } while (v != To);
    printf("\n");
  }
}
//---------------------------------------------------------------------------
void Matrix::PrintFloydPaths()
{
  for (int v = 0; v < _Size; v++)
    for (int w = 0; w < _Size; w++)
      PrintFloydPath(v, w);
  printf("\n");
}
//---------------------------------------------------------------------------
Matrix::~Matrix()
{
  for (int i = 0; i < _Size; i++)
    delete[] _m[i];
  delete[] _m;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void Graph::Init(double Value)
{
  for (int i = 0; i < _Size; i++)
    for (int j = 0; j < _Size; j++)
      if (i != j)
        _m[i][j] = Value;
}
//---------------------------------------------------------------------------
void Graph::AddEdge(int V0, int V1, double Weight)
{
  if (V0 >= 0 && V1 >= 0 && V0 < _Size && V1 < _Size && V0 != V1 && Weight >= 0)
  {
    _m[V0][V1] = Weight;
  }
}
//---------------------------------------------------------------------------
void Graph::DeleteEdge(int V0, int V1)
{
  if (V0 >= 0 && V1 >= 0 && V0 < _Size && V1 < _Size && V0 != V1)
  {
    _m[V0][V1] = MAXDOUBLE;
  }
}
//---------------------------------------------------------------------------
void Graph::Random(double Density, double MaxWeight)
{
  if (Density >= 0 && Density <= 1 && MaxWeight >= 0)
  {
    for (int i = 0; i < _Size; i++)
      for (int j = 0; j < _Size; j++)
        if (i > j)
        {
          if (Density >= (double)rand() / RAND_MAX)
            _m[i][j] = MaxWeight * rand() / RAND_MAX;
          else
            _m[i][j] = MAXDOUBLE;
          _m[j][i] = _m[i][j];
        }
        else
          continue;
  }
}
//---------------------------------------------------------------------------
void Graph::Print(void)
{
  for (int i = 0; i < _Size; i++)
  {
    for (int j = 0; j < _Size; j++)
      if (_m[i][j] < MAXDOUBLE)
        printf("%7.1lf", _m[i][j]);
      else
        printf("     oo");
    printf("\n");
  }
  printf("\n");
}
//---------------------------------------------------------------------------
Graph Graph::ShortestPath(int From, int To)
{
  if (From >= 0 && From < _Size && To < _Size && To >= 0)
  {
    if (From == To)
      return Graph(0);
    Deikstra *D = new Deikstra[_Size];
    D[From].Path = 0;
    D[From].Vertex = -1;
    int U, V = From;
    double SPath;
    do
    {
      D[V].Label = true;
      for (U = 0; U < _Size; U++)
      {
        if (D[U].Label || _m[V][U] == MAXDOUBLE)
          continue;
        if (D[U].Path > D[V].Path + _m[V][U])
        {
          D[U].Path = D[V].Path + _m[V][U];
          D[U].Vertex = V;
        }
      }
      SPath = MAXDOUBLE;
      V = -1;
      for (U = 0; U < _Size; U++)
        if (!(D[U].Label) && D[U].Path < SPath)
        {
          SPath = D[U].Path;
          V = U;
        }
    } while (V != -1 && V != To);
    Graph G(_Size);
    V = To;
    while (D[V].Vertex != -1)
    {
      G.AddEdge(V, D[V].Vertex, _m[V][D[V].Vertex]);
      V = D[V].Vertex;
    }
    delete[] D;
    return G;
  }
  return Graph(0);
}
//---------------------------------------------------------------------------
int Graph::EdgeCount(void)
{
  if (_Size)
  {
    int Count = 0;
    for (int i = 0; i < _Size; i++)
      for (int j = 0; j < _Size; j++)
      {
        if (i == j)
          continue;
        if (_m[i][j] < MAXDOUBLE)
          Count++;
      }
    return Count;
  }
  return 0;
}
//---------------------------------------------------------------------------
Graph Graph::Floyd(Matrix &M)
{
  Graph G(*this);
  if (M.Size() == _Size)
  {
    for (int i = 0; i < _Size; i++)
      for (int s = 0; s < _Size; s++)
        M.Set(i, s, G._m[i][s] == MAXDOUBLE ? -1 : s);
    for (int i = 0; i < _Size; i++)
      for (int s = 0; s < _Size; s++)
        if (G._m[s][i] < MAXDOUBLE)
          for (int t = 0; t < _Size; t++)
            if (G._m[i][t] < MAXDOUBLE)
              if (G._m[s][t] > G._m[s][i] + G._m[i][t])
              {
                G._m[s][t] = G._m[s][i] + G._m[i][t];
                M.Set(s, t, M(s, i));
              }
  }
  return G;
}
//---------------------------------------------------------------------------
void Graph::FindMinEdge(int &V0, int &V1)
{
  double MinWeight = MAXDOUBLE;
  V0 = V1 = -1;
  for (int i = 0; i < _Size; i++)
    for (int s = 0; s < _Size; s++)
    {
      if (i == s)
        continue;
      if (_m[i][s] < MAXDOUBLE)
      {
        MinWeight = _m[i][s];
        V0 = i;
        V1 = s;
      }
    }
  if (MinWeight == MAXDOUBLE)
    V0 = V1 = -1;
}
//---------------------------------------------------------------------------
Graph Graph::Kruskal(void)
{
  Graph MST(_Size);
  Graph G(*this);
  bool *Labelled = new bool[_Size];
  for (int i = 0; i < _Size; i++)
    Labelled[i] = false;
  int V0 = -1, V1 = -1;
  while (MST.EdgeCount() < (_Size - 1) * 2)
  {
    G.FindMinEdge(V0, V1);
    if (V0 == -1 && V1 == -1)
      break;
    if (!Labelled[V0] || !Labelled[V1])
    {
      MST.AddEdge(V0, V1, _m[V0][V1]);
      MST.AddEdge(V1, V0, _m[V0][V1]);
      Labelled[V0] = true;
      Labelled[V1] = true;
    }
    G.DeleteEdge(V0, V1);
    G.DeleteEdge(V1, V0);
  }
  delete[] Labelled;
  return MST;
}
//---------------------------------------------------------------------------
void Graph::Visit(int From, Cont &C)
{
  if (From >= 0 && From < _Size)
  {
    int V = From;
    bool *Labelled = new bool[_Size];
    for (int i = 0; i < _Size; i++)
      Labelled[i] = false;
    C.Push(V);
    Labelled[V] = true;
    do
    {
      V = C.Pop();
      printf("%d ", V);
      for (int U = 0; U < _Size; U++)
      {
        if (!Labelled[U] && _m[V][U] != MAXDOUBLE)
        {
          C.Push(U);
          Labelled[U] = true;
        }
      }
    } while (!C.Empty());
    delete[] Labelled;
    printf("\n");
  }
}
//---------------------------------------------------------------------------
int Graph::Hamiltonian(int v, int w, int Length, bool *Labelled, Graph &G)
{
  if (v == w)
    return Length == 0 ? 1 : 0;
  Labelled[v] = true;
  for (int t = 0; t < _Size; t++)
    if (_m[v][t] < MAXDOUBLE && _m[v][t] != 0 && !Labelled[t])
      if (Hamiltonian(t, w, Length - 1, Labelled, G))
      {
        G.AddEdge(t, v, _m[t][v]);
        G.AddEdge(v, t, _m[v][t]);
        return 1;
      }
  Labelled[v] = false;
  return 0;
}
//---------------------------------------------------------------------------
Graph Graph::HamiltonianPath(int From, int To)
{
  bool *Labelled = new bool[_Size];
  for (int i = 0; i < _Size; i++)
    Labelled[i] = false;
  Graph G(_Size);
  int f = Hamiltonian(From, To, _Size - 1, Labelled, G);
  delete[] Labelled;
  return G;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void SGraph::AddEdge(int V0, int V1, double Weight)
{
  Graph::AddEdge(V0, V1, 1);
  Graph::AddEdge(V1, V0, 1);
}
//---------------------------------------------------------------------------
void SGraph::Random(double Density, double MaxWeight)
{
  if (Density >= 0 && Density <= 1 && MaxWeight >= 0)
  {
    for (int i = 0; i < _Size; i++)
      for (int j = 0; j < _Size; j++)
        if (i > j)
        {
          if (Density >= (double)rand() / RAND_MAX)
            _m[i][j] = 1.0;
          else
            _m[i][j] = MAXDOUBLE;
          _m[j][i] = _m[i][j];
        }
        else
          continue;
  }
}
//---------------------------------------------------------------------------
bool SGraph::IsConnected()
{
  std::vector<int> v(_Size, false);
  std::queue<int> q;
  q.push(0);
  v[0] = true;
  int c = 1;
  while (!q.empty())
  {
    int p = q.front();
    for (int i = 0; i < _Size; i++)
    {
      if (i != p && operator()(p, i) < MAXDOUBLE && v[i] == false)
      {
        v[i] = true;
        c++;
        q.push(i);
      }
    }
    q.pop();
  }
  return (c == _Size);
}

bool SGraph::HaveEulersCycle()
{
  if (!IsConnected())
    return false;
  for (int i = 0; i < _Size; i++)
  {
    int count = 0;
    for (int j = 0; j < _Size; j++)
    {
      if (i != j && operator()(i, j) < MAXDOUBLE)
      {
        count++;
      }
    }
    if (count % 2 == 1)
      return false;
  }
  return true;
}

std::vector<int> GetEulersCycle(SGraph graph)
{
  std::stack<int> s;
  std::vector<int> c;

  s.push(0);
  while (!s.empty())
  {
    int v = s.top();
    int i;
    for (i = 0; i < graph.Size(); i++)
    {
      if (v != i && graph(v, i) < MAXDOUBLE)
      {
        graph.DeleteEdge(v, i);
        graph.DeleteEdge(i, v);
        s.push(i);
        break;
      }
    }
    if (i == graph.Size())
    {
      c.push_back(s.top());
      s.pop();
    }
  }
  return c;
}

std::vector<int> GetHamiltonCycle(SGraph graph)
{
  std::vector<int> path;
  std::vector<bool> visited(graph.Size(), false);
  std::stack<std::pair<int, int>> stack;

  stack.push({0, 0});
  visited[0] = true;
  path.push_back(0);

  while (!stack.empty())
  {
    auto &[current, next] = stack.top();

    if (path.size() == graph.Size() && graph(path.back(), 0) < MAXDOUBLE && path.back() != 0)
    {
      return path;
    }

    bool found = false;
    for (int neighbor = next; neighbor < graph.Size(); ++neighbor)
    {
      if (graph(current, neighbor) < MAXDOUBLE && !visited[neighbor])
      {
        stack.top().second = neighbor + 1;
        stack.push({neighbor, 0});
        visited[neighbor] = true;
        path.push_back(neighbor);
        found = true;
        break;
      }
    }

    if (!found)
    {
      stack.pop();
      visited[current] = false;
      path.pop_back();
    }
  }

  return {};
}

int random(int a, int b)
{
  return rand() % (b - a + 1) + a;
}

SGraph GenerateEulersGraph(int size)
{
  SGraph graph(size);

  if (size == 3 || size == 4)
  {
    for (int i = 0; i < size; i++)
      graph.AddEdge(i, (i + 1) % size);
    return graph;
  }

  int next_v = 0;
  next_v = random(4, size);
  if (next_v == size - 1)
    next_v = size;

  for (int i = 0; i < next_v; i++)
    graph.AddEdge(i, (i + 1) % next_v);

  while (next_v < size)
  {
    int a = random(0, next_v - 1);
    int b = random(0, next_v - 1);
    while (a == b)
      b = random(0, next_v - 1);

    int next_vs = random(next_v + 2, size);

    if (size - next_vs <= 1)
      next_vs = size;

    int local_v = random(next_v + 1, next_vs - 1);

    graph.AddEdge(a, next_v++);

    while (next_v < local_v)
    {
      graph.AddEdge(next_v - 1, next_v);
      next_v++;
    }
    next_v--;
    graph.AddEdge(b, next_v++);

    graph.AddEdge(a, next_v++);
    while (next_v < next_vs)
    {
      graph.AddEdge(next_v - 1, next_v);
      next_v++;
    }
    next_v--;
    graph.AddEdge(b, next_v++);
  }

  return graph;
}

SGraph GenerateHamiltonGraph(int size)
{
  SGraph graph(size);
  std::vector<int> vec(size);
  for (int i = 0; i < size; i++)
    vec[i] = i;
  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(vec.begin(), vec.end(), g);
  for (int i = 0; i < size; i++)
  {
    graph.AddEdge(vec[i], vec[(i + 1) % size]);
  }
  for (int i = 0; i < size; i++)
  {
    graph.AddEdge(random(0, size - 1), random(0, size - 1));
  }
  return graph;
}
//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  // std::ofstream outEE("outEE.txt");
  std::ofstream outHE("outHE.txt");
  // std::ofstream outEV("outEV.txt");
  std::ofstream outHV("outHV.txt");

  auto begin = std::chrono::steady_clock::now();
  auto end = std::chrono::steady_clock::now();
  auto total_time = std::chrono::duration_cast<std::chrono::microseconds>(end - end);
  srand((unsigned)time(NULL));

  // for (int i = 10; i <= 1000; i += 10)
  // {
  //   total_time = std::chrono::duration_cast<std::chrono::microseconds>(end - end);
  //   for (int j = 0; j < 100; j++)
  //   {
  //     auto g = GenerateEulersGraph(i);
  //     begin = std::chrono::steady_clock::now();
  //     GetEulersCycle(g);
  //     end = std::chrono::steady_clock::now();
  //     total_time += std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
  //     outEE << g.EdgeCount() << "|" << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << std::endl;
  //   }

  //   outEV << i << "|" << total_time.count() / 100 << std::endl;
  // }

  for (int i = 3; i <= 30; i += 1)
  {
    total_time = std::chrono::duration_cast<std::chrono::microseconds>(end - end);
    for (int j = 0; j < 100; j++)
    {
      auto g = GenerateHamiltonGraph(i);
      begin = std::chrono::steady_clock::now();
      GetHamiltonCycle(g);
      end = std::chrono::steady_clock::now();
      total_time += std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
      outHE << g.EdgeCount() << "|" << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << std::endl;
    }

    outHV << i << "|" << total_time.count() / 100 << std::endl;
  }

  return 0;
}
//---------------------------------------------------------------------------