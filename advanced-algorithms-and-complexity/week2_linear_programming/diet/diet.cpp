#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdio>
#include <cmath>
#include <set>
using namespace std;

typedef vector<vector<double>> Matrix;
typedef vector<double> Column;

const double SUM_MAX = 1e+9;
const double EPS = 1e-6;

struct Position {
  Position(int column, int row):
      column(column),
      row(row)
  {}
  int column;
  int row;
};

class GaussianElimination {
  Matrix a;
  Column b;

  Position SelectPivotElement(const Matrix &a, int num_vars_solved) {
    Position pivot_element(num_vars_solved, num_vars_solved);
    while(pivot_element.row < a.size() && !a[pivot_element.row][pivot_element.column]) {
        ++pivot_element.row;
    }
    if(pivot_element.row == a.size())
        pivot_element.row = num_vars_solved;
    return pivot_element;
  }

  void SwapLines(Matrix &a, Column &b, std::vector <bool> &used_rows, Position &pivot_element) {
    std::swap(a[pivot_element.column], a[pivot_element.row]);
    std::swap(b[pivot_element.column], b[pivot_element.row]);
    std::swap(used_rows[pivot_element.column], used_rows[pivot_element.row]);
    pivot_element.row = pivot_element.column;
  }

  void ProcessPivotElement(Matrix &a, Column &b, const Position &pivot_element) {
    if(!a[pivot_element.row][pivot_element.column]) {
        return;
    }
    else {
        double row_normalizer = a[pivot_element.row][pivot_element.column];
        for(int j = 0; j < a[pivot_element.row].size(); ++j) {
            a[pivot_element.row][j] /= row_normalizer;
        }
        b[pivot_element.row] /= row_normalizer;

        for(int i = 0; i < a.size(); ++i) {
            if(i != pivot_element.row) {
                double col_multiplier = a[i][pivot_element.column];
                for(int j = 0; j < a[i].size(); ++j) {
                    a[i][j] -= (col_multiplier * a[pivot_element.row][j]);
                }
                b[i] -= (col_multiplier * b[pivot_element.row]);    
            }
        }
    }
  }

  void MarkPivotElementUsed(const Position &pivot_element, std::vector <bool> &used_rows, std::vector <bool> &used_columns) {
    used_rows[pivot_element.row] = true;
    used_columns[pivot_element.column] = true;
  }

public:
  GaussianElimination(Matrix &a, Column &b): a(a), b(b) { }
  pair<int, Column> solve() {
    int size = a.size();

    std::vector <bool> used_columns(size, false);
    std::vector <bool> used_rows(size, false);
    int result = 0;
    for (int step = 0; step < size; ++step) {
        Position pivot_element = SelectPivotElement(a, step);
        if(a[pivot_element.row][pivot_element.column] == 0 && b[pivot_element.row] != 0) {
          result = -1;
          break;
        }
        else if(a[pivot_element.row][pivot_element.column] == 0 && b[pivot_element.row] == 0) {
          result = 1;
        }
        else if(result == 0) {
          SwapLines(a, b, used_rows, pivot_element);
          ProcessPivotElement(a, b, pivot_element);
        }
        MarkPivotElementUsed(pivot_element, used_rows, used_columns);
    }
    return make_pair(result, b);
  }
};


class Diet {
private:
  int n;
  int m;
  Matrix a;
  Column b;
  Column c;

  void get_combinations(set<int> elements, int m, set<set<int>> &combinations) {
    if(elements.size() < m) {
      return;
    }
    else if(elements.size() == m) {
      combinations.insert(elements);
    }
    else {
      auto first_elem = *elements.begin();
      elements.erase(elements.begin());
      set<set<int>> smaller_combinations;
      get_combinations(elements, m - 1, smaller_combinations);
      for(auto s: smaller_combinations) {
        s.insert(first_elem);
        combinations.insert(s);
      }
      get_combinations(elements, m, combinations);
     }
  }

public:
  Diet(int n, int m, Matrix &a, Column &b, Column &c): n(n), m(m), a(a), b(b), c(c) { }
  pair<int, Column> solve() {
    // Add inequalities of the form amount_i >= 0 to the original set of inequalities.
    for(int i = 0; i < m; ++i) {
      Column x(m, 0);
      x[i] = -1;
      a.push_back(x);
      b.push_back(0.0);
    }
    // Adding an inequality of the form amount_1 + amount_2 + ... + amount_m <= 10^9.
    a.push_back(Column(m, 1));
    b.push_back(SUM_MAX);

    int result = -1;
    Column answer;
    double optimal_value = 0.0;

    //Select m inequalities from the set of all inequalities and treat them as equalities
    set<int> elements;
    for(int i = 0; i < a.size(); ++i) elements.insert(i);
    set<set<int>> combinations;
    get_combinations(elements, m, combinations);

    for(auto comb: combinations) {
      Matrix equalities_a;
      Column equalities_b;
      Matrix inequalities_a;
      Column inequalities_b;
      for(int i = 0; i < a.size(); ++i) {
        if(comb.find(i) != comb.end()) {
          equalities_a.push_back(a[i]);
          equalities_b.push_back(b[i]);
        }
        else {
          inequalities_a.push_back(a[i]);
          inequalities_b.push_back(b[i]);
        }
      }

      // cout << "equalities.size(): " << equalities_a.size() << "\n";
      // cout << "inequalities.size(): " << inequalities_a.size() << "\n";
      // Use gaussian elimination to solve the system of equations
      auto solution = GaussianElimination(equalities_a, equalities_b).solve();
      if(solution.first == 0) {
        // If Bounded, test solution for all other inequalities
        bool valid = true;
        for(auto z = 0; z < inequalities_a.size(); ++z) {
          double ineq = 0.0;
          for(int k = 0; k < inequalities_a[z].size(); ++k) ineq += inequalities_a[z][k]*solution.second[k];
          if(ineq >= inequalities_b[z] + EPS) {
            valid = false;
            break;
          }
        }

        if(!valid) {
          continue;
        }

        //If all other inequalities are satisfied, check for boundedness
        double sum_amounts = 0.0;
        for(auto x: solution.second) sum_amounts += x;
        if(sum_amounts >= SUM_MAX - EPS && sum_amounts <= SUM_MAX + EPS) {
          result = 1;
          break;
        }

        // If all other inequalities are satisfied and solution is bounded, compute the value of objective function
        result = 0;
        double val = 0.0;
        for(int i = 0; i < solution.second.size(); ++i) val += c[i]*solution.second[i];
        if(val > optimal_value) {
          optimal_value = val;
          answer = solution.second;
        }
      }
    }

    return make_pair(result, answer);
  }
};

int main(){
  int n, m;
  cin >> n >> m;
  Matrix A(n, vector<double>(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> A[i][j];
    }
  }

  Column b(n);
  for (int i = 0; i < n; i++) {
    cin >> b[i];
  }
  Column c(m);
  for (int i = 0; i < m; i++) {
    cin >> c[i];
  }

  pair<int, Column> ans = Diet(n, m, A, b, c).solve();

  switch (ans.first) {
    case -1: 
      printf("No solution\n");
      break;
    case 0: 
      printf("Bounded solution\n");
      for (int i = 0; i < m; i++) {
        printf("%.18f%c", ans.second[i], " \n"[i + 1 == m]);
      }
      break;
    case 1:
      printf("Infinity\n");
      break;      
  }
  return 0;
}
