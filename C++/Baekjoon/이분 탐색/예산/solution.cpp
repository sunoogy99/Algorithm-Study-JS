#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

long long N, M;
vector<long long> costs;

// ���Ѱ� �������� ���� ������ �� �ִ��� ���θ� ��ȯ�ϴ� �Լ�
bool checkEnough(long long upLimit) {
	long long sum = 0;
	for (int i = 0; i < N; i++) {
		sum += min(upLimit, costs[i]);
	}

	if (sum <= M) return true;
	else return false;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;

	costs.resize(N);
	for (int i = 0; i < N; i++) {
		cin >> costs[i];
	}

	cin >> M;

	sort(costs.begin(), costs.end());

	long long start = 1; // costs[0]���� �����ϸ� M�� costs[0]���� ���� ��� �̻��� ���� ��µ�
	long long end = costs[N - 1];

	long long ans;
	while (start <= end) {
		long long mid = start + (end - start) / 2;
		
		if (checkEnough(mid)) {
			ans = mid;
			start = mid + 1;
		}
		else {
			end = mid - 1;
		}
	}

	cout << ans << '\n';
	return 0;
}