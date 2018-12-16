#pragma once
#include "Exception.hpp"

template<typename T>
struct NNode{//элемент очереди
  	T _data; // значенеи элемента
	NNode *_next;	//ссылка на следущий элемент
};

 #include <iostream>

template<typename T>
class queue {
private:
    NNode<T> *_head; //начало очереди
    NNode<T> *_tail; // конец очереди
    int _size; //размер очереди
public:
   queue(const queue<T>& q);//конструктор копировани€
   queue();//конструктор
   void add(T &_data);//заносим элемент в конец очереди
   T remove();//удал€ем элемент из начала очереди
   int size(); // размер
   template<typename U>
   friend std::ostream& operator <<(std::ostream& out, const queue<U>& q); //вывод на экран
   template<typename U>
   friend std::istream& operator >>(std::istream& in, queue<U>& q); //ввод элемента 
   ~queue(); //деструктор
};

template<typename T>
queue<T>::queue(const queue<T>& q):_head(nullptr), _tail(nullptr), _size(0){//конструктор копировани€
	NNode<T> *tmp = q._head;
	for(int i = 0; i < q.size(); ++i){
		this->add(tmp->_data);
		tmp = tmp->_next;
	}
}

template<typename T>
queue<T>::queue<T>():_head(nullptr), _tail(nullptr), _size(0){
   }

template<typename T>
void queue<T>::add(T &_data){
	  NNode<T> *buf = new NNode<T>;//создаЄм и инициализируем новый элемент
	  buf->_next = nullptr;
	  buf->_data = _data;
	  if(_head == nullptr && _tail == nullptr){//если очередь пуста
			_head = buf;
			_tail = buf;//устанваливаем и начало и конец этим элементом
	  }
	  else{
		  _tail->_next = buf;
		  _tail = buf;
	  }
	  ++_size;
}

template<typename T>
T queue<T>::remove(){
	   if(_size <= 0){//если пустой
			throw Exception("Queue underflow");
	   }
		NNode<T> *buf = _head;	//заносим в буфер начало очереди
		T _data = buf->_data;//запоминаем данные
		_head = _head->_next;//переходим к следующему
		delete buf;//очищаем буфер
		--_size;
		return _data;
}

template<typename T>
int queue<T>::size(){ 
	return _size; 
}



template<typename T>
std::ostream& operator <<(std::ostream& out, const queue<T>& q){
	NNode<T> *buf = q._head;
	for(int i = 0; i < q._size; ++i){//проходим по каждому элементу
			out << buf->_data << ' ';
		   buf = buf->_next;//переходим к следующему
		}
	return out;
}

template<typename T>
std::istream& operator >>(std::istream& in, queue<T>& q){
	 T buf;
	 in >> buf;
	 q.add(buf);
	 return in;
}

template<typename T>
queue<T>::~queue(){ //деструктор
		for(int i = 0; i < _size; ++i){//проходим по каждому элементу
		   NNode<T> *buf = _tail;
		   _tail = _tail->_next;//переходим к следующему
		   delete buf;//удал€ем предыдущий
		}
}
