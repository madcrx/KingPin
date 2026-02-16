#if !defined(AFX_DLGQUANTITY_H__8F583064_36DE_43DE_B2E7_85406224FBCF__INCLUDED_)
#define AFX_DLGQUANTITY_H__8F583064_36DE_43DE_B2E7_85406224FBCF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DlgQuantity.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgQuantity dialog

class CDlgQuantity : public CDialog
{
// Construction
public:
	CDlgQuantity(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgQuantity)
	enum { IDD = IDD_DIALOG_QUANTITY };
	CSliderCtrl	m_AmountCtrl;
	int		m_nNum;
	CString	m_Question;
	CString	m_Fact1;
	//}}AFX_DATA

  int m_nMin;
  int m_nMax;

  CString m_Title;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgQuantity)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgQuantity)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonMax();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnChangeEditNum();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGQUANTITY_H__8F583064_36DE_43DE_B2E7_85406224FBCF__INCLUDED_)
