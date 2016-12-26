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
	expression input;
	input.input(str);
	printf("answer = %lf", input.count());
}