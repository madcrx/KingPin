#if !defined(AFX_DLGDRUGS_H__A3905C71_D51A_11D4_946E_444553540001__INCLUDED_)
#define AFX_DLGDRUGS_H__A3905C71_D51A_11D4_946E_444553540001__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DlgDrugs.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgDrugs dialog

class CDlgDrugs : public CDialog
{
// Construction
public:
	CDlgDrugs(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgDrugs)
	enum { IDD = IDD_DIALOG_DRUGS };
	CListCtrl	m_ListSellCtrl;
	CListCtrl	m_ListBuyCtrl;
	CString	m_Coat;
	CString	m_Money;
	//}}AFX_DATA

  void FillLists ();
  void FillStrings ();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDrugs)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgDrugs)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonBuy();
	afx_msg void OnButtonDump();
	afx_msg void OnButtonSell();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

  afx_msg void OnCustomDrawBuyList ( NMHDR* pNMHDR, LRESULT* pResult );
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDRUGS_H__A3905C71_D51A_11D4_946E_444553540001__INCLUDED_)
