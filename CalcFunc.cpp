#include"CalcFunc.h"
#include"stdafx.h"
int IsDigit(const char c)
{
	int n=c-48;
	if(n>=0 && n<=9)
		return n;
	else return -1;
}
int IsOperator(const char c)
{
	if((c=='+')||(c=='-')||(c=='*')||(c=='/')||(c=='^')||(c=='!'))
		return 1;
	else
		return 0;
}
int IsPoint(const char c)
{
	if(c=='.')
		return 1;
	else 
		return 0;
}