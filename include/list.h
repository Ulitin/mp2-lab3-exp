
#pragma once
#include <iostream>
using namespace std;

//структура звена списка
template <class T>
struct _Node
{
	T data;
	_Node<T> *next;

	_Node<T>(T i, _Node *ptr1) { data = i; next = ptr1; }
	//Конструктор для создания нового элемента
};


//класс список
template <class T>
class _List
{
protected:

	int size; //счетчик числа элементов
	_Node<T> *head;
	_Node<T> *tail;

public:
	_List() { size = 0; head = tail = NULL; }

	~_List();

	T viewData(_Node<T>* ptr) { return ptr->data; }
	T* viewPtr(_Node<T>* ptr) { return ptr; }
	int GetSize() { return size; }
	void Print_list();

	bool is_list_empty();
	int size_of_list();

	void add_el_in_head(T data);
	void add_el_in_tail(T data);
	void add_node(_Node<T>* ptr, T data);

	T del_el_fr_head();
	T del_el_fr_tail();
	void del_node(_Node<T>* ptr);
	T get_tail() { return tail->data; }
	_Node<T>* find_ptr(T elem);


};

/////////////////////////////////////////////////////////////////////////////
//реализация функций для списка
template <class T> _List<T>::~_List()
{
	while (head)
	{
		_Node<T>* temp = head->next;
		delete head;
		head = temp;
	}
}

template <class T> void _List<T>::Print_list()
{
	_Node<T>* temp = head;
	while (temp)
	{
		cout << temp->data << endl;
		temp = temp->next;
	};

}


template <class T> bool _List<T>::is_list_empty()
{
	if (head == NULL)
	{
		return true;
	}
	else
		return false;
}

template <class T> void _List<T>::add_el_in_head(T data_)
{
		_Node<T>* new_node = new _Node<T>(data_, head);
		if (head == NULL)
		{
			tail = new_node;
		}
		head = new_node;
		size++;
}

template <class T> int _List<T>::size_of_list()
{
	_Node<T>* tmp = head;
	int size = 0;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	return size;
}


template <class T> void _List<T>::add_el_in_tail(T data)
{
	_Node<T>* new_node = new _Node<T>(data, NULL);
	if (tail == NULL)
	{

		head = new_node;
	}
	else {
		tail->next = new_node;
	}
	tail = new_node;
	size++;
}

template <class T> void _List<T>::add_node(_Node<T>* ptr, T data)
{
	if (ptr)
	{
		_Node<T>* new_node = new _Node<T>(data, ptr->next);
		ptr->next = new_node;
		size++;
	}
	else
	{
		_Node<T>* new_node = new _Node<T>(data, NULL);
		head = new_node;
		tail = new_node;

		size++;
	}
}

template <class T> T _List<T>::del_el_fr_head()
{
	if (size)
	{
		_Node<T>* temp = head->next;
		T res = head->data;
		delete head;
		head = temp;
		size--;
		return res;
	}
	else
		throw string("Error");
}

template <class T> T _List<T>::del_el_fr_tail()
{
	if (size == 0)
	{
		throw 1;
	}
	else
		if (size == 1)
		{
			head = tail = NULL;
			size--;
		}
		else
		{
			_Node<T>* temp = head;
			while (temp->next->next)
			{
				temp = temp->next;
			}
			delete temp->next;
			temp->next = NULL;
			size--;
		}
}

template <class T> void _List<T>::del_node(_Node<T>* ptr)
{
	if (size == 0)
	{
		throw string("Error");
	}
	else
		if (size == 1)
		{
			head = tail = NULL;
			size--;
		}
		else
		{
			_Node<T>* temp = ptr->next->next;
			delete ptr->next;
			ptr->next = temp;
			size--;
		}

}

template <class T> _Node<T>* _List<T> ::find_ptr(T elem)
{
	if (size == 0)
	{
		throw string("Error");
	}
	else
	{
		_Node<T>* temp = head;
		while (temp != NULL)
		{
			if (temp->data == elem)
			{
				break;
			}
			else
			{
				temp = temp->next;
			}
		}
		if (temp == NULL)
		{
			throw string("Error");
		}
		return temp;
	}
}
////////////////////////////////////////////////////////////////////////////////
//класс стек
template <class T>
class _Stack
{
	_List<T> memory;
public:
	_Stack();

	T viewData(_Node<T>* ptr);
	bool is_stack_empty();
	void push(const T elem);
	int size_of_stack();
	T pop();
	T view_top();
	T view_bot();
	void del_el_fr_tail();
};

////////////////////////////////////////////////////////////////////////////////////////////////
//реализация функций для стека
template <class T> _Stack<T>::_Stack() {}

template <class T> void _Stack<T>::push(const T elem)
{
	memory.add_el_in_head(elem);
};

template <class T> T _Stack<T>::pop()
{
	return memory.del_el_fr_head();
};

template <class T> bool _Stack<T>::is_stack_empty()
{
	return memory.is_list_empty();
};


template <class T> void _Stack<T>::del_el_fr_tail()
{
	return memory.del_el_fr_tail();
};



template <class T> int _Stack<T>::size_of_stack()
{
	return memory.size_of_list();
};

template <class T> T _Stack<T>::viewData(_Node<T>* ptr)
{
	return memory.viewData();
};

template <class T> T _Stack<T>::view_bot()
{
	T bot = memory.del_el_fr_tail();
	memory.add_el_in_tail(bot);
	return bot;
};

template <class T> T _Stack<T>::view_top()
{
	T top = memory.del_el_fr_head();
	memory.add_el_in_head(top);
	return top;
};