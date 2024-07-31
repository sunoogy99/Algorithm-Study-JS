// ���� ������ �ſ� ū ���¿��� ���� ���� ��� ���� ��� ���踸 �ʿ��� ��� �̿��ϴ� ���
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int N;

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;

	vector<int> numbers(N);
	vector<int> v(N);
	for (int i = 0; i < N; i++) {
		cin >> numbers[i];
		v[i] = numbers[i];
	}

	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());

	for (int i = 0; i < N; i++) {
		numbers[i] = lower_bound(v.begin(), v.end(), numbers[i]) - v.begin();
	}

	for (const int num : numbers) {
		cout << num << ' ';
	}

	return 0;
}