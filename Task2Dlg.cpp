
// Task2Dlg.cpp : ���� ����������
//

#include "stdafx.h"
#include "Task2.h"
#include "Task2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���������� ���� CTask2Dlg



CTask2Dlg::CTask2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTask2Dlg::IDD, pParent)
	, mypath(_T(""))
	, liststartexe(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTask2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, mypath);
	DDX_Control(pDX, IDC_LIST1, exelist);
	DDX_Control(pDX, IDC_LIST2, processlist);
	DDX_LBString(pDX, IDC_LIST2, liststartexe);
}

BEGIN_MESSAGE_MAP(CTask2Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_LBN_SELCHANGE(IDC_LIST1, &CTask2Dlg::OnLbnSelchangeList1)
	ON_EN_CHANGE(IDC_EDIT1, &CTask2Dlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTask2Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTask2Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON1, &CTask2Dlg::OnBnClickedButton1)
	ON_LBN_SELCHANGE(IDC_LIST2, &CTask2Dlg::OnLbnSelchangeList2)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// ����������� ��������� CTask2Dlg

BOOL CTask2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ������ ������ ��� ����� ����������� ����.  ����� ������ ��� �������������,
	//  ���� ������� ���� ���������� �� �������� ����������
	SetIcon(m_hIcon, TRUE);			// ������� ������
	SetIcon(m_hIcon, FALSE);		// ������ ������

	mypath = L"C:\\Windows\\System32";
	UpdateData(FALSE);

	// TODO: �������� �������������� �������������
	SetTimer(1, 500, NULL); // ����� �������, ������ � ��. ��� � 500�� ����� ������ (���������� �-� OnTimer)

	return TRUE;  // ������� �������� TRUE, ���� ����� �� ������� �������� ����������
}

// ��� ���������� ������ ����������� � ���������� ���� ����� ��������������� ����������� ���� �����,
//  ����� ���������� ������.  ��� ���������� MFC, ������������ ������ ���������� ��� �������������,
//  ��� ������������� ����������� ������� ��������.

void CTask2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �������� ���������� ��� ���������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ������������ ������ �� ������ ����������� ��������������
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ��������� ������
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ������� �������� ��� ������� ��� ��������� ����������� ������� ��� �����������
//  ���������� ����.
HCURSOR CTask2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





void CTask2Dlg::OnLbnSelchangeList1()
{

	UpdateData(TRUE);

}


void CTask2Dlg::OnEnChangeEdit1()
{

	UpdateData(TRUE);

}


void CTask2Dlg::OnBnClickedButton1()
{
	UpdateData(TRUE);
	exelist.ResetContent();
	CFileFind finder;
	BOOL bWorking = finder.FindFile(mypath + ("\\*.exe"));
	while (bWorking){
		bWorking = finder.FindNextFile();
		exelist.AddString((LPCTSTR)finder.GetFileName());
	}
}



void CTask2Dlg::OnBnClickedButton2()
{
	/*
	BOOL bSelect = TRUE;
	int j = exelist.GetCurSel();
	HANDLE s;
	for (int i = 0; i < processlist.GetCount(); i++){
		processlist.AddString(exe);
		processlist.SetItemData(i, i);
	}
	*/
	int index_cur = exelist.GetCurSel(); // ������ �����������
	CString name_cur;
	exelist.GetText(index_cur, name_cur);

	// processlist.AddString(name_cur);



	// CString text = SetSel(i, bSelect);
	// if (bSelect){
	// 	  void f = exelist.GetText(i);
	// }
	STARTUPINFO si; // ��������� ��� �������� ������ ��������
	PROCESS_INFORMATION pi; // ����

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	CreateProcess(mypath + L"\\" + name_cur, NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi);

	int index_new_item;
	index_new_item = processlist.AddString(name_cur); // ��������� � ���������� ������
	processlist.SetItemData(index_new_item, (int)pi.hProcess); // ����������� � ������� ��������� ��������
	CloseHandle(pi.hThread); // ����������� �����
}


void CTask2Dlg::OnBnClickedButton3()
{
	UpdateData(true);

	int iSelect = processlist.GetCurSel();
	if (iSelect != LB_ERR){
		TerminateProcess((HANDLE)processlist.GetItemData(iSelect), NULL); // ��������� ������� (***)
		//processlist.DeleteString(iSelect); // �������
	}

	UpdateData(false);

}


void CTask2Dlg::OnLbnSelchangeList2()
{
	// TODO: �������� ���� ��� ����������� �����������
}



void CTask2Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �������� ���� ��� ����������� ��������� ��� ����� ������������
	DWORD dwStopCode = 0; // ������� ��� �� �������
	for (int i = 0; i < processlist.GetCount(); i++)
	{
		GetExitCodeProcess((HANDLE)processlist.GetItemData(i), &dwStopCode); // (***) - ��������� ��������, ������ ���� ������� ��� ���������� ��������  
		if (dwStopCode != STILL_ACTIVE) // STILL_ACTIVE - �� ��� �������� 
		{
			CloseHandle((HANDLE)processlist.GetItemData(i));
			processlist.DeleteString(i);
		}
	}

	CDialogEx::OnTimer(nIDEvent);
}