#include <bits/stdc++.h>
#include <algorithm>
#include <cctype>
#include <map>

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

bool test_seq(uint16_t target, vector<uint16_t> buttons, vector<int> &seq) {
    uint16_t res = 0;
    for (auto num : seq) {
        res ^= buttons.at(num-1);
    }
    return res == target;
}

// Returns buttons solution
vector<int> bruteforce(uint16_t target, vector<uint16_t> buttons, int depth_limit = 100) {
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

int p1(vector<string>& lines) {
    int sum = 0;
    for (string line: lines) {
        vector<string> splt = split_string(line, ' ');
        vector<uint16_t> buttons;

        int size = splt.at(0).size()-2;

        string target_lamps = splt.at(0);
        uint16_t target = 0;
        for (int i = 1; i < target_lamps.length()-1; i++) {
            if (target_lamps.at(i) != '#') {
                continue;
            }
            uint16_t tm = 1 << target_lamps.length()-2 >> i;
            target ^= tm;
        }

        for (int i = 1; i < splt.size()-1; i++) {
            string btn = splt.at(i);
            ranges::replace(btn, '(', ' ');
            ranges::replace(btn, ')', ' ');
            ltrim(btn);
            rtrim(btn);
            vector<string> s = split_string(btn, ',');
            uint16_t mask = 0;

            for (string str : s) {
                uint16_t tm = 1 << size-1 >> stoi(str);
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


bool test_seq2(vector<uint16_t> &target, vector<set<uint16_t>> &buttons, vector<int> &seq) {
    vector<uint16_t> res = vector<uint16_t>(target.size(), 0);

    for (auto i = 0; i < seq.size(); i++) {
        res.at(i)+=seq.at(i);
        if (res.at(i) > target.at(i)) {return false;}
    }

    return res == target;
}


// Returns buttons solution
int bruteforce2(vector<uint16_t> &target, vector<set<uint16_t>> &buttons, int depth_limit, int current_depht, vector<int> &current_seq) {
    if (depth_limit > current_depht) {
        // test each button
        for (int i = 0; i < buttons.size(); i++) {
            for (auto ln : buttons.at(i)) {
                current_seq.at(ln)++;
            }

            if (test_seq2(target,buttons,current_seq)) {
                return current_depht;
            }

            for (auto ln : buttons.at(i)) {
                current_seq.at(ln)--;
            }
        }
        for (int i = 0; i < buttons.size(); i++) {
            for (auto ln : buttons.at(i)) {
                current_seq.at(ln)++;
            }

            int res = bruteforce2(target, buttons, depth_limit, current_depht+1, current_seq);

            if (res > 0) {
                return res;
            }

            for (auto ln : buttons.at(i)) {
                current_seq.at(ln)--;
            }
        }
    }
    return 0;
}


int p2(vector<string>& lines) {
    int sum = 0;
    for (string line: lines) {
        vector<string> splt = split_string(line, ' ');
        vector<set<uint16_t>> buttons;

        vector<uint16_t> target;
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
            set<uint16_t> btns;

            for (string str : s) {
                btns.insert(stoi(str));
            }
            buttons.push_back(btns);
        }

        // Solve here
        ranges::sort(buttons, [](const set<uint16_t> &a, const set<uint16_t> &b) {
            return a.size() > b.size();
        });
        cout << "\n";
        vector<int> res_seq = vector<int>(target.size(), 0);
        for (int i = 1; i < 1000; i++) {
            cout << "testing for " << i-1 << "\n";
            int result = bruteforce2(target, buttons, i, 1, res_seq);
            sum += result;
            if (result > 0) {
                break;
            }
        }


        cout << sum << "\n";
    }
    return sum;
}

int main() {
    ifstream file("./example.txt");
    string line;
    vector<string> input;
    while (std::getline(file, line)) {input.push_back(line);}
    cout << "Part 1: " << p1(input) << "\n";
    cout << "Part 2: " << p2(input) << "\n";

    return 0;
}


