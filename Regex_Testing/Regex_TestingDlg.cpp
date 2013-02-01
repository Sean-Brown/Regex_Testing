
// Regex_TestingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AboutDlg.h"
#include "Regex_Testing.h"
#include "Regex_TestingDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRegex_TestingDlg dialog

CRegex_TestingDlg::CRegex_TestingDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CRegex_TestingDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRegex_TestingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CRegex_TestingDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CRegex_TestingDlg message handlers

BOOL CRegex_TestingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	// Initialize the logger
	Init_Log_File();
	// Set the application PropertyPages
	SetAppPages();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CRegex_TestingDlg::SetAppPages(void)
{
	m_PropertySheet.AddPage(&m_OptionsPage);
	m_PropertySheet.AddPage(&m_DuplicatesPage);
	m_PropertySheet.AddPage(&m_DeletedPage);
	m_PropertySheet.AddPage(&m_iTunesPage);

	m_PropertySheet.Create(this,
						   WS_CHILD | WS_VISIBLE,
						   0);
	m_PropertySheet.ModifyStyle(0, WS_TABSTOP);
	m_PropertySheet.ModifyStyleEx(0, WS_EX_CONTROLPARENT);

	CRect propSheetRect;
	GetDlgItem(IDC_PROP_SHEET)->GetWindowRect(&propSheetRect);
	ScreenToClient(&propSheetRect);
	m_PropertySheet.SetWindowPos(NULL, 
								 propSheetRect.left - 7, // SetWindowPos adds 7, so subtract it off
								 propSheetRect.top - 7, // Again, SetWindowPos adds 7, so subtract it off
								 0,
								 0,
								 SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE);
}

void CRegex_TestingDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRegex_TestingDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CRegex_TestingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

