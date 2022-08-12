// CalculatorDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CCalculatorDlg �Ի���
class CCalculatorDlg : public CDialog
{
// ����
public:
	CCalculatorDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CALCULATOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// ���ʽ�ַ���
	CString m_CalcStr;
	// ������
	double m_Result;
	CEdit m_ResultCtr;//�������ؼ�
	CEdit m_CalcStrCtr;//���ʽ�ַ����ؼ�
	int m_ResultForm;
	afx_msg void OnBnClickedCalculate();
	afx_msg void OnBnClickedChange();
	afx_msg void OnBnClickedClear();
	afx_msg void OnBnClickedBtnPi();
	afx_msg void OnBnClickedBtnE();
	afx_msg void OnBnClickedBtn1();
	afx_msg void OnBnClickedBtn2();
	afx_msg void OnBnClickedBtn3();
	afx_msg void OnBnClickedBtn4();
	afx_msg void OnBnClickedBtn5();
	afx_msg void OnBnClickedBtn6();
	afx_msg void OnBnClickedBtn7();
	afx_msg void OnBnClickedBtn8();
	afx_msg void OnBnClickedBtn9();
	afx_msg void OnBnClickedBtn0();
	afx_msg void OnBnClickedBtnPoint();
	afx_msg void OnBnClickedBtnPower();
	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnBnClickedBtnMinus();
	afx_msg void OnBnClickedBtnMultiply();
	afx_msg void OnBnClickedBtnDivide();
	afx_msg void OnBnClickedBtnSin();
	afx_msg void OnBnClickedBtnCosine();
	afx_msg void OnBnClickedBtnTan();
	afx_msg void OnBnClickedBtnLbracket();
	afx_msg void OnBnClickedBtnRbracket();
	afx_msg void OnBnClickedBtnAbs();
	afx_msg void OnBnClickedBtnLg();
	afx_msg void OnBnClickedBtnLn();
	afx_msg void OnBnClickedBtnFactor();
	afx_msg void OnBnClickedBtnPlusorminus();
	afx_msg void OnBnClickedBtnBackspace();
	// �Ƿ����л���ť
	int m_IsShift;
	afx_msg void OnBnClickedBtnShift();
	CButton m_Sine;
	CButton m_Cosine;
	CButton m_Tan;
	afx_msg void OnBnClickedBtnUndo();
};
