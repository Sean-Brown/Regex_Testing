
// Regex_TestingDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include "afxdlgs.h"
#include "OptionsPage.h"
#include "DuplicatesPage.h"
#include "DeletedPage.h"
#include "iTunesPage.h"
#include "Logger.h"

// CRegex_TestingDlg dialog
class CRegex_TestingDlg : public CDialogEx
{
// Construction
public:
	CRegex_TestingDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_REGEX_TESTING_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	void SetAppPages(void);
private:
	// The property sheet which will hold of the the required pages. It will be embedded in the main dialog.
	CPropertySheet m_PropertySheet;
protected:
	// The first page on the property sheet, holding the general configuration properties.
	COptionsPage m_OptionsPage;
	// The second tab which will hold a list of all the duplicate songs that were found
	CDuplicatesPage m_DuplicatesPage;
	// The third tab which will show all of the songs the user has deleted
	CDeletedPage m_DeletedPage;
	// The fourth tab which will hold all of the user's songs
	CiTunesPage m_iTunesPage;
};
