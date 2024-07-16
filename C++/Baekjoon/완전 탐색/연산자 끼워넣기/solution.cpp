#include <algorithm>
#include <climits>
#include <iostream>
#include <string>
using namespace std;

#define ADD 0
#define SUB 1
#define MUL	2
#define DIV	3

int N;
int numbers[12];
int oper[4];

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> numbers[i];
	}

	for (int i = 0; i < 4; i++) {
		cin >> oper[i];
	}

	string operString = "";
	char operChar[4] = { '+', '-', '*', '/' };
	for (int i = 0; i < 4; i++) {
		// ���� ���� �� �ݺ��ؼ� �߰��ϴ� ��� string(Ƚ��, �ݺ��� ����)
		operString += string(oper[i], operChar[i]);
	}

	// next_permutation�� ����� �� �����ؼ� ����ؾ� ��� ����� ���� ���� Ž���� �� ����
	// ���� �� ���� ���� - ASCII CODE ���� - *, +, -, /
	sort(operString.begin(), operString.end());

	int maxVal = INT_MIN;
	int minVal = INT_MAX;
	do {
		int val = numbers[0]; // �ʱⰪ
		for (int i = 0; i < operString.length(); i++) {
			int val2 = numbers[i + 1];
			if (operString[i] == '+') {
				val = val + val2;
			}
			else if (operString[i] == '-') {
				val = val - val2;
			}
			else if (operString[i] == '*') {
				val = val * val2;
			}
			else if (operString[i] == '/') {
				val = val / val2;
			}
		}

		maxVal = max(val, maxVal);
		minVal = min(val, minVal);
	} while (next_permutation(operString.begin(), operString.end()));

	cout << maxVal << '\n' << minVal << '\n';
	return 0;
}