#pragma once
#include "Exception.hpp"

template<typename T>
struct node{//элемент стека
  	T _data; // значенеи элемента
	node *next;	//ссылка на следущий элемент
};


#include <iostream>
template<typename T>
class stack {
private:
    node<T> *_head; //начало стека
    int _size; //размер стека
public:
   stack(const stack& s);//конструктор копировани€
   stack();//конструктор
   void add(const T &_data);//заносим элемент в конец стека
   T pop();//удал€ем элемент из конца стека
   int size() const; //размер
   stack<T>& operator=(const stack& s);
   template<typename U>
   friend std::ostream& operator <<(std::ostream& out, const stack<U>& s); //вывод стека на экран
   template<typename U>
   friend std::istream& operator >>(std::istream& in, stack<U>& s); //вввод элемента стека

   ~stack(); //деструктор
};

template<typename T>
stack<T>& stack<T>::operator=(const stack& s){
	for(int i = 0; i < _size; ++i){//проходим по каждому элементу
			node<T> *buf = _head;
			_head = _head->next;//переходим к следующему
			delete buf;//удал€ем предыдущий
		}
	_head = nullptr;
		_size = 0;
	T* ss = new T[s.size()];
	node<T> *temp = s._head;
	for(int i = 0; i < s.size(); ++i){
		ss[i] =temp->_data;
		temp = temp->next;
	}
	for(int i = 0; i < s.size(); ++i){
		this->add(ss[i]);
	}
	delete[] ss;
	return *this;
}

template<typename T>
stack<T>::stack(const stack<T>& s):_head(nullptr), _size(0){
	T* ss = new T[s.size()];
	node<T> *temp = s._head;
	for(int i = 0; i < s.size(); ++i){
		ss[i] = temp->_data;
		temp = temp->next;
	}
	for(int i = 0; i < s.size(); ++i){
		this->add(ss[i]);
	}
	delete[] ss;
}

template<typename T>
stack<T>::stack<T>():_head(nullptr), _size(0){
   }

template<typename T>
void stack<T>::add(const T &_data){
	  node<T> *buf = new node<T>;//создаЄм и инициализируем новый элемент
	  buf->next = _head;
	  buf->_data = _data;
      _head = buf;
	  ++_size;
}

template<typename T>
T stack<T>::pop(){
	   if(_size <= 0){//если пустой
			throw Exception("stack underflow");
	   }
		node<T> *buf = _head;	//заносим в буфер начало стека
		T _data = buf->_data;//запоминаем данные
		_head = _head->next;//переходим к следующему
		delete buf;//очищаем буфер
		--_size;
		return _data;
}

template<typename T>
int stack<T>::size() const{ 
	return _size; 
}




template<typename T>
std::ostream& operator <<(std::ostream& out, const stack<T>& s){
	node<T> *buf = s._head;
	for(int i = 0; i < s._size; ++i){//проходим по каждому элементу
		   out << buf->_data << ' ';
		   buf = buf->next;//переходим к следующему
		}
	return out;
}

template<typename T>
std::istream& operator >>(std::istream& in, stack<T>& s){
	 T buf;
	 in >> buf;
	 s.add(buf);
	 return in;
}

template<typename T>
stack<T>::~stack(){ //деструктор
		for(int i = 0; i < _size; ++i){//проходим по каждому элементу
		   node<T> *buf = _head;
		   _head = _head->next;//переходим к следующему
		   delete buf;//удал€ем предыдущий
		}
		_size = 0;
}
