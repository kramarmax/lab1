#include <iostream>
#include "Exception.hpp"

using namespace std;

template<typename T>
struct Node{ //узел дека
	T data;//значение
	Node<T> *n;//ссылка на следующий элемент
	Node<T> *p;//ссылка на предыдущий элмент
};


template<typename T>
class Dequeue{//двусв€зный список
private:
	size_t _size;//рамер дека
	Node<T> *start;//начало дека
	Node<T> *end;//конец дека
public:
	Dequeue& operator=(const Dequeue<T>& d){
		Node<T>* temp;
		while(_size > 0){//удал€ем все элементы дека
			temp = start;
			start = start->n;
			delete temp;
			--_size;
		}
		_size = 0;
		start = nullptr;
		end = nullptr;
		Node<T> *tmp = d.start;
		for(int i = 0; i < d.size(); ++i){
			this->push_back(tmp->data);
			tmp = tmp->n;
		}
		return *this;
	}
	Dequeue(const Dequeue<T>& d){
		_size = 0;
		start = nullptr;
		end = nullptr;
		Node<T> *tmp = d.start;
		for(int i = 0; i < d.size(); ++i){
			this->push_back(tmp->data);
			tmp = tmp->n;
		}
	}

	Dequeue(){
		_size = 0;
		start = nullptr;
		end = nullptr;
	}

	size_t size() const{//размер дека
		 return _size;
	}

	void push_front(const T &data){//добавл€ет в начало дека
		++_size;
		Node<T> *temp = new Node<T>();
		temp->data = data;
		temp->n = start;
		temp->p = nullptr;
		if (start != nullptr) 
			start->p = temp;
		start = temp;
		if (end == nullptr)
			end = temp;
	}
	
	T pop_front(){//удал€ет из начала дека
		if(start == nullptr){
			throw Exception("Dequeue underflow");
		}
		--_size;
		T res = start->data;
		Node<T> *temp = start;
		start = start->n;
		if (start != nullptr) 
			start->p = nullptr;
		if (temp == end)
			end = nullptr;
		delete temp;
		return res;

	}
	void push_back(const T &data){//ƒобавл€ет элемент в конец
		++_size;
		Node<T> *temp = new Node<T>();
		temp->n = nullptr;
		temp->data = data;
		temp->p = end;

		if (end != nullptr) 
			end->n = temp;
		end = temp;
		if (start == nullptr)
			start = temp;
	}

	T pop_back(){//удал€ет элемент с конца
		if(end == nullptr){
			throw Exception("Dequeue underflow");
		}
		T res = end->data;
		--_size;
		Node<T> *temp = end;
		end = end->p;
		if (end != nullptr) 
			end->n = nullptr;
		if (temp == start) 
			start = nullptr;
		delete temp;
		return res;
	}


	~Dequeue(){//деструктор
		Node<T>* temp;
		while(_size > 0){//удал€ем все элементы дека
			temp = start;
			start = start->n;
			delete temp;
			--_size;
		}
	}
};
