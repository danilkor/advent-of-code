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

map<tuple<bool, bool, string>, long long> memo;
long long dfs2(vector<vector<string>> &g, bool dac, bool fft, string pos) {
    if (memo.contains(tuple(dac, fft, pos))) {
        return memo.at(tuple(dac, fft, pos));
    }
    if (pos == "out") {
        if (dac && fft) {
            return 1;
        }
        return 0;
    }
    for (long long i = 0; i < g.size(); ++i) {
        if (g.at(i).at(0) == pos) {
            long long sum = 0;
            for (long long j = 1; j < g.at(i).size(); ++j) {
                if (g.at(i).at(j) == "dac") {
                    sum += dfs2(g, true, fft, g.at(i).at(j));
                } else if (g.at(i).at(j) == "fft") {
                    sum += dfs2(g, dac, true, g.at(i).at(j));
                } else {
                    sum += dfs2(g, dac, fft, g.at(i).at(j));
                }
            }
            memo.insert({tuple(dac, fft, pos), sum});
            return sum;
        }
    }
    return 0;
}

long long p2(vector<string> &lines) {
    vector<vector<string>> con;
    for (long long i = 0; i < lines.size(); ++i) {
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
    string pos = "svr";
    long long result = dfs2(con, false, false, pos);
    return result;
}


int main() {
    ifstream file("./input.txt");
    string line;
    vector<string> input;
    while (std::getline(file, line)) {input.push_back(line);}

    int p1r = p1(input);
    cout << "Part 1: " << p1r << "\n";
    long long p2r = p2(input);
    // cout << "Part 1: " << p1r << "\n";
    cout << "Part 2: " << p2r  << "\n";
    return 0;
}