#include <expression.h>


expression :: expression() {
	exp = new char;
	exp[0] = '=';
}

expression :: expression(expression &input) {
	int size = strlen(input.exp);
	exp = new char[size];
	for (int i = 0; i < size; i++) {
		exp[i] = input.exp[i];
	}
}

expression expression :: operator = (expression &input) {
	if (&input == this) {
		throw std::logic_error("Error. Equal signs.");
	}
	int size = Strlen(input.exp);
	if (strlen(exp) != size) {
		delete[] exp;
		exp = new char[size];
	}
	for (int i = 0; i < size; i++) {
		exp[i] = input.exp[i];
	}
	return *this;
}

int expression:: Strlen(char *str) {
	int i = 0;
	for (; str[i] != 0; i++) {}
	return i;
}

int expression::priority_of_sign(char sign) {
	int output;
	switch (sign)
	{
	case ')':
	case '(': output = 0; break;
	case '^': 
	case '|': output = 3; break;
	case '*':
	case '/': output = 2; break;
	case '+':
	case '-': output = 1; break;
	default: output = -1;
	}
	return output;
}

bool expression :: test_on_operation(char input) {
	if (input == '+' || input == '-' || input == '*' || input == '/' || input == '|' || input == '^') {
		return true;
	}
	else {
		return false;
	}
}

bool expression::test_on_element(char input) {
	if ((input >= '0' && input <= '9') || (input >= 'a' && input <= 'z') || (input >= 'A' && input <= 'Z')){
		return true;
	}
	else {
		return false;
	}
}

bool test_on_variables(char input) {
	if ((input >= 'a' && input <= 'z') || (input >= 'A' && input <= 'Z')) {
		return true;
	}
	else {
		return false;
	}
}

bool test_on_number(char input) {
	if (input >= '0' && input <= '9') {
		return true;
	}
	else {
		return false;
	}
}

expression::expression(char* input) {
	int pos = 0, len = Strlen(input);
	char sign, t;
	stack ExpStack, OperationStack;
	bool key;
	do {
		sign = input[pos++];
		if (test_on_element(sign)) {
			ExpStack.push(sign);
		}
		else if (sign == '(') {
			OperationStack.push(sign);
		}
		else if (sign == ')') {
			t = OperationStack.top();
			while (OperationStack.top() != '(') {
				t = OperationStack.top();
				ExpStack.push(t);
				OperationStack.pop();
			}
			OperationStack.pop();
		}
		else {
			if ((OperationStack.see()) && (priority_of_sign(sign) < priority_of_sign(OperationStack.top()))) {
				while (OperationStack.see()) {
					t = OperationStack.top();
					if (priority_of_sign(sign) <= priority_of_sign(t)) {
						ExpStack.push(t);
						OperationStack.pop();
					}
					else {
						OperationStack.push(t);
						OperationStack.pop();
						break;
					}
				}
			}
			OperationStack.push(sign);
		}
	}
	while ((sign != 0) && (pos < (len+1)) && (sign != ' '));
	if (sign == ' ') {
		do {
			sign = input[pos++];
			if (name_var.test_on_equel(sign)) {
				throw std::logic_error("error in input");
			}
			if (test_on_variables(sign)) {
				if (input[pos++] == '=') {
					if (test_on_number(input[pos])) {
						var.push(input[pos]);
						name_var.push(sign);
					}
					else {
					throw std::logic_error("error in input");
					}
				}
				else {
					throw std::logic_error("error in input");
				}
			}
			else {
				throw std::logic_error("error in input");
			}
			pos+=2;
		} while (sign != 0 && pos < (len + 1));
	}
	pos = 0;
	for (int i = 0; (i < len) && (input[i] != ' '); i++) {
		if ((input[i] != '(') && (input[i] != ')')) {
			pos++;
		}
	}
	exp = new char[len+1];
	exp[pos] = 0;
	pos--;
	while (ExpStack.see()) {
		exp[pos] = ExpStack.top();
		ExpStack.pop();
		pos--;
	}
}

double expression::counting() {
	return 0;
}
