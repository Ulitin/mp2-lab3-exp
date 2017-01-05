#pragma once
#include "stack.h"
#include "list.h"

struct variables {
	double  data;
	char *name_data;
	variables *next;
};

class expression {
	queue ExpStack;		//expression
	variables *var;

public:

	expression();
	expression(char* input);
	double count();									// output result
	void input(char* str);
	expression (expression &exp);
	expression operator = (expression &exp);
	bool overwrite(char *name_, double data_);
	~expression();

private:

	void push_name_in_struct(char *name_, double data_);
	int prior_of_operator(char sign);					// output priority of sign
	bool test_on_operator(char input);		// test on sign operation
	bool test_on_symbol(char *input);		// test on number
	double find_el_var(char * str);
	bool test_on_equal_varnames(char *str);
	bool test_on_unar_minus(char* input, int pointer, bool abs_flag);
	void test_on_try_sign(char* symbol);
	bool test_on_figure(char *input);
	bool test_on_letter(char *input);
	
	
};
