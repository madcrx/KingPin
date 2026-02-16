#if !defined(AFX_PAGECONFIGCOPS_H__FFBE8A71_62B9_48A5_9A19_570C79FE18D1__INCLUDED_)
#define AFX_PAGECONFIGCOPS_H__FFBE8A71_62B9_48A5_9A19_570C79FE18D1__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PageConfigCops.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageConfigCops dialog

class CPageConfigCops : public CPropertyPage
{
	DECLARE_DYNCREATE(CPageConfigCops)

// Construction
public:
	CPageConfigCops();
	~CPageConfigCops();

// Dialog Data
	//{{AFX_DATA(CPageConfigCops)
	enum { IDD = IDD_PAGE_CONFIG_COPS };
	int		m_Damage;
	int		m_DeputyEscape;
	int		m_DeputyHit;
	int		m_Drop;
	int		m_Escape;
	int		m_Hit;
	int		m_Jail;
	int		m_Toughness;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageConfigCops)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageConfigCops)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGECONFIGCOPS_H__FFBE8A71_62B9_48A5_9A19_570C79FE18D1__INCLUDED_)
