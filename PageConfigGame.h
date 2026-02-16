#if !defined(AFX_PAGECONFIGGAME_H__66187706_1919_497F_BFEB_35E938175840__INCLUDED_)
#define AFX_PAGECONFIGGAME_H__66187706_1919_497F_BFEB_35E938175840__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PageConfigGame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageConfigGame dialog

class CPageConfigGame : public CPropertyPage
{
	DECLARE_DYNCREATE(CPageConfigGame)

// Construction
public:
	CPageConfigGame();
	~CPageConfigGame();

// Dialog Data
	//{{AFX_DATA(CPageConfigGame)
	enum { IDD = IDD_PAGE_CONFIG_GAME };
	BOOL	m_bMessages;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageConfigGame)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageConfigGame)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGECONFIGGAME_H__66187706_1919_497F_BFEB_35E938175840__INCLUDED_)
