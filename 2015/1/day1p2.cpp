#include <iostream>
#include <string>

using namespace std;

int main() {
	freopen("../input.txt", "r", stdin);
	string input;
	cin >> input;
	int floor = 0;
	for (unsigned int i = 0; i < input.size(); i++) {
		if (input[i] == '(') {
			floor += 1;
		}
		else if (input[i] == ')') {
			floor -= 1;
		}
		if (floor < 0) {
			cout << (i + 1) << "\n";
			break;
		}
	}
}
