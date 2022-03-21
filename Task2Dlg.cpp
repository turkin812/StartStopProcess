
// Task2Dlg.cpp : файл реализации
//

#include "stdafx.h"
#include "Task2.h"
#include "Task2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// диалоговое окно CTask2Dlg



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


// обработчики сообщений CTask2Dlg

BOOL CTask2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	mypath = L"C:\\Windows\\System32";
	UpdateData(FALSE);

	// TODO: добавьте дополнительную инициализацию
	SetTimer(1, 500, NULL); // Номер таймера, Период в мс. Раз в 500мс будет пикать (вызываться ф-я OnTimer)

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CTask2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
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
	int index_cur = exelist.GetCurSel(); // Индекс выделенного
	CString name_cur;
	exelist.GetText(index_cur, name_cur);

	// processlist.AddString(name_cur);



	// CString text = SetSel(i, bSelect);
	// if (bSelect){
	// 	  void f = exelist.GetText(i);
	// }
	STARTUPINFO si; // Структура для создания нового процесса
	PROCESS_INFORMATION pi; // Тоже

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	CreateProcess(mypath + L"\\" + name_cur, NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi);

	int index_new_item;
	index_new_item = processlist.AddString(name_cur); // Добавляет и возвращает индекс
	processlist.SetItemData(index_new_item, (int)pi.hProcess); // Привязывает к индексу описатель процесса
	CloseHandle(pi.hThread); // Закрывается поток
}


void CTask2Dlg::OnBnClickedButton3()
{
	UpdateData(true);

	int iSelect = processlist.GetCurSel();
	if (iSelect != LB_ERR){
		TerminateProcess((HANDLE)processlist.GetItemData(iSelect), NULL); // Закрывает процесс (***)
		//processlist.DeleteString(iSelect); // Удаляет
	}

	UpdateData(false);

}


void CTask2Dlg::OnLbnSelchangeList2()
{
	// TODO: добавьте свой код обработчика уведомлений
}



void CTask2Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	DWORD dwStopCode = 0; // Запущен или не запущен
	for (int i = 0; i < processlist.GetCount(); i++)
	{
		GetExitCodeProcess((HANDLE)processlist.GetItemData(i), &dwStopCode); // (***) - описатель процесса, ссылка куда вернуть код завершения процесса  
		if (dwStopCode != STILL_ACTIVE) // STILL_ACTIVE - всё еще активный 
		{
			CloseHandle((HANDLE)processlist.GetItemData(i));
			processlist.DeleteString(i);
		}
	}

	CDialogEx::OnTimer(nIDEvent);
}