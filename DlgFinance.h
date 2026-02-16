#if !defined(AFX_DLGFINANCE_H__E41163DF_CEEB_41E8_A3CC_6324DDE2E40C__INCLUDED_)
#define AFX_DLGFINANCE_H__E41163DF_CEEB_41E8_A3CC_6324DDE2E40C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DlgFinance.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgFinance dialog

class CDlgFinance : public CDialog
{
// Construction
public:
	CDlgFinance(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgFinance)
	enum { IDD = IDD_DIALOG_FINANCE };
	CStatic	m_TotalCtrl;
	CStatic	m_DebtCtrl;
	CStatic	m_DayCtrl;
	CStatic	m_CashCtrl;
	CStatic	m_BankCtrl;
	CButton	m_WithdrawlCtrl;
	CButton	m_PaybackCtrl;
	CButton	m_DepositCtrl;
	CButton	m_BorrowCtrl;
	//}}AFX_DATA

  void LoadScreen ();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgFinance)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
  BOOL m_bLoanGiven;
protected:
  long m_Cash;
  long m_Bank;
  long m_Debt;
  long m_Total;

	// Generated message map functions
	//{{AFX_MSG(CDlgFinance)
	afx_msg void OnButtonDeposit();
	afx_msg void OnButtonWithdrawl();
	afx_msg void OnButtonBorrow();
	afx_msg void OnButtonPayback();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGFINANCE_H__E41163DF_CEEB_41E8_A3CC_6324DDE2E40C__INCLUDED_)
