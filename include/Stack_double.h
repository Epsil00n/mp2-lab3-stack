class Stack {
private:
	double* pMem_d;
	int top;
	int size;
public:
	Stack(int _size = 0);
	~Stack();
	void Put(const double &Val);
	double Get();
	double TopElem() const;
	bool IsFull() const;
	bool IsEmpty() const;
};

Stack::Stack(int _size) : size(_size), top(-1)
{
	pMem_d = new double[_size];
}

Stack::~Stack()
{
	delete[] pMem_d;
}

void Stack::Put(const double &Val)
{
	if (top < size)
		pMem_d[++top] = Val;
	else throw - 1;
}

double Stack::Get()
{
	if (top > -1)
		return pMem_d[top--];
	else throw -1;
}

double Stack::TopElem()const
{
	if (top > -1)
		return pMem_d[top];
	else throw - 1;
}

bool Stack::IsEmpty()const
{
	return top == -1;
}

bool Stack::IsFull()const
{
	return top == size;
}