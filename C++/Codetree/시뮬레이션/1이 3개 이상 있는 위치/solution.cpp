#include <iostream>
using namespace std;

int n;
int grid[101][101];

int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };

bool inRange(int x, int y) {
	return x > 0 && x <= n && y > 0 && y <= n;
}

int main() {
	cin >> n;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> grid[i][j];
		}
	}

	int res = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			int oCnt = 0;
			for (int d = 0; d < 4; d++) {
				int newX = i + dx[d];
				int newY = j + dy[d];

				// ĭ�� 0�� ���� �־ �湮 �����ϸ�, �ֺ� ĭ�� 1�� �� �� �ִ��� ī��Ʈ�ϰ�
				// 1�� 3�� �̻��̸� res ���� ��Ŵ
				if (inRange(newX, newY) && grid[newX][newY]) {
					oCnt++;
				}
			}

			if (oCnt >= 3) {
				res++;
			}
		}
	}

	cout << res << '\n';
	return 0;
}