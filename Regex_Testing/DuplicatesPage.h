#pragma once


// DuplicatesPage dialog

class CDuplicatesPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CDuplicatesPage)

public:
	CDuplicatesPage();
	virtual ~CDuplicatesPage();

// Dialog Data
	enum { IDD = IDD_DUPLICATESPAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
