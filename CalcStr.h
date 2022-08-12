// CalcStr.h: interface for the CCalcStr class.
//
//////////////////////////////////////////////////////////////////////



typedef struct stack
{
	double num;//数字
	char opsign;//运算符
	int bracket;//所处括号层
	struct stack * pnext;//链表
}stack;

#define GETNEXTLEVEL() getlevel(getnextopsign())

//错误码
#define E_INVALID 1
#define E_ZERODIV 2
#define E_BRACKET 3
#define E_DUPLICATE 4
#define E_FUNCTION 5
//常量
#define E 2.718281828
#define PI 3.141592654

class CCalcStr  
{
public:
	double CalcStr(const char *pstr);
	WORD GetError();//检查错误代码
	double CalcStr(const char * pstr,char * variable,double value);
	CCalcStr();
	virtual ~CCalcStr();

protected:
	int STRLEN;//字符串长度
	WORD m_ErrorCode;//出错代码
	double m_Result;//最后结果
	char * m_StringToCalc;//要计算的表达式（已经替换好）
	int bracket;//当前嵌套深度
	int stacknum;//堆栈数目
	int point;//表达式处理指针
	stack firststack;//动态链表首

	stack * getstack(int n);//得到某堆栈指针
	bool check();//检查表达式是否合法
	void pop();//从堆栈弹出
	void push(int opsign);//压入堆栈
	void popall();
	//将本操作开始以前push的并且现在（本操作以后）可以pop的操作都pop
	void calc(int opsign);//根据操作符及算式中优先级计算
	int getfuncfromstr(char * opstr);//根据字符串返回相应函数的标识
	int getcuropsign();//得到当前运算符,并跳过之
	int getnextopsign();//得到下一个运算符,包括'('
	int getlevel(int opsign);;//得到运算符的优先级别
	double fact(int n);//阶乘
	double getnumber();//得到数字
	double maincalc(const char * str);//计算的主过程
	
};

//定义的运算符
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


//运算优先级别
#define ENDBRACKETLEVEL 0
#define NOOPSIGN 0
#define ADDLEVEL 1 
#define SUBLEVEL 1
#define MULLEVEL 2
#define DIVLEVEL 2
#define TRIGLEVEL 3 //三角函数
#define LOGLEVEL 3 //对数函数
#define ABSLEVEL 3
#define POWLEVEL 4
#define FACTLEVEL 5
#define BRACKETLEVEL 10


