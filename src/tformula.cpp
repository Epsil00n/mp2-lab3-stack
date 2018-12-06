#include <stdio.h>
#include <iostream>
#include <string.h>
#include "TStack.h"
#include "TFormula.h"


TFormula :: TFormula (char *form)                            // �����������
{
	int size = strlen(form);
	if (size>=MaxLen) throw -1;
	for (int i=0; i<size; i++)
		Formula[i] = form[i];
}

int TFormula :: FormulaChecker(int Brackets[],int size)     // �������� ������������ ������
{
	TStack st(size);
	for (int i=0; i<size; i++)
	{
		if (Formula[i]=='(') st.Put(i);
		if (Formula[i]==')') st.Get();
	}
	if (st.IsEmpty()) return 1;
	else return 0;
}

int TFormula :: FormulaConverter()                          // �������������� � ����������� �����
{
	int size = 0;
	int ind = 0;
	while (Formula[ind] != '=') { size++; ind++;}
	TStack st(size);

	int Index = 0; //����� ����������� �����
	int Priority = -1;		//��������� ��������
	int PriorityStackOp = -1; //��������� ��������� �������� � �����

	for (int i=0; i<size; i++)
	{
		if ((Formula[i] >= '0')&&(Formula[i] <= '9')||(Formula[i] == '.'))
		{
			PostfixForm[Index] = Formula [i];
			Index++;
			std::cout<<Formula [i];
		}
		if ((Formula[i] == '+')||(Formula[i] == '-')||(Formula[i] == '*')||(Formula[i] == '/')
			||(Formula[i] == '(')||(Formula[i] == ')'))
		{
			switch (Formula[i])
			{
				case '+': 
				{
					PostfixForm[Index] = ' ';
					std::cout<<PostfixForm[Index];
					Index++;
					Priority = 2;
					if (Priority<=PriorityStackOp)									//���� ������ ��� �����
					{
						while (!st.IsEmpty())
						{
							PostfixForm[Index] = st.Get();
							std::cout<<PostfixForm[Index];
							Index++;
							PostfixForm[Index] = ' ';
							std::cout<<PostfixForm[Index];
							Index++;
						}
					}
					if ((st.IsEmpty())||(Priority>PriorityStackOp))					//���� ������
					{
						st.Put('+');	
						PriorityStackOp = Priority;
					}
					break;
				}
				case '-':
				{
					PostfixForm[Index] = ' ';
					std::cout<<PostfixForm[Index];
					Index++;
					Priority = 2;
					if (Priority<=PriorityStackOp)
					{
						while (!st.IsEmpty())
						{
							PostfixForm[Index] = st.Get();
							std::cout<<PostfixForm[Index];
							Index++;
							PostfixForm[Index] = ' ';
							std::cout<<PostfixForm[Index];
							Index++;
						}
					}
					if ((st.IsEmpty())||(Priority>PriorityStackOp))
					{
						st.Put('-');	
						PriorityStackOp = Priority;
					}
					break;
				}
				case '*': 
				{
					PostfixForm[Index] = ' ';
					std::cout<<PostfixForm[Index];
					Index++;
					Priority = 3;
					if (Priority<=PriorityStackOp)
					{
						while (!st.IsEmpty())
						{
							PostfixForm[Index] = st.Get();
							std::cout<<PostfixForm[Index];
							Index++;
							PostfixForm[Index] = ' ';
							std::cout<<PostfixForm[Index];
							Index++;
						}
					}
					if ((st.IsEmpty())||(Priority>PriorityStackOp))
					{
						st.Put('*');	
						PriorityStackOp = Priority;
					}
					break;
				}
				case '/' :
				{
					PostfixForm[Index] = ' ';
					std::cout<<PostfixForm[Index];
					Index++;
					Priority = 3;
					if (Priority<=PriorityStackOp)
					{
						while (!st.IsEmpty())
						{
							PostfixForm[Index] = st.Get();
							std::cout<<PostfixForm[Index];
							Index++;
							PostfixForm[Index] = ' ';
							std::cout<<PostfixForm[Index];
							Index++;
						}
					}
					if ((st.IsEmpty())||(Priority>PriorityStackOp))
					{
						st.Put('/');	
						PriorityStackOp = Priority;
					}
					break;
				}
				case '(' :
				{
					Priority = 0;
					PriorityStackOp = Priority;
					st.Put('(');
					break;
				}
				case ')' :
				{
					PostfixForm[Index] = ' ';
					std::cout<<PostfixForm[Index];
					Index++;
					Priority = 1;
					PriorityStackOp = Priority;
					while (st.TopElem()!='(')
						{
							PostfixForm[Index] = st.Get();
							std::cout<<PostfixForm[Index];
							Index++;
							PostfixForm[Index] = ' ';
							std::cout<<PostfixForm[Index];
							Index++;
						}
					st.Get();
					break;
				}
			}
		}
		if (!((Formula[i] >= '0')&&(Formula[i] <= '9')||(Formula[i] == '.'))&&(!((Formula[i] == '+')||(Formula[i] == '-')||(Formula[i] == '*')||(Formula[i] == '/')
			||(Formula[i] == '(')||(Formula[i] == ')'))))
			throw -1;
	}
	while(!st.IsEmpty()) {
		PostfixForm[Index] = ' ';
		std::cout<<PostfixForm[Index];
		Index++;
		PostfixForm[Index] = st.Get();
		std::cout<<PostfixForm[Index];
		Index++;
	}
	PostfixForm[Index] = ' ';

	std::cout<<std::endl;
	return 1;
}

double TFormula :: FormulaCalculator()                      // ���������� �������
{
	double str [MaxLen] = {0};
	char y [50];

	double result = 0;
	FormulaConverter();

	int ind = 0; //������ � str
	int i = 0; //������ � PostfixForm
	while (PostfixForm[i] != '\0')
	{
		if ((PostfixForm[i] >= '0')&&(PostfixForm[i] <= '9')) 
		{
			int j = 0;
			while (PostfixForm[i] != ' ') {
				y[j] = PostfixForm[i];
				i++; j++;
			}
			y[j] = 0;
			str [ind] = atof(y);
			ind++;
		}
		switch (PostfixForm[i])
		{
			case '+' :
				{
					double top_el = str[--ind]; //���������� ������� �� �������
					str[ind] = 0; //��������
					result = str [--ind] + top_el; //���������� � ����������
					str[ind] = result; //������ ���������
					ind++; //���������� ������ �� c��� �������
					break;
				}
			case '-' :
				{
					double top_el = str[--ind];
					str[ind] = 0; 
					result = str [--ind] - top_el;
					str[ind] = result;
					ind++;
					break;
				}
			case '*' :
				{
					double top_el = str[--ind];
					str[ind] = 0; 
					result = str [--ind] *  top_el;
					str[ind] = result;
					ind++;
					break;
				}
			case '/' :
				{
					double top_el = str[--ind];
					str[ind] = 0; 
					result = str [--ind] / top_el;
					str[ind] = result;
					ind++;
					break;
				}
		}
		i++;
	}

	return result;
}