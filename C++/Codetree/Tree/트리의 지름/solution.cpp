#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

int n;
vector<vector<pair<int, int>>> tree; // ����� ����, ����ġ ����
bool visited[100001];

int maxDist;
int farVer;

void dfs(int x, int sum) {
	visited[x] = true;
	bool noneGo = true; // �� �̻� Ž���� ��尡 ���� ���

	for (pair<int, int> c : tree[x]) {
		if (!visited[c.first]) {
			noneGo = false;
			dfs(c.first, sum + c.second);
		}
	}

	// ���� ����� ���
	if (noneGo) {
		if (sum > maxDist) {
			maxDist = sum;
			farVer = x;
		}

		return;
	}
}

int main() {
	cin >> n;

	tree.resize(n + 1);

	int a, b, w;
	for (int i = 0; i < n - 1; i++) {
		cin >> a >> b >> w;
		tree[a].push_back(make_pair(b, w));
		tree[b].push_back(make_pair(a, w));
	}

	dfs(1, 0);
	memset(visited, false, sizeof visited);

	dfs(farVer, 0);

	cout << maxDist << '\n';
	return 0;
}