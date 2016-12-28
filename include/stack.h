#pragma once
#include <stdexcept>

struct CNode 
{
	char *data;
	CNode* next;
};

class queue 
{
	CNode *element;
	int Size;

public:
	queue() 
	{
		element = NULL;
		Size = 0;
	}

	queue(queue &qu) {
		for (int i = 0; i < qu.Size; i++) {
			this->push(qu.view_bot(i));
		}
	}

	queue operator = (queue &qu) {
		if (this == &qu) {
			return *this;
		}
		while (this->see()) {
			this->pop_down();
		}
		for (int i = 0; i < qu.Size; i++) {
			this->push(qu.view_bot(i));
		}
	}

	bool push(char *x) 
	{
		CNode *node = new CNode;
		int len = 0;
		for (; x[len] != NULL; len++) {}
		node->data = new char[strlen(x) + 1];
		strcpy(node->data, x);
		Size++;
		if (element != NULL)
		{
			node->next = element;
			element = node;
		}
		else if (element == NULL)
		{
			node->next = NULL;
			element = node;
		}
		return true;
	}

	char* view_bot(const int i = 0) 
	{
		CNode *first = element;
		CNode *w_first = element;
		for (int j = i; j != 0; j--) {
			w_first = w_first->next;
		}
		while (w_first->next != NULL) {
			first = first->next;
			w_first = w_first->next;
		}
		if (first == NULL) { throw std::logic_error("stack is empty"); }
		else { return first->data; }
	}

	bool pop_down() 
	{
		CNode *first = element;
		if (!this->see()) { return false; }
		CNode *second = NULL;
		while (first->next != NULL)
		{
			second = first;
			first = first->next;
		}
		if (second != NULL)
		{
			Size--;
			second->next = NULL;
			delete[] first->data;
			delete first;
			return true;
		}
		else 
		{
			Size--;
			delete[] first->data;
			delete first;
			first = NULL;
			return true;
		}
		return false;
	}

	bool see(const int i = 0 ) { //подсчет с нуля
		if ((Size-i) > 0) {
			return true;
		}
		return false;
	}


	~queue() {
		while (this->see()) {
			this->pop_down();
		}
	}
};




class stack
{
	CNode *element;

public:
	stack()
	{
		element = 0;
	}

	bool push(char *x)
	{
		CNode *node = new CNode;
		int len = 0;
		for (; x[len] != 0; len++) {}
		node->data = new char[strlen(x) + 1];
		strcpy(node->data, x);
		if (element != 0)
		{
			node->next = element;
			element = node;
		}
		else if (element == 0)
		{
			node->next = 0;
			element = node;
		}
		return true;
	}

	char* top() 
	{
		if (element != 0) 
		{
			return element->data;
		}
		else if (element == 0) 
		{
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


	~stack() {
		if (element != 0) {
			while (this->see()) {
				this->pop();
			}
				delete element;
		}
	}
};