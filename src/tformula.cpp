#include <iostream>
#include "tstack.h"
#include "tformula.h"
#include "Stack_double.h"
#include <string.h>

TFormula::TFormula(char * form)
{
	for (int i = 0; i <= strlen(form); ++i)
	{
		Formula[i] = form[i];
	}
}

int TFormula::FormulaChecker(int Brackets[], int size)
{
	TStack br(MaxLen);
	int errors = 0;
	int j = 0;
	int k = 0; 
	int size_f = strlen(Formula);
	for (int i = 0; (i<size_f); ++i) 
	{
		if ((Formula[i] != '(') && (Formula[i] != ')')) continue;

		j++;
		if (Formula[i] == '(') 
		{ 
			br.Put(j); 
		}
		if (Formula[i] == ')')
			if (br.IsEmpty()) 
			{
				Brackets[k++] = -1;
				Brackets[k++] = j;
				errors++;
			}
			else 
			{
				Brackets[k++] = br.Get();
				Brackets[k++] = j;
			}
	}
	
	while (!(br.IsEmpty())) 
	{
		Brackets[k++] = br.Get();
		Brackets[k++] = -1;
		errors++;
	}

	if (errors != 0) 
	{
		for (int i = 0; i < size; ++i)
			std::cout << Brackets[i] << ' ';
		std::cout << std::endl;
	}
	else std::cout << "all correct"<<std::endl;
	
	return errors;
}

int TFormula::FormulaConverter() 
{
	TStack prior(MaxLen);
	int j = 0; // ñ÷åò÷èê äëÿ PostfixForm[MaxLen]
	int tmp[MaxLen];
	if (FormulaChecker(tmp, MaxLen) != 0) 
	{ 
		return 1;
		throw "Wrong brackets"; 
	}
	// ïðèîðèòåòû
	// ( - 0 (40)
	// ) - 1 (41)
	// +(43) -(45) - 2
	// *(42) /(47) - 3
	// ó íàñ òóò äâà ñëó÷àÿ: êîãäà ÷èñëî èëè êîãäà îïåðàöèÿ
	int pr[48] = {-1};
	pr[40] = 0;
	pr[41] = 1;
	pr[43] = pr[45] = 2;
	pr[42] = pr[47] = 3;
	int size_f = strlen(Formula);
	for (int i = 0; i<size_f ; ++i)
	{
		if ((Formula[i] >= '0') && (Formula[i] <= '9') || (Formula[i]=='.'))
		{
			while ((Formula[i] >= '0') && (Formula[i] <= '9') || (Formula[i] == '.'))
				PostfixForm[j++] = Formula[i++];
			
			PostfixForm[j++] = ' ';
			i--;
			continue;
		}
		if (Formula[i] == ')')
		{
			while (prior.TopElem() != '(')
			{
				PostfixForm[j++] = prior.Get(); //âûòàëêèâàåì âñå îïåðàòîðû èç ñòåêà
				PostfixForm[j++] = ' ';
			}
			prior.Get(); // âûòàëêèâàåì è ñàìó ñêîáêó
		} 
		else if ((Formula[i] == '(') || prior.IsEmpty() || (pr[Formula[i]] > pr[prior.TopElem()]))
		{
			prior.Put(Formula[i]); 
			continue;
		}
		else if (pr[Formula[i]] <= pr[prior.TopElem()])
		{
			while ((!prior.IsEmpty())&&(pr[Formula[i]] <= pr[prior.TopElem()]))
			{
				PostfixForm[j++] = prior.Get();
				PostfixForm[j++] = ' ';
			}
			prior.Put(Formula[i]);
		}
		

	}

	while (!prior.IsEmpty())
	{
		PostfixForm[j++] = prior.Get();
		PostfixForm[j++] = ' ';
	}

	PostfixForm[j] = '\0';
	int h = 0;
	while (PostfixForm[h]!='\0')
		std::cout << PostfixForm[h++];
	return 0;
}

double TFormula::FormulaCalculator() 
{
	double res;
	Stack operands(MaxLen);
	double op1, op2;
	if (FormulaConverter() != 0) throw - 1;
	for (int i = 0; PostfixForm[i]!='\0'; ++i) 
	{
		char g[128] = {'\0'};
		int j = 0;
		if (PostfixForm[i] == ' ') continue;
		if ((PostfixForm[i] >= '0') && (PostfixForm[i] <= '9') || (PostfixForm[i] == '.'))
		{
			while ((PostfixForm[i] >= '0') && (PostfixForm[i] <= '9') || (PostfixForm[i] == '.'))
				g[j++] = PostfixForm[i++];
			op1 = std::atof(g);
			//	std::cout << "op1:   " << op1 << "  ";

			operands.Put(op1);
		}
		switch (PostfixForm[i]) {
		case '+': 

			op2 = operands.Get();
//			std::cout << op2 << ' ';
			op1 = operands.Get();
//			std::cout << op1 << ' '<< i<<' ';
			res = op1 + op2;
			operands.Put(res);
			break;
		case'-':
			op2 = operands.Get();
			op1 = operands.Get();
			res = op1 - op2;
			operands.Put(res);
			break;
		case'*':
			op2 = operands.Get();
			op1 = operands.Get();
			res = op1 * op2;
			operands.Put(res);
			break;
		case'/':
			op2 = operands.Get();
			op1 = operands.Get();
			res = op1 / op2;
			operands.Put(res);
			break;
		default: 
			break;
		}
	}
	res = operands.Get();
	std::cout << res << " ";
	return res;
}
