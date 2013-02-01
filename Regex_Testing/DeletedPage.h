#pragma once


// DeletedPage dialog

class CDeletedPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CDeletedPage)

public:
	CDeletedPage();
	virtual ~CDeletedPage();

// Dialog Data
	enum { IDD = IDD_DELETEDPAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
