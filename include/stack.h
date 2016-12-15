#pragma once
#include <stdexcept>

struct CNode {
	char data;
	CNode* next;
};

class stack {
	CNode *element;

public:
	stack() {
		element = 0;
	}

	bool push(char x) {
		CNode *node = new CNode;
		if (element != 0) {
			node->data = x;
			node->next = element;
			this->element = node;
		}
		else if (element == 0) {
			element = new CNode;
			element->data = x;
			element->next = 0;
		}
		return true;
	}

	char& top() {
		if (element != 0) {
			return element->data;
		}
		else if (element == 0) {
			throw std::logic_error("stack is empty");
		}
	}

	bool pop() {
		if (element != 0) {
			CNode* box = element;
			element = element->next;
			delete box;
			return true;
		}
		return false;
	}

	bool see() {
		if (element != 0) {	
			return true;
		}
		return false;
	}

	bool test_on_equel(char ch) {
		CNode *pointer = element;
		while (pointer != 0) {
			if (pointer->data == ch) {
				return true;
			}
			else {
				pointer = pointer->next;
			}
		}
		return false;
	}

	~stack() {
		CNode *box;
		if (element != 0) {
			while (this->see()) {
				this->pop();
			}
			delete element;
		}
	}
};