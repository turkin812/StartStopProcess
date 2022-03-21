
// Task2Dlg.h : файл заголовка
//

#pragma once
#include "afxwin.h"


// диалоговое окно CTask2Dlg
class CTask2Dlg : public CDialogEx
{
// Создание
public:
	CTask2Dlg(CWnd* pParent = NULL);	// стандартный конструктор

// Данные диалогового окна
	enum { IDD = IDD_TASK2_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString mypath;
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnEnChangeEdit1();
	CListBox exelist;
	CListBox processlist;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnLbnSelchangeList2();
	CString liststartexe;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
