// CalcStr.cpp: implementation of the CCalcStr class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CalcStr.h"
#include <math.h>


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCalcStr::CCalcStr()
{
	firststack.pnext=NULL;
}

CCalcStr::~CCalcStr()
{

}



double CCalcStr::maincalc(const char *str)
{
	int curop;
	STRLEN=(int)strlen(str);
	m_StringToCalc=new char[STRLEN+1];
	strcpy(m_StringToCalc,str);
	point=0;bracket=0;stacknum=0;m_ErrorCode=0;
	if(!check()) {return 0;}//�Ϸ�?
	m_Result=getnumber();
	while(point<=STRLEN-1 && m_ErrorCode==0){
		curop=getcuropsign();//��ǰ������
		if(curop==ENDBRACKET){
			--bracket;
			if(getstack(stacknum)->opsign==0){
				//����ǰ��Ϊ��
				pop();
			}
			popall();
			//������������ǰpush�Ķ������ڿ���pop�Ķ�pop
		}
		else calc(curop);
	}
	if(m_ErrorCode!=0){//�д���
		while(stacknum>0) pop();//�������ж�ջ
		m_Result=0;
	}
	delete m_StringToCalc;
	return m_Result;
}

double CCalcStr::getnumber()
{
	if(point>STRLEN-1) return 0;
	char strnum[256];
	int n=0;
	if(isalpha(m_StringToCalc[point])) return 0;//����������
	if(m_StringToCalc[point]=='-' || m_StringToCalc[point]=='+'){//һ��ʼ���Ǹ��Ż�����
		return 0;
	}
	while(m_StringToCalc[point]=='('){//��������'('
		push(0);
	}
	if(m_StringToCalc[point]=='-') return 0;//���и���

	//����������
	while((m_StringToCalc[point]<'0' || m_StringToCalc[point]>'9') && m_StringToCalc[point]!='.') point++;

	//�����ָ��Ƶ�strnum
	while((m_StringToCalc[point]>='0' && m_StringToCalc[point]<='9')
		|| m_StringToCalc[point]=='.'
		|| (m_StringToCalc[point]=='e' && m_StringToCalc[point+1]=='-')
		|| (m_StringToCalc[point]=='-' && m_StringToCalc[point-1]=='e')
		|| (m_StringToCalc[point]=='e' && m_StringToCalc[point+1]=='+')
		|| (m_StringToCalc[point]=='+' && m_StringToCalc[point-1]=='e')){
		strnum[n++]=m_StringToCalc[point++];
		if(point>STRLEN-1) break;
	}
	strnum[n]='\0';
	return atof(strnum);//������Ӧ��ֵ
}

double CCalcStr::fact(int n)
{
	double r=1;
	if(n<=1) return 1;
	while(n>1){
		r*=n;
		--n;
	}
	return r;
}

int CCalcStr::getlevel(int opsign)
{
	switch(opsign){
	case ADD:
	case SUB:
		return ADDLEVEL;
	case MUL:
	case DIV:
		return MULLEVEL;
	case POW:
		return POWLEVEL;
	case FACT:
		return FACTLEVEL;
	case BRACKET:
		return BRACKETLEVEL;
	case ENDBRACKET:
		return ENDBRACKETLEVEL;
	case LN:
	case LG:
		return LOGLEVEL;
	case ABS:
		return ABSLEVEL;
	}
	if(opsign<=ABS && opsign >=SIN) return TRIGLEVEL;
	return NOOPSIGN;
}

int CCalcStr::getnextopsign()
{
	int p=point;
	int i;
	char opstr[10]={0};
	while(p<=STRLEN-1){
		switch(m_StringToCalc[p++]){
		case '+':
			return ADD;
		case '-':
			return SUB;
		case '*':
			return MUL;
		case '/':
			return DIV;
		case '(':
			return BRACKET;
		case '^':
			return POW;
		case '!':
			return FACT;
		case ')':
			return ENDBRACKET;
		}
		if(isalpha(m_StringToCalc[p-1])){//�Ƿ����Ѿ�����Ĳ�����
			i=0;
			while(isalpha(m_StringToCalc[p-1])){
				opstr[i++]=m_StringToCalc[p-1];
				p++;
				if(p>STRLEN) break;
			}
			return getfuncfromstr(opstr);
		}
	}
	return 0;
}

int CCalcStr::getcuropsign()
{
	int op=getnextopsign();
	if(op>=SIN && op<=COT) point+=3;
	else if(op>=ARCSIN && op<=ARCCOT) point+=6;
	else if(op==LN || op==LG) point+=2;
	else if(op==ABS) point+=3;
	else point++;
	return op;
}

int CCalcStr::getfuncfromstr(char *opstr)
{
	if(!strcmp(opstr,"sin")) return SIN;
	else if(!strcmp(opstr,"cos")) return COS;
	else if(!strcmp(opstr,"tan")) return TAN;
	else if(!strcmp(opstr,"cot")) return COT;
	else if(!strcmp(opstr,"arcsin")) return ARCSIN;
	else if(!strcmp(opstr,"arccos")) return ARCCOS;
	else if(!strcmp(opstr,"arctan")) return ARCTAN;
	else if(!strcmp(opstr,"arccot")) return ARCCOT;
	else if(!strcmp(opstr,"abs")) return ABS;
	else if(!strcmp(opstr,"lg")) return LG;
	else if(!strcmp(opstr,"ln")) return LN;
	return -1;
}

void CCalcStr::calc(int opsign)
{
	int oplevel=getlevel(opsign);
	if(GETNEXTLEVEL()>oplevel){
		push(opsign);
		m_Result=getnumber();
	}
	else
	{
		switch(opsign){
		case ADD:
			m_Result+=getnumber();break;
		case SUB:
			m_Result-=getnumber();break;
		case MUL:
			m_Result*=getnumber();break;
		case DIV:
			m_Result/=getnumber();break;
		case SIN:
			m_Result=sin(getnumber());break;
		case COS:
			m_Result=cos(getnumber());break;
		case TAN:
			m_Result=tan(getnumber());break;
		case COT:
			m_Result=1/tan(getnumber());break;
		case ARCSIN:
			m_Result=asin(getnumber());break;
		case ARCCOS:
			m_Result=acos(getnumber());break;
		case ARCTAN:
			m_Result=atan(getnumber());break;
		case ARCCOT:
			m_Result=atan(1/getnumber());break;
		case LN:
			m_Result=log(getnumber());break;
		case LG:
			m_Result=log10(getnumber());break;
		case ABS:
			m_Result=fabs(getnumber());break;
		case POW:
			m_Result=pow(m_Result,getnumber());break;
		case FACT:
			m_Result=fact((long)m_Result);break;
		}
		popall();
		//������ջ�п��Լ�������
	}
}

void CCalcStr::popall()
{
	while(stacknum>0 //�ж�ջ
		&& GETNEXTLEVEL()<=getlevel(getstack(stacknum)->opsign)
		//�������ȼ�����
		&& getstack(stacknum)->bracket==bracket)//����Ƕ�ײ�����
		pop();
}

void CCalcStr::push(int opsign)
{
	stack *p=getstack(stacknum);//ջ��
	if(stacknum>0) p=(p->pnext=new stack);//������ջ
	p->bracket=bracket;//����Ƕ�׼���
	p->pnext=NULL;
	if(m_StringToCalc[point]=='('){
		bracket++;
		point++;
	}
	p->num=m_Result;//������
	p->opsign=opsign;//�������
	stacknum++;
}

void CCalcStr::pop()
{
	stack *p=getstack(stacknum);
	switch(p->opsign){//�����������
	case ADD:
		m_Result+=p->num;
		break;
	case SUB:
		m_Result=p->num-m_Result;
		break;
	case MUL:
		m_Result*=p->num;
		break;
	case DIV:
		m_Result=p->num/m_Result;
		break;
	case POW:
		m_Result=pow(p->num,m_Result);
		break;
	case FACT:
		m_Result=fact((long)m_Result);
		break;
	case SIN:
		m_Result=sin(m_Result);
		break;
	case COS:
		m_Result=cos(m_Result);
		break;
	case TAN:
		m_Result=tan(m_Result);
		break;
	case COT:
		m_Result=1/tan(m_Result);
		break;
	case ARCSIN:
		m_Result=asin(m_Result);
		break;
	case ARCCOS:
		m_Result=acos(m_Result);
		break;
	case ARCTAN:
		m_Result=atan(m_Result);
		break;
	case ARCCOT:
		m_Result=atan(1/m_Result);
		break;
	case LN:
		m_Result=log(m_Result);
		break;
	case LG:
		m_Result=log10(m_Result);
		break;
	case ABS:
		m_Result=fabs(m_Result);
		break;
	case 0:
		break;
	}
	if(stacknum>1) delete p;
	stacknum--;
}

bool CCalcStr::check()
{
	int optestl=0,optestr=0;
	int left=0,right=0;
	char opstr[256]={0};
	int j=0;

	for(int i=0;i<STRLEN;i++){
		optestl=0;
		optestr=0;
		if(m_StringToCalc[i]<='9' && m_StringToCalc[i]>='0')
			//����
			continue;
		if(m_StringToCalc[i]<='z' && m_StringToCalc[i]>='a'){
			//�ַ������ж��Ƿ��ǺϷ�������
			j=0;
			while(isalpha(m_StringToCalc[i])){//����������opstr
				opstr[j++]=m_StringToCalc[i++];
				if(i>=STRLEN) break;
			}
			opstr[j]='\0';
			i--;
			if(opstr[0]=='e' && opstr[1]=='\0'
				&& (m_StringToCalc[i+1]=='-'
				|| m_StringToCalc[i+1]=='+'))
				//��ѧ��������ʾ������
				continue;
			if(getfuncfromstr(opstr)!=-1)
			{
				if((m_StringToCalc[i+1]=='+')||(m_StringToCalc[i+1]=='-')||(m_StringToCalc[i+1]=='*')||
					(m_StringToCalc[i+1]=='/')||(m_StringToCalc[i+1]=='^')||(m_StringToCalc[i+1]=='!')||(m_StringToCalc[i+1]=='\0'))
				{
					m_ErrorCode=E_FUNCTION;
					return 0;
				}
				else
					continue;
			}
			else{//�Ƿ�����
				m_ErrorCode=E_INVALID;
				return 0;
			}
		}
		if((m_StringToCalc[i]=='/' || m_StringToCalc[i]=='*' )&&( m_StringToCalc[i+1]=='/'|| m_StringToCalc[i+1]=='*'))
		{
			m_ErrorCode=E_INVALID;
			return 0;
		}
		if(m_StringToCalc[i]=='^'||m_StringToCalc[i]=='+'||m_StringToCalc[i]=='-'||m_StringToCalc[i]=='*'||m_StringToCalc[i]=='/')
			optestl=1;
		if(m_StringToCalc[i+1]=='^'||m_StringToCalc[i+1]=='!'||m_StringToCalc[i+1]=='+'||m_StringToCalc[i+1]=='-'||m_StringToCalc[i+1]=='*'||m_StringToCalc[i+1]=='/')
			optestr=1;
		if(optestl==1 && optestr==1)
		{
			m_ErrorCode=E_DUPLICATE;
			return 0;
		}
		if((m_StringToCalc[i]=='(')&& m_StringToCalc[i+1]==')')
		{
			m_ErrorCode=E_BRACKET;
			return 0;
		}

		switch(m_StringToCalc[i]){//�����
		case '(':
			++right;
			break;
		case ')':
			++left;
			break;
		case '^':
		case '!':
		case '+':
		case '-':
		case '*':
		case '/':
		case '.':
			break;
		case 'e':
			if(m_StringToCalc[i+1]=='-'
				|| m_StringToCalc[i+1]=='-')
			break;
		default:
			m_ErrorCode=E_INVALID;
			return 0;
		}
		if(right<left)
		{
			m_ErrorCode=E_BRACKET;
			return 0;
		}
	}
	if(right!=left){//���Ų�ƥ��
		m_ErrorCode=E_BRACKET;
		return 0;
	}
	return TRUE;
}


stack * CCalcStr::getstack(int n)
{
	stack *p=NULL;
	if(n==0) return &firststack;
	for(int i=0;i<n;i++){
		if(i==0) p=&firststack;
		else p=p->pnext;
	}
	return p;
}

WORD CCalcStr::GetError()
{
	return m_ErrorCode;
}

double CCalcStr::CalcStr(const char *pstr)
{
	//������ʽ����λ������ �� ����,��ֱ�Ӵ������,��������λ��������,Ȼ���ٴ������
	if(pstr[0]=='-'||pstr[0]=='+')
		return maincalc(pstr);
	STRLEN=(int)strlen(pstr);
	char* lpszStrToCalc=new char[STRLEN+2];

	lpszStrToCalc[0]='+';
	for(int i=1;i<=STRLEN+1;i++)
	{
		lpszStrToCalc[i]=pstr[i-1];
	}
	return maincalc(lpszStrToCalc);
}
