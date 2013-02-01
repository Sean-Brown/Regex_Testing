#pragma once
#include "afxeditbrowsectrl.h"
#include "Regex_Testing_Library.h"

class COptions;

// OptionsPage dialog

class COptionsPage : public CPropertyPage
{
	DECLARE_DYNAMIC(COptionsPage)

public:
	COptionsPage(CRegex_Testing_Library* p_RTLib = NULL);
	virtual ~COptionsPage();

// Dialog Data
	enum { IDD = IDD_OPTIONSPAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_strLibDir; // The path to the music library
	BOOL m_bKeepWhole; // Specifies whether or not to keep albums whole (only delete duplicates within an album)
	BOOL m_bRemoveLive; // Specifies whether or not to delete a "live" version of a song when it has a duplicate
	BOOL m_bPermDel; // Specifies whether or not to permanently delete a song (if unchecked, store deleted songs)
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedFindDups();
private:
	CRegex_Testing_Library* m_pRTLib;
	COptions* m_pOptions;
};
