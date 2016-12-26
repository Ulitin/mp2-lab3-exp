#include "expression.h"


expression::expression() {
	var = NULL;
}

void expression:: input(char* str) {
	expression add(str);
	if (var != 0) {
		while (var->next != 0) {
			variables *buf = var;
			var = var->next;
			delete[] buf->name_data;
			delete buf;
		}
		delete[] var->name_data;
		delete var;
	}
	*this = add;
}

expression expression::operator = (expression exp) {
	// popozzhe
}

int expression::prior_of_operator(char sign) {
	int prior;
	switch (sign)
	{
	case '^': prior = 3; break;

	case '*':
	case '/': prior = 2; break;

	case '+':
	case '-': prior = 1; break;

	case ')':
	case '(':
	case '|': prior = 0; break;

	default: prior = -1;
	}
	return prior;
}

bool expression::test_on_operator(char input) {
	if (input == '+'
		|| input == '-'
		|| input == '*'
		|| input == '/'
		|| input == '|'
		|| input == '^') {
		return true;
	}
	else {
		return false;
	}
}


void expression::test_on_try_sign(char* symbol) {
	if ((test_on_operator(*symbol))) {
		if ((!test_on_symbol(symbol + 1))) {
			if ((*(symbol + 1) != '(')) {
				if ((*(symbol + 1) != '|')) {
					throw std::logic_error("error in sign");
				}
			}
		}
	}
}

bool expression::test_on_letter(char *input) {
	if (((*input) >= 'a' && (*input) <= 'z')
		|| ((*input) >= 'A' && (*input) <= 'Z')) {
		return true;
	}
	else {
		return false;
	}
}

bool expression::test_on_figure(char *input) {
	if (((*input) >= '0' && (*input) <= '9')) {
		return true;
	}
	else {
		return false;
	}
}

bool expression::test_on_equal_varnames(char *str) {
	variables *tmp = var;
	while (tmp)
	{
		if (strcmp(str, tmp->name_data) == 0) {
			return true;
		}
		tmp = tmp->next;
	}
	return false;
}

void expression::push_name_in_struct(char* name_, double data_) {
	if (!var) {
		var = new variables;
		int len = strlen(name_);
		var->name_data = new char[len + 1];
		strcpy(var->name_data, name_);
		var->data = data_;
		var->next = NULL;
	}
	else {
		variables *tmp = new variables;
		int len = strlen(name_);
		tmp->name_data = new char[len + 1];
		strcpy(tmp->name_data, name_);
		tmp->data = data_;
		tmp->next = this->var;
		this->var = tmp;
	}
}


bool expression::test_on_symbol(char *input) {
	if ((test_on_letter(input))
		|| (test_on_figure(input))) {
		return true;
	}
	else {
		return false;
	}
}

bool expression::test_on_unar_minus(char* input, int pointer, bool abs_flag) {
	if (test_on_symbol(input + pointer)
		&& *(input + pointer - 1) == '-') {
		if (pointer == 1
			|| *(input + pointer - 2) == '('
			|| (*(input + pointer - 2) == '|'
				&& abs_flag == true))
			return true;
	}
	return false;
}

expression::expression(char* input) {
	int pos = 0, CountBrackets = 0 , len_input = strlen(input);
	char *symbol, *buffer;
	stack OperatorStk;
	int abs_flag = 0;
	var = NULL;
	do {
		symbol = input + pos++;
		if (test_on_symbol(symbol) || test_on_unar_minus(input, pos, abs_flag) && (*symbol) != '\0') {
			int len = 1;
			bool flag_for_point = false;
			if (test_on_figure(symbol) || ( (*symbol) == '-' && test_on_figure(symbol+1)) ) {
				while (test_on_figure(input + pos - 1 + len)
					|| input[pos - 1 + len] == '.') {

					if ((input[pos - 1 + len] == '.')
						&& (flag_for_point == false)) {
						flag_for_point = true;
					}
					else if ((input[pos - 1 + len] == '.')
						&& (flag_for_point == true)) {
						throw std::logic_error("error count of len of figure!");
					}
					len++;
				}
			}
			else if (test_on_letter(symbol) || ((*symbol) == '-' && test_on_letter(symbol + 1)) ) {
				while (test_on_letter(input + pos + len - 1)) {
					len++;
				}
			}
			char* put_compfig_in_stack = new char[len + 1];
			put_compfig_in_stack[len] = '\0';

			for (int i = 0; i < len; i++) {
				put_compfig_in_stack[i] = input[pos - 1 + i];
			}
			ExpStack.push(put_compfig_in_stack);
			delete[] put_compfig_in_stack;
			pos += len - 1;
		}

		else if (((*symbol == '|') && (abs_flag == 0)) || (*symbol == '(')) {
			if (*symbol == '(') {
				CountBrackets++;
			}
			else {
				abs_flag = 1;
			}
				
			char *new_char = new char[2];
			*new_char = *symbol;
			new_char[1] = '\0';
			OperatorStk.push(new_char);
			delete[] new_char;
			//continue; bug
		}
		else if (*symbol == ')' || (*symbol == '|' && abs_flag == 1)) {
			buffer = OperatorStk.top();
			if (*symbol == ')') {
				CountBrackets--;
			}
			else {
				abs_flag = 0;
			}
			if (*symbol == '|') {
				while (*(OperatorStk.top()) != '|') {
					buffer = OperatorStk.top();
					char *ch = new char[2];
					*ch = *buffer;
					ch[1] = '\0';
					ExpStack.push(ch);
					delete[] ch;
					OperatorStk.pop();
				}
				ExpStack.push(symbol);
			}
			else {
				while (*(OperatorStk.top()) != '(') {
					buffer = OperatorStk.top();
					char *ch = new char[2];
					*ch = *buffer;
					ch[1] = '\0';
					ExpStack.push(ch);
					delete[] ch;
					OperatorStk.pop();
				}
			}
			OperatorStk.pop();
		}
		else {
			if ((OperatorStk.see() && (prior_of_operator(*symbol) < prior_of_operator(*OperatorStk.top())))) {
				while (OperatorStk.see() && (prior_of_operator(*symbol) < prior_of_operator(*OperatorStk.top()))) {
					test_on_try_sign(symbol);
					buffer = OperatorStk.top();
					if (prior_of_operator(*symbol) <= prior_of_operator(*buffer)) {
						char *ch = new char[2];
						*ch = *buffer;
						ch[1] = '\0';
						ExpStack.push(ch);
						delete[] ch;
						OperatorStk.pop();
					}
					else {
						char *ch = new char[2];
						*ch = *buffer;
						ch[1] = '\0';
						ExpStack.push(ch);
						delete[] ch;
						OperatorStk.pop();
						break;
					}
				}
			}

			char *ch = new char[2];
			*ch = *symbol;
			ch[1] = '\0';
			if (ch[0] != ' ' && pos <= len_input && prior_of_operator(ch[0]) == -1) {
				throw std::logic_error("error in polish");
			}
			test_on_try_sign(symbol);
			OperatorStk.push(ch);
			delete[] ch;
		}
	} while ((*symbol != '\0') && (pos <= len_input) && (*symbol != ' ')); // translate in polish ended



	if (CountBrackets != 0) {
		throw std::logic_error("error in counting brackets");
	}

	if (abs_flag == 1) {
		throw std::logic_error("error in counting abs");
	}



	while (*(input + pos - 1) == ' ') {	// wrote complex figure
		int len = 0;
		if (!test_on_letter(input + pos)) {
			throw std::logic_error("error befor =");
		}
		len++;
		while (test_on_letter(input + pos + len)) {
			len++;
		}
		char* put_name = new char[len + 1];
		put_name[len] = '\0';
		for (int i = 0; i < len; i++) {
			put_name[i] = input[pos + i];
		}

		if (test_on_equal_varnames(put_name)) {
			throw std::logic_error("vars are eq");
		}
		pos += len;
		if (input[pos] != '=') {
			throw std::logic_error("error =");
		}
		pos++;
		if (!test_on_figure(input + pos) && *(input + pos) != '-') {
			throw std::logic_error("error after =");
		}
		len = 1;
		bool flag_for_point = false;
		while (test_on_figure(input + pos + len) || input[pos + len] == '.') {
			if (input[pos + len] == '.') {
				if (!flag_for_point) {
					flag_for_point = true;
				}
				else {
					throw std::logic_error("error in comp fig!");
				}
			}
			len++;
		}
		char* put_data = new char[len + 1];
		put_data[len] = '\0';
		for (int i = 0; i < len; i++) {
			put_data[i] = input[pos + i];
		}
		pos += len;
		push_name_in_struct(put_name, atof(put_data));
		pos++;
	}
	if (pos <= len_input) {
		throw std::logic_error("error after polish");
	}
}

double expression::find_el_var(char * str) {
	variables *buf = var;
	while (buf != NULL) {
		if (strcmp(str, buf->name_data) == 0) {
			return buf->data;
		}
		buf = buf->next;
	}

	throw std::logic_error("error, isn't variables !");
}


double expression::count() {
	double x;
	_Stack<double> st;
	while (ExpStack.see())
	{
		char* tmp = new char[2];
		tmp[1] = '\0';
		tmp[0] = *ExpStack.view_bot();
		int point = 0;
		int sign = 1;
		if (tmp[0] == '-') {
			if (test_on_symbol(ExpStack.view_bot() + 1)) {
				tmp[0] = ' ';
				sign = -1;
				point = 1;
				tmp[0] = *(ExpStack.view_bot()+ 1);
			}
		}
		if (test_on_symbol(tmp)) {
			if (test_on_figure(tmp)) {
				st.push(atof(ExpStack.view_bot() + point)*sign);
			}
			else {
				st.push(find_el_var(ExpStack.view_bot() + point)*sign);
			}
		}

		switch (tmp[0]) {
		case '+': st.push(st.pop() + st.pop()); break;
		case '-': x = st.pop(); st.push(st.pop() - x); break;
		case '*': st.push(st.pop() * st.pop()); break;
		case '/': x = st.pop(); st.push(st.pop() / x); break;
		case '^': x = st.pop(); st.push(pow(st.pop(), x)); break;
		case '|': st.push(abs(st.pop())); break;
		}

		delete[] tmp;
		ExpStack.pop_down();
	}
	if (st.size_of_stack() == 1)
		return st.view_top();
	else throw std::logic_error("Input error, stack isn't empty");
}

expression:: ~expression() {
	if (var != 0) {
		while (var->next != 0) {
			variables *buf = var;
			var = var->next;
			delete[] buf->name_data;
			delete buf;
		}
		delete[] var->name_data;
		delete var;
	}
}