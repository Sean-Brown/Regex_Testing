// OptionsPage.cpp : implementation file
//

#include "stdafx.h"
#include "Regex_Testing.h"
#include "OptionsPage.h"
#include "afxdialogex.h"

// OptionsPage dialog

IMPLEMENT_DYNAMIC(COptionsPage, CPropertyPage)

COptionsPage::COptionsPage(CRegex_Testing_Library* p_RTLib/*= NULL*/)
: CPropertyPage(COptionsPage::IDD)
, m_pRTLib(p_RTLib)
, m_pOptions(NULL)
, m_bKeepWhole(FALSE)
, m_bRemoveLive(FALSE)
, m_bPermDel(FALSE)
{
}

COptionsPage::~COptionsPage()
{
}

void COptionsPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_MUSIC_DIR, m_strLibDir);
	DDX_Check(pDX, IDC_WHOLE_ALBUMS, m_bKeepWhole);
	DDX_Check(pDX, IDC_REMOVE_LIVE, m_bRemoveLive);
	DDX_Check(pDX, IDC_PERM_DEL, m_bPermDel);
}


BEGIN_MESSAGE_MAP(COptionsPage, CPropertyPage)
	ON_BN_CLICKED(IDC_FIND_DUPS, &COptionsPage::OnBnClickedFindDups)
END_MESSAGE_MAP()

BOOL COptionsPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

// Begin finding the duplicates
void COptionsPage::OnBnClickedFindDups()
{
	// Make sure there's valid data
	if ( !UpdateData(TRUE) )
	{
		AfxMessageBox(_T("Please enter appropriate data"), MB_OK);
		return;
	}
	// Create the library path object
	boost::filesystem::path _LibPath(m_strLibDir.GetBuffer());
	// Delete any old options
	if ( m_pOptions != NULL )
	{
		delete m_pOptions;
		m_pOptions = NULL;
	}
	// Delete old libraries
	if ( m_pRTLib != NULL )
	{
		delete m_pRTLib;
		m_pRTLib = NULL;
	}
	// Create the options and library objects
	m_pOptions = new COptions(_LibPath, m_bKeepWhole, m_bRemoveLive, FALSE, FALSE, FALSE, NULL);
	m_pRTLib = new CRegex_Testing_Library(*m_pOptions);
	// Change the cursor to a wait cursors
	HCURSOR	hWaitCursor	= LoadCursor(NULL, IDC_WAIT);
	HCURSOR	hOldCursor = SetCursor(hWaitCursor);
	m_pRTLib->Begin();
	// Set the cursor back to normal
	SetCursor(hOldCursor);
}
