#include <iostream>
#include <vector>
using namespace std;

int precedence(char Operator) {
	switch (Operator)
	{
	case '+':
	case '-':
		return 1;
		break;
	case '*':
	case '/':
		return 2;
		break;
	case '^':
		return 3;
		break;
	default:
		return 0;
		break;
	}
}

bool isOperator(char opd) {
	switch (opd)
	{
	case '+':
	case '-':
	case '*':
	case '/':
	case '^':
		return true;
		break;
	default:
		return false;
		break;
	}
}

void stringToStringArray(vector<string>& expression, string tempExpression) {
	int reader = 0;
	while (reader < tempExpression.length()) {
		string temp;
		temp = tempExpression[reader];		
		if (reader < tempExpression.length() && !isOperator(tempExpression[reader]) && tempExpression[reader] != '(' && tempExpression[reader] != ')') {
			reader++;
			while (reader < tempExpression.length() && !isOperator(tempExpression[reader]) && tempExpression[reader] != '(' && tempExpression[reader] != ')') {
				temp += tempExpression[reader];
				reader++;
			}
		}
		else reader++;
		expression.push_back(temp);
	}
}

string infixToPrefix(vector<string> expression) {
	string ready = "";
	char stack[50] = "";
	stack[0] = '(';
	int top = 0;
	vector<string> temp;
	vector<string> tempRev;
	int reader = 0;

	while (reader < expression.size()) {
		if (expression[reader] == "(") {
			stack[++top] = '(';
		}
		else if (expression[reader] == ")") {
			while (top >= 0 && stack[top] != '(') {
				tempRev.push_back(temp.back());
				temp.pop_back();
				tempRev.push_back(temp.back());
				temp.pop_back();
				string x;
				x = stack[top--];
				x += tempRev.back();
				tempRev.pop_back();
				x += tempRev.back();
				tempRev.pop_back();
				temp.push_back(x);
			}
			top--;
		}
		else if (isOperator(expression[reader][0])) {
			while (top >= 0 && precedence(expression[reader][0]) <= precedence(stack[top])) {
				tempRev.push_back(temp.back());
				temp.pop_back();
				tempRev.push_back(temp.back());
				temp.pop_back();
				string x;
				x = stack[top--];
				x += tempRev.back();
				tempRev.pop_back();
				x += tempRev.back();
				tempRev.pop_back();
				temp.push_back(x);
			}
			stack[++top] = expression[reader][0];
		}
		else {
			temp.push_back(expression[reader]);
		}
		reader++;
	}
	while (top > 0) {
		tempRev.push_back(temp.back());
		temp.pop_back();
		tempRev.push_back(temp.back());
		temp.pop_back();
		string x;
		x = stack[top--];
		x += tempRev.back();
		tempRev.pop_back();
		x += tempRev.back();
		tempRev.pop_back();
		temp.push_back(x);
	}
	while (temp.size() > 0) {
		tempRev.push_back(temp.back());
		temp.pop_back();
	}
	while (tempRev.size() > 0) {
		ready += tempRev.back();
		tempRev.pop_back();
	}
	return ready;
}


int main()
{
	while (true) {
		vector<string> expression;
		string tempExpression;
		cout << "enter the infix expression: ";
		cin >> tempExpression;
		stringToStringArray(expression, tempExpression);
		cout << infixToPrefix(expression) << endl;
	}
	return 0;
}