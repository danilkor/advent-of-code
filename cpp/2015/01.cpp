#include <bits/stdc++.h>
#include <aoc.hpp>
#include <string_stuff.hpp>

using namespace std;

long long p1(const vector<string> &lines) {
    long long result {0};



    return result;
}

long long p2(const vector<string> &lines) {
    long long result {0};



    return result;
}



int main() {
    time_t start, end;
    time(&start);

    ios_base::sync_with_stdio(false);

    const auto input = aoc::slurp_lines("/dev/stdin");
    long long s1 = p1(input);
    long long s2 = p2(input);
    cout << "P1: " << s1 << endl;
    cout << "P2: " << s2 << endl;

    time(&end);
    double time_taken = double(end - start);
    cout << endl << endl;
    cout << "Time taken: " << fixed << time_taken << setprecision(5);
    cout << " sec " << endl;
    return 0;
}