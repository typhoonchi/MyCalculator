// CalcStr.h: interface for the CCalcStr class.
//
//////////////////////////////////////////////////////////////////////



typedef struct stack
{
	double num;//����
	char opsign;//�����
	int bracket;//�������Ų�
	struct stack * pnext;//����
}stack;

#define GETNEXTLEVEL() getlevel(getnextopsign())

//������
#define E_INVALID 1
#define E_ZERODIV 2
#define E_BRACKET 3
#define E_DUPLICATE 4
#define E_FUNCTION 5
//����
#define E 2.718281828
#define PI 3.141592654

class CCalcStr  
{
public:
	double CalcStr(const char *pstr);
	WORD GetError();//���������
	double CalcStr(const char * pstr,char * variable,double value);
	CCalcStr();
	virtual ~CCalcStr();

protected:
	int STRLEN;//�ַ�������
	WORD m_ErrorCode;//�������
	double m_Result;//�����
	char * m_StringToCalc;//Ҫ����ı��ʽ���Ѿ��滻�ã�
	int bracket;//��ǰǶ�����
	int stacknum;//��ջ��Ŀ
	int point;//���ʽ����ָ��
	stack firststack;//��̬������

	stack * getstack(int n);//�õ�ĳ��ջָ��
	bool check();//�����ʽ�Ƿ�Ϸ�
	void pop();//�Ӷ�ջ����
	void push(int opsign);//ѹ���ջ
	void popall();
	//����������ʼ��ǰpush�Ĳ������ڣ��������Ժ󣩿���pop�Ĳ�����pop
	void calc(int opsign);//���ݲ���������ʽ�����ȼ�����
	int getfuncfromstr(char * opstr);//�����ַ���������Ӧ�����ı�ʶ
	int getcuropsign();//�õ���ǰ�����,������֮
	int getnextopsign();//�õ���һ�������,����'('
	int getlevel(int opsign);;//�õ�����������ȼ���
	double fact(int n);//�׳�
	double getnumber();//�õ�����
	double maincalc(const char * str);//�����������
	
};

//����������
#define ADD 1
#define SUB 2
#define MUL 3
#define DIV 4
#define POW 5
#define FACT 6
#define BRACKET 7
#define ENDBRACKET 8
#define SIN 9
#define COS 10
#define TAN 11
#define COT 12
#define ARCSIN 13
#define ARCCOS 14
#define ARCTAN 15
#define ARCCOT 16
#define LN 17
#define LG 18
#define ABS 19


//�������ȼ���
#define ENDBRACKETLEVEL 0
#define NOOPSIGN 0
#define ADDLEVEL 1 
#define SUBLEVEL 1
#define MULLEVEL 2
#define DIVLEVEL 2
#define TRIGLEVEL 3 //���Ǻ���
#define LOGLEVEL 3 //��������
#define ABSLEVEL 3
#define POWLEVEL 4
#define FACTLEVEL 5
#define BRACKETLEVEL 10


