#if !defined(AFX_DLGJET_H__D21AEB3B_9FA9_4E9E_A2A8_467F1A6CE63D__INCLUDED_)
#define AFX_DLGJET_H__D21AEB3B_9FA9_4E9E_A2A8_467F1A6CE63D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DlgJet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgJet dialog

class CDlgJet : public CDialog
{
// Construction
public:
	CDlgJet(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgJet)
	enum { IDD = IDD_DIALOG_JET };
	CListBox	m_ListCtrl;
	CString	m_Place;
	//}}AFX_DATA

  int m_nLocation;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgJet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgJet)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGJET_H__D21AEB3B_9FA9_4E9E_A2A8_467F1A6CE63D__INCLUDED_)
