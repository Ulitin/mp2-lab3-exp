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

	void push_name_in_struct(char *name_, double data_);
	int prior_of_operator(char sign);				// output priority of sign
	bool expression::test_on_operator(char input); // test on sign operation
	bool expression::test_on_symbol(char *input);	// test on number
	double counting();								// output result
	double find_el_var(char * str);
	bool expression::test_on_equal_varnames(char *str);
	bool expression::test_on_unar_minus(char* input, int pointer, bool abs_flag);

	~expression() {
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
};
