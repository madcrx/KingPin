#if !defined(AFX_DLGGUNS_H__74711919_DDA1_4716_9FFB_2B231FBA0515__INCLUDED_)
#define AFX_DLGGUNS_H__74711919_DDA1_4716_9FFB_2B231FBA0515__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DlgGuns.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgGuns dialog

class CDlgGuns : public CDialog
{
// Construction
public:
	CDlgGuns(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgGuns)
	enum { IDD = IDD_DIALOG_GUNS };
	CButton	m_DumpCtrl;
	CButton	m_SellCtrl;
	CButton	m_BuyCtrl;
	CListCtrl	m_ListSellCtrl;
	CListCtrl	m_ListBuyCtrl;
	CString	m_Coat;
	CString	m_Money;
	//}}AFX_DATA

  void FillLists ();
  void FillStrings ();
  void EnableButtons ();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgGuns)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgGuns)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonBuy();
	afx_msg void OnButtonDump();
	afx_msg void OnButtonSell();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGGUNS_H__74711919_DDA1_4716_9FFB_2B231FBA0515__INCLUDED_)
