#include <iostream>
using namespace std;

int n, m;
int parent[100001];
int height[100001];
int cnt[100001]; // i�� ����� ���� ���� ����

int Find(int x) {
	if (x == parent[x]) return x;
	else return parent[x] = Find(parent[x]);
}

void Union(int x, int y) {
	x = Find(x);
	y = Find(y);

	if (x == y) return;

	// cnt�� �θ� ����� �͸� �����ϸ� ��
	// 2�� ���꿡 ���ؼ� Find�� rootId ã�Ƽ�
	// rootId�� cnt�� ��ȯ�ϸ� ��

	if (height[x] < height[y]) {
		parent[x] = y; // y �ؿ� x�� �޸� ��
		cnt[y] += cnt[x];
	}
	else if (height[x] > height[y]) {
		parent[y] = x; // x �ؿ� y�� �޸� ��
		cnt[x] += cnt[y];
	}
	else {
		parent[y] = x;
		height[x]++;
		cnt[x] += cnt[y];
	}
}

int main() {
	cin >> n >> m;

	for (int i = 0; i <= n; i++) {
		parent[i] = i;
		height[i] = 0;
		cnt[i] = 1; // �ڱ� �ڽ� ������ ������ �ʱ� ����
	}

	for (int i = 0; i < m; i++) {
		char op;
		int a, b;

		cin >> op;

		if (op == 'x') {
			cin >> a >> b;
			Union(a, b);
		}
		else if (op == 'y') {
			cin >> a;
			int rootId = Find(a);
			cout << cnt[rootId] << '\n';
		}
	}

	return 0;
}