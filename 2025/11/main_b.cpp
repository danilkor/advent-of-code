#include <bits/stdc++.h>
#include <algorithm>

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


int dfs(vector<vector<string>> &g, set<string> &visited, string pos) {
    if (pos == "out") {
        return 1;
    }
    if (visited.contains(pos)) {
            return 0;
    }
    visited.insert(pos);
    for (int i = 0; i < g.size(); ++i) {
        if (g.at(i).at(0) == pos) {
            int sum = 0;
            for (int j = 1; j < g.at(i).size(); ++j) {
                sum += dfs(g, visited, g.at(i).at(j));
            }
            visited.erase(pos);
            return sum;
        }
    }
    visited.erase(pos);
    return 0;
}

int p1(vector<string> &lines) {
    vector<vector<string>> con;
    for (int i = 0; i < lines.size(); ++i) {
        string line = lines.at(i);
        ltrim(line); rtrim(line);
        vector<string> splt = split_string(line, ':');
        con.push_back(vector<string>{splt.at(0)});
        line = splt.at(1);
        ltrim(line);
        vector<string> connections = split_string(line, ' ');
        for (auto connection : connections) {
            con.at(i).push_back(connection);
        }
    }

    cout << "done connections" << "\n";
    set<string> vis;
    string pos = "you";
    int result = dfs(con, vis, pos);
    return result;
}

map<string, int> memo;

// this one backtracks
int dfs2(vector<vector<string>> &g, set<string> &visited, string pos) {
    // if (memo.contains(pos)) {
    //     cout << "used memo" << "\n";
    //     return memo.at(pos);
    // }
    if (pos == "srv") {
        if (visited.contains("fft") && visited.contains("dac")) {
            return 1;
        }
        return 0;
    }
    if (visited.contains(pos)) {
        return 0;
    }
    visited.insert(pos);
    int sum = 0;
    for (int i = 0; i < g.size(); ++i) {
        bool contains = false;
        for (int j = 1; j < g.at(i).size(); ++j) {
            if (g.at(i).at(j) == pos) {
                contains = true;
                break;
            }
        }
        if (contains) {
            sum += dfs2(g, visited, g.at(i).at(0));
        }
    }
    visited.erase(pos);
    memo.insert({pos, sum});
    return sum;
}

int p2(vector<string> &lines) {
    vector<vector<string>> con;
    for (int i = 0; i < lines.size(); ++i) {
        string line = lines.at(i);
        ltrim(line); rtrim(line);
        vector<string> splt = split_string(line, ':');
        con.push_back(vector<string>{splt.at(0)});
        line = splt.at(1);
        ltrim(line);
        vector<string> connections = split_string(line, ' ');
        for (auto connection : connections) {
            con.at(i).push_back(connection);
        }
    }

    cout << "done connections" << "\n";
    set<string> vis;
    string pos = "out";
    int result = dfs2(con, vis, pos);
    return result;
}



int main() {
    ifstream file("./example.txt");
    string line;
    vector<string> input;
    while (std::getline(file, line)) {input.push_back(line);}

    int p1r = p1(input);
    // cout << "Part 1: " << p1r << "\n";
    int p2r = p2(input);
    cout << "Part 1: " << p1r << "\n";
    cout << "Part 2: " << p2r  << "\n";
    return 0;
}