#pragma once


// iTunesPage dialog

class CiTunesPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CiTunesPage)

public:
	CiTunesPage();
	virtual ~CiTunesPage();

// Dialog Data
	enum { IDD = IDD_ITUNESPAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
