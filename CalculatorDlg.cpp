// CalculatorDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Calculator.h"
#include "CalculatorDlg.h"
#include "CalcStr.h"
#include "CalcFunc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//本实现文件内部函数声明
//TO ADD HERE:
//

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CCalculatorDlg 对话框



CCalculatorDlg::CCalculatorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCalculatorDlg::IDD, pParent)
	, m_CalcStr(_T(""))
	, m_Result(0)
	, m_ResultForm(0)
	, m_IsShift(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_ResultForm=0;
}

void CCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CALCSTR, m_CalcStr);
	DDV_MaxChars(pDX, m_CalcStr, 255);
	DDX_Text(pDX, IDC_RESULT, m_Result);
	DDX_Control(pDX, IDC_RESULT, m_ResultCtr);
	DDX_Control(pDX, IDC_CALCSTR, m_CalcStrCtr);
	DDX_Control(pDX, IDC_BTN_SIN, m_Sine);
	DDX_Control(pDX, IDC_BTN_COSINE, m_Cosine);
	DDX_Control(pDX, IDC_BTN_TAN, m_Tan);
}

BEGIN_MESSAGE_MAP(CCalculatorDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_CALCULATE, OnBnClickedCalculate)
	
	ON_BN_CLICKED(IDC_CHANGE, OnBnClickedChange)
	ON_BN_CLICKED(IDC_CLEAR, OnBnClickedClear)
	ON_BN_CLICKED(IDC_BTN_PI, OnBnClickedBtnPi)
	ON_BN_CLICKED(IDC_BTN_E, OnBnClickedBtnE)
	ON_BN_CLICKED(IDC_BTN_1, OnBnClickedBtn1)
	ON_BN_CLICKED(IDC_BTN_2, OnBnClickedBtn2)
	ON_BN_CLICKED(IDC_BTN_3, OnBnClickedBtn3)
	ON_BN_CLICKED(IDC_BTN_4, OnBnClickedBtn4)
	ON_BN_CLICKED(IDC_BTN_5, OnBnClickedBtn5)
	ON_BN_CLICKED(IDC_BTN_6, OnBnClickedBtn6)
	ON_BN_CLICKED(IDC_BTN_7, OnBnClickedBtn7)
	ON_BN_CLICKED(IDC_BTN_8, OnBnClickedBtn8)
	ON_BN_CLICKED(IDC_BTN_9, OnBnClickedBtn9)
	ON_BN_CLICKED(IDC_BTN_0, OnBnClickedBtn0)
	ON_BN_CLICKED(IDC_BTN_POINT, OnBnClickedBtnPoint)
	ON_BN_CLICKED(IDC_BTN_POWER, OnBnClickedBtnPower)
	ON_BN_CLICKED(IDC_BTN_ADD, OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_MINUS, OnBnClickedBtnMinus)
	ON_BN_CLICKED(IDC_BTN_MULTIPLY, OnBnClickedBtnMultiply)
	ON_BN_CLICKED(IDC_BTN_DIVIDE, OnBnClickedBtnDivide)
	ON_BN_CLICKED(IDC_BTN_SIN, OnBnClickedBtnSin)
	ON_BN_CLICKED(IDC_BTN_COSINE, OnBnClickedBtnCosine)
	ON_BN_CLICKED(IDC_BTN_TAN, OnBnClickedBtnTan)
	ON_BN_CLICKED(IDC_BTN_LBRACKET, OnBnClickedBtnLbracket)
	ON_BN_CLICKED(IDC_BTN_RBRACKET, OnBnClickedBtnRbracket)
	ON_BN_CLICKED(IDC_BTN_ABS, OnBnClickedBtnAbs)
	ON_BN_CLICKED(IDC_BTN_LG, OnBnClickedBtnLg)
	ON_BN_CLICKED(IDC_BTN_LN, OnBnClickedBtnLn)
	ON_BN_CLICKED(IDC_BTN_FACTOR, OnBnClickedBtnFactor)
	ON_BN_CLICKED(IDC_BTN_PLUSORMINUS, OnBnClickedBtnPlusorminus)
	ON_BN_CLICKED(IDC_BTN_BACKSPACE, OnBnClickedBtnBackspace)
	ON_BN_CLICKED(IDC_BTN_SHIFT, OnBnClickedBtnShift)
	ON_BN_CLICKED(IDC_BTN_UNDO, OnBnClickedBtnUndo)
END_MESSAGE_MAP()


// CCalculatorDlg 消息处理程序

BOOL CCalculatorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将\“关于...\”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO：在此添加额外的初始化代码
	
	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
}

void CCalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCalculatorDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
HCURSOR CCalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCalculatorDlg::OnBnClickedCalculate()
{
	::MessageBeep(MB_ICONINFORMATION);

	m_CalcStrCtr.GetWindowText(m_CalcStr);
	if(m_CalcStr.IsEmpty())
	{
		m_CalcStrCtr.SetFocus();
		return;
	}
	int strlen=m_CalcStr.GetLength();
	m_CalcStrCtr.SetFocus();
	m_CalcStrCtr.SetSel(0,strlen);

	//对编辑框中输入的表达式进行初级语法检查和处理
	CString m_StrTemp;
	for(int i=0;i<strlen;)
	{
		if(m_CalcStr[i]==' ')
		{
			if(m_CalcStr[i+1]!=' '&&m_CalcStr[i-1]!=' ')
				m_StrTemp+='*';
			else
			{
				m_ResultCtr.SetWindowText("空格太多!");
				return;
			}
			i++;
			continue;
		}
		if(m_CalcStr[i]=='.'&& (i==0||(IsDigit(m_CalcStr[i+1])==-1)||IsDigit(m_CalcStr[i-1])==-1))
		{
			m_ResultCtr.SetWindowText("小数点用法有误!");
			return;
		}
		if(m_CalcStr[i]=='.')
		{
			int index=i+1;
			while(IsDigit(m_CalcStr[index])!=-1)
			{
				index++;
			}
			if(index<strlen && m_CalcStr[index]=='.')
			{
				m_ResultCtr.SetWindowText("小数点用法有误!");
				return;
			}
		}
		if((i<strlen-1) && (m_CalcStr[i]=='p') && (m_CalcStr[i+1]=='i'))
		{
			if(m_CalcStr[i+2]=='p'||m_CalcStr[i+2]=='e'||((i>0)&&(IsDigit(m_CalcStr[i-1])!=-1))||
				IsDigit(m_CalcStr[i+2])!=-1)
			{
				m_ResultCtr.SetWindowText("语法错误!");
				return;
			}
			i++;
			i++;
			m_StrTemp+="3.14159265358979";
			continue;
		}
		if(m_CalcStr[i]=='e'&& i==0)
		{
			if(m_CalcStr[i+1]=='p'||m_CalcStr[i+1]=='e')
			{
				m_ResultCtr.SetWindowText("语法错误!");
				return;
			}
			i++;
			m_StrTemp+="2.71828182845";
			continue;
		}

		if((m_CalcStr[i]=='e')&&((m_CalcStr[i-1]<'0'||m_CalcStr[i-1]>'9'||m_CalcStr[i-1]=='.')))
		{
			i++;
			m_StrTemp+="2.71828182845";
			continue;
		}
		m_StrTemp+=m_CalcStr[i];
		i++;
	}
	if(IsOperator(m_CalcStr[strlen-1])&&(m_CalcStr[strlen-1]!='!'))
	{
		m_ResultCtr.SetWindowText("操作符用法有误!");
		return;
	}
	m_CalcStr=m_StrTemp;
	//////////////////////////////////////////////////////////////
	char *m_StringToCalc=new char[m_CalcStr.GetLength()+1];
	strcpy(m_StringToCalc,m_CalcStr);
	CCalcStr CalcStrobj;
	m_Result=CalcStrobj.CalcStr(m_StringToCalc);
	if(CalcStrobj.GetError()==E_INVALID)
	{
		m_ResultCtr.SetWindowText("语法错误!");
		return;
	}
	if(CalcStrobj.GetError()==E_DUPLICATE)
	{
		m_ResultCtr.SetWindowText("操作符冗余!");
		return;
	}
	if(CalcStrobj.GetError()==E_ZERODIV)
	{
		m_ResultCtr.SetWindowText("除数为零!");
		return;
	}
	if(CalcStrobj.GetError()==E_BRACKET)
	{
		m_ResultCtr.SetWindowText("括号不匹配!");
		return;
	}
	if(CalcStrobj.GetError()==E_FUNCTION)
	{
		m_ResultCtr.SetWindowText("函数用法有误!");
		return;
	}
	CString lpszResult;
	if(((int)m_Result-m_Result)==0)
		lpszResult.Format("%d",(int)m_Result);
	else
		lpszResult.Format("%f",m_Result);
	m_ResultCtr.SetWindowText(lpszResult);
}


void CCalculatorDlg::OnBnClickedChange()
{
	// TODO: 在此添加控件通知处理程序代码
	CString lpszResult;
	if(m_ResultForm==0)
	{
		m_ResultForm=1;
		lpszResult.Format("%E",m_Result);
	}
	else
	{
		m_ResultForm=0;
		if(((int)m_Result-m_Result)==0)
			lpszResult.Format("%d",(int)m_Result);
		else
			lpszResult.Format("%f",m_Result);
	}
	m_ResultCtr.SetWindowText(lpszResult);
}

void CCalculatorDlg::OnBnClickedClear()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ResultCtr.SetWindowText("");
	m_CalcStrCtr.SetWindowText("");
	m_CalcStrCtr.SetFocus();

}

//本实现文件内部函数实现
//TO ADD HERE:
//
void CCalculatorDlg::OnBnClickedBtnPi()
{
	m_CalcStrCtr.ReplaceSel("pi");
	m_CalcStrCtr.GetWindowText(m_CalcStr);
	m_CalcStrCtr.SetFocus();

}

void CCalculatorDlg::OnBnClickedBtnE()
{
	m_CalcStrCtr.ReplaceSel("e");
	m_CalcStrCtr.GetWindowText(m_CalcStr);
	m_CalcStrCtr.SetFocus();
}

void CCalculatorDlg::OnBnClickedBtn1()
{
	m_CalcStrCtr.ReplaceSel("1");
	m_CalcStrCtr.GetWindowText(m_CalcStr);
	m_CalcStrCtr.SetFocus();
}

void CCalculatorDlg::OnBnClickedBtn2()
{
	m_CalcStrCtr.ReplaceSel("2");
	m_CalcStrCtr.GetWindowText(m_CalcStr);
	m_CalcStrCtr.SetFocus();
}

void CCalculatorDlg::OnBnClickedBtn3()
{
	m_CalcStrCtr.ReplaceSel("3");
	m_CalcStrCtr.GetWindowText(m_CalcStr);
	m_CalcStrCtr.SetFocus();
}

void CCalculatorDlg::OnBnClickedBtn4()
{
	m_CalcStrCtr.ReplaceSel("4");
	m_CalcStrCtr.GetWindowText(m_CalcStr);
	m_CalcStrCtr.SetFocus();
}

void CCalculatorDlg::OnBnClickedBtn5()
{
	m_CalcStrCtr.ReplaceSel("5");
	m_CalcStrCtr.GetWindowText(m_CalcStr);
	m_CalcStrCtr.SetFocus();
}

void CCalculatorDlg::OnBnClickedBtn6()
{
	m_CalcStrCtr.ReplaceSel("6");
	m_CalcStrCtr.GetWindowText(m_CalcStr);
	m_CalcStrCtr.SetFocus();
}

void CCalculatorDlg::OnBnClickedBtn7()
{
	m_CalcStrCtr.ReplaceSel("7");
	m_CalcStrCtr.GetWindowText(m_CalcStr);
	m_CalcStrCtr.SetFocus();
}

void CCalculatorDlg::OnBnClickedBtn8()
{
	m_CalcStrCtr.ReplaceSel("8");
	m_CalcStrCtr.GetWindowText(m_CalcStr);
	m_CalcStrCtr.SetFocus();
}

void CCalculatorDlg::OnBnClickedBtn9()
{
	m_CalcStrCtr.ReplaceSel("9");
	m_CalcStrCtr.GetWindowText(m_CalcStr);
	m_CalcStrCtr.SetFocus();
}

void CCalculatorDlg::OnBnClickedBtn0()
{
	m_CalcStrCtr.ReplaceSel("0");
	m_CalcStrCtr.GetWindowText(m_CalcStr);
	m_CalcStrCtr.SetFocus();
}

void CCalculatorDlg::OnBnClickedBtnPoint()
{
	m_CalcStrCtr.ReplaceSel(".");
	m_CalcStrCtr.GetWindowText(m_CalcStr);
	m_CalcStrCtr.SetFocus();
}

void CCalculatorDlg::OnBnClickedBtnPower()
{
	m_CalcStrCtr.ReplaceSel("^");
	m_CalcStrCtr.GetWindowText(m_CalcStr);
	m_CalcStrCtr.SetFocus();
}

void CCalculatorDlg::OnBnClickedBtnAdd()
{
	m_CalcStrCtr.ReplaceSel("+");
	m_CalcStrCtr.GetWindowText(m_CalcStr);
	m_CalcStrCtr.SetFocus();
}

void CCalculatorDlg::OnBnClickedBtnMinus()
{
	m_CalcStrCtr.ReplaceSel("-");
	m_CalcStrCtr.GetWindowText(m_CalcStr);
	m_CalcStrCtr.SetFocus();
}

void CCalculatorDlg::OnBnClickedBtnMultiply()
{
	m_CalcStrCtr.ReplaceSel("*");
	m_CalcStrCtr.GetWindowText(m_CalcStr);
	m_CalcStrCtr.SetFocus();
}

void CCalculatorDlg::OnBnClickedBtnDivide()
{
	m_CalcStrCtr.ReplaceSel("/");
	m_CalcStrCtr.GetWindowText(m_CalcStr);
	m_CalcStrCtr.SetFocus();
}

void CCalculatorDlg::OnBnClickedBtnSin()
{
	if(m_IsShift)
		m_CalcStrCtr.ReplaceSel("arcsin");
	else
		m_CalcStrCtr.ReplaceSel("sin");
	m_CalcStrCtr.GetWindowText(m_CalcStr);
	m_CalcStrCtr.SetFocus();
}

void CCalculatorDlg::OnBnClickedBtnCosine()
{
	if(m_IsShift)
		m_CalcStrCtr.ReplaceSel("arccos");
	else
		m_CalcStrCtr.ReplaceSel("cos");
	m_CalcStrCtr.GetWindowText(m_CalcStr);
	m_CalcStrCtr.SetFocus();
}

void CCalculatorDlg::OnBnClickedBtnTan()
{
	if(m_IsShift)
		m_CalcStrCtr.ReplaceSel("arctan");
	else
		m_CalcStrCtr.ReplaceSel("tan");
	m_CalcStrCtr.GetWindowText(m_CalcStr);
	m_CalcStrCtr.SetFocus();
}

void CCalculatorDlg::OnBnClickedBtnLbracket()
{
	m_CalcStrCtr.ReplaceSel("(");
	m_CalcStrCtr.GetWindowText(m_CalcStr);
	m_CalcStrCtr.SetFocus();
}

void CCalculatorDlg::OnBnClickedBtnRbracket()
{
	m_CalcStrCtr.ReplaceSel(")");
	m_CalcStrCtr.GetWindowText(m_CalcStr);
	m_CalcStrCtr.SetFocus();
}

void CCalculatorDlg::OnBnClickedBtnAbs()
{
	m_CalcStrCtr.ReplaceSel("abs");
	m_CalcStrCtr.GetWindowText(m_CalcStr);
	m_CalcStrCtr.SetFocus();
}

void CCalculatorDlg::OnBnClickedBtnLg()
{
	m_CalcStrCtr.ReplaceSel("lg");
	m_CalcStrCtr.GetWindowText(m_CalcStr);
	m_CalcStrCtr.SetFocus();
}

void CCalculatorDlg::OnBnClickedBtnLn()
{
	m_CalcStrCtr.ReplaceSel("ln");
	m_CalcStrCtr.GetWindowText(m_CalcStr);
	m_CalcStrCtr.SetFocus();
}

void CCalculatorDlg::OnBnClickedBtnFactor()
{
	m_CalcStrCtr.ReplaceSel("!");
	m_CalcStrCtr.GetWindowText(m_CalcStr);
	m_CalcStrCtr.SetFocus();
}

void CCalculatorDlg::OnBnClickedBtnPlusorminus()
{
	m_CalcStrCtr.GetWindowText(m_CalcStr);
	int strlen=m_CalcStr.GetLength();
	if(m_CalcStr.IsEmpty())
	{
		m_CalcStrCtr.SetFocus();
		m_CalcStrCtr.SetSel(0,0);
		return;
	}
	if(m_CalcStr[0]=='+')
	{
		m_CalcStrCtr.SetSel(0,1);
		m_CalcStrCtr.ReplaceSel("-");
		m_CalcStrCtr.SetFocus();
		m_CalcStrCtr.SetSel(strlen,strlen);
		return;
	}
	if(m_CalcStr[0]=='-')
	{
		m_CalcStrCtr.SetSel(0,1);
		m_CalcStrCtr.ReplaceSel("+");
		m_CalcStrCtr.SetFocus();
		m_CalcStrCtr.SetSel(strlen,strlen);
		return;
	}
	m_CalcStr='-'+m_CalcStr;
	m_CalcStrCtr.SetWindowText(m_CalcStr);
	m_CalcStrCtr.SetFocus();
	m_CalcStrCtr.SetSel(strlen+1,strlen+1);
}

void CCalculatorDlg::OnBnClickedBtnBackspace()
{
	int nCharStart,nCharEnd;
	m_CalcStrCtr.GetSel(nCharStart,nCharEnd);
	m_CalcStrCtr.SetSel(nCharStart,nCharEnd);
	m_CalcStrCtr.ReplaceSel("");
	if(nCharEnd==nCharStart)
	{
		m_CalcStrCtr.SetSel(nCharStart-1,nCharStart);
		m_CalcStrCtr.ReplaceSel("");	
	}
	m_CalcStrCtr.SetFocus();
}

void CCalculatorDlg::OnBnClickedBtnShift()
{
	if(m_IsShift==0)
	{
		m_Sine.SetWindowText("asin");
		m_Cosine.SetWindowText("acos");
		m_Tan.SetWindowText("atan");
		m_IsShift=1;
	}
	else
	{
		m_Sine.SetWindowText("sin");
		m_Cosine.SetWindowText("cos");
		m_Tan.SetWindowText("tan");
		m_IsShift=0;
	}
	m_CalcStrCtr.SetFocus();
}

void CCalculatorDlg::OnBnClickedBtnUndo()
{
	if(m_CalcStrCtr.CanUndo())
		m_CalcStrCtr.Undo();
	m_CalcStrCtr.SetFocus();
}
