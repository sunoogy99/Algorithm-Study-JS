#include <iostream>
using namespace std;

int n, m; // n : row, m : column
int grid[101][101];

int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, 1, 0, -1 };

bool inRange(int x, int y) {
	return x > 0 && x <= m && y > 0 && y <= n;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m;

	pair<int, int> pos = { 1, 1 }; // ����� x, y
	int moveDir = 0; // �����̴� ����

	int num = 1;
	grid[pos.second][pos.first] = num;

	for (int i = 2; i <= n * m; i++) {
		// ���� �̵��� ���� ����
		int newX = pos.first + dx[moveDir];
		int newY = pos.second + dy[moveDir];

		// �̵� ���� ���� �Ǻ� �� ���� ��ȯ
		if (!inRange(newX, newY) || grid[newY][newX] != 0) {
			moveDir = (moveDir + 1) % 4;
		}

		// ����� ���� ��ǥ ����
		pos.first = pos.first + dx[moveDir];
		pos.second = pos.second + dy[moveDir];

		// x, y => col, row�̹Ƿ� ������ pos.second, pos.first�� �־�� ��
		grid[pos.second][pos.first] = i;
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cout << grid[i][j] << ' ';
		}

		cout << '\n';
	}

	return 0;
}