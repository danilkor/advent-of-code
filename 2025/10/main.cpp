#include <bits/stdc++.h>
#include <algorithm>
#include <cctype>
#include <map>
#include "z3++.h"

using namespace std;

// Trim from the start (in place)
inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

// Trim from the end (in place)
inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}
vector<string> split_string(string& str, char delim) {
    vector<string> res;
    stringstream ss(str);
    string s;
    while (getline(ss, s, delim)) {
        res.push_back(s);
    }
    return res;
}

void combineUtil(vector<vector<int>> &res, vector<int> &temp, int n, int start, int k)
{
    if (k == 0)
    {
        // Store the current combination
        res.push_back(temp);
        return;
    }

    // Try each number from 'start' to 'n'
    for (int i = start; i <= n; ++i)
    {

        // Add number to current combination
        temp.push_back(i);

        // Recur to build the combination
        combineUtil(res, temp, n, i + 1, k - 1);
        temp.pop_back();
    }
}
// Function to initiate the combination generation
vector<vector<int>> getCombinations(int n, int k)
{
    vector<vector<int>> res;
    vector<int> temp;

    combineUtil(res, temp, n, 1, k);
    return res;
}

bool test_seq(int target, vector<int> buttons, vector<int> &seq) {
    int res = 0;
    for (auto num : seq) {
        res ^= buttons.at(num-1);
    }
    return res == target;
}

// Returns buttons solution
vector<int> bruteforce(int target, vector<int> buttons, int depth_limit = 100) {
    for (int i = 1; i < depth_limit; ++i) {
        for (auto seq : getCombinations(buttons.size(), i)) {
            if (test_seq(target, buttons, seq)) {
                return seq;
            }
        }
    }
    vector<int> empty;
    return empty;
}

void print_matrix(vector<vector<int>> &matrix) {
    for (auto row : matrix) {
        for (auto n : row) {
            cout << n << "\t";
        }
        cout << "\n";
    }
}


int p1(vector<string>& lines) {
    int sum = 0;
    for (string line: lines) {
        vector<string> splt = split_string(line, ' ');
        vector<int> buttons;

        int size = splt.at(0).size()-2;

        string target_lamps = splt.at(0);
        int target { 0 };
        for (int i = 1; i < target_lamps.length()-1; i++) {
            if (target_lamps.at(i) != '#') {
                continue;
            }
            int tm = 1 << target_lamps.length()-2 >> i;
            target ^= tm;
        }

        for (int i = 1; i < splt.size()-1; i++) {
            string btn = splt.at(i);
            ranges::replace(btn, '(', ' ');
            ranges::replace(btn, ')', ' ');
            ltrim(btn);
            rtrim(btn);
            vector<string> s = split_string(btn, ',');
            int mask = 0;

            for (string str : s) {
                int tm = 1 << size-1 >> stoi(str);
                mask ^= tm;
            }
            buttons.push_back(mask);
        }

        vector<int> seq = bruteforce(target, buttons, 10);
        if (seq.size() == 0) {
            cout << "no sequence found, exiting";
            return 0;
        }
        sum += seq.size();
    }
    return sum;
}


void swap_rows(vector<vector<int>> &matrix, int row1, int row2) {
    vector<int> temp_row1 = matrix.at(row1);
    matrix.at(row1) = matrix.at(row2);
    matrix.at(row2) = temp_row1;
}
int nonzero_row(vector<vector<int>> &matrix, int pivot_row, int col) {
    for (int i = pivot_row+1; i < matrix.size(); ++i) {
        if (matrix.at(i).at(col) != 0) {
            return i;
        }
    }
    return -1;
}
void make_pivot_1(vector<vector<int>> &matrix, int pivot_row, int col) {
    const int pivot_e = matrix.at(pivot_row).at(col);
    for (int i = 0; i < matrix.at(0).size(); ++i) {
        matrix.at(pivot_row).at(i) = matrix.at(pivot_row).at(i) / pivot_e;
    }
}
void eliminate_below(vector<vector<int>> &matrix, int pivot_row, int col) {
    int pivot_e = matrix.at(pivot_row).at(col);
    for (int i = pivot_row + 1; i < matrix.size(); ++i) {
        int factor = matrix.at(i).at(col);
        for (int j = 0; j < matrix.at(i).size(); ++j) {
            matrix.at(i).at(j) -= factor * matrix.at(pivot_row).at(j);
        }
    }
}
void matrix_to_row_echelon(vector<vector<int>> &matrix) {
    int pivot_row = 0;
    for (int col = 0; col < matrix.at(0).size(); ++col) {
        int nzr = nonzero_row(matrix, pivot_row, col);
        if (nzr != -1) {
            swap_rows(matrix, pivot_row, nzr);
            make_pivot_1(matrix, pivot_row, col);
            eliminate_below(matrix, pivot_row, col);
            pivot_row++;
        }
    }
}

int solve_gaussian(vector<int> &target, vector<vector<int>> &buttons) {
    // Transform into matrix
    vector<vector<int>> mx (target.size(), vector<int>(buttons.size()+1));

    //set target in the matrix
    for (int i = 0; i < target.size(); ++i) {
        mx.at(i).at(mx.at(0).size()-1) = target.at(i);
    }

    // set buttons in the matrix
    for (int i = 0; i < buttons.size(); ++i) {
        for (int j = 0; j < buttons.at(i).size(); ++j) {
            mx.at(buttons.at(i).at(j)).at(i) = 1;
        }
    }
    matrix_to_row_echelon(mx);
    return 0;
}
int solve_z3(vector<int> &target, vector<vector<int>> &buttons) {
    // Transform into matrix
    vector<vector<int>> mx (target.size(), vector<int>(buttons.size()+1));

    //set target in the matrix
    for (int i = 0; i < target.size(); ++i) {
        mx.at(i).at(mx.at(0).size()-1) = target.at(i);
    }

    // set buttons in the matrix
    for (int i = 0; i < buttons.size(); ++i) {
        for (int j = 0; j < buttons.at(i).size(); ++j) {
            mx.at(buttons.at(i).at(j)).at(i) = 1;
        }
    }

    z3::context ctx;
    z3::expr_vector x(ctx);
    z3::solver s(ctx);
    // Create variables
    vector<z3::expr> vars;
    for (int i = 0; i < mx.size(); ++i) {
        for (int j = 0; j < mx.at(0).size()-1; ++j) {
            stringstream x_name;
            x_name << "x_" << i << "_" << j;
            x.push_back(ctx.int_const(x_name.str().c_str()));
            s.add(x[x.size()-1] >= 0);
            // cout << x_name.str() << "\t";
        }
        // cout << "\n";
    }



    // Vertical variables are equal
    for (int i = 0; i < mx.at(0).size()-1; ++i) {
        for (int j = 1; j < mx.size(); j++) {
            s.add(x[(mx.at(0).size()-1)*j+i] == x[(mx.at(0).size()-1)*(j-1)+i]);
        }
    }

    // Create conditions
    for (int i = 0; i < mx.size(); ++i) {
        z3::expr_vector eq(ctx);
        for (int t = 0; t < mx.at(0).size()-1; ++t) {
            if (mx.at(i).at(t) == 1) {
                eq.push_back(x[(mx.at(0).size()-1)*i+t]);
            }
        }
        s.add(z3::sum(eq) == mx.at(i).at(mx.at(0).size()-1));
    }

    int smallest_solution = 99999999;
    z3::expr_vector fr(ctx);
    for (int i = 0; i < mx.at(0).size()-1; ++i) {
        fr.push_back(x[i]);
    }
    // s.add(z3::sum(fr) < 11);
    // cout << s << "\n\n\n\n\n";
    while (s.check() == z3::sat) {
        auto model = s.get_model();
        int sum = 0;
        for (int i = 0; i < mx.at(0).size()-1; ++i) {
            sum += model.eval(x[i]).as_int64();
            // cout << model.eval(x[i]).as_int64() << " ";
            // cout.flush();
        }
        // cout << "\n";
        if (smallest_solution > sum) {
            smallest_solution = sum;
        }
        s.add(z3::sum(fr) < smallest_solution);
        // cout << s << "\n\n\n\n\n";
    }

    return smallest_solution;
}





int p2(vector<string>& lines) {
    int sum = 0;
    for (string line: lines) {
        vector<string> splt = split_string(line, ' ');
        vector<vector<int>> buttons;

        vector<int> target;
        string target_lamps = splt.at(splt.size()-1);
        ranges::replace(target_lamps, '{', ' ');
        ranges::replace(target_lamps, '}', ' ');
        ltrim(target_lamps);
        rtrim(target_lamps);

        for (string n : split_string(target_lamps, ',')) {
            target.push_back(stoi(n));
        }

        for (int i = 1; i < splt.size()-1; i++) {
            string btn = splt.at(i);
            ranges::replace(btn, '(', ' ');
            ranges::replace(btn, ')', ' ');
            ltrim(btn);
            rtrim(btn);
            vector<string> s = split_string(btn, ',');
            vector<int> btns;

            for (string str : s) {
                btns.push_back(stoi(str));
            }
            buttons.push_back(btns);
        }

        // Solve here
        ranges::sort(buttons, [](const vector<int> &a, const vector<int> &b) {
            return a.size() > b.size();
        });

        sum += solve_z3(target, buttons);
    }
    return sum;
}



int main(int argc, char *argv[]) {
    // string filename {"./input.txt"};
    string filename {"./example.txt"};

    if (argc > 1) {
        filename = argv[1];
    }

    ifstream file(filename);
    string line;
    vector<string> input;
    while (std::getline(file, line)) {input.push_back(line);}
    cout << "Part 1: " << p1(input) << "\n";
    cout << "Part 2: " <<  p2(input) << "\n";
    return 0;
}


