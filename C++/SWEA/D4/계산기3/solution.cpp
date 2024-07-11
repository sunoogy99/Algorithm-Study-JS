#include <iostream>
#include <string>
#include <stack>
using namespace std;

// ���� -> ���� ǥ������� �ٲٱ�
// ù��° �ǿ����� -> ���ÿ� �ְ�
// ������ ������ ���� �ǿ����� ���ÿ� �ְ� �ǿ����� ��ȯ
// ������� ���ڿ��� �����

int len;
string expr;

// (9+(5*2+1)+(3*3*7*6*9*1*7+1+8*6+6*1*1*5*2)*4*7+4*3*8*2*6+(7*8*4*5)+3+7+(2+6+5+1+7+6+7*3*(6+2)+6+6)*2+4+2*2+4*9*3)
// 952*1++33*7*6*9*1*7*1+86*+61152****+4*7*43826****

// (9+(5*2+1)*3)
// 952*1+3*+

// (9+(5*2+1)+3)
// 952*1++3+

// �� �κ��� ���� �������� ���� ���� ǥ��� -> ���� ǥ��� �ٲٴ� ������ �����Ͽ� �����Ͽ���.
string expr_transformer(int len, string old) {
	stack<char> oper; // ���� ��ȣ�� ������
	string ret = "";

	for (int i = 0; i < len; i++) {
		if (old[i] >= '0' && old[i] <= '9') {
			ret += old[i];
		}
		else if (old[i] == '(') {
			oper.push(old[i]);
		}
		else if (old[i] == ')') {
			while (oper.top() != '(') {
				ret += oper.top();
				oper.pop();
			}

			// ���� ��ȣ ������
			oper.pop();
		}
		else {
			if (oper.empty()) {
				oper.push(old[i]);
			}
			else if (oper.top() == '(') {
				oper.push(old[i]);
			}
			else if (oper.top() == '+' && old[i] == '*') {
				oper.push(old[i]);
			}
			else {
				// ���� �����ڰ� ���� �����ں��� �켱������ ���ų� ���� ���
				while (oper.top() != '(' && !(oper.top() == '+' && old[i] == '*')) {
					ret += oper.top();
					oper.pop();
				}

				oper.push(old[i]);
			}
		}
	}

	while (!oper.empty()) {
		ret += oper.top();
		oper.pop();
	}

	return ret;
}

int cal_post_expr(string expr) {
	stack<int> oprd;

	for (int i = 0; i < expr.length(); i++) {
		if (expr[i] == '+' || expr[i] == '*') {
			int operand2 = oprd.top();
			oprd.pop();
			int operand1 = oprd.top();
			oprd.pop();

			if (expr[i] == '+') {
				oprd.push(operand1 + operand2);
			}
			else {
				oprd.push(operand1 * operand2);
			}
		}
		else {
			oprd.push(expr[i] - '0');
		}
	}

	int ret = oprd.top();
	oprd.pop();
	return ret;
}

int main() {
	for (int i = 1; i <= 10; i++) {
		cin >> len;
		cin >> expr;
		string new_expr = expr_transformer(len, expr);
		cout << '#' << i << ' ' << cal_post_expr(new_expr) << endl;
	}

	return 0;
}