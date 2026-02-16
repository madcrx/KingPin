#if !defined(AFX_DLGSELLING_H__B870A91F_0DCD_4A92_A049_708BCD10F18C__INCLUDED_)
#define AFX_DLGSELLING_H__B870A91F_0DCD_4A92_A049_708BCD10F18C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DlgSelling.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSelling dialog

class CDlgSelling : public CDialog
{
// Construction
public:
	CDlgSelling(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSelling)
	enum { IDD = IDD_DIALOG_SELLING };
	CSliderCtrl	m_AmountCtrl;
	CString	m_Fact1;
	CString	m_Profit;
	int		m_nNum;
	CString	m_Worth;
	//}}AFX_DATA

  int m_nMin;
  int m_nMax;
  int m_nCurPrice;
  int m_nBoughtPrice;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSelling)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSelling)
	afx_msg void OnButtonMax();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEditNum();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSELLING_H__B870A91F_0DCD_4A92_A049_708BCD10F18C__INCLUDED_)
