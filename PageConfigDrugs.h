#if !defined(AFX_PAGECONFIGDRUGS_H__2258628A_4F85_4D10_AA0C_3771B56ED9E6__INCLUDED_)
#define AFX_PAGECONFIGDRUGS_H__2258628A_4F85_4D10_AA0C_3771B56ED9E6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PageConfigDrugs.h : header file
//

#include "defines.h"

/////////////////////////////////////////////////////////////////////////////
// CPageConfigDrugs dialog

class CPageConfigDrugs : public CPropertyPage
{
	DECLARE_DYNCREATE(CPageConfigDrugs)

// Construction
public:
	CPageConfigDrugs();
	~CPageConfigDrugs();

// Dialog Data
	//{{AFX_DATA(CPageConfigDrugs)
	enum { IDD = IDD_PAGE_CONFIG_DRUGS };
	CListBox	m_DrugNumList;
	BOOL	m_bCheap;
	BOOL	m_bExpensive;
	CString	m_CheapStr;
	int		m_nMax;
	int		m_nMin;
	CString	m_NameStr;
	//}}AFX_DATA

  drug_t m_DrugList [NUM_DRUGS];
  int m_nCurSelection;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageConfigDrugs)
	public:
	virtual BOOL OnKillActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageConfigDrugs)
	afx_msg void OnSelchangeListDrugNum();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGECONFIGDRUGS_H__2258628A_4F85_4D10_AA0C_3771B56ED9E6__INCLUDED_)
