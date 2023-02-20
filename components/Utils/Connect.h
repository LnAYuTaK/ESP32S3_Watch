#pragma once 
#include <stdlib.h>
#include <vector>
#include <stdio.h>
using namespace std;
#define Connect(sender,signal,receiver,method)((sender)->signal.Bind(receiver,method));
template< class ...Args>
class SlotBase
{
public:
	virtual void Exec(Args...args) = 0;
	virtual ~SlotBase() {}
};
 
template<class T, class ...Args>
class Slot :public SlotBase<Args...>
{
	typedef void (T::*Func)(Args...);
public:
	Slot(T* pOjb, Func func)
	{
		m_func = func;
		m_pSlotBase = pOjb;
	}
 
	void Exec(Args...args)
	{
		(m_pSlotBase->*m_func)(args...);
	}
private:
	T* m_pSlotBase = NULL;
	Func m_func;
};
 
template <class...Args>
class pSignal
{
public:
	template<class T>
	void Bind(T* obj, void (T::*func)(Args...))
	{
		m_pSlotSet.push_back(new Slot<T, Args...>(obj, func));
	}
 
	void operator()(Args...args)
	{
		for (int i = 0; i < (int)m_pSlotSet.size(); i++)
		{
			m_pSlotSet[i]->Exec(args...);
		}
	}
private:
	vector< SlotBase<Args...>* > m_pSlotSet;
};

template<class...Args>
class Signal
{
public:
	Signal()
	{
	}
	void emit(Args...args)
	{
		ValueChanged(args...);
	}
public:
	pSignal<Args...> ValueChanged;
};
 