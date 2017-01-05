#include "expression.h"

int main(int ac, char* av[])
{
	char* str;
	str = new char[100];
	for (int i = 0; i < 100; i++) {
		str[i] = ' ';
	}
	cin.getline(str, 100);
	for (int i = 100; str[i] == ' '; i--) {
		str[i] = NULL;
	}
	expression input("5+a a=-5");
	expression input_2;
	input_2 = input;
	input_2.overwrite("a",5);
	printf("answer = %lf\n", input_2.count());
	printf("answer = %lf\n", input.count());
}