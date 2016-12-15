#pragma once
#include <stack.h>


class expression {
	char *exp;		//expression
	stack var;		//variables
	stack name_var;		//variables

public:

	expression();					//конструктор по умолчнию
	expression(char* input);		//переработать строку в обратную польскую запись
	expression(expression &input);  //конструктор копирования

	expression operator = (expression &input);

	int priority_of_sign(char sign);				// output priority of sign
	bool expression::test_on_operation(char input); // test on sign operation
	int Strlen(char *str);							// the calculation of the long lines
	bool expression::test_on_element(char input);	// test on namber
	double counting();								// output resalt

	~expression() {
		delete[] exp;
	}
};