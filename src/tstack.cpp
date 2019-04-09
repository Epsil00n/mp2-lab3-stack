#include <iostream>
#include "tstack.h"

TStack::TStack(int Size):TDataRoot(Size)
{
	top = 0;
}

void TStack:: Put(const TData &Val) // положить в стэк
{
	if (pMem == nullptr) 
	{
		SetRetCode(DataNoMem);
	}
	else if (IsFull()) 
	{ 
		SetRetCode(DataFull); 
	}
	else
	{
		pMem[top++] = Val;
		DataCount++;
	}
}

TData TStack::Get() 
{
	if (pMem == nullptr)
	{
		SetRetCode(DataNoMem);
	}
	else if (IsEmpty())
	{
		SetRetCode(DataEmpty);
	}
	else {
		DataCount--;
		return pMem[--top];
	}
}

TData TStack::TopElem()
{
	if (pMem == nullptr) 
	{
		SetRetCode(DataNoMem);
	}
	else if (IsEmpty())
	{
		SetRetCode(DataEmpty);
	}
	else return pMem[top - 1];
}

int TStack:: IsValid(){
	return true;
}

void TStack::Print() 
{
	for (int i = 0; i < top; ++i)
		std::cout << pMem[i] << " ";
	std::cout << std::endl;
}