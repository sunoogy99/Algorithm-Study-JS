#include <iostream>
#include <cmath>
using namespace std;

int N, K;
int grid[1001][1001];

// 1-based index
int dx[5] = { 0, 0, -1, 0, 1 };
int dy[5] = { 0, 1, 0, -1, 0 };

// �̵� ���� ����
// ����) swapMoveDir(dx[i], dy[i]);
void swapMoveDir(pair<int, int>& moveDir, int coefficient) {
	moveDir = { moveDir.second * coefficient, moveDir.first * coefficient };
}

// ���� ���� �ȿ� �ִ��� �Ǵ��ϴ� �Լ�
bool inRange(int x, int y) {
	return x > 0 && x <= N && y > 0 && y <= N;
}

// K�� ��� �������� �����ϴ��� ��ǥ ��ȯ�ϱ�
pair<int, int> findStartPos(int k, pair<int, int>& moveDir) {
	int dir = ceil((double)k / N); // ��� �������� ã��
	// k, N ��� �����̹Ƿ�, �׳� k/N�� �ϸ� �Ҽ������� ������ �ʾ� ceil �Լ� ���� �ǹ̰� ����
	// 1 - ���� (0, 1)
	// 2 - ���� (-1, 0)
	// 3 - ���� (0, -1)
	// 4 - ���� (1, 0)

	moveDir = { dx[dir], dy[dir] };

	// ���� ��ǥ ���ϱ�
	int rest = k % N == 0 ? N : k % N;
	int idx;
	
	if (dir == 1 || dir == 2) idx = rest;
	else if (dir == 3 || dir == 4) idx = N + 1 - rest; // 3, 4 ���⿡���� index�� �ݴ� ������� ������
	else return { -1, -1 }; // �߸��� ��

	// row, col ������ �ƴ϶� x, y ��ǥ ������
	if (dir == 1) return { idx, 0 };
	else if (dir == 2) return { N + 1, idx };
	else if (dir == 3) return { idx, N + 1 };
	else if (dir == 4) return { 0, idx };
	else return { -1, -1 }; // �߸��� ��
}

int main() {
	cin >> N;
	
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			char c;
			cin >> c;

			// /�� �� ���� ��ȯ�� x, y swap �� -1 ������
			if (c == '/') grid[i][j] = -1;
			// \�� �� ���� ��ȯ�� x, y swap �� 1 ������
			else if (c == '\\') grid[i][j] = 1;
		}
	}

	cin >> K;

	pair<int, int> moveDir;
	// K ������ �� ó�� ���� ��ǥ ��ġ ���ϱ�
	pair<int, int> srcPos = findStartPos(K, moveDir); // ���⼭ moveDir �ʱ�ȭ��

	int hitCnt = 0; // �ſ￡ �ε��� Ƚ��
	
	// ���� �ȿ� ���ʷ� ���� �� ��ǥ ��
	int destX = srcPos.first + moveDir.first;
	int destY = srcPos.second + moveDir.second;

	while (inRange(destX, destY)) {
		// grid�� row, col �����̶� y, x ������ �����ؾ� ��
		int swapCoefficient = grid[destY][destX]; // �ſ￡ ���� �ε��� ������ ��� ����Ǵ��� �ٲ��� ���� ��� (1 or -1)
		swapMoveDir(moveDir, swapCoefficient); // �ſ￡ ���� �ε��� ���ο� ���� ����
		hitCnt++; // swap �Լ� ���� = �ſ￡ 1�� ƨ��

		destX += moveDir.first;
		destY += moveDir.second;
	} 

	cout << hitCnt << '\n';
	return 0;
}