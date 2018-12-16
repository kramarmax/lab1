#pragma once
#include "Exception.hpp"

template <class T> class List;

template <class T> class DoubleLinkedList
{
	List <T>	*p_first;
	List <T>	*p_last;
	size_t			_count;
public:
	int				AddItem(const T &pData, bool fFreeSelf = true);//добавление элемента
	void            Delete(size_t id);//удаление элемента из списка
	int             DelItem(List<T> *item);//удаление элемента по ссылке
	List<T>	*Next(List<T> * item);//следующий элемент
	List<T>	*Prev(List<T> * item);//предыдущий элемент
	List<T>	*ItemById(size_t id);//элемент по его Id
	T operator[](size_t id);//получение значения по id
	List<T>	*ItemByData(T * pData);//получение элемента по значению
	size_t			Count();//размер списка
	void			Flush();//очистка списка
	DoubleLinkedList<T>& operator=( DoubleLinkedList& l);
	DoubleLinkedList();	//конструктор
	DoubleLinkedList(DoubleLinkedList<T>& l);	//конструктор копирвоания
	~DoubleLinkedList(); //деструктор
};



template <class T> class List//элемент списка
{
	List <T> *p_prev; //ссылка на предыдущий элемент
	List <T> *p_next;
	bool is_free; //пустой ли

	T m_pData;//данные
	List();
	~List();

public:
	T data();
	friend	DoubleLinkedList<T>;
};

template <class T> DoubleLinkedList<T>& DoubleLinkedList<T>::operator=( DoubleLinkedList& l){
	while(p_first)
	{
		DelItem(p_first);
	}
	p_first = p_last = nullptr;
	 _count = 0;

	for(int i = 0; i < l.Count(); ++i)
	{
	    this->AddItem(l[i]);
	}
	return *this;
}

template <class T> DoubleLinkedList<T>::DoubleLinkedList(DoubleLinkedList<T>& l)
{
	p_first = p_last = nullptr;
	_count = 0;

	for(int i = 0; i < l.Count(); ++i)
	{
	    this->AddItem(l[i]);
	}
}

template <class T> DoubleLinkedList<T>::DoubleLinkedList()
{
	p_first = p_last = nullptr;
	_count = 0;
}

template <class T> DoubleLinkedList<T>::~DoubleLinkedList()//деструктор
{
	while(p_first)
	{
		DelItem(p_first);
	}
	p_first = p_last = nullptr;
}

template <class T> void DoubleLinkedList<T>::Delete(size_t id)
{
	DelItem(ItemById(id));
}

template <class T> void DoubleLinkedList<T>::Flush()
{
	while(p_first)
	{
		DelItem(p_first);
	}
	p_first = p_last = nullptr;
}

template <class T> size_t DoubleLinkedList<T>::Count()
{
	return _count;
}

template <class T> int DoubleLinkedList<T>::AddItem(const T &pData, bool fFreeSelf)
{
	List<T> * item = new List<T>;

	item->m_pData = pData;
	item->is_free = fFreeSelf;

	if ( !p_first && !p_last )
	{
		p_first = p_last = item;
	}
	else 
	{
		p_last->p_next = item;
		item->p_prev = p_last;
		p_last = item;
	}

	return ++_count;
}

template <class T> int DoubleLinkedList<T>::DelItem(List<T> *item)
{
	if(_count == 0)
	{
		throw Exception("List underflow");
	}
	if ( item->p_next && item->p_prev )
	{
		item->p_next->p_prev = item->p_prev;
		item->p_prev->p_next = item->p_next;
	}
	else if ( !item->p_next && item->p_prev )
	{
		item->p_prev->p_next = nullptr;
		p_last = item->p_prev;
	}
	else if ( item->p_next && !item->p_prev )
	{
		item->p_next->p_prev = nullptr;
		p_first = item->p_next;
	}
	else 
	{
		p_first = p_last = nullptr;
	}
	delete item;
	return --_count;
}

template <class T> T DoubleLinkedList<T>::operator[](size_t id)
{
	if ( id >= _count ) throw Exception("Index out of range");

	for(List<T> * item = Next(0); item; item = Next(item) ) 
	{
		if ( !id-- )
		{
				return item->m_pData;
		}
	}
	return T(0);
}

template <class T> List<T> *DoubleLinkedList<T>::ItemById(size_t id)
{
	if ( id >= _count )
	{
		return nullptr;
	}
	for(List<T> * item = Next(0); item; item = Next(item) )
	{
		if ( !id-- )
		{
			return item;
		}
	}

	return nullptr;
}

template <class T> List<T> *DoubleLinkedList<T>::ItemByData(T * pData)
{
	for(List<T> * item = Next(0); item; item = Next(item) )
	{
		if ( item->m_pData == pData )
		{
			return item;
		}
	}
	return nullptr;
}


template <class T> List<T> *DoubleLinkedList<T>::Next(List<T> *item)
{
	return ( item ? item->p_next : p_first );
}

template <class T> List<T> *DoubleLinkedList<T>::Prev(List<T> *item)
{
	return ( item ? item->p_prev: p_last );
}

template <class T> List<T>::List()
{
	p_next = p_prev = nullptr;
	m_pData = T(0);
	is_free = true;
}

template <class T> List<T>::~List()
{
	if ( is_free )
	{
		m_pData = T(0);
	}
	p_next = p_prev = nullptr;
}

template <class T> T List<T>::data()
{
	return m_pData;
}
