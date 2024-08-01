#include <iostream>
#include <vector>
using namespace std;

int N, M, K;
// N: ���� ����, M: ���� ������ �Ͼ�� Ƚ��, K: ������ ���� ���ϴ� Ƚ��
// N: �ִ� 100��
// M, K: �ִ� 1��

vector<long long> segTree; // ������ 2^63 - 1���� ����
vector<long long> numbers;

long long init(int node, int s, int e) {
	if (s == e) return segTree[node] = numbers[s];

	int m = (s + e) / 2;
	long long a = init(node * 2, s, m);
	long long b = init(node * 2 + 1, m + 1, e);
	return segTree[node] = a + b;
}

long long update(int node, int s, int e, int ii, long long value) {
	// ii : update�� index
	// value : update�� ��

	// ���� ���� �̳��� ���� ���� ���, �״�� ��ȯ
	if (s > ii || e < ii) return segTree[node];

	segTree[node] = value; // �ϴ� �� �ֱ�

	// �ܸ� ����̸鼭 ii�� �����ϴ� ��� -> �� ����
	if (s == e) return segTree[node];

	int m = (s + e) / 2;
	long long a = update(node * 2, s, m, ii, value);
	long long b = update(node * 2 + 1, m + 1, e, ii, value);
	return segTree[node] = a + b;
}

long long query(int node, int ts, int te, int qs, int qe) {
	// Ʈ�� ������ ���� ����'��' ���ԵǴ� ��� (Ʈ�� ���� <= ���� ����)
	// �ش� ��� �� ��ȯ
	if (ts >= qs && te <= qe) return segTree[node];

	// Ʈ�� ������ ���� ������ ���� ��ġ�� �ʴ� ���
	// 0�� ��ȯ�Ͽ� ���� ������ ���� �� �ƹ� ��ȭ �Ͼ�� �ʵ��� �ϱ� ����
	if (te < qs || ts > qe) return 0;

	// �Ϻ� ��ħ Ȥ�� Ʈ�������� ���� ����'��' ���� (���� ���� <= Ʈ�� ����)
	int m = (ts + te) / 2;
	long long a = query(node * 2, ts, m, qs, qe);
	long long b = query(node * 2 + 1, m + 1, te, qs, qe);
	return a + b;
}

int main() {
	cin >> N >> M >> K;

	numbers.resize(N + 1);
	for (int i = 1; i <= N; i++) {
		cin >> numbers[i];
	}

	segTree.resize(N * 4);
	init(1, 1, N);

	vector<long long> ans;
	for (int i = 0; i < M + K; i++) {
		long long a, b, c;
		cin >> a >> b >> c;

		// update 
		if (a == 1) {
			update(1, 1, N, b, c);
		}
		// query (������)
		else if (a == 2) {
			ans.push_back(query(1, 1, N, b, c));
		}
	}

	for (long long res : ans) {
		cout << res << '\n';
	}

	return 0;
}